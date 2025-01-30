#include <Servo.h>
Servo servo;
int angle = 0;
#define outputA 6
 #define outputB 7
//int servo=8;
 int counter = 0; 
 int aState;
 int aLastState;  

 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   servo.attach(8);
  servo.write(angle);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 

 void loop() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
       counter=180;
       for(angle = 10; angle < counter; angle++) 
       {
        servo.write(angle);               
    delay(15);  
       }
     } else {
       counter --;
       for(angle = counter; angle > 0; angle--) 
       {
        servo.write(angle);               
    delay(15);  
       }
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }
