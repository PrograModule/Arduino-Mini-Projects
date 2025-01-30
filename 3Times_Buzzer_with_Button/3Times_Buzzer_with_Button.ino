int buzzer=7;
int button=6;
int value=1;
int flag=0;
int flag1=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  pinMode (button, INPUT_PULLUP);
  pinMode (buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 
value = digitalRead(button);
  Serial.print("Button Value =");
  Serial.println(value);
  if(value==0 && flag==0){
    Buzzer();
    flag=1;
    flag1=0;
  }
  if(value==0 && flag==1)
  {
    noTone(buzzer);
    
  }
  if(value==1 && flag1==0)
  {
    Buzzer();
    flag1=1;
    flag=0;
  }
  if(value==1 && flag1==1)
  {
    noTone(buzzer);
    
  }
delay(500);
}

void Buzzer()
{
  tone (buzzer, 450);
      delay(200);
      noTone(buzzer);
      delay(200);

      tone (buzzer, 450);
      delay(200);
      noTone(buzzer);
      delay(200);

      tone (buzzer, 450);
      delay(200);
      noTone(buzzer);
      delay(200);

}
