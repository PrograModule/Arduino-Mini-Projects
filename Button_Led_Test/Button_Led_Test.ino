int led_pin = 13;
int button = 6;

int flag = 0;
int hold_flag = 0;
int count=0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (button, INPUT_PULLUP);
  pinMode (led_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(button);
  Serial.print("Press the Button");
  Serial.print("Button Value =");
  Serial.println(value);
  //Serial.println("");
  if (value == 0)
  {
    delay(300);
    flag = 1 ;
    
    //digitalWrite(led_pin,HIGH);
  }
  
  if (flag == 1  &&  hold_flag == 0) { // on 
    digitalWrite(led_pin, HIGH);
    //flag=0;
     
  }
 else if(value == 1)
 {
  delay(300);
    hold_flag = 1;
 }
if(flag==1 && hold_flag == 1){
  digitalWrite(led_pin, LOW);
}
//  if (hold_flag==1)
//  {
//    digitalWrite(led_pin, LOW);
    //flag=0;
    //hold_flag=0;
  //}
//  if(value==1)
//  {
//    delay(300);
//    flag =1;
//  }
//  if (flag == 1  &&  hold_flag == 0) { // on 
//    digitalWrite(led_pin, HIGH);
//  }
//   else if (value == 1 )
//  {
//    delay(300);
//    flag=0;
//    //digitalWrite(led_pin,LOW);
//  }
Serial.println(flag);  
//if (flag == 0  &&  hold_flag == 0) // off
//  { 
//    digitalWrite(led_pin, LOW);
//
//  }
delay(1000);
}
 
