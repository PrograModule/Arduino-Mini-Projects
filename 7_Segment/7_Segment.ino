#include <SevSeg.h>
SevSeg sevseg;
int flag=0;
int value=0; 
int count=0;
int lastcount=0;
int irSensor = 12;
void setup(){
   Serial.begin(9600);
  pinMode(irSensor, INPUT);
    byte numDigits = 1;
    byte digitPins[] = {};
    byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8};
    bool resistorsOnSegments = true;

    byte hardwareConfig = COMMON_CATHODE; 
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
}

void loop(){
//        sevseg.setNumber(6);
//        sevseg.refreshDisplay(); 
Serial.print("Sensor Value =");
  Serial.print(value);
   int value = digitalRead(irSensor);
  Serial.println("");
  delay(1000);
  if(value == 0 && flag==0)
  {
       
    count++;
    flag=1;  
  }
  
  lastcount=count;
     sevseg.setNumber(count);  
     sevseg.refreshDisplay();
     delay(100);  
  if(value==1 && flag==1)
  {
    flag=0;
    
  }
  sevseg.setNumber(lastcount);  
     sevseg.refreshDisplay();
     delay(100); 
}
