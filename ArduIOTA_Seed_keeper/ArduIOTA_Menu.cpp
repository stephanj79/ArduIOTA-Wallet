#include "Arduino.h"
#include "EEPROM.h"
#include "ArduIOTA_Menu.h"

ArduIOTA_Menu::ArduIOTA_Menu (bool showMenu)  {
  this->showMenu = showMenu;
}

void ArduIOTA_Menu::ShowMenu() // Show main menu
{
  //lcd.clear();
  //SchreibeLcd("Set Seed", 1, lcdOben);
  //SchreibeLcd("Get Seed", 1, lcdUnten);
  
  Serial.println("\r\nMenu\r\n1. Set seed\r\n2. Read seed\r\n3. Factory default\r\n4. Close\r\n5. Start Server\r\n_____________");
  Serial.print(">  ");
}

String ArduIOTA_Menu::MenuEingabe() // main menu choice
{
  Serial.setTimeout(1000L) ; 
  String menuEingabe = Serial.readString();
  menuEingabe.replace("#", "");
  return menuEingabe;
}
