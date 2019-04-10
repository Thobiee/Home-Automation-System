/**
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from more than one PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 *
 * Example sketch/program showing how to read data from more than one PICC (that is: a RFID Tag or Card) using a
 * MFRC522 based RFID Reader on the Arduino SPI interface.
 *
 * Warning: This may not work! Multiple devices at one SPI are difficult and cause many trouble!! Engineering skill
 *          and knowledge are required!
 *
 * @license Released into the public domain.
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS 1    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI SS 2    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Stepper.h>
const int stepsPerRevolution = 510;
Stepper myStepper(stepsPerRevolution, 14, 16, 15, 17);

#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_1_PIN        53         // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2

#define NR_OF_READERS   1

byte ssPins[] = {SS_1_PIN};

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

/**
 * Initialize.
 */
void setup() {
   myStepper.setSpeed(60);
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();        // Init SPI bus

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

/**
 * Main loop.
 */
void loop() {

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {

      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);

      // Check is the PICC of Classic MIFARE type 
      if(piccType != MFRC522 :: PICC_TYPE_MIFARE_MINI &&
        piccType != MFRC522 :: PICC_TYPE_MIFARE_1K &&
        piccType != MFRC522 :: PICC_TYPE_MIFARE_4K) {
        Serial.println (F("Your tag is not of type MIFARE Classic."));
        return ;
      }
       
      String strID = "" ;
      for (byte i = 0; i < 4; i++) {
        /**strID += (mfrc522[reader].uid.uidByte[i] < 0x10 ? "0" : "") + 
        String(mfrc522[reader].uid.uidByte[i], HEX) + (i != 3 ? ":" : "");*/
        strID.concat(String(mfrc522[reader].uid.uidByte[i] < 0x10 ? " 0" : " "));
        strID.concat(String(mfrc522[reader].uid.uidByte[i], HEX));
      }
      strID.toUpperCase();

      Print(strID);

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void Print(String tagID){
    if (tagID.substring(1) == "40 1D 79 A5") 
    {
      Serial.println(tagID);
      myStepper.step(-stepsPerRevolution);
      delay(1000);
      myStepper.step(stepsPerRevolution);
    }
}
