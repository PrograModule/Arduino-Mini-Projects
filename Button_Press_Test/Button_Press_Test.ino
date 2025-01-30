int state=LOW;
int lastState=LOW;
int count=0;
int LED_ON=9;
void setup() {
  // put your setup code here, to run once:
pinMode(13,INPUT_PULLUP);
pinMode(LED_ON,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  lastState=state;
state=digitalRead(8);
if(state==HIGH && lastState==LOW) { // debouncing condition
count ++;
if(count == 1){
// if one button click is detected the code is suppose to blink LED on pin 13 for 2 seconds
digitalWrite(LED_ON,HIGH); // setting pin13 high after when 1 button press is detected
delay(2000); // delaying 2 seconds before pin13 is set lOW
digitalWrite(LED_ON,LOW);
}// setting pin13 low, thereby switching off the LED on pin13
else
if(count == 2){
// if one button click is detected the code is suppose to blink LED on pin 13 for 2 seconds
digitalWrite(LED_ON,HIGH);// setting pin13 high after when 1 button press is detected
delay(2000); // delaying 2 seconds before pin13 is set lOW
digitalWrite(LED_ON,LOW); // setting pin13 low, thereby switching off the LED on pin13

}
else
if(count == 3){
// if one button click is detected the code is suppose to blink LED on pin 13 for 2 seconds
digitalWrite(LED_ON,HIGH); // setting pin13 high after when 1 button press is detected
delay(2000); // delaying 2 seconds before pin13 is set lOW
digitalWrite(LED_ON,LOW); // setting pin13 low, thereby switching off the LED on pin13

}
}

}
