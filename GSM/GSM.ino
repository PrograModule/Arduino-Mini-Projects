String textMessage;
int ledpin=8;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200); // SIM900A
  // SIM900A.begin(9600);

  delay(20000); // wait for gsm
  //  Serial.print("SIM900 ready...");

  //  Serial.println("SIM900a software serial initialize");
  Serial.println("AT");
  delay(100);
  // AT command to set SIM900 to SMS mode
  Serial.print("AT+CMGF=1\r");
  delay(100);
  // Set module to send SMS data to serial out upon receipt
  Serial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);

  //digitalWrite(setup_ready_led_pin, HIGH); // Glows when setup is complete and sysytem is ready for action
  delay(1000);
  sys_ready();
  pinMode(ledpin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(ledpin,HIGH);
}

void slave_1_low() //to inform master of current state
{
  Serial.println("AT+CMGF=1");
  delay(1000);
  // SIM900.println("AT + CMGS = \"" + 919874724390 + "\"");
  Serial.println("AT+CMGS=\"+919874724390\"\r");
  delay(1000);
  Serial.print("light on");
  // Serial.print("valve1 on");
  delay(1000);
  Serial.write((char)26); //ctrl+z
  delay(1000);
}

void receive_sms() {
  if (Serial.available() > 0) {
    textMessage = Serial.readString();
    delay(10);
  }
}
void sys_ready()
{
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+918013809702\"\r");
  delay(1000);
  // Serial3.print("Master is ready for action");
  Serial.print("Slave 1 is ready for action"); // for slave  xxxx = slave 1 , slave 2, slave 3...
  delay(1000);
  Serial.write((char)26); //ctrl+z
  delay(1000);
}
