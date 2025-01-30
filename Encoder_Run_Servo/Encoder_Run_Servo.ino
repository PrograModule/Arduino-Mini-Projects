// Rotary Encoder Inputs
const int SW_PIN = 4;//define a pin for rotary encode switch
const int PIN_A =5;
const int PIN_B =6;

//#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
//Encoder myEnc(PIN_A, PIN_B);
//   avoid using pins with LEDs attached

const int homePosition = 90; //initial position
const int stepValue = 3;//how fast the servo should rotate when turning the knob
const int servoPin = 9;//~must be a pin that that is labeled with ~
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int servoAngel =homePosition;


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 or 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(SW_PIN, INPUT);
  Serial.println("Robojax Encoder with LCD and Servo");
   myservo.attach(servoPin);  // attaches the servo on pin
   myservo.write(servoAngel);//move servo to initial position

//  lcd.begin();
//  // Turn on the blacklight and print a message.
//  lcd.backlight();     
//  lcd.print("Robojax Encoder");
//  lcd.setCursor (0,1); // go to start of 2nd line
//  lcd.print("Servo Test");   
//  delay(2000);   
//   lcd.clear();// clear previous values from screen   
//  lcd.print("Robojax Encoder");
//  lcd.setCursor (0,1); // go to start of 2nd line  
//  lcd.print("Angel: ");   
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {

    if(newPosition >  oldPosition)
    {
    int newStep = abs(newPosition - oldPosition);
      Serial.print("Angle ");
      Serial.println(servoAngel);      
      servoAngel -= stepValue;
      if(servoAngel <0)
          servoAngel =0;      
      myservo.write(servoAngel); //move servo to new angel
      lcdAngel(servoAngel);//print on LCD
    }

    if(newPosition <  oldPosition )
    {
    int newStep = abs(newPosition - oldPosition);
      Serial.print("Angle ");
      Serial.println(servoAngel);        
      servoAngel += stepValue;
      if(servoAngel >180)
          servoAngel =180;
      myservo.write(servoAngel); //move servo to new angel
      lcdAngel(servoAngel);//print on LCD
    }
   oldPosition = newPosition;//remember the new position
  }

  if( digitalRead(SW_PIN) == LOW)
  {
    Serial.print("Home: ");
    Serial.println(homePosition);
    servoAngel =homePosition;
      myservo.write(servoAngel); //move servo to new angel
      Serial.println(servoAngel);//print on LCD
  
  }

  //delay(200);
}

/*
 * lcdAngel(int angel)
 * prints the angle on LCD
 * written by Ahmad Shamshiri
 * www.robojax.com
 * Jan 27, 2022 at 13:18
 * Watch full details video: https://youtu.be/6xVLbNlmK-g
 */
//void lcdAngel(int angel)
//{
//  
//  int startChar =7;
//  for(int i=startChar; i<16; i++)
//  {
//   lcd.setCursor (i,1);    
//    lcd.print(" ");   
//  }
// 
//   lcd.setCursor (startChar,1); // line 1 
//   lcd.print(angel); 
//   lcd.print((char)223);
//}
