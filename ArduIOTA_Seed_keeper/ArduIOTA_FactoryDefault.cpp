#include "Arduino.h"
#include "EEPROM.h"
#include "ArduIOTA.h"
#include "ArduIOTA_FactoryDefault.h"
#include "ArduIOTA_Menu.h"

ArduIOTA_FactoryDefault::ArduIOTA_FactoryDefault (byte adresseFactoryDefault)  {
  this->adresseFactoryDefault = adresseFactoryDefault;
}

bool ArduIOTA_FactoryDefault::IfFactoryDefault() // is factory default state
{
  return (String(EEPROM.read(this->adresseFactoryDefault)) == "0");
}

void ArduIOTA_FactoryDefault::WriteFactoryDefault(byte b)
{
  EEPROM.write(this->adresseFactoryDefault, b);
}

int ArduIOTA_FactoryDefault::SetFactoryDefault()
{
  if(this->showFactoryDefault)
  {
    Serial.println();
    Serial.println("Set factory default-DELETE ALL\r\n1. Ok\r\n2. Cancel\r\n");
    this->showFactoryDefault = false;
  }
  
  Serial.setTimeout(1000L); 
  String eingabeLoeschen = Serial.readString();
  eingabeLoeschen.replace("#", "");

  if(eingabeLoeschen == "0")
  {
    this->SetFactoryDefault();
  }
  else if(eingabeLoeschen == "1")
  {
    
    return 1;
  }
  else if(eingabeLoeschen == "2")
  {
    return 2;
  }
  else
  {
    this->SetFactoryDefault();
  }
}
