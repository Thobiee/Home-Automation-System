#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>             // Libracy for serial communication
#include <Stepper.h>
#include <LiquidCrystal.h>
#include "dht.h"
#include <Keypad.h>

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)
#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_1_PIN        53         // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2
#define NR_OF_READERS   1
#define buzzer 13 // defining pin 13 for buzzer output
#define ir 18 // defining pin for IR input
#define pushbutton 19 //defining button to stop alarm

#define HouseLights 25 // defining pin 25 for lights output
#define pir 20 // defining pin for PIR input

#define PerLight 24 // defining pin 24 for perimeter lights
#define ldr A0 // defining pin for LDR input
#define dht_apin A2 // Analog Pin sensor is connected to
#define fan_pin 26
#define pot_pin A1
#define rFID_RED A3
#define rFID_GREEN A4
#define rFID_BLUE A5

const int stepsPerRevolution = 510;
byte ssPins[] = {SS_1_PIN};
int receivedChar = 0;         //Place holder for NodeMCU character
int lastCommand = 0;     // previous state of the button
int previousMillis = 0;
long interval = 5000;  
boolean perimeterAlarm = false;
int LDRvalue;

int pot=0, threshold=0;
dht DHT;

char pwd[5]={'C','*','8','0','7'};
bool correct;
int i;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
};
byte rowPins[ROWS] = {33, 32, 31, 30}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {37, 66, 35, 34}; //connect to the column pinouts of the keypad

Stepper stepper(STEPS, 6, 8, 7, 9);
Stepper myStepper(stepsPerRevolution, 14, 16, 15, 17);
SoftwareSerial ArduinoSerial(11, 10);   // Pins declaration for serial communication between NodeMCU and Mega

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


void setup() {
  
  ///////RGB Door state
  pinMode(rFID_RED, OUTPUT);
  pinMode(rFID_RED, OUTPUT);
  pinMode(rFID_RED, OUTPUT); 
  
  ///////Perimeter Security 
  pinMode(buzzer,OUTPUT);
  pinMode(ir,INPUT);
  pinMode(pushbutton,INPUT);
  digitalWrite(buzzer,LOW);
  attachInterrupt(digitalPinToInterrupt(ir), turnBuzzerON, CHANGE); //turnOn() method would be called when the value of PIR sensor changes
  attachInterrupt(digitalPinToInterrupt(pushbutton), turnBuzzerOFF, CHANGE);
  
  ///////House Lights
  pinMode(HouseLights,OUTPUT);
  pinMode(pir,INPUT);
  digitalWrite(HouseLights,LOW);
  attachInterrupt(digitalPinToInterrupt(pir), turnLightsON, HIGH); //turnOn() method would be called when the value of PIR sensor changes

  /////Perimeter Lights
  pinMode(PerLight,OUTPUT);
  pinMode(ldr,INPUT);
  digitalWrite(PerLight,LOW);
  
  ///////Temp
  pinMode(fan_pin,OUTPUT);
  pinMode(pot_pin,INPUT);

  
  ////// Stepper speed
  myStepper.setSpeed(60);
  Serial.begin(115200);
  while (!Serial);
  
  SPI.begin();        // Init SPI bus

  ////// RFID reader
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
  ArduinoSerial.begin(9600);
  Serial.println("HOME AUTOMATION");
}

void loop() {
  // RFID reader function
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {

      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);

      // Check is the PICC of Classic MIFARE type 
      if (piccType != MFRC522 :: PICC_TYPE_MIFARE_MINI &&
        piccType != MFRC522 :: PICC_TYPE_MIFARE_1K &&
        piccType != MFRC522 :: PICC_TYPE_MIFARE_4K) {
        Serial.println (F("Your tag is not of type MIFARE Classic."));
        return ;
      }
       
      String strID = "" ;
      for (byte i = 0; i < 4; i++) {
        strID.concat(String(mfrc522[reader].uid.uidByte[i] < 0x10 ? " 0" : " "));
        strID.concat(String(mfrc522[reader].uid.uidByte[i], HEX));
      }
      strID.toUpperCase();

      Print(strID);
      setRGBColor(255, 255, 255);
      
      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
  
  // Read command from NodeMCU
  int command= 5;
  command = commandFromNodeMCU();
 
  // compare the buttonState to its previous state
  if (command != lastCommand) {
    Serial.print("Value received from NodeMCU: ");
    Serial.println(command);
    
    switch (command) {    
      case 1:  //Web App Indoor Light Function --> OFF
        Serial.println("Print method call");
        turnLightsOFF();
        break; 
        
      case 2:  //Web App Garage Door Function --> Open
        Serial.println("Garage Door Opened");
        garageDoorOpen(); 
        break;
      
      case 3:  //Web App Garage Door Function --> Close
        Serial.println("Garage Door Closed");
        garageDoorClose(); 
        break;
        
      case 4:  //Web App Security Alarm Function --> Activate
        Serial.println("Turning on alarm systems");
        perimeterAlarm = true;
        break;
        
      case 5:  //Web App Security Alarm Function --> de-activate
        Serial.println("Turning off alarm systems");
        perimeterAlarm = false;
        break;
      
      case 6:  //Web App Outdoor Security Alarm Function --> Deactivate
        Serial.println("Print method call");
        break;
        
      case 7:  //Web App Indoor Light Function -->ON
        Serial.println("Print method call");
        turnLightsON();
        break;  //End Case
     }
     lastCommand = command;
  }

  LDRvalue = analogRead(ldr);
  
  if(LDRvalue<516) {
    turnPerON();
  } else {
    turnPerOFF();
  }
  Serial.println(LDRvalue);
  delay(500); 
  
  DHT.read11(dht_apin);
  pot= analogRead(pot_pin);
  threshold = map(pot,0,1023,0,40);
  Serial.print("Threshold Value of Temperature");
  Serial.println(threshold);
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature); 
  Serial.println("C  ");
  
  if(DHT.temperature > threshold) {
    digitalWrite(fan_pin,HIGH);
    Serial.println("on");
  } else {
    digitalWrite(fan_pin,LOW);
    Serial.println("off");
  }
}

/**
 * Read input data coming from NodeMCU ESP8266 Wi-Fi
 */
int commandFromNodeMCU(){
  if(ArduinoSerial.available() > 0){
    receivedChar = ArduinoSerial.read();
  } 
  // save the current state as the last state, for next time through the loop
  return receivedChar;
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

void turnBuzzerON() {
  if(perimeterAlarm == true) {
    digitalWrite(buzzer,HIGH); //switching the buzzer on
    Serial.println("buzzor on");
  }
}

void turnBuzzerOFF() {
  digitalWrite(buzzer,LOW); //switching the buzzer off
  Serial.print("buzzor off");
 
}

void turnLightsON() {
  digitalWrite(HouseLights,HIGH); //switching the buzzer off
  Serial.println("House Lights on");
}

void turnLightsOFF() {
  digitalWrite(HouseLights,LOW); //switching the buzzer off
  Serial.println("House Lights off");
}

void turnPerON() {
  Serial.println("Lights on");
  digitalWrite(PerLight,HIGH); //switching the buzzer off
}

void turnPerOFF() {
  Serial.println("Lights on");
  digitalWrite(PerLight,LOW); //switching the buzzer off
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void setRGBColor(int red, int green, int blue) {
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;

  analogWrite(rFID_RED, red);
  analogWrite(rFID_GREEN, green);
  analogWrite(rFID_BLUE, blue);  
}

void Print(String tagID){

  if (tagID.substring(1) == "40 1D 79 A5") {
    setRGBColor(255,255,0);  // Blue
    Serial.println("Valid Card");
    Serial.println("Enter Password");
    
    correct = true;
    char customKey;
    i=0; 
    
    while(i<5) {
      customKey = customKeypad.getKey();
      
      if (customKey) {
        Serial.print(customKey);
        
        if(customKey != pwd[i]) {
          correct = false;
          i++;
        } else
        i++;
      }
    }
    
    if(correct == true) {
      setRGBColor(255,0,255);  // Green
      Serial.println("Correct Password");
      
      myStepper.step(-stepsPerRevolution);
      delay(3000);
      myStepper.step(stepsPerRevolution);
    } else {
      setRGBColor(0, 255, 255);  // red
      Serial.println("Incorrect Password"); 
    }
  }
}
