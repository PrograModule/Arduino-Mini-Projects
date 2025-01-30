#include <dht.h>
 int temp;
 int hum;
dht DHT;

#define DHT11_PIN 7

String mystring1;
String mystring2;
String totalstring;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int chk = DHT.read11(DHT11_PIN);
  
  temp= DHT.temperature;
 
  hum= DHT.humidity;
  
  mystring1=String(temp);
  mystring2=String(hum);
  totalstring="Temperature: " +mystring1 +" Humidity: " +mystring2;
  
  Serial.println("Converted Strings");
  Serial.print("Temperature = ");
  Serial.println(mystring1);
   Serial.print("Humidity = ");
  Serial.println(mystring2);
  Serial.println(totalstring);
  delay(2000);
}
