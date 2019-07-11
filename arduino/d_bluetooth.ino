

char command[MAX_MESSAGE_LENGTH+1];
String commandString;


//SoftwareSerial mySerial(10, 11); // RX, TX

// Board          Transmit  Receive   PWM Unusable
// Arduino Uno        9         8         10

AltSoftSerial mySerial;//(8,9); // RX, TX

void setup_bluetooth() {
  mySerial.begin(9600);
  commandString="";
}

bool recive_bluetooth()
{
  if (mySerial.available()) 
  {
   int t=0;
    while(mySerial.available()&&t<MAX_MESSAGE_LENGTH) {
      *(((char*)command + t))=mySerial.read();
      delay(2);
      t++;
    }
    *(((char*)command + t))=0; //end of char string
      commandString= String(command);  
//      mySerial.print(string);   //send back what i've recived     
    Serial.println(commandString);
    return true;
  }
  else
    return false;
}



