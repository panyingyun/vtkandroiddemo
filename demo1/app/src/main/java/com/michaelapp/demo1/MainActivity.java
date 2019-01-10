package com.michaelapp.demo1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView helloTv = (TextView)findViewById(R.id.hello);
        helloTv.setText(JavaNativeLib.stringFromJNI());

        TextView numberTV = (TextView)findViewById(R.id.number);
        int sum = JavaNativeLib.add(10,20);
        numberTV.setText("sum 10 + 20 = "+String.valueOf(sum));

    }
}
