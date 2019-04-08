#define buzzer 13 // defining pin 13 for buzzer output
#define ir 2 // defining pin for IR input
#define button 3

int IRvalue, buttonV;
void setup() 
{
 //defining pin modes for digital pins
  pinMode(buzzer,OUTPUT);
  pinMode(ir,INPUT);
  pinMode(button,INPUT);
  
  Serial.begin(9600);
  
  digitalWrite(buzzer,LOW);
  
  attachInterrupt(digitalPinToInterrupt(ir), turnON, CHANGE); //turnOn() method would be called when the value of PIR sensor changes
  attachInterrupt(digitalPinToInterrupt(button), turnOFF, CHANGE);
}

void loop() 
{
  IRvalue = digitalRead(ir);
  buttonV = digitalRead(button);
  Serial.print("IR = ");
  Serial.print(IRvalue);
  Serial.println();
  Serial.print("button ");
  Serial.print(buttonV);
  Serial.println();
  delay(1000);
  //digitalWrite(HouseLights, LOW);
}

void turnON()
{
  digitalWrite(buzzer,HIGH); //switching the buzzer on
  Serial.print("buzzor on");
}

void turnOFF()
{
  digitalWrite(buzzer,LOW); //switching the buzzer off
  Serial.print("buzzor off");
}
