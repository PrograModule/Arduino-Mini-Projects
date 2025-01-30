#include <Servo.h>
Servo servo;
int angle = 10;
int button = 7;
int value = 0;
int flag=0;
void setup() {
  Serial.begin(9600);
  pinMode (button, INPUT_PULLUP);
  servo.attach(8);
  servo.write(angle);
}
void loop()
{
  // scan from 0 to 180 degrees
  value = digitalRead(button);
  Serial.print("Button Value =");
  Serial.println(value);
  if (value == 0 && flag==0)
  {
    
    for (angle = 50; angle < 180; angle++)
    {
      flag=1;
      servo.write(angle);
      delay(15);
    }
    value=1;
  }
  delay(2000);
  // now scan back from 180 to 0 degrees
  if (value == 1 && flag== 1)
  { 
    for (angle = 180; angle > 50; angle--)
    {
      flag=0;
      servo.write(angle);
      delay(15);
    }
    value=0;
  }
  delay(2000);
}
