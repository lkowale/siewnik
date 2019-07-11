  void tarowanie(){
    Serial.println("rozp tarowanie");
          scale.tare();
          storage.offset=scale.get_offset();
          saveConfig();
        //wyslij offset
        rootSendCommand["c"] = "t2";
        rootSendCommand["v"] = scale.get_offset();    
        rootSendCommand.printTo(mySerial);
        mySerial.print("#"); 
        
        rootSendCommand.remove("t2");
        stanPracy=NORMAL;
  }

