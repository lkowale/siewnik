#include <hx711.h>

#include <EEPROM.h>
//#include <EnableInterrupt.h>

#include <PinChangeInt.h>

#include <ArduinoJson.h>
//#include <hx711_RAR.h>
//#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
#include <MemoryFree.h>
 
#define OKNO_KOLO 1000
#define OKNO_WAGA 500
#define OKNO_KALIBRACJA 30000
#define OKNO_POWIERZCHNIA 100 
#define OKNO_WYSLIJ 1000
#define START_DELAY 50

//stan pracy
#define NORMAL 0
#define KALIBRACJA 1
#define TAROWANIE 2
#define MAPOWANIE 3
#define SKALOWANIE 4
#define STOP 5

#define MAX_MESSAGE_LENGTH 64

#define PIN_KOLO A2   //pin kola pomiaru predkosci
#define PIN_WALEK A3  //pin zlicznia obrotow walka wysiewajacego
#define PIN_WPROWADZAJACY A4 //pin zlicznia obrotow walka wprowadzajacego

#define DLUGOSC_MAPY 10
