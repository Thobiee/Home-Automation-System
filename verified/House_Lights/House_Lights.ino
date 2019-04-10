#define HouseLights 25 // defining pin 25 for lights output
#define pir 20 // defining pin for LDR input

int PirValue;
void setup() 
{
 //defining pin modes for digital pins
  pinMode(HouseLights,OUTPUT);
  pinMode(pir,INPUT);
  
 Serial.begin(9600);
  
  digitalWrite(HouseLights,LOW);
  
  attachInterrupt(digitalPinToInterrupt(pir), turnON, HIGH); //turnOn() method would be called when the value of PIR sensor changes
}

void loop() 
{
  PirValue = digitalRead(pir);
  Serial.println(PirValue);
  delay(5000);
  digitalWrite(HouseLights, LOW);
}

void turnON()
{
  digitalWrite(HouseLights,HIGH); //switching the buzzer off
    
}
