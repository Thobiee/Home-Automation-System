#include <SoftwareSerial.h>             // Libracy for serial communication

SoftwareSerial ArduinoSerial(11, 10);   // Pins declaration for serial communication between NodeMCU and Mega

int receivedChar;         //Place holder for NodeMCU character

void setup() {
  ArduinoSerial.begin(9600);
}

void loop() {
  // Read command from NodeMCU
  int command = commandFromNodeMCU();

  switch (command) {
    case 0:  //Print method call to serial
      Serial.println("Print method call");

      // check if pesdestrain button is pushed 
      //methodCall(); 
      break;  //End Case
  
    case 1:  //Print method call to serial
      Serial.println("Print method call");
      //methodCall(); 
      break;
      
    case 2:  //Print method call to serial
      Serial.println("Print method call");
      //methodCall(); 
      break;
  
    case 3:  //Print method call to serial
      Serial.println("Print method call");
      //methodCall(); 
      break;
      
    case 4:  //Print method call to serial
      Serial.println("Print method call");
      //methodCall(); 
      break;
   }
}

/**
 * Read input data coming from NodeMCU ESP8266 Wi-Fi
 */
int commandFromNodeMCU(){
  if(ArduinoSerial.available() > 0){
    receivedChar = ArduinoSerial.read();
  }
  Serial.print("Value received from NodeMCU: ");
  Serial.println(receivedChar);
  return receivedChar;
}
