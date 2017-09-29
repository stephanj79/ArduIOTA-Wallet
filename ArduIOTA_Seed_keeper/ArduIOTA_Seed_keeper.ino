#include <Ethernet.h>
#include <SD.h>
#include <EEPROM.h>
#include "ArduIOTA.h"
#include "ArduIOTA_Menu.h"
#include "ArduIOTA_Pin.h"
#include "ArduIOTA_Seed.h"
#include "ArduIOTA_FactoryDefault.h"
//#include "ArduIOTA_Lcd.h"


/*
 * ArduIOTA Seedkeeper
 * 
 * By Stephan Jäger
 * 
 * Adresse0 > if facotrydefault true = 1, otherwise 0
 * Adresse1 to Adresse4 > pin to access
 * Adresse5 to Adresse86 > Seed
 * 
 * Use on your own risk!!!
 * 
 */

// _______________________________________________________________________________________________________________________________________________________________PROP 
const byte factoryLength          = 1;
const byte pinLength              = 4;
const byte seedLength             = 81; 

const byte adresseFactoryDefault  = 0;
const byte adressePinStart        = adresseFactoryDefault + factoryLength;
const byte adressePinStop         = pinLength;
const byte adresseSeedStart       = adressePinStart + pinLength;
const byte adresseSeedStop        = adresseSeedStart + seedLength;

ArduIOTA                            arduIota(500);
ArduIOTA_FactoryDefault             factoryDefault(adresseFactoryDefault);
ArduIOTA_Menu                       menu(true);
ArduIOTA_Pin                        pin(adressePinStart, adressePinStop,pinLength, adresseFactoryDefault);
ArduIOTA_Seed                       seed(adresseSeedStart, adresseSeedStop, seedLength);
//ArduIOTA_Lcd                        displayLcd(16, 2);

byte mac[] = { 0x5A, 0xA2, 0xDA, 0x0D, 0x56, 0x7A }; // MAC-Adresse des Ethernet-Shield
byte ip[]  = { 192, 168, 0, 177 };                   // IP zum aufrufen des Webservers
EthernetServer server(80);
File webFile;               // the web page file on the SD card

bool webserverstartet = false;
bool clientConnected = false;

void ServerGo(){
  if(!webserverstartet)
  {
    Serial.println("5");
    Serial.println();
    Serial.println("Server startet "+String(ip[0])+"."+String(ip[1])+"."+String(ip[2])+"."+String(ip[3]));
    webserverstartet = true;
  }
  EthernetClient client = server.available();
  if (client) 
  {
    if(!clientConnected)
    {
      Serial.println("Client connected");
      clientConnected = true;
    }
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {  
        char c = client.read();        
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          
          webFile = SD.open("1index.htm");        // open web page file
          if (webFile) {
            while(webFile.available()) {
            client.write(webFile.read()); // send web page to client
            }
            webFile.close();
          }  
          client.print(seed.ReturnSeed());
          webFile = SD.open("2index.htm");        // open web page file
          if (webFile) {
            while(webFile.available()) {
            client.write(webFile.read()); // send web page to client
            }
            webFile.close();
          }
          break;
        }
        if (c == '\n') {
        currentLineIsBlank = true;
        } 
        else if (c != '\r') {
        currentLineIsBlank = false;
        }
      }
    }
    delay(1);
    client.stop();
  }

  delay(1000);
  ServerGo();
}
// _______________________________________________________________________________________________________________________________________________________________SETUP
void setup() {
  Serial.flush();
  Serial.begin(9600);
  Serial.println("arduIOTA Seed Keeper");
  while (!Serial) {
    return; 
  }
  if(factoryDefault.IfFactoryDefault())
  {
    Serial.println("Setup PIN");  
    pin.SetPin(); 
    factoryDefault.WriteFactoryDefault(1);
    pin.isAuth = false;
    arduIota.software_Reset(); 
  }  
  if(!pin.VerifyPin() && !pin.isAuth)
  {
    pin.setupStart = true;
    pin.isAuth = false;
    arduIota.software_Reset(); 
  }

  Ethernet.begin(mac, ip);  // initialize Ethernet device
  server.begin();           // start to listen for clients

  if (!SD.begin(4)) {
    Serial.println("ERROR-SD");
    return;
  }
  if (!SD.exists("1index.htm")) {
    Serial.println("Can't find files!");
    return;
  }
}

// _______________________________________________________________________________________________________________________________________________________________LOOP
void loop() {
  String menuEingabe = ""; // menu entry
   
  while(menu.showMenu)
  {
    if(!menu.loopStart)
    {
      menu.ShowMenu();
      menu.loopStart = true;  
    }

    menuEingabe = menu.MenuEingabe();
    
    if(menuEingabe == "")
    {
      return;
    }
    
    if(menuEingabe == "1")
    {
      seed.SetSeed();
      menu.showMenu = true;
      menu.ShowMenu();
      menu.loopStart = true; 
    }
    
    if(menuEingabe == "2")
    {
      seed.GetSeed();
      menu.showMenu = true;
      menu.ShowMenu();
      menu.loopStart = true;  
    } 
     
    if(menuEingabe == "3")
    {
      factoryDefault.showFactoryDefault = true;
      int i = factoryDefault.SetFactoryDefault();
      if(i==1)
      {
        menu.showMenu = true;
        menu.ShowMenu();
      }
      else if(i==2)
      {
        Serial.println("Format arduIOTA");       
        arduIota.FormatArduIota();      
        factoryDefault.WriteFactoryDefault(0);
        Serial.println("\r\nsuccessful!\r\nreboot...\r\n");
        Serial.flush();
        pin.isAuth = false;
        arduIota.software_Reset();
      }
    }  
    
    if(menuEingabe == "4")
    {
      Serial.flush();
      Serial.println();
      pin.isAuth = false;
      arduIota.software_Reset();
    }  
    if(menuEingabe == "5")
    {
      ServerGo();     
    }    
  }
}
