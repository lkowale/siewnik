// ID of the settings block
#define CONFIG_VERSION "ks1"
// Tell it where to store your config data in EEPROM
#define CONFIG_START 0

//wspolczynniki funkcji obliczania pwm=a*dawka_na_sek+b
//#define a_PWM_f 30
//#define b_PWM_f 30

// Example settings structure
struct StoreStruct {
  // This is for mere detection if they are your settings
  char version[4];
  // The variables of your settings
  float scaleGain;
  long offset;
  int wagaSkalowania;
  int dawka;
  float gram_obrot;
  byte a_PWM_f;
  byte b_PWM_f;  
  bool mapSet;
  } storage = {
  CONFIG_VERSION,
  // The default values
  214.f,8000,5000,2000,8.f,30,30,false
};

void loadConfig() {
  // To make sure there are settings, and they are YOURS!
  // If nothing is found it will use the default settings.
  if (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
  EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
  EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2])
  for (unsigned int t=0; t<sizeof(storage); t++)
  *((char*)&storage + t) = EEPROM.read(CONFIG_START + t);
}

void saveConfig() {
  for (unsigned int t=0; t<sizeof(storage); t++)
  EEPROM.write(CONFIG_START + t, *((char*)&storage + t));
}

