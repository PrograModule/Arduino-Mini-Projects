//#include <SoftwareSerial.h>
//SoftwareSerial Serial3(15,14);
 
#include <String.h>
#include <dht.h> 
 
#define DHT11_PIN 8
 
dht DHT;

 
void setup()
{
  Serial3.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  //dht.begin();
 
  delay(1000);
}
 
void loop()
{
//      float h = dht.readHumidity();
//      float t = dht.readTemperature(); 
      delay(100);   
         
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.println(" °C");
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.println(" %");   
  delay(2000); 
      
//      Serial.print("Humidity = ");
//      Serial.print(h);
      
      
   
  if (Serial3.available())
    Serial.write(Serial3.read());
 
  Serial3.println("AT");
  delay(1000);
 
  Serial3.println("AT+CPIN?");
  delay(1000);
 
  Serial3.println("AT+CREG?");
  delay(1000);
 
  Serial3.println("AT+CGATT?");
  delay(1000);
 
  Serial3.println("AT+CIPSHUT");
  delay(1000);
 
  Serial3.println("AT+CIPSTATUS");
  delay(2000);
 
  Serial3.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  Serial3.println("AT+SAPBR=3,1,\"APN\",\"www\"");//start task and setting the APN,
  //Serial3.println("AT+SAPBR=3,1,\"APN\",\"live.vodafone.com\"");
  delay(1000);
 
  ShowSerialData();
 
  Serial3.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  Serial3.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  Serial3.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  Serial3.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  Serial3.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=1NSLCXWZEZHAY8HV&field1=" + String(DHT.temperature) +"&field2="+String(DHT.humidity);
  Serial.println(str);
  Serial3.println(str);//begin send data to remote server
  
  delay(4000);
  ShowSerialData();
 
  Serial3.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  Serial3.println();
 
  ShowSerialData();
 
  Serial3.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 
void ShowSerialData()
{
  while(Serial3.available()!=0)
  Serial.write(Serial3.read());
  delay(5000); 
  
}
