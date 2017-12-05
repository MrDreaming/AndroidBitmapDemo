package com.example.bitmapdemo;


import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Bitmap.Config;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;

public class MainActivity extends Activity {
	
	private ImageView ivDisplay = null;
	private Bitmap bitmapOrig = null;
	private Bitmap bitmapGray = null;
	private Bitmap bitmapWip = null;
	
	static {
		System.loadLibrary("bitmapdemo");
	}
	
	public native void convertBmp(Bitmap bitmapIn, Bitmap bitmapOut);
	
	Boolean isColor;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		ivDisplay = (ImageView) findViewById(R.id.ivDisplay);
		
		BitmapFactory.Options options = new BitmapFactory.Options();
		// Make sure it is 24 bit color as our image processing algorithm
		// expects this format
		options.inPreferredConfig = Config.ARGB_8888;
		bitmapOrig = BitmapFactory.decodeResource(this.getResources(),
				R.drawable.sampleimage, options);
		if (bitmapOrig != null)
			ivDisplay.setImageBitmap(bitmapOrig);
		isColor = true;
		bitmapWip = Bitmap.createBitmap(bitmapOrig.getWidth(),
				bitmapOrig.getHeight(), Config.ARGB_8888); //ALPHA_8
		//convertBmp(bitmapOrig, bitmapWip);
		//ivDisplay.setImageBitmap(bitmapWip);
		
		findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				if(isColor){
					isColor = false;
					convertBmp(bitmapOrig, bitmapWip);
					ivDisplay.setImageBitmap(bitmapWip);
				}else{
					isColor = true;
					ivDisplay.setImageBitmap(bitmapOrig);
				}
			}
		});
	}
}
