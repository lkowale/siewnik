package com.siewnik.siewnik;

import android.bluetooth.BluetoothSocket;
import android.widget.TextView;

import java.io.IOException;

/**
 * Created by pandejo on 05.01.2018.
 */

public class ArduinoEvent {

    int indeks;
    TextView tv;
    BluetoothSocket btSocket = null;

    void init(TextView t, BluetoothSocket btS){
        btSocket=btS;
        tv=t;
        tv.setText("");
    }

    void printLine(String line){
        tv.append(line);
        tv.append(System.getProperty("line.separator"));
    }

    void parse(String indeks,String s){
        printLine(s);
    }
    void parse(String indeks,String s1,String s2){
    }

}
