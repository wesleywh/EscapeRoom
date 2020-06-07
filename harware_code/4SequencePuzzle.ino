/*
 * "Object placement" Puzzle
 * 
 * This puzzle requires the players to place specific rfid tags
 * in the correct locations and it will be marked as a success
 * and display a number on an LCD screen
 */

#define DEBUG
#include <SPI.h>                  //For MFRC522 RFID Reader
#include <MFRC522.h>              //For MFRC522 RFID Reader
#include <Servo.h>                //For the SG90 Servo Motor

// GLOBALS
const byte servoPin = 2;          //The pin the servo is attached to on the board
const byte numReaders = 4;        //Number of RFID Readers
const byte ssPins[] = {6,7,8,9};  //Each reader has a unique slave select pin
const byte resetPin = 10;         //All RFID readers share the reset pin
MFRC522 mfrc522[numReaders];      //Initialize array of MFRC522 instances
const String correctIDs[] = {"25918652","204712843","23117519925","21515125125"}; //The Sequence of correct IDs
String currentIDs[numReaders];    //The ID currently detected by the RFID reader
Servo servo;                      //Servo holder class

void setup() 
{ 
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println(F("Serial communication started"));
  #endif
  
  SPI.begin();                                //Initialize SPI bus
  #ifdef DEBUG
  Serial.println("Enabled SPI PINs");
  #endif
  for (uint8_t i=0; i<numReaders; i++)
  {
    mfrc522[i].PCD_Init(ssPins[i], resetPin); //Initialize all the RFID Readers
    PrintDebugInfo(mfrc522[i], i, ssPins[i]);
    delay(100); //Delay Before starting the next reader
  }
  servo.attach(servoPin);                     //Setup servo on this arduino pin
  servo.write(0);
  delay(1000);
  servo.write(90);                            //Spin servo to this angle
  #ifdef DEBUG
  Serial.println(F("--- FINISHED SETUP ---"));
  #endif
}

void PrintDebugInfo(MFRC522 rfid, int index, byte ssPin)
{
    #ifdef DEBUG
//    Serial.println(rfid.PCD_PerformSelfTest() ? "OK" : "ERROR");
    Serial.print(F("Reader #"));
    Serial.print(index);
    Serial.print(F(" initialized on pin "));
    Serial.print(String(ssPin));
    Serial.print(F(". Antenna strength: "));
    Serial.print(rfid.PCD_GetAntennaGain());
    Serial.print(F(". Version : "));
    rfid.PCD_DumpVersionToSerial();
    #endif
}

void loop() 
{
  boolean puzzleSolved = true;    //Assume puzzle is solved
  boolean changedValue = false;    //Assume tags have not changed since last reading
        
  //Loop through the readers
  for(uint8_t i=0; i<numReaders; i++)
  {
    mfrc522[i].PCD_Init();        //Initialize RFID reader sensor
    mfrc522[i].PCD_SetAntennaGain(MFRC522::PCD_RxGain::RxGain_max);  //Set RFID sensor sensitivity to maximum
    String readRFID = "";         //Value to hold detected rfid tag
    if(mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) //Is a tag present that this can read?
    {
        readRFID = GetRFIDFromTag(mfrc522[i]);
    }

    if (readRFID != currentIDs[i])      //A new tag is in this RFID sensor
    {
      changedValue = true;
      currentIDs[i] = readRFID;         //Set the new tag
    }

    if (currentIDs[i] != correctIDs[i]) //If the tag doesn't match the right one the puzzle isn't solved
    {
      puzzleSolved = false;
    }

    mfrc522[i].PICC_HaltA();            // Stop PICC
    mfrc522[i].PCD_StopCrypto1();       // Stop Encryption on PCD
  }

  if (changedValue)
  {
    for(uint8_t i=0; i<numReaders; i++)
    {
      Serial.print(F("Reader #"));
      Serial.print(String(i));
      Serial.print(F(" on Pin #"));
      Serial.print(String(ssPins[i]));
      Serial.print(F(" detected tag: "));
      Serial.println(currentIDs[i]);
    }
    Serial.println(F("----"));
  }

  if (puzzleSolved)
  {
    SolvedPuzzle();
  }
}

String GetRFIDFromTag(MFRC522 rfid)
{
  rfid.PICC_ReadCardSerial();
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  String uidString = String(rfid.uid.uidByte[0])+String(rfid.uid.uidByte[1])+String(rfid.uid.uidByte[2])+String(rfid.uid.uidByte[3]);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  return uidString;
}

void SolvedPuzzle()
{
  #ifdef DEBUG
  Serial.println(F("PUZZLE HAS BEEN SOLVED!"));
  #endif
  servo.write(0);
  while(true){}
}
