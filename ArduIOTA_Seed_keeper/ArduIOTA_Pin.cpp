#include "Arduino.h"
#include "EEPROM.h"
#include "ArduIOTA_FactoryDefault.h"
#include "ArduIOTA_Pin.h"

ArduIOTA_Pin::ArduIOTA_Pin(byte adressePinStart, byte adressePinStop, byte pinLength, byte adresseFactoryDefault)  {
 this->adressePinStart = adressePinStart;
 this->adressePinStop = adressePinStop;
 this->pinLength = pinLength;
 this->adresseFactoryDefault = adresseFactoryDefault;
}

String ArduIOTA_Pin::GetPin() // get pin from eeprom
{
  String returnPin = "";
  for (byte i = this->adressePinStart; i <= this->adressePinStop ; i++) 
  {
    char c = EEPROM.read(i);  
    returnPin += c;
  }

  return returnPin;
}

void ArduIOTA_Pin::SetPin() // Set pin to eeprom
{
  byte bufferSetPin[this->pinLength]; 
  Serial.setTimeout(60000L);
  Serial.println("Enter PIN");
  Serial.readBytesUntil('#', (char *) bufferSetPin, this->pinLength);
  String pinEingabe = String((char*) bufferSetPin);

  if(pinEingabe == "")
  {
    this->SetPin();
  }
  
  for (byte i = 0; i < this->pinLength ; i++) 
  {
    EEPROM.write(i + this->adressePinStart, bufferSetPin[i]);
  }  
}

bool ArduIOTA_Pin::VerifyPin() //verifiy the pin
{
  byte bufferUserEingabePin[this->pinLength];

  for (byte i = 0; i < this->pinLength ; i++) 
  {
    bufferUserEingabePin[i] = 0;
  }
  
  Serial.setTimeout(5000L);
  if(!this->setupStart)
  {
    Serial.println("Enter PIN");
  }
  Serial.readBytesUntil('#', (char *) bufferUserEingabePin, this->pinLength);
  String pinEingabe = (String((char*)bufferUserEingabePin)).substring(0, this->pinLength);

  if(this->GetPin() == pinEingabe)
  {
    isAuth = true;
  }
  else
  {
    isAuth = false;
  }
  
  return isAuth;
}
