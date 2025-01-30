#define ir_sensor D1
#define LED D5
int val = 0 ;  


 void setup()  
 {  
   Serial.begin(9600); // sensor buart rate  
   pinMode(D5,OUTPUT);// Led Pin Connected To D5 Pin    
   pinMode(D1,INPUT);
 }  
 void loop()   
 {  
  val = digitalRead(D1); // IR Sensor output pin connected to D1  
  Serial.println(val);  // see the value in serial m0nitor in Arduino IDE  
  delay(100);      // for timer  
  if(val == 0)  
  {  
   digitalWrite(D5,HIGH); // LED ON 
   //Serial.print("value = ");
   Serial.println("High"); 
  }  
  else  
  {  
   digitalWrite(D5,LOW); // LED OFF  
   //Serial.print("value = ");
   Serial.println("Low");
  } 
  }  
