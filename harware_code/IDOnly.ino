#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

int code[] = {32,154,149,117}; //This is the stored UID (Unlock Card)
int codeRead = 0;
String uidString;
void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  Serial.println(F("START READING"));
}

void loop() {
  if(  rfid.PICC_IsNewCardPresent())
  {
      readRFID();
  }
  delay(100);
}

void readRFID()
{
  rfid.PICC_ReadCardSerial();
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  uidString = String(rfid.uid.uidByte[0])+String(rfid.uid.uidByte[1])+String(rfid.uid.uidByte[2])+String(rfid.uid.uidByte[3]);
  Serial.println(uidString);
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
