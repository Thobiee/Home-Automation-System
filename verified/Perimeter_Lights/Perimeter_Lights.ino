#define PerLight 13 // defining pin 13 for perimeter lights
#define ldr 2 // defining pin for LDR input


//bool LDRstate, prevLDRstate = true; // here true means day and false means night
int LDRvalue; // variable to store input from LDR

void setup() 
{
 //defining pin modes for digital pins
  pinMode(PerLight,OUTPUT);
  
  pinMode(ldr,INPUT);
  
  Serial.begin(9600);
  digitalWrite(PerLight,LOW);
  
  attachInterrupt(digitalPinToInterrupt(ldr), turnON, LOW); //turnOn() method would be called when the value of PIR sensor changes
}

// state change code used from https://www.arduino.cc/en/Tutorial/StateChangeDetection
void loop() 
{
  LDRvalue = digitalRead(ldr);
  Serial.println(LDRvalue);
  delay(500);
  digitalWrite(PerLight, LOW);  
}

void turnON()
{
  digitalWrite(PerLight,HIGH); //switching the buzzer off
}

void turnOFF()
{
  digitalWrite(PerLight,LOW); //switching the buzzer off
}
