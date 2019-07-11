package com.siewnik.siewnik;

import android.bluetooth.BluetoothSocket;
import android.widget.TextView;

import org.json.JSONObject;

import java.io.IOException;

/**
 * Created by pandejo on 05.01.2018.
 */

public class TarujWage extends ArduinoEvent{
    int indeks;


void TarujWage(){indeks=1;}

void init(TextView t,BluetoothSocket btS){
    super.init(t,btS);

    printLine("Tarowanie start");

            try
            {
                btSocket.getOutputStream().write("t1".toString().getBytes());
            }
            catch (IOException e)
            {
//                msg("Error");
            }
    }

    @Override
    void parse(String indeks,String s)
    {
       printLine("Wytarowano, offset: "+s);
    }
}
