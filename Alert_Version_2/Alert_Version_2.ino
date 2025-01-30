int buzzer = 7;
#define Sensor 8
#define button 9

int Sensor_value = 1;
int button_value = 1;

int flag = 0;
int flag1 = 0;
int holdflag = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (button, INPUT_PULLUP);
  pinMode (Sensor, INPUT_PULLUP);
  pinMode (buzzer, OUTPUT);
}

void loop() {

  button_value = digitalRead(button); // button pin
  Sensor_value = digitalRead(Sensor); // sensor pin

  if (Sensor_value == 0 && flag == 0) { // sensor input
    //SendMessage();
    digitalWrite(buzzer, HIGH);
    flag = 1;
    //flag1 = 0;

  }
  if ( flag == 1 && holdflag == 0 && button_value == 0 ) { // sensor input and button pressed
    digitalWrite(buzzer, LOW);
    holdflag = 1;
  } //done
  
if(Sensor_value==1)
{
  //digitalWrite(buzzer, HIGH);
  flag = 0;
  holdflag=0;
}
  delay(1000);
}
