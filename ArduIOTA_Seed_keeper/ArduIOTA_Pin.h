#ifndef __ArduIOTA_PIN__
#define __ArduIOTA_PIN__

#include "Arduino.h"

class ArduIOTA_Pin {
private:

 byte adressePinStart;
 byte adressePinStop;
 byte pinLength;
 byte adresseFactoryDefault;

public:
  ArduIOTA_Pin(byte adressePinStart, byte adressePinStop, byte pinLength, byte adresseFactoryDefault);

 bool isAuth;
  bool setupStart;
    
  String GetPin();
  void SetPin();
  bool VerifyPin();
};

#endif
