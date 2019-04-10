#define PerLight 24 // defining pin 24 for perimeter lights
#define ldr A0 // defining pin for LDR input


//bool LDRstate, prevLDRstate = true; // here true means day and false means night
int LDRvalue; // variable to store input from LDR

void setup() 
{
 //defining pin modes for digital pins
  pinMode(PerLight,OUTPUT);
  
  pinMode(ldr,INPUT);
  
  Serial.begin(9600);
  digitalWrite(PerLight,LOW);
  
//  attachInterrupt(digitalPinToInterrupt(ldr), turnON, LOW); //turnOn() method would be called when the value of PIR sensor changes
 //attachInterrupt(digitalPinToInterrupt(ldr), turnOFF, HIGH);
}

// state change code used from https://www.arduino.cc/en/Tutorial/StateChangeDetection
void loop() 
{
  LDRvalue = analogRead(ldr);
  if(LDRvalue<516)
  {
    turnON();
    }
  else
  {
    turnOFF();
   }
  Serial.println(LDRvalue);
  delay(500); 
}

void turnON()
{
  Serial.println("Lights on");
  digitalWrite(PerLight,HIGH); //switching the buzzer off
}

void turnOFF()
{
  Serial.println("Lights on");
  digitalWrite(PerLight,LOW); //switching the buzzer off
}
