void loop() {
   
if(stanPracy==NORMAL)
  loop_normal();
  
if(stanPracy==TAROWANIE)
  tarowanie(); 

if(stanPracy==KALIBRACJA)
  kalibracja();

if(stanPracy==MAPOWANIE)
  mapowanie();  
  
//jesli cos przyszlo przetworz to
if(recive_bluetooth())
    wprowadzanie();
    
  ilosc_petli++;
}
