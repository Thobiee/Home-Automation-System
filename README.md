# Home-Automation-System

This project will contain the following:

1. Project Description
2. Hardware requirements
3. Bill of Materials
4. Hardware Connections
5. Schematics
6. Arduino Code
7. Project Demo etc.


## Hardware Connections and Schematics

![Hardware Connections and Schematics](/Images/IH_Project_Schematics.png "Hardware Connections and Schematics")

## Bill of Materials

#### Sensors:
- 1x RC522 RFID reader and RFID-Tag
- 1x Keypad 
- 1x Rotary Potentiometer 
- 4x Infrared sensors + emitters (square perimeter) 
- 1x Passive Infrared sensor w/lens dome
- 1x Photoresistor
- 1x RHT03 Temperature + Humidity Sensor Module
- 1x Wi-Fi module (NodeMCU ESP8266)

#### Actuators:
- 4x Green, 4x Orange LEDs
- 1x RGB LED
- 1x Alarm Buzzer
- 1x LCD Screen
- 2x 28BYJ-48 Stepper Motors
- 2x X113647 Stepper Driver Boards
- 1x DC Motor Fan

#### Miscellaneous:
- 1x Arduino Mega 2560 (Microcontroller board)
- 1x External power supply board
- 1x big + 2x smaller Prototyping Breadboards
- Various Jumper Wires
- Various Resistors (1k)

## Web Application

#### 1. Indoor Lights: 
The indoor light in the house can be triggered to ON/OFF by clicking the button function. Another alternative to this is to use the Motion sensor inside the house to trigger indoor lights to come ON.

#### 2. Garage Door: 
The garage door can only be triggered to Open/Close from the Web Application, this is mainly because of security in the house.

#### 3. Security Alarm: 
For the purpose of securing the house for when the owners are off to work or even sleeping at night, we added functionality to set the perimeter alarm to Activate/Deactivate depending on the owner. The Activate function arms the alarm, so it can trigger the perimeter security alarm when being intruded. And the Deactivate disarms the perimeter security alarm, this could be done when the family is home during the day.

![Web Application](/Images/web_App.PNG "Web Application")


## Team

The Home Automation project was designed and implemented as a group and the tasks/roles of the group members includes:

#### Vivek Pujara
- Lead Programmer
- Project Management Lead

#### Mikhail Shchukin
- Documentation Lead Specialist
- Prototype Testing

#### Gideon Eromosele
- Primary Hardware Designer
- Auxillary Programmer

#### Oluwatobi Adegbola
- Auxillary Hardware Designer
- User Requirement Ellicitation


## Usage

To use the Home Automation System, first all the below listed library must be downloaded and installed correctly. Contained inside the implementation folder are **_two_** other folder called: 

#### Arduino Mega2560
Contained in this folder, is the **_Serial_Communication.ino_** code to be uploaded on _Arduino Mega2560_ microcontroller board using the above **_Hardware Connections and Schematics_** as instruction guide.

#### NodeMCU Wi-Fi
This folder, contains the code **_WiFi_Control.ino_** to be uploaded to _NodeMCU ESP8266 Wi-Fi module._ The code uses the internet to give commands to the _Arduino Mega board_ **_(see Web Application for the Interface)._** To be able to communicate with _Arduino Mega, pin D2 (GPIO4) and D3 (GPIO0)_ must be connected to _Arduino Mega pin 10 and 11_ **_(see Hardware Connections and Schematics),_** so to allows serial communication between both boards with help of SoftwareSerial library.

### Libraries

1. **SPI.h -->** Serial Peripheral Interface is for communicating with one or more peripheral devices quickly over short distances
2. **MFRC522.h -->** Is a libracy for RFID Reader and Tag
3. **SoftwareSerial.h -->** Is a libracy for serial communication between two or more microcontrollers
4. **Stepper.h -->** Is a libracy for Stepper and Driver motor
5. **dht.h -->** Is a libracy to read Temperature and Humidity 
6. **Keypad.h -->** Is a libracy for Membrane Keypad
7. **ESP8266WiFi.h -->** Is a libracy for ESP8266 e.g. NodeMCU Wi-Fi module

## Credits

Our sincere appreciation, goes to the following for making their materials available for use. 

- Trevor Tomesh for Advise and Instructions
- Miguel Balboa https://github.com/miguelbalboa/rfid
- Rui Santos https://randomnerdtutorials.com/esp8266-web-server/
- Arduino CC http://arduino.cc/playground/Main/DHTLib
