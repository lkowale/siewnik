void loop_normal()
{ 
//  unsigned long czas=millis();
  
      if(flaga_kolo)
    {
      dystans_licznik+=droga;
      predkosc=3600*droga/(float)dt;
//      Serial.print("dt");      
//      Serial.print(dt);
//      Serial.print(" droga");      
//      Serial.print(droga);
//      Serial.print(" predkosc");      
//      Serial.print(predkosc);
          float powierzchnia=droga*szer_siewnika;
//              0,8054      =0,2983*2,7
          float dawka_powierzchnie=(float)storage.dawka/10000*powierzchnia;
//    dawka 8kg/ha          0,6443= 8000/10000 * 0,8054
//    dawka 16kg/ha         1,2886= 16000/10000 * 0,8054
          float dawka_msekunde=dawka_powierzchnie/(float)dt;
//                    0,00298=0,6443  / 216[ms]
//                    5,96=1,2886  / 216[ms]
          float obrot_czas=storage.gram_obrot/dawka_msekunde;
//                3053=9,1/0,00298
      
      
          pwm=getPWM(obrot_czas);


//      Serial.print(" dawka_powierzchnie");      
//      Serial.print(dawka_powierzchnie);
//      Serial.print("dt");      
//      Serial.print(dt);  
//      Serial.print("dawka_sekunde");      
//      Serial.print(dawka_sekunde);   
//      Serial.print("obrot_czas");      
//      Serial.print(obrot_czas);               
//      Serial.print("storage.gram_obrot");      
//      Serial.print(storage.gram_obrot);      
//      Serial.print(" obrot_czas");      
//      Serial.print(obrot_czas);
//      Serial.print(" pwm");      
//      Serial.println(pwm);      
          
      licznik_kolo_last=licznik_kolo;
      poczatek_okna_kolo = millis();
      flaga_kolo=false;
//      Serial.print(predkosc);
      analogWrite(walekWysiewajacy,pwm);
      digitalWrite(walekWprowadzajacy,HIGH); 
    }  
   //    jesli w czasie OKNO_KOLO nie przyszlo nowe przerwanie -> kolo zatrzymane
   if (poczatek_okna_kolo + OKNO_KOLO < millis()){
      predkosc=0;
           digitalWrite(walekWprowadzajacy,LOW);  
           analogWrite(walekWysiewajacy,0);
   }

   if(flaga_walek)
   {
    flaga_walek=false;
    czas_walek=millis();
   }

   if(flaga_walek_wprowadzajacy)
   {
    flaga_walek_wprowadzajacy=false;
    czas_walek_wprowadzajacy=millis();
   } 

   //policz wydatek chwilowy
    int pow_zasiana=szer_siewnika*dystans_licznik;   
   if(pow_zasiana-poczatek_okna_powierzchnia > OKNO_POWIERZCHNIA)
   {
    wydatek=100*(waga_dawki-waga);
    waga_dawki=waga;
    poczatek_okna_powierzchnia=pow_zasiana;
    wyd_walek_chwil=waga/(licznik_walek-licznik_walek_last);
    licznik_walek_last=licznik_walek;
//     Serial.print("pow_zasiana ");      
//      Serial.print(pow_zasiana);
//      Serial.print(" wydatek");      
//      Serial.print(wydatek);
//      Serial.print(" waga_dawki");      
//      Serial.println(waga_dawki);
//      Serial.print(" pwm");      
//      Serial.println(pwm);          
   }
   // pobierz dane z wagi
   if (poczatek_okna_waga + OKNO_WAGA < millis()){
         waga=scale.get_units(4);
         poczatek_okna_waga=millis();
        rootSend["il_petli"] =ilosc_petli; 
        rootSend["waga"] = (int)waga;
        rootSend["pamiec"] = freeMemory();   
        rootSend["PWM"] = pwm;   
        rootSend["Predkosc"] = (int)predkosc; 
        rootSend["Droga"] =(int)dystans_licznik;   
        rootSend["Pow_zasiana"] =(int)pow_zasiana;  
        rootSend["Wyd_chwil"] =(int)wydatek;  
        rootSend["Wal_chwil"] =wyd_walek_chwil;          
        rootSend["Wal_wys"] =(millis()-czas_walek);  
        rootSend["Wal_wprow"] =(millis()-czas_walek_wprowadzajacy); 
                
        rootSend.printTo(mySerial);
        mySerial.print("#"); 
//        rootSend.printTo(Serial);           
         ilosc_petli=0;      
   }
          
   
}

