#define CLK 6
#define DT 5
#define SW 4
int BUZZER = 7;
int frequency;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
// fade in from min to max in increments of 5 points:
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(BUZZER, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30); 
}
}
