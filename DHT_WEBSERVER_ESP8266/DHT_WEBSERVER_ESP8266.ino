#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "Cryptappz_Lab";
const char* password = "cryp98745";

const long utcOffsetInSeconds = 3600;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


#define DHTPIN D6     // Digital pin connected to the DHT sensor

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

// current temperature & humidity, updated in loop()
float t = 0.0;
float h = 0.0;
String Day=daysOfTheWeek[timeClient.getDay()];
int H= timeClient.getHours();

String mystr=String(H);
int M=timeClient.getMinutes();

String mystr1=String(M);
int S=timeClient.getSeconds();

String mystr2=String(S);
String Time=mystr+":"+mystr1+":"+mystr2;
//String Time=timeClient.getFormattedTime();
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;    // will store last time DHT was updated

// Updates DHT readings every 10 seconds
const long interval = 10000;  

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }.dateTime-labels{font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;}
  </style>
</head>
<body>
  <h2>ESP8266 DHT Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    
    <span id="temperature" style="color:red;">%Temperature%</span> 
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    
    <span id="humidity" style="color:yellow;">%Humidity%</span>
    <sup class="units">&percnt;</sup>
  </p>
  <p>
    <i class="fa fa-calendar" style="font-size:24px;color:red"></i> 
    <span class="dateTime-labels">Day</span>
    
    <span id="Day" style="color:yellow;">%Day%</span>
    <sup class="units"></sup>
  </p>
  <p>
  <i class="fa fa-calendar" style="font-size:24px;color:red"></i> 
    <span class="dateTime-labels">Time</span>
    
    <span id="Time" style="color:yellow;">%Time%</span>
    <sup class="units"></sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("Day").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/Day", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("Time").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/Time", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(t);
  }
  else if(var == "HUMIDITY"){
    return String(h);
  }
  else if(var=="DAY")
  {
    return String(Day);
  }
  else if(var=="TIME")
  {
    return String(Time);
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  dht.begin();
  timeClient.begin();
  timeClient.update();
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(10000);
    Serial.println(".");
  }

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(h).c_str());
  });
  server.on("/Day", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(Day).c_str());
  });
  server.on("/Time", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(Time).c_str());
  });
    
  // Start server
  server.begin();
}
 
void loop(){  

  timeClient.update();

String Day=daysOfTheWeek[timeClient.getDay()];
//String mystr;
//String mystr1;
//String mystr2;
int H= timeClient.getHours();

String mystr=String(H);
int M=timeClient.getMinutes();

String mystr1=String(M);
int S=timeClient.getSeconds();

String mystr2=String(S);
String Time=mystr+":"+mystr1+":"+mystr2;
//String Time=timeClient.getFormattedTime();
  Serial.print(Day);
  Serial.print(", ");
  Serial.print(Time);
  Serial.print(":");
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;
    // Read temperature as Celsius (the default)
    float newT = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    //float newT = dht.readTemperature(true);
    // if temperature read failed, don't change t value
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      t = newT;
      Serial.println(t);
    }
    // Read Humidity
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value 
    if (isnan(newH)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      h = newH;
      Serial.println(h);
    }
  }
  delay(1000);
}
