#include <SoftwareSerial.h> //software serial library for serial communication b/w arduino & GSM

SoftwareSerial mySerial(10, 11);//connect Tx pin of GSM to pin 8 of arduino && Rx pin of GSM to pin no 9 of arduino

int led = 7;
String message;


void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);

  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}

void loop()
{
  if (mySerial.available()>0){
  message = mySerial.readString();
  }

  if(message.indexOf("ON") > -1){
      Serial.println("LED ON");
     digitalWrite(led,HIGH);
     }
    else if(message.indexOf("OFF") > -1){

      Serial.println("LED OFF");
      digitalWrite(led,LOW);

  }

  delay(100);
}
