#include "Arduino.h"
#include "EEPROM.h"
#include "ArduIOTA_Lcd.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
  
ArduIOTA_Lcd::ArduIOTA_Lcd (byte col, byte row)  {
  this->col = col;
  this->row = row;  
  lcd.begin(col,row);
}
void ArduIOTA_Lcd::SchreibeLcd(String s, int offset, int i)
{
  lcd.setCursor(offset, i);
  lcd.print(s);
}
void ArduIOTA_Lcd::SchreibeLcdOben(String s, int offset)
{
  lcd.setCursor(offset, 0);
  lcd.print(s);
}
void ArduIOTA_Lcd::SchreibeLcdUnten(String s, int offset)
{
  lcd.setCursor(offset, 1);
  lcd.print(s);
}
