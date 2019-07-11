/////////////////////////////////////                                          wprowadzanie      ///////////////////////  ///////////////////////  ///////////////////////  ///////////////////////  ///////////////////////

void wprowadzanie()
{
  //tarowanie
  if(commandString.startsWith("t1",0))
  {
//   Serial.println("t1");    
      stanPracy=TAROWANIE;
//      commandString.clear();
  }
  
  //kalibracja poczatek
  if(commandString.startsWith("k1",0))
  {
//   Serial.println("k1");    
      stanPracy=SKALOWANIE;
          scale.set_scale();
          scale.tare();
        rootSendCommand["c"] = "k2";           
        rootSendCommand["v"] = storage.wagaSkalowania;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#"); 
                
  }
  
  //kalibracja polozono ciezar
  if(commandString.startsWith("k4",0))
  {
          float odczyt10 = scale.get_units(10);
          storage.scaleGain = (float)odczyt10  / (float)storage.wagaSkalowania;
          scale.set_scale(storage.scaleGain);
        
          saveConfig();
        rootSendCommand["c"] = "k5";           
        rootSendCommand["v"] = storage.scaleGain;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#"); 
          
  }
  
  if(commandString.startsWith("k6",0))
  {
//   Serial.println("k6");

          scale.tare();

          storage.offset=scale.get_offset();         
          saveConfig();
        rootSendCommand["c"] = "k7";           
        rootSendCommand["v"] = storage.offset;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#"); 
         
        stanPracy=NORMAL;
  }  
  
  /////////////////////////////////////                                          //kalibracja wydatek wałka gramow siewu / obrot
  if (commandString.startsWith("kw1", 0))
  {
    //   Serial.println("k1");
    stanPracy = KALIBRACJA;
    indeks_zadania=0;
    flaga_walek=false;
  }
   /////////////////////////////////////                                          //mapowanie
  if (commandString.startsWith("m1", 0))
  {
    //   Serial.println("k1");
    stanPracy = MAPOWANIE;
    indeks_zadania=0;
    flaga_walek=false;
  }  
  /////////////////////////////////////                                          //ustawianie zmiennych
  if (commandString.startsWith("s", 0))
  {
    int comm_value=commandString.substring(2).toInt();
    
    if(commandString.startsWith("a", 1))
    {
//      Serial.print("Set a:");
      storage.a_PWM_f=(byte)comm_value;
//      Serial.println(storage.a_PWM_f);      
      saveConfig();
     }   
    if(commandString.startsWith("b", 1))
    {
      storage.b_PWM_f=(byte)comm_value;    
      saveConfig();
     }     
  
    if(commandString.startsWith("d", 1))
    {
      storage.dawka=comm_value;    
      saveConfig();
      //predkosc minimalna siewnika przy podanej dawce
      float min_pr=(((storage.gram_obrot*10000/storage.dawka)/szer_siewnika)/(mapa[0].ms*0.001))*3.6;

        rootSendCommand["c"] = "minPr";           
        rootSendCommand["v"] = min_pr;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");
        delay(START_DELAY);
        
      float max_pr=(((storage.gram_obrot*10000/storage.dawka)/szer_siewnika)/(mapa[DLUGOSC_MAPY-1].ms*0,001))*3.6;

        rootSendCommand["c"] = "max_pr";           
        rootSendCommand["v"] = max_pr;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");
        delay(START_DELAY);
      
     }   
  }    
  if (commandString.startsWith("g", 0))
  {
        rootSendCommand["c"] = "scaleGain";           
        rootSendCommand["v"] = storage.scaleGain;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");
        delay(START_DELAY);
        rootSendCommand["c"] = "offset";           
        rootSendCommand["v"] = storage.offset;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");
        delay(START_DELAY);        
        rootSendCommand["c"] = "dawka";           
        rootSendCommand["v"] = storage.dawka;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");
        delay(START_DELAY);
        rootSendCommand["c"] = "gram_obrot";           
        rootSendCommand["v"] = storage.gram_obrot;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");  
        delay(START_DELAY);           
        rootSendCommand["c"] = "a_PWM_f";           
        rootSendCommand["v"] = storage.a_PWM_f;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");  
        delay(START_DELAY);  
        rootSendCommand["c"] = "b_PWM_f";           
        rootSendCommand["v"] = storage.b_PWM_f;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");            
        delay(START_DELAY);

//wyslij tez mape PWM
//        mapa[i].PWM=temp_pwm;
//        mapa[i].ms=czas;
        rootSendCommand["c"] ="PWM";           
        rootSendCommand["v"] = "ms";      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");            
        delay(START_DELAY);
        
        for(int i=0;i<DLUGOSC_MAPY;i++)
        {
        rootSendCommand["c"] = mapa[i].PWM;           
        rootSendCommand["v"] = mapa[i].ms;      
        rootSendCommand.printTo(mySerial);
        mySerial.print("#");            
        delay(START_DELAY);        
        }
        
        stanPracy=NORMAL;
        Serial.println("Start"); 
        delay(OKNO_WAGA);
  }     
  if (commandString.startsWith("nogo", 0))
  {
        stanPracy=STOP;
        Serial.println("Stop"); 
  }    
}
