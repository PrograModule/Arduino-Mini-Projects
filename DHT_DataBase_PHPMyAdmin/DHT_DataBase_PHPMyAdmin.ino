#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>
#include "DHTStable.h"

// Replace with your network credentials
const char* ssid     = "Cryptappz_Lab";
const char* password = "cryp98745";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://localhost/Public_HTML/post-esp-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key
String apiKeyValue = "tPmAT5Ab3j7F9";

String sensorName = "DHT11";
String sensorLocation = "Office";

/*#include <SPI.h>
  #define BME_SCK 18
  #define BME_MISO 19
  #define BME_MOSI 23
  #define BME_CS 5*/

//#define SEALEVELPRESSURE_HPA (1013.25)

DHTStable DHT;  // I2C
//Adafruit_BME280 bme(BME_CS);  // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);  // software SPI
#define DHT11_PIN 13
void setup() {
  Serial.begin(115200);
  pinMode(13, INPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // (you can also pass in a Wire library object like &Wire2)
  //  bool status = bme.begin(0x76);
  //  if (!status) {
  //    Serial.println("Could not find a valid BME280 sensor, check wiring or change I2C address!");
  //    while (1);
  //  }
  int chk = DHT.read11(DHT11_PIN);
}

void loop() {
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    // Ignore SSL certificate validation
    client->setInsecure();

    //create an HTTPClient instance
    HTTPClient https;

    // Your Domain name with URL path or IP address with path
    https.begin(*client, serverName);

    // Specify content-type header
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                             + "&location=" + sensorLocation + "&value1=" + String(DHT.getTemperature())
                             + "&value2=" + String(DHT.getHumidity()) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

    // Send HTTP POST request
    int httpResponseCode = https.POST(httpRequestData);

    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = https.POST("Hello, World!");

    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = https.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    https.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(30000);
}
