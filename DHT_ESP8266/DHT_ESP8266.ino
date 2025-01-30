#include <dht.h>
#define DHT11_PIN 4
dht DHT;


void setup(){

  Serial.begin(9600);
  pinMode(DHT11_PIN, INPUT);
  
}
void loop(){
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);
}
