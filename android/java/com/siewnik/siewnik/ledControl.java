package com.siewnik.siewnik;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.media.MediaScannerConnection;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.UUID;


public class ledControl extends ActionBarActivity {

    Button btnOk,btnDis;

    TextView textV;
    EditText editT;
    ArduinoEvent activeEvent;
//    TextFragment activeFragment;
    String address = null;
    private ProgressDialog progress;

    private ListView lv;
    ArrayList<User> contactList;
    UsersAdapter adapter;

    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    //SPP UUID. Look for it
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private ConnectedThread mConnectedThread;
    private int mState;
    private static final String TAG = "MainActivity";

    // Constants that indicate the current connection state
    public static final int STATE_NONE = 0;       // we're doing nothing
    public static final int STATE_LISTEN = 1;     // now listening for incoming connections
    public static final int STATE_CONNECTING = 2; // now initiating an outgoing connection
    public static final int STATE_CONNECTED = 3;  // now connected to a remote device

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Intent newint = getIntent();
        address = newint.getStringExtra(com.siewnik.siewnik.DeviceList.EXTRA_ADDRESS); //receive the address of the bluetooth device

        //view of the ledControl
        setContentView(R.layout.activity_led_control);

        //call the widgtes
//        btnOn = (Button)findViewById(R.id.button2);
        btnOk = (Button)findViewById(R.id.button3);
        btnDis = (Button)findViewById(R.id.button4);
//        brightness = (SeekBar)findViewById(R.id.seekBar);
        textV = (TextView)findViewById(R.id.textView2);
        editT= (EditText)findViewById(R.id.editText);



        new ConnectBT().execute(); //Call the class to connect


        btnOk.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                enterCommand();      //method to turn on
            }
        });
//
//        btnOff.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View v)
//            {
//                turnOffLed();   //method to turn off
//            }
//        });
//
        btnDis.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Disconnect(); //close connection
            }
        });


        contactList = new ArrayList<User>();




        adapter = new UsersAdapter(this, contactList);
        lv = (ListView) findViewById(R.id.listview1);
        lv.setAdapter(adapter);
        activeEvent=new ArduinoEvent();
        activeEvent.init(textV,btSocket);


        }

    @Override
    protected void onDestroy() {

        try
        {
            btSocket.getOutputStream().write("nogo".getBytes());
        }
        catch (IOException e)
        {
//                msg("Error");
        }

        super.onDestroy();
    }

    private void Disconnect()
    {
        if (btSocket!=null) //If the btSocket is busy
        {
            try
            {
                btSocket.getOutputStream().write("nogo".getBytes());
                btSocket.close(); //close connection
            }
            catch (IOException e)
            { msg("Error");}
        }
        finish(); //return to the first layout

    }

//    private void turnOffLed()
//    {
//        if (btSocket!=null)
//        {
//            try
//            {
//                btSocket.getOutputStream().write("tf".toString().getBytes());
//            }
//            catch (IOException e)
//            {
//                msg("Error");
//            }
//        }
//    }

    private void enterCommand()
    {

        String input = editT.getText().toString();
        editT.setText("");

        if(input.startsWith("taruj")) {
            activeEvent = new TarujWage();
            activeEvent.init(textV,btSocket);
        }

        if(input.startsWith("kalibruj")) {
            activeEvent = new Kalibruj();
            activeEvent.init(textV,btSocket);
        }
        if(input.startsWith("ok")){
            activeEvent.parse("k3","k3");
        }
        if(input.startsWith("kk")){
            activeEvent.parse("k6","k6");
        }
        if(input.startsWith("kalwal")) {
            activeEvent = new KalibrujWalek();
            activeEvent.init(textV,btSocket);
        }
        if(input.startsWith("map")) {
            activeEvent = new Mapowanie();
            activeEvent.init(textV,btSocket);
        }
        if(input.startsWith("s")) {
            try
            {
                btSocket.getOutputStream().write(input.getBytes());
            }
            catch (IOException e)
            {
//                msg("Error");
            }
        }

        if(input.startsWith("g")) {
            activeEvent = new InitArduino();
            activeEvent.init(textV,btSocket);
        }

        if(input.startsWith("nogo")) {
            try {
                btSocket.getOutputStream().write("nogo".getBytes());
            } catch (IOException e) {
//                msg("Error");
            }
        }
    //        if (btSocket!=null)
//        {
//            try
//            {
////          przetraw komende
//
//                btSocket.getOutputStream().write("{\"dawka\":\"8000\"}".toString().getBytes());
//            }
//            catch (IOException e)
//            {
//                msg("Error");
//            }
//        }
    }

    // fast way to call Toast
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_led_control, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true; //if it's here, it's almost connected

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(ledControl.this, "Connecting...", "Please wait!!!");  //show a progress dialog
        }

        @Override
        protected Void doInBackground(Void... devices) //while the progress dialog is shown, the connection is done in background
        {
            try
            {
                if (btSocket == null || !isBtConnected)
                {
                 myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                 BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//connects to the device's address and checks if it's available
                 btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
                 BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                 btSocket.connect();//start connection
                    // Start the thread to manage the connection and perform transmissions
                    mConnectedThread = new ConnectedThread(btSocket);
                    mConnectedThread.start();
                }
            }
            catch (IOException e)
            {
                ConnectSuccess = false;//if the try failed, you can check the exception here
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result) //after the doInBackground, it checks if everything went fine
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Connection Failed. Is it a SPP Bluetooth? Try again.");
                finish();
            }
            else
            {
                msg("Connected.");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }


private class ConnectedThread extends Thread {
    private final BluetoothSocket mmSocket;
    private final InputStream mmInStream;
    private final OutputStream mmOutStream;

    public ConnectedThread(BluetoothSocket socket) {

        mmSocket = socket;
        InputStream tmpIn = null;
        OutputStream tmpOut = null;

        // Get the BluetoothSocket input and output streams
        try {
            tmpIn = socket.getInputStream();
            tmpOut = socket.getOutputStream();
        } catch (IOException e) {

        }

        mmInStream = tmpIn;
        mmOutStream = tmpOut;
        mState = STATE_CONNECTED;
    }

    public void run() {

        byte[] buffer = new byte[1024];
        byte[] toSend = new byte [1024];
        int bytes=0,begin=0;

        // Keep listening to the InputStream while connected
        while (mState == STATE_CONNECTED) {
            try {
                bytes += mmInStream.read(buffer, bytes, buffer.length - bytes);
                for(int i = begin; i < bytes; i++) {
                    if (buffer[i] == "#".getBytes()[0]) {
                        System.arraycopy(buffer, begin, toSend, 0,i-begin);
                        // mHandler.obtainMessage(1, begin, i, buffer).sendToTarget();
//                        String s = new String(buffer,begin,i-begin);
                       mHandler.obtainMessage(Constants.MESSAGE_READ, i-begin, -1, toSend)
                                .sendToTarget();

//                        response.setText(buffer, begin, i-begin);

                        begin = i + 1;
                        if (i == bytes - 1) {
                            bytes = 0;
                            begin = 0;
                        }
                    }
                }
//                    // Read from the InputStream
//                    bytes = mmInStream.read(buffer);
//
//                    // Send the obtained bytes to the UI Activity
//                    mHandler.obtainMessage(Constants.MESSAGE_READ, bytes, -1, buffer)
//                            .sendToTarget();
            } catch (IOException e) {

//                connectionLost();
                break;
            }
        }
    }

    /**
     * Write to the connected OutStream.
     *
     * @param buffer The bytes to write
     */
    public void write(byte[] buffer) {
        try {
            mmOutStream.write(buffer);

        } catch (IOException e) {

        }
    }

    public void cancel() {
        try {
            mmSocket.close();
        } catch (IOException e) {

        }
    }
}
    /**
     * The Handler that gets information back from the BluetoothChatService
     */
    private final Handler mHandler = new Handler() {
        JSONObject json;
        @Override
        public void handleMessage(Message msg) {
//            FragmentActivity activity = getActivity();
            switch (msg.what) {
//                case Constants.MESSAGE_STATE_CHANGE:
//                    switch (msg.arg1) {
//                        case BluetoothChatService.STATE_CONNECTED:
//                            setStatus(getString(R.string.title_connected_to, mConnectedDeviceName));
//                            mConversationArrayAdapter.clear();
//                            break;
//                        case BluetoothChatService.STATE_CONNECTING:
//                            setStatus(R.string.title_connecting);
//                            break;
//                        case BluetoothChatService.STATE_LISTEN:
//                        case BluetoothChatService.STATE_NONE:
//                            setStatus(R.string.title_not_connected);
//                            break;
//                    }
//                    break;
//                case Constants.MESSAGE_WRITE:
//                    byte[] writeBuf = (byte[]) msg.obj;
//                    // construct a string from the buffer
//                    String writeMessage = new String(writeBuf);
//                    mConversationArrayAdapter.add("Me:  " + writeMessage);
//
//                    break;
                case Constants.MESSAGE_READ:
                    byte[] readBuf = (byte[]) msg.obj;
                    // construct a string from the valid bytes in the buffer
                    String readMessage = new String(readBuf, 0, msg.arg1);
//                    response.setText(readMessage);
                        contactList.clear();
                    try{
//                        JSONObject json =new JSONObject("{\"waga\":\"3222\",\"dystans\":\"3223\",\"predkosc\":\"15.7\"}#");
                        JSONObject json =new JSONObject(readMessage);
                        //jesli jest oboekt comm jest to polecnie  do wykonania przez aktywny obiekt 
                        if(json.has("c")) {
                            if (json.getString("c").equals("kw3")||json.getString("c").equals("m2")) {
                                activeEvent.parse(json.getString("c"), json.getString("v"), json.getString("v1"));
                                    if(json.getString("c").equals("m2")) {
                                        saveToFile(json.getString("v") + ";" + json.getString("v1"));
//                                        saveToFile(System.getProperty("line.separator"));
                                        saveToFile("\r\n");
                                    }

                            }
                            else
                                activeEvent.parse(json.getString("c"), json.getString("v"));
                        }
                        else
                            {
                            for (Iterator<String> iter = json.keys(); iter.hasNext(); ) {
                                String key = iter.next();
                                String value = json.getString(key);
                                User contact = new User(key, value);
                                // adding contact to contact list
                                contactList.add(contact);
                            }
                            adapter.notifyDataSetChanged();
                        }
                    } catch (final JSONException e) {
                        Log.e(TAG, "Json parsing error: " + e.getMessage());
                        textV.append("Error parsing:"+readMessage);
                        textV.append(System.getProperty("line.separator"));

//                        runOnUiThread(new Runnable() {
//                            @Override
//                            public void run() {
//                                Toast.makeText(getApplicationContext(),
//                                        "Json parsing error: " + e.getMessage(),
//                                        Toast.LENGTH_LONG).show();
//
//                            }
//                        });

                    }

//                    try{
//                        json =new JSONObject(readMessage);
//                        for(Iterator<String> iter = json.keys(); iter.hasNext();) {
//                            String key = iter.next();
//                            String value= json.getString(key);
//
//                            HashMap<String, String> contact = new HashMap<>();
//
//                            // adding each child node to HashMap key => value
//                            contact.put("name", key);
//                            contact.put("value", value);
//
//
//                            // adding contact to contact list
//                            contactList.add(contact);
//                        }
////                        adapter.notifyData
//                        } catch (final JSONException e) {
//                            Log.e(TAG, "Json parsing error: " + e.getMessage());
//                            runOnUiThread(new Runnable() {
//                                @Override
//                                public void run() {
//                                    Toast.makeText(getApplicationContext(),
//                                            "Json parsing error: " + e.getMessage(),
//                                            Toast.LENGTH_LONG).show();
//                                }
//                            });
//
//                        }


//                    mConversationArrayAdapter.add(mConnectedDeviceName + ":  " + readMessage);
//                    writeToBuffer(readMessage);
//                    writeToFile(readMessage);
//                    writeToFile1(readMessage,getActivity());
                    break;
//                case Constants.MESSAGE_DEVICE_NAME:
//                    // save the connected device's name
//                    mConnectedDeviceName = msg.getData().getString(Constants.DEVICE_NAME);
//                    if (null != activity) {
//                        Toast.makeText(activity, "Connected to "
//                                + mConnectedDeviceName, Toast.LENGTH_SHORT).show();
//                    }
//                    break;
//                case Constants.MESSAGE_TOAST:
//                    if (null != activity) {
//                        Toast.makeText(activity, msg.getData().getString(Constants.TOAST),
//                                Toast.LENGTH_SHORT).show();
//                    }
//                    break;
            }
        }
    };

    public class User {
        public String name;
        public String value;

        public User(String name, String value) {
            this.name = name;
            this.value = value;
        }
    }

    public class UsersAdapter extends ArrayAdapter<User> {
        public UsersAdapter(Context context, ArrayList<User> users) {
            super(context, 0, users);
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            // Get the data item for this position
            User user = getItem(position);
            // Check if an existing view is being reused, otherwise inflate the view
            if (convertView == null) {
                convertView = LayoutInflater.from(getContext()).inflate(R.layout.list_item, parent, false);
            }
            // Lookup view for data population
            TextView tvName = (TextView) convertView.findViewById(R.id.name);
            TextView tvHome = (TextView) convertView.findViewById(R.id.value);
            // Populate the data into the template view using the data object


            tvName.setText(user.name);
            tvHome.setText(user.value);
                if(user.name.equals("Wal_wys") || user.name.equals("Wal_wprow"))
                    if(Integer.parseInt(user.value)>3500)
                        tvHome.setBackgroundColor(Color.RED);
                    else
                        tvHome.setBackgroundColor(Color.GREEN);


            // Return the completed view to render on screen
            return convertView;
        }
    }
    private void saveToFile(String s){
        Date date = new Date();
        SimpleDateFormat simpleDateFormat =
                new SimpleDateFormat("ddMM_HHmm");


        // Get the directory for the user's public pictures directory.
        final File path =
                Environment.getExternalStoragePublicDirectory
                        (
                                //Environment.DIRECTORY_PICTURES
                                //Environment.DIRECTORY_DCIM +
                                "mapowanieSiewnika/"

                        );

        // Make sure the path directory exists.
        if(!path.exists())
        {
            // Make it, if it doesn't exit
            path.mkdirs();
        }

//        final File file = new File(path, "test1.txt");
        final File file = new File(path, simpleDateFormat.format(date)
                +".cvs");

        // Save your stream, don't forget to flush() it before closing it.

        try
        {
//            if(!file.exists())
                file.createNewFile();
            FileOutputStream fOut = new FileOutputStream(file,true);
            OutputStreamWriter myOutWriter = new OutputStreamWriter(fOut);
            myOutWriter.write(s);
            myOutWriter.close();

            fOut.flush();
            fOut.close();
        }
        catch (IOException e)
        {
            Log.e("Exception", "File write failed: " + e.toString());
        }
        MediaScannerConnection.scanFile(getApplicationContext(), new String[] {file.toString()}, null, null);
        Toast.makeText(getApplicationContext(), "Saved", Toast.LENGTH_SHORT).show();
    }
}