#define PerLight 13 // defining pin 13 for perimeter lights
#define ldr 5 // defining pin for LDR input


bool LDRstate, prevLDRstate = true; // here true means day and false means night
int LDRvalue =10; // variable to store input from LDR

void setup() 
{
 //defining pin modes for digital pins
  pinMode(PerLight,OUTPUT);
  
  pinMode(ldr,INPUT);
  
  Serial.begin(9600);
  digitalWrite(PerLight,LOW);
}

// state change code used from https://www.arduino.cc/en/Tutorial/StateChangeDetection
void loop() 
{
  LDRvalue = digitalRead(ldr);
  Serial.println(LDRvalue);
  delay(5000);
  if(LDRvalue == HIGH)
  {
    LDRstate = false; //false indicates night
  }
  else
  {
    LDRstate = true; //true indicates day
  }
  
  if (prevLDRstate != LDRstate) //making sure that state changed from day to night and it was not already night, this ensurre the buzzer sounding only once a night
  {
    if(LDRstate == false) 
        {
          digitalWrite(buzzer,HIGH);
        } 
   else 
       {
        digitalWrite(buzzer,LOW);
       }   
    
    // Delay a little bit to avoid bouncing
    
    delay(2000);
  }
  
  prevLDRstate = LDRstate; // forwarding the state for next iteration
  
}

