package com.siewnik.siewnik;

import android.bluetooth.BluetoothSocket;
import android.widget.TextView;

import java.io.IOException;

/**
 * Created by pandejo on 05.01.2018.
 */

public class Kalibruj extends ArduinoEvent {

    void init(TextView t, BluetoothSocket btS){
        super.init(t,btS);

        printLine("Kalibrcja start");

        try
        {
            btSocket.getOutputStream().write("k1".toString().getBytes());
        }
        catch (IOException e)
        {
//                msg("Error");
        }
    }

    void parse(String indeks,String s){
        if(indeks.equals("k2"))
            printLine("Postaw na wagę: "+s+"[g] i wyslij ok");
        if(indeks.equals("k3"))
        {
            try
            {
                btSocket.getOutputStream().write("k4".toString().getBytes());
            }
            catch (IOException e)
            {
//                msg("Error");
            }
        }

        if(indeks.equals("k5"))
            printLine("Przeskalowano, wsp.wagi: "+s+" zdejmij cieżar i wyslij kk");

        if(indeks.equals("k6"))
            try
            {
                btSocket.getOutputStream().write("k6".toString().getBytes());
            }
            catch (IOException e)
            {
//                msg("Error");
            }
        if(indeks.equals("k7"))
            printLine("Wytarowano wagę, offset: "+s);
    }
}
