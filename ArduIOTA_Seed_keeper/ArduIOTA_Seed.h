#ifndef __ArduIOTA_SEED__
#define __ArduIOTA_SEED__

#include "Arduino.h"

class ArduIOTA_Seed {
private:
 byte adresseSeedStart;
 byte adresseSeedStop;
 byte seedLength;  

 bool showMenu;
 bool loopStart;
 bool setSeedgestartet;

public:
 ArduIOTA_Seed(byte adresseSeedStart, byte adresseSeedStop, byte seedLength);
    
 void GetSeed();
 void SetSeed();
 String ReturnSeed();
};

#endif
