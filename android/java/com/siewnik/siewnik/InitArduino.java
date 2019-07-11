package com.siewnik.siewnik;

import android.bluetooth.BluetoothSocket;
import android.widget.TextView;

import java.io.IOException;

/**
 * Created by pandejo on 16.01.2018.
 */

public class InitArduino extends ArduinoEvent {

    void init(TextView t, BluetoothSocket btS){
        super.init(t,btS);

        printLine("łacze...");

        try
        {
            btSocket.getOutputStream().write("g".toString().getBytes());
        }
        catch (IOException e)
        {
//                msg("Error");
        }
    }

    @Override
    void parse(String indeks,String s)
    {
        printLine(indeks+":"+s);
    }
}
