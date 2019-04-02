// Load Wi-Fi library
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/
SoftwareSerial NodeSerial(D2, D3);

// Replace with your network credentials
//const char ssid[] = "SASKTEL0400";
//const char password[] = "3065294159";
const char ssid[]="SM-G955W0291";  // replace with your ssid & pass
const char password[]="yszc9330";
int status = WL_IDLE_STATUS;

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output0State = "off";
String output1State = "off";
String output2State = "off";
String output3State = "off";
String output4State = "off";

/** Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 15;
const int output3 = 3;
const int output2 = 2;
const int output1 = 1;
const int output0 = 13;*/

const int zero = 0;
const int one = 1;
const int two = 2;
const int three = 3;
const int four = 4;
const int five = 5;

void setup() {
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
  Serial.begin(115200);  
  NodeSerial.begin(9600);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }

  // Connect to Wi-Fi network with SSID and password
  WiFi.begin(ssid,password);
  
  // attempt to connect to WiFi network:
  while (WiFi.status() != WL_CONNECTED) {    
    delay(500);
    Serial.print("Searching for connection ... ");
    Serial.println(ssid);
  }
  server.begin();
  wiFiStatus();
}
/**
 * Thanks to Rui Santos from https://randomnerdtutorials.com/esp8266-web-server/
 */
void loop(){
  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("GPIO 0 on");
              output0State = "on";             
              sendingData(zero);
            
              /**output4State = "off";      
              output3State = "off";        
              output2State = "off";        
              output1State = "off";*/
              
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("GPIO 0 off");
              output0State = "off";             
              sendingData(zero);
              
            } else if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("GPIO 1 on");
              output1State = "on";
              sendingData(one);
    
              /**output4State = "off";        
              output3State = "off";        
              output2State = "off";        
              output0State = "off";*/
              
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("GPIO 1 off");
              output1State = "off";             
              sendingData(one);
              
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2State = "on";
              sendingData(two);
 
              /**output4State = "off";        
              output3State = "off";        
              output1State = "off";        
              output0State = "off";*/
              
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2State = "off";             
              sendingData(two);
              
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              output3State = "on";
              sendingData(three);

              /**output4State = "off";       
              output2State = "off";        
              output1State = "off";        
              output0State = "off";*/
              
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              output3State = "off";             
              sendingData(three);
              
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              sendingData(four);

              /**output3State = "off";       
              output2State = "off";        
              output1State = "off";        
              output0State = "off";*/
              
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";             
              sendingData(four);
              
            } 
            
            // Display the HTML web page
            HTML_Page(client, output0State, output1State, output2State, output3State, output4State);
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected...");
    Serial.println("");
  }
}

void wiFiStatus(){
  
  // Print local IP address and start web server
  Serial.print("SSID --> ");
  Serial.println (WiFi.SSID());
  Serial.println("Successfully connected Wi-Fi!!!");
  
  Serial.print("IP Address allotted to NodeMcu ESP --> ");
  Serial.println(WiFi.localIP());
  
  Serial.print("MAC Address of ESP --> ");
  Serial.println(WiFi.macAddress() +"\n");
  //WiFi.printDiag(Serial);
}

void sendingData(int val){
  NodeSerial.write(val / 256);
  NodeSerial.write(val % 256);  
  delay(50);
}

void HTML_Page(WiFiClient client, String A, String B, String C, String D, String E){
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  // CSS to style the on/off buttons 
  // Feel free to change the background-color and font-size attributes to fit your preferences
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #195B6A; border: none; color: white; padding: 10px 50px;");
  client.println("text-decoration: none; font-size: 16px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #77878A;}");
  client.println(".center {margin: auto; border: 2px solid black; text-align: center; padding: 25px; width: 500px; height: 470px;  background-color: lightblue;}");
  client.println(".dropbtn {\n  background-color: #4CAF50;\n  color: white;\n  padding: 16px;\n  font-size: 16px;\n  border: none;\n  cursor: pointer;\n}\n\n.dropbtn:hover, .dropbtn:focus {\n  background-color: #3e8e41;\n}\n\n.dropdown {\n  position: relative;\n  display: inline-block;\n}\n\n.dropdown-content {\n  display: none;\n  position: absolute;\n  background-color: #f9f9f9;\n  min-width: 230px;\n  overflow: auto;\n  box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);\n}\n\n.dropdown-content a {\n  color: black;\n  padding: 12px 16px;\n  text-decoration: none;\n  display: block;\n}\n\n.dropdown-content a:hover {background-color: #f1f1f1}\n\n.show {display:block;}</style></head>");
  
  // Web Page Heading
  client.println("<body><div class=center>");
  client.println("<h1>Home Automation System</h1>");

  // Display current state, and ON/OFF buttons for GPIO 5
  client.println("<center>TS - State " + A + "</center>");
  // If the output5State is off, it displays the ON button       
  if (A == "off") {
    client.println("<a href=\"/0/on\"><button class=\"button\">Lights</button></a>");
  } else {
    client.println("<a href=\"/0/off\"><button class=\"button button2\">L Clicked</button></a>");
  } 
     
  // Display current state, and ON/OFF buttons for GPIO 1  
  client.println("<center>AD - State " + B + "</center>");
  // If the output4State is off, it displays the ON button       
  if (B == "off") {
    client.println("<a href=\"/1/on\"><button class=\"button\">Outside Security</button></a>");
  } else {
    client.println("<a href=\"/1/off\"><button class=\"button button2\">OS Clicked</button></a> \n");
  }
  
  // Display current state, and ON/OFF buttons for GPIO 2  
  client.println("<center>R1 - State " + C + "</center>");
  // If the output5State is off, it displays the ON button       
  if (C == "off") {
    client.println("<a href=\"/2/on\"><button class=\"button\">Garrage Door</button></a>");
  } else {
    client.println("<a href=\"/2/off\"><button class=\"button button2\">GD Clicked</button></a>");
  } 

  client.println("<div align=center><h3>Fan Speed</h3></div>");
     
  // Display current state, and ON/OFF buttons for GPIO 3  
  client.println("<center>R2 - State " + D + "</center>");
  // If the output4State is off, it displays the ON button       
  if (D == "off") {
    client.println("<a href=\"/3/on\"><button class=\"button\">Increase</button></a>");
  } else {
    client.println("<a href=\"/3/off\"><button class=\"button button2\">I Clicked</button></a>");
  }
  
  // Display current state, and ON/OFF buttons for GPIO 4 
  client.println("<center>R3 - State " + E + "</center>");
  // If the output5State is off, it displays the ON button       
  if (E == "off") {
    client.println("<a href=\"/4/on\"><button class=\"button\">Decrease</button></a>");
  } else {
    client.println("<a href=\"/4/off\"><button class=\"button button2\">D Clicked</button></a>");
  } 

  client.println("<script>document.getElementById(\"myBtn\").onclick = function() {myFunction()};");
  client.println("function myFunction() {document.getElementById(\"myDropdown\").classList.toggle(\"show\");}</script>");
  client.println("<h4>Interactive Hardware Group Project</h4>");
  client.println("</div></body></html>");
}
