#include <SPI.h> //for the SD card module
#include <SD.h> // for the SD card
#include <dht.h> // for the DHT sensor
#include <RTClib.h> // for the RTC
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "GravityTDS.h"
#define TdsSensorPin A0
int ADC_value;
unsigned long int avgval_ADC;
int buffer_tds[10], temp1;
float TDS = 0;
dht DHT;
float t;
float a[10], avg = 0.0, sum = 0.0;
int i, count = 0;

#define DHT11_PIN 6
#define LED 7
//define DHT pin
//#define DHTPIN 2     // what pin we're connected to

// uncomment whatever type you're using
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// initialize DHT sensor for normal 16mhz Arduino
//DHT dht(DHTPIN, DHTTYPE);

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
  //dht.begin();

  //initializing Serial monitor
  Serial.begin(9600);
  SPI.begin();
  pinMode(TdsSensorPin, INPUT);
  pinMode (LED, OUTPUT);
  //pinMode(10, OUTPUT);
  //digitalWrite(10, HIGH);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("WELCOME");
  delay(1000);
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
  myFile = SD.open("DATA.txt", FILE_WRITE);

  // if the file opened ok, write to it:
  if (myFile) {
    Serial.println("File opened ok");
    // print the headings for our data
    myFile.println("Date,Time,Temp (°C),TDS (PPM),Avg of TDS");

    myFile.close();
  }
}

void loggingTime() {
  DateTime now = rtc.now();
  myFile = SD.open("DATA.txt", FILE_WRITE);
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
  lcd.clear();
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  t = DHT.temperature;
  lcd.setCursor(11, 0);
  lcd.print((char)223);
  lcd.setCursor(12, 0);
  lcd.print("C");
  delay(3000);

  //debugging temperature
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.println("°C");
  myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    //Serial.println("open with success");
    myFile.print(t);
    myFile.println(",");
  }
  myFile.close();
}
void loggingTDS() {
  lcd.clear();
  for (int i = 0; i < 10; i++)
  {
    buffer_tds[i] = analogRead(TdsSensorPin);
    delay(30);
  }

  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_tds[i] > buffer_tds[j])
      {
        temp1 = buffer_tds[i];
        buffer_tds[i] = buffer_tds[j];
        buffer_tds[j] = temp1;
      }
    }
  }

  avgval_ADC = 0;
  for (int i = 2; i < 8; i++)
    avgval_ADC += buffer_tds[i];

  float voltage_value = (float)avgval_ADC * 5.0 / 1024.0 / 6;
  float TDS = (133.42 / voltage_value * voltage_value - 255.86 * voltage_value * voltage_value + 857.39 * voltage_value) * 0.5;
  lcd.setCursor(0, 0);
  lcd.print("TDS Value =");
  lcd.setCursor(0, 1);
  lcd.print(TDS);
  lcd.setCursor(7, 1);
  lcd.print("PPM");
  digitalWrite(LED,HIGH);
  a[i] = TDS;
  //      Serial.println("***********");
  //      Serial.print(TDS);
       sum=sum+TDS;
  //      Serial.println("**********");
  //      Serial.print(sum);

  //      Serial.print("Values of TDS: ");
  //      Serial.println(a[i]);

  if (TDS < 50)
  {
    lcd.setCursor(11, 1);
    lcd.print("LQ");  // LQ = Low Quality
  }
  if (TDS >= 50 && TDS <= 150)
  {
    lcd.setCursor(11, 1);
    lcd.print("Ideal");
  }
  if (TDS >= 150 && TDS <= 250)
  {
    lcd.setCursor(11, 1);
    lcd.print("Good");
  }
  if (TDS >= 250 && TDS <= 300)
  {
    lcd.setCursor(11, 1);
    lcd.print("Fair");
  }
  if (TDS >= 300 && TDS <= 500)
  {
    lcd.setCursor(11, 1);
    lcd.print("Poor");
  }
  if (TDS >= 1200)
  {
    lcd.setCursor(11, 1);
    lcd.print("Unsafe");
  }
  delay(1000);
  count++;
  Serial.print("count:");
  Serial.println(count);
   avg = sum / count;
  //debugging purposes

  Serial.print("TDS: ");
  Serial.print(TDS);
  Serial.println(" PPM");
  //Serial.print(f);
  //Serial.println(" *F\t");

  myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    Serial.println("open with success");
    myFile.print(TDS);
    myFile.print(",");
    myFile.print(avg);
    myFile.println(",");
  }
  myFile.close();

 
  if (count == 10)
  {
    lcd.clear();
    digitalWrite(LED,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Avg of TDS:");
    lcd.setCursor(0, 1);
    lcd.print(avg);
    lcd.setCursor(7, 1);
    lcd.print(avg);
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Remove Probe");
    lcd.setCursor(0, 1);
    lcd.print("Check TDS again");
    delay(30000);
  }
  if (count == 20)
  {
    lcd.clear();
    digitalWrite(LED,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Avg of TDS:");
    lcd.setCursor(0, 1);
    lcd.print(avg);
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Insert another");
    lcd.setCursor(0, 1);
    lcd.print("sensor");
    delay(3000);
    count = 0;
    avg = 0;
    sum = 0;
  }
  Serial.print("Avg of TDS: ");
  Serial.println(avg);
}
void loop() {
  loggingTime();
  loggingTemp();
  loggingTDS();
  delay(500);
}
