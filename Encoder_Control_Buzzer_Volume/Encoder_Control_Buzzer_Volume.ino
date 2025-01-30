#define CLK 6
#define DT 5
#define SW 4
int BUZZER = 7;
int frequency;
int s;
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
  int CLK_Value = analogRead(CLK);
  frequency=map(CLK,0,1023,0,255);
  tone(BUZZER);
  s=analogWrite(frequency);
  Serial.print("\n Value of the rotary-encoder: ");

  Serial.println(CLK_Value);// displaying the POT values

  Serial.print("");

  Serial.print("Frequency of the buzzer: ");

  Serial.print(frequency);// displaying the frequency
Serial.print("Sound: ");

  Serial.print(s);
  
  Serial.print("");

  delay(500);
}
