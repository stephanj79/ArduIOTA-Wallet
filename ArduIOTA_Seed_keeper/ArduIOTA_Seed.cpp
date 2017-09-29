#include "Arduino.h"
#include "EEPROM.h"
#include "ArduIOTA_Seed.h"
#include "ArduIOTA_Menu.h"

ArduIOTA_Seed::ArduIOTA_Seed (byte adresseSeedStart, byte adresseSeedStop, byte seedLength)  {
  this->adresseSeedStart = adresseSeedStart;
  this->adresseSeedStop = adresseSeedStop;
  this->seedLength = seedLength;
}

String ArduIOTA_Seed::ReturnSeed() // get the seed
{
  String returnSeed = "";
  
  for (byte i = this->adresseSeedStart; i <= this->adresseSeedStop ; i++) 
  {
    char c = EEPROM.read(i);  
    returnSeed += c;
  }
  
  String r = returnSeed.substring(0,returnSeed.length()-1 );
  return r;
}

void ArduIOTA_Seed::GetSeed() // get the seed
{
  String returnSeed = "";
  
  for (byte i = this->adresseSeedStart; i <= this->adresseSeedStop ; i++) 
  {
    char c = EEPROM.read(i);  
    returnSeed += c;
  }

  Serial.println();
  Serial.println("Seed: ");
  Serial.print(returnSeed);
  Serial.println();
  return;
}

void ArduIOTA_Seed::SetSeed() // Set Seed
{
  String seedEingabe = "";
  byte bufferSetPin[this->seedLength];
  
  for (byte i = 0; i < this->seedLength ; i++) 
  {
    bufferSetPin[i] = 0;
  }
  
  Serial.setTimeout(60000L);
  if(!setSeedgestartet)
  {
    Serial.println();
    Serial.println("Enter seed (end with #)");
    setSeedgestartet = true;
  }
  Serial.readBytesUntil('#', (char *) bufferSetPin, this->seedLength);
  
  seedEingabe = (String((char*)bufferSetPin)).substring(0,this->seedLength);

  if(seedEingabe == "")
  {
    SetSeed();
  }

  for (byte i = 0; i < this->seedLength ; i++) 
  {
    EEPROM.write(i + this->adresseSeedStart, bufferSetPin[i]);
    delay(1);
    Serial.print("write " + String(i * 100 / this->seedLength));
    Serial.println("%");
  }  

  Serial.print("write 100%");

  String returnSeed = "";
  for (byte i = this->adresseSeedStart; i <= this->adresseSeedStop ; i++) 
  {
    char c = EEPROM.read(i);  
    returnSeed+=  c;
  }
  
  Serial.println();
  Serial.println("success.");

  Serial.println("Seed: ");
  Serial.print(returnSeed);
  
  this->setSeedgestartet = false; 
  return;
}

