#include <SPI.h> //for the SD card module
#include <SD.h> // for the SD card
#include <dht.h> // for the DHT sensor
#include <RTClib.h> // for the RTC
#define DHT11_PIN 6
//#define DHTPIN 2     // what pin we're connected to

// uncomment whatever type you're using
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
// initialize DHT sensor for normal 16mhz Arduino
//DHT dht(DHTPIN, DHTTYPE);

dht DHT;
// change this to match your SD shield or module;
// Arduino Ethernet shield and modules: pin 4
// Data loggin SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int chipSelect = 4;

// Create a file to store the data
File myFile;

// RTC
RTC_DS1307 rtc;

void setup() {
  //initializing the DHT sensor
  //DHT.begin();
int chk = DHT.read11(DHT11_PIN);
  //initializing Serial monitor
  Serial.begin(9600);
  SPI.begin();
//  pinMode(TdsSensorPin, INPUT);
//  pinMode (LED, OUTPUT);
  //pinMode(10, OUTPUT);
  //digitalWrite(10, HIGH);
//  lcd.init();
//  lcd.backlight();
//  lcd.setCursor(4, 0);
//  lcd.print("WELCOME");
//  delay(1000);
  // setup for the RTC
  while (!Serial); // for Leonardo/Micro/Zero
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  else {
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }

  // setup for the SD card
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  //open file
  myFile = SD.open("DHT_Data.txt", FILE_WRITE);

  // if the file opened ok, write to it:
  if (myFile) {
    Serial.println("File opened ok");
    // print the headings for our data
    myFile.println("Date,Time,Temp(*C),Humidity");

    myFile.close();
  }
}

void loggingTime() {
  DateTime now = rtc.now();
  myFile = SD.open("DHT_Data.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(',');
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.print(",");
  }
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.println(now.day(), DEC);
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  myFile.close();
  delay(1000);
}
void loggingTemp() {
//  lcd.clear();
//  int chk = DHT.read11(DHT11_PIN);
//  lcd.setCursor(0, 0);
//  lcd.print("Temp: ");
//  lcd.print(DHT.temperature);
//  t = DHT.temperature;
//  lcd.setCursor(11, 0);
//  lcd.print((char)223);
//  lcd.setCursor(12, 0);
//  lcd.print("C");
  float h = DHT.humidity;
  // Read temperature as Celsius
  float t = DHT.temperature;
  // Read temperature as Fahrenheit
  //float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
//  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  //float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
//  Serial.print(f);
//  Serial.print(" *F\t");
//  Serial.print("Heat index: ");
//  Serial.print(hi);
//  Serial.println(" *F");

  delay(3000);

  //debugging temperature
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.println("°C");
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  myFile = SD.open("DHT_Data.txt", FILE_WRITE);
  if (myFile) {
    //Serial.println("open with success");
    myFile.print(t);
    myFile.print(",");
     myFile.print(h);
     myFile.println(",");
     
  }
  myFile.close();
}

void loop() {
  loggingTime();
  loggingTemp();
  delay(500);
}
