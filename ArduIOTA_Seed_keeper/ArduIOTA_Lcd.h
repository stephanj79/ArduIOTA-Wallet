#ifndef __ArduIOTA_LCD__
#define __ArduIOTA_LCD__

#include <LiquidCrystal.h>

class ArduIOTA_Lcd {
private:
byte col;
byte row;

public:
 ArduIOTA_Lcd (byte col, byte row);

 void SchreibeLcd(String s, int offset, int i);
 void SchreibeLcdOben(String s, int offset);
 void SchreibeLcdUnten(String s, int offset);
};

#endif
