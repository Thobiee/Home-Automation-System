#include <SoftwareSerial.h>             // Libracy for serial communication
#include <Stepper.h>

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

SoftwareSerial ArduinoSerial(11, 10);   // Pins declaration for serial communication between NodeMCU and Mega
Stepper stepper(STEPS, 6, 8, 7, 9);

int receivedChar;         //Place holder for NodeMCU character
int buttonState = 0;         // current state of the button
int lastCommand = 0;     // previous state of the button

void setup() {
  Serial.begin(115200);
  ArduinoSerial.begin(9600);
}

void loop() {
  // Read command from NodeMCU
   int command= 5;
   command = commandFromNodeMCU();
 
  // compare the buttonState to its previous state
  if (command != lastCommand) 
  {
    Serial.print("Value received from NodeMCU: ");
    Serial.println(command);
  
  switch (command) 
  {
    case 0:  //Print method call to serial
      Serial.println("Print method call");

      // check if pesdestrain button is pushed 
      //methodCall(); 
      break;  //End Case
  
    case 1:  //Print method call to serial
      Serial.println("Print method call");
      //methodCall(); 
      break;
      
    case 2:  //Garage Door Function --> Open
      Serial.println("Garage Door Opened");
      garageDoorOpen(); 
      break;
  
    case 3:  //Garage Door Function --> Close
      Serial.println("Garage Door Closed");
      garageDoorClose(); 
      break;
      
    case 4:  //Print method call to serial
      Serial.println("Print method call");
      //methodCall(); 
      break;
   }
    lastCommand = command;
  }
    
}

/**
 * Read input data coming from NodeMCU ESP8266 Wi-Fi
 */
int commandFromNodeMCU(){
  if(ArduinoSerial.available() > 0){
    receivedChar = ArduinoSerial.read();
  }
//  Serial.print("Value received from NodeMCU: ");
//  Serial.println(receivedChar);
//  return receivedChar;

  buttonState = receivedChar;
  
  
    
  // save the current state as the last state, for next time through the loop
  return buttonState;
}

void garageDoorOpen(){
  stepper.setSpeed(14); // 6 rpm
  stepper.step(-2058);
  delay(50);// do 2038 steps in the other direction with faster speed -- corresponds to one revolution in 10 seconds
  stepper.setSpeed(14); // 6 rpm
  stepper.step(-2038);
  delay(50);
  stepper.setSpeed(14); // 6 rpm
  stepper.step(-1058);
  
}

void garageDoorClose(){
  stepper.setSpeed(14); // 1 rpm
  stepper.step(2038); // do 2038 steps -- corresponds to one revolution in one minute
  delay(50); // wait for one second
  stepper.setSpeed(14); // 1 rpm
  stepper.step(2038);// do 2038 steps -- corresponds to one revolution in one minute
  delay(50);
  stepper.setSpeed(14); // 1 rpm
  stepper.step(1058); // do 2038 steps -- corresponds to one revolution in one minute

}
