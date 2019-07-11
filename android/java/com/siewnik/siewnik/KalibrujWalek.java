package com.siewnik.siewnik;

import android.bluetooth.BluetoothSocket;
import android.widget.TextView;

import java.io.IOException;

/**
 * Created by pandejo on 09.01.2018.
 */

public class KalibrujWalek extends ArduinoEvent {

    void init(TextView t, BluetoothSocket btS){
        super.init(t,btS);

        printLine("Kalibrcja walka start");

        try
        {
            btSocket.getOutputStream().write("kw1".toString().getBytes());
        }
        catch (IOException e)
        {
//                msg("Error");
        }
    }

    void parse(String indeks,String s){
        if(indeks.equals("kw2"))
            printLine("Waga poczatkowa: "+s);

        if(indeks.equals("kw4"))
            printLine("Koniec, wydatek wałka: "+s+" gram na obrót");

//        if(indeks.equals("kw3"))
//            printLine("Obrot: "+s);
    }

    void parse(String indeks,String s1,String s2){
        if(indeks.equals("kw3"))
            printLine("Obrot: "+s1+" waga:"+s2);
    }
}
