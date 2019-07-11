void setup() {

    setup_bluetooth(); 
  
    loadConfig();
    if(storage.mapSet) loadMap();
      
  scale.set_scale(storage.scaleGain);
  scale.set_offset(storage.offset); 
  poczatek_okna_kolo=millis();  
  poczatek_okna_waga=millis();
  czas_walek_wprowadzajacy=millis();
  czas_walek=millis();  

    pinMode(walekWprowadzajacy, OUTPUT); 
    digitalWrite(walekWprowadzajacy, LOW);    
  
  Serial.begin(9600); 

Serial.println(getPWM(8000));
Serial.println(getPWM(7000));
Serial.println(getPWM(6000));
Serial.println(getPWM(5000));
Serial.println(getPWM(4000));
Serial.println(getPWM(3000));
Serial.println(getPWM(2000));
Serial.println(getPWM(1000));
Serial.println(getPWM(500));
Serial.println();
Serial.println(getPWM(8962));
Serial.println(getPWM(5595));
Serial.println(getPWM(4054));
Serial.println(getPWM(3200));
Serial.println(getPWM(2652));
Serial.println(getPWM(2327));
Serial.println(getPWM(1552));
Serial.println(getPWM(1553));
Serial.println(getPWM(1554));
//  attachPinChangeInterrupt(ARDUINOPIN, interruptFunction, FALLING);
//  enableInterrupt(PIN_KOLO, przerwanie_kolo, RISING);  
//  enableInterrupt(PIN_WALEK, przerwanie_walek, RISING);    
//  enableInterrupt(PIN_WPROWADZAJACY, przerwanie_walek_wprowadzajacy, RISING);    

  attachPinChangeInterrupt(PIN_KOLO, przerwanie_kolo, RISING);  
  attachPinChangeInterrupt(PIN_WALEK, przerwanie_walek, RISING);    
  attachPinChangeInterrupt(PIN_WPROWADZAJACY, przerwanie_walek_wprowadzajacy, RISING);   
  
  delay(100);   
}


