#include "dht.h"
#define dht_apin A2 // Analog Pin sensor is connected to
#define fan_pin 26
#define pot_pin A1

int pot=0, threshold=0;
dht DHT;
 
void setup(){
 
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  pinMode(fan_pin,OUTPUT);
  pinMode(pot_pin,INPUT);
 
}//end "setup()"
 
void loop(){
  //Start of Program 
 
    DHT.read11(dht_apin);
    pot= analogRead(pot_pin);
    threshold = map(pot,0,1023,0,40);
    Serial.println(threshold);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    if(DHT.temperature > threshold)
    {
      digitalWrite(fan_pin,HIGH);
      Serial.println("on");
    }
    else
    {
    digitalWrite(fan_pin,LOW);
    Serial.println("off");
    }
    
    delay(5000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop()
