
HX711 scale(A1, A0);    // parameter "gain" is ommited; the default value 128 is used by the library

      
int stanPracy=STOP;
String msg;
// sterowanie silnika wysypu
int walekWysiewajacy = 11;
int walekWprowadzajacy =12;


float waga;

unsigned long poczatek_okna_waga=0;
unsigned long poczatek_okna_powierzchnia=0;

byte pwm=0;
byte pwm_wprowadzajacy=0;
float szer_siewnika=2.7;

int powierzchnia_dawki;
int waga_dawki;
int wydatek=0;
unsigned int ilosc_petli=0;
byte indeks_zadania;
byte sub_indeks;

StaticJsonBuffer<128> jsonBufferSend;
StaticJsonBuffer<64> jsonBufferSendCommand;
StaticJsonBuffer<64> jsonBufferRecive;

JsonObject& rootSend = jsonBufferSend.createObject();
JsonObject& rootSendCommand = jsonBufferSendCommand.createObject();

int waga_poczatek;
byte licznik;
unsigned long poczatek_okna_mapowanie=0;
byte temp_pwm;
bool time_set;

struct MapStruct {
  byte PWM;
  unsigned int ms;
} mapa[DLUGOSC_MAPY];

byte wyd_walek_chwil;
