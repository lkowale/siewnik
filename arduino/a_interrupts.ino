

float obwod_kola=0.38*3.14;
byte ilosc_srub=4;
unsigned long poczatek_okna_kolo;
float dystans_licznik=0;
float predkosc;
      unsigned long dt;
      float droga=obwod_kola/ilosc_srub;
 
 

volatile unsigned long licznik_kolo = 0;

unsigned long licznik_kolo_last=0;
volatile bool flaga_kolo=false;

void przerwanie_kolo() {
      flaga_kolo=true;
      dt=millis()-poczatek_okna_kolo;
}


volatile unsigned long licznik_walek = 0;
volatile unsigned long licznik_walek_last = 0;
unsigned long czas_walek = 0;
volatile bool flaga_walek=false;


void przerwanie_walek() {
  licznik_walek++;
  flaga_walek=true;
}


volatile bool flaga_walek_wprowadzajacy=false;
unsigned long czas_walek_wprowadzajacy = 0;

void przerwanie_walek_wprowadzajacy() {
  flaga_walek_wprowadzajacy=true;
}
