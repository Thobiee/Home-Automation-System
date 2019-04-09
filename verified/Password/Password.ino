/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
char pwd[5]={'C','*','8','0','7'};
bool correct;
int i;

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
};
byte rowPins[ROWS] = {3, 2, 11, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  correct = true;
  char customKey;
  Serial.println("Please enter the password");
  i=0; 
  while(i<5)
  {
     customKey = customKeypad.getKey();
      if (customKey)
        {
          Serial.print(customKey);
          if(customKey != pwd[i])
             {
               correct = false;
              i++;
             }
          else
            i++;
        }
  }
  if(correct == true)
    Serial.println("\nCorrect Password\n");
  else
    Serial.println("\nIncorrect Password\n");
}
