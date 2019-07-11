void kalibracja(){
    if(indeks_zadania==0)
  {
    //krec walkiem az ustawi sie na czujniku
      analogWrite(walekWysiewajacy,200);    
//      param+=flaga_walek;
//      param+=" indeks_zadania:";
//      param+=indeks_zadania;
//      Serial.println(param);
    if(flaga_walek){
      flaga_walek=false; 
      indeks_zadania=1;
      analogWrite(walekWysiewajacy,0);      
    }
  }
      
  if(indeks_zadania==1)
  { 
    waga_poczatek=scale.get_units(4);
        rootSendCommand["c"] = "kw2";           
        rootSendCommand["v"] = waga_poczatek;              
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");      
//        param=String(waga_poczatek);
//    sendCommand("kw2",param);
    licznik_walek=0;       
    
//      String param="flaga_walek:";
//      param+=flaga_walek;
//      param+=" indeks_zadania:";
//      param+=indeks_zadania;
//      Serial.println(param);    
      
    indeks_zadania=2;  
    analogWrite(walekWysiewajacy,200);    
  }
  
  if(indeks_zadania==2)
  { 
     if(flaga_walek)    
      if(licznik_walek<10){

//        Serial.println(licznik);        
        flaga_walek=false;
        rootSendCommand["c"] = "kw3";           
        rootSendCommand["v"] = licznik_walek;      
        rootSendCommand["v1"] = (int)scale.get_units(4);          
        rootSendCommand.printTo(mySerial);
        mySerial.print("#"); 
                
//{"comm":"kw2","val":"-12"}        
//        param="{\"comm\":\"kw3\",\"val\":\"";
//        param+=String(licznik);
//        param+=licznik;
//        param+="\"}#";
//        mySerial.print(param);        
        
//        sendCommand("kw3",param);    
//        param=licznik;
//        param1=String((int)scale.get_units(4));
//      sendCommand2("kw3",String(licznik),String((int)scale.get_units(4)));              

      }
      else
      if(licznik_walek==10)
          {
            analogWrite(walekWysiewajacy,0);    
            int waga_10=waga_poczatek-scale.get_units(4);
            storage.gram_obrot=(float)waga_10/10.0;
            saveConfig();
//            sendCommand("kw4",String(storage.gram_obrot));  
        rootSendCommand["c"] = "kw4";           
        rootSendCommand["v"] = storage.gram_obrot;              
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");            
            stanPracy = NORMAL;
          }
      
  }  
}

void mapowanie(){
      if(indeks_zadania==0)
  {
    //krec walkiem az ustawi sie na czujniku
      analogWrite(walekWysiewajacy,200);    
    if(flaga_walek){
      flaga_walek=false; 
      indeks_zadania=1;
      analogWrite(walekWysiewajacy,0);    
      licznik_walek=0;
      sub_indeks=0;
      time_set=false;
    }
  }
  
  if(indeks_zadania==1)
  { 
    if(!time_set){
        temp_pwm=60+(sub_indeks*20);
        poczatek_okna_mapowanie=millis();
        analogWrite(walekWysiewajacy,temp_pwm);  
        time_set=true;
    }
    else
    if(flaga_walek){
      flaga_walek=false;  
      analogWrite(walekWysiewajacy,0);         
      long czas=millis()-poczatek_okna_mapowanie;
      
//        String param=" millis:";
//        param+=millis();
//        param+=" poczatek_okna_mapowanie:";
//        param+=poczatek_okna_mapowanie;
//        param+=" czas:";
//        param+=czas;        
//        Serial.println(param);   
             
        rootSendCommand["c"] = "m2";           
        rootSendCommand["v"] = temp_pwm;      
        rootSendCommand["v1"] = czas;          
        rootSendCommand.printTo(mySerial);
//        rootSendCommand.printTo(Serial);        
        mySerial.print("#");      
//zapisz do mapy
        mapa[sub_indeks].PWM=temp_pwm;
        mapa[sub_indeks].ms=czas;
        sub_indeks++;
        time_set=false;
      if(temp_pwm==240)     
          indeks_zadania=2;
    }
  }  
  
  if(indeks_zadania==2)
  { 
      saveMap();
      storage.mapSet=true;
      saveConfig();
      stanPracy = NORMAL;
 }
}
