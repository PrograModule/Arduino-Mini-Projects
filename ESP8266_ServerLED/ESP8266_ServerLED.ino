#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ESP_D54736";  // SSID of esp8266
const char* password = "123";

#define led 2
int val = 0 ;
bool toggle = 0;
ESP8266WebServer server(80);

void handleRoot() {
  toggle = !toggle;             //Toggling Led Variable
  digitalWrite(led, toggle);    //Toggle Led
  //  if(toggle==0){
  //   digitalWrite(led, LOW);    //Toggle Led
  //  }
  //  if(toggle==1)
  //  {
  //    digitalWrite(led, HIGH);
  //  }
  //  digitalWrite(led_2, toggle);
  String s = "\r\n\r\n  <!DOCTYPE HTML>\r\n<html><h1>Esp8266 Communication</h1> ";
  s += "<p>Success!!!</html>\r\n\r\n";
  server.send(200, "text/html", s);    //Reply to the client
}
void setup() {
  // put your setup code here, to run once:
  delay(200);                           //Stable Wifi
  Serial.begin(9600);                 //Set Baud Rate
  pinMode(led, OUTPUT);                   //Led/Solenoid at pin 2
  //pinMode(led_2, OUTPUT);
  WiFi.softAP(ssid);//, password);      //In Access Point Mode

  IPAddress myIP = WiFi.softAPIP();     //Check the IP assigned. Put this Ip in the client host.
  Serial.print("AP IP address: ");
  Serial.println(myIP);         //Print the esp8266-01 IP(Client must also be on the save IP series)
  server.on("/Led", handleRoot);           //Checking client connection
  //server.on("/Led_1", handleRoot1);
  server.begin();                       // Start the server
  Serial.println("Server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

}
