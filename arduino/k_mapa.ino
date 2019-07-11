

void loadMap(){
  unsigned int t;
      for ( t = 0; t < DLUGOSC_MAPY*sizeof(MapStruct); t++)
         *((char*)&mapa + t) = EEPROM.read(sizeof(storage)+1 + t);

//    Serial.print("loaded bytes");
//    Serial.println(t);         
}
void saveMap(){
  unsigned int t;
  for ( t = 0; t < DLUGOSC_MAPY*sizeof(MapStruct); t++)
    EEPROM.write(sizeof(storage)+1 + t, *((char*)&mapa + t));  

//    Serial.print("saved bytes");
//    Serial.println(t);
    
    storage.mapSet=true;
    saveConfig();

//    Serial.print(storage.mapSet);

}

byte getPWM(unsigned int ms)
{
  int i=0;
 if(mapa[0].ms>ms)
  for(i=1;i<DLUGOSC_MAPY;i++)
  {
    if(mapa[i].ms<ms)
//        return mapa[i-1].PWM+((mapa[i].PWM-mapa[i-1].PWM)*(ms-mapa[i-1].ms)/(mapa[i].ms-mapa[i-1].ms));
        return mapa[i-1].PWM+((mapa[i].PWM-mapa[i-1].PWM)*(mapa[i-1].ms-ms)/(mapa[i-1].ms-mapa[i].ms));
  }
  
 if(i==DLUGOSC_MAPY) return 255; 
 
    return 0;  
}
