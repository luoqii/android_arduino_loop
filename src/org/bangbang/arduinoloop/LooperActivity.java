package org.bangbang.arduinoloop;

import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.text.TextUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import com.android.future.usb.UsbAccessory;
import com.android.future.usb.UsbManager;
import com.tudou.android.fw.activity.LogcatActivity;
import com.tudou.android.fw.util.Log;

/**
 * based on https://github.com/Lauszus/ArduinoBlinkLED
 * 
 * @see https://github.com/luoqii/USB_Host_Shield_2.0/blob/master/examples/adk/ArduinoBlinkLED/ArduinoBlinkLED.ino
 * @author bangbang.song@gmail.com
 * 
 */
public class LooperActivity extends Activity {
	protected static final String TAG = LooperActivity.class.getSimpleName();

	private static final String STATE_STR_NOT_CONNECTED = "not connected.";
	private static final String STATE_STR_CONNECTED = "connected.";
	private static final String STATE_STR_REQUEST_PERMISSION = "check permission.";

	private static final String ACTION_USB_PERMISSION = "com.google.android.DemoKit.action.USB_PERMISSION";

	private UsbManager mUsbManager;
	private PendingIntent mPermissionIntent;
	private boolean mPermissionRequestPending;

	UsbAccessory mAccessory;
	ParcelFileDescriptor mFileDescriptor;
	FileInputStream mInputStream;
	FileOutputStream mOutputStream;

	private TextView mText;
	private ListView mSession;
	private ArrayAdapter<SessionItem> mAdapter;

	private final BroadcastReceiver mUsbReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			Log.d(TAG, "onReceive() action: " + action);
			if (ACTION_USB_PERMISSION.equals(action)) {
				synchronized (this) {
					UsbAccessory accessory = UsbManager.getAccessory(intent);
					if (intent.getBooleanExtra(
							UsbManager.EXTRA_PERMISSION_GRANTED, false)) {
						openAccessory(accessory);
					} else {
						Log.d(TAG, "permission denied for accessory "
								+ accessory);
					}
					mPermissionRequestPending = false;
				}
			} else if (UsbManager.ACTION_USB_ACCESSORY_DETACHED.equals(action)) {
				UsbAccessory accessory = UsbManager.getAccessory(intent);
				if (accessory != null && accessory.equals(mAccessory)) {
					closeAccessory();
				}

				updateCheckLable(STATE_STR_NOT_CONNECTED);
			}
		}
	};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		mText = (TextView) findViewById(R.id.text);
		mSession = (ListView)findViewById(R.id.session);
		mAdapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, new ArrayList<SessionItem>());
		mSession.setAdapter(mAdapter);
		mSession.setTranscriptMode(ListView.TRANSCRIPT_MODE_ALWAYS_SCROLL);
		
		mUsbManager = UsbManager.getInstance(this);
		mPermissionIntent = PendingIntent.getBroadcast(this, 0, new Intent(
				ACTION_USB_PERMISSION), 0);
		IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
		filter.addAction(UsbManager.ACTION_USB_ACCESSORY_DETACHED);
		filter.addAction(UsbManager.ACTION_USB_ACCESSORY_ATTACHED);
		registerReceiver(mUsbReceiver, filter);
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		
		unregisterReceiver(mUsbReceiver);
	}

	@Override
	protected void onResume() {
		super.onResume();

		checkAccessory();
	}

	private void checkAccessory() {
		if (mInputStream != null && mOutputStream != null) {
			updateCheckLable(STATE_STR_CONNECTED);
			return;
		}

		UsbAccessory[] accessories = mUsbManager.getAccessoryList();
		UsbAccessory accessory = (accessories == null ? null : accessories[0]);
		Log.d(TAG, "mAccessory: " + accessory);
		if (accessory != null) {
			if (mUsbManager.hasPermission(accessory)) {
				openAccessory(accessory);
			} else {
				synchronized (mUsbReceiver) {
					if (!mPermissionRequestPending) {
						mUsbManager.requestPermission(accessory,
								mPermissionIntent);
						updateCheckLable(STATE_STR_REQUEST_PERMISSION);
						mPermissionRequestPending = true;
					}
				}
			}
		} else {
		}
	}

	private void updateCheckLable(String label) {
		((TextView) findViewById(R.id.status_text)).setText(label);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		int id = item.getItemId();
		if (id == R.id.logcat) {
			Intent intent = new Intent();
			intent.setClass(LooperActivity.this, LogcatActivity.class);
			startActivity(intent);
			return true;
		} else if (id == R.id.check) {
			checkAccessory();
			return true;
		}

		return super.onOptionsItemSelected(item);
	}

	private void openAccessory(UsbAccessory accessory) {
		mFileDescriptor = mUsbManager.openAccessory(accessory);
		if (mFileDescriptor != null) {
			mAccessory = accessory;
			FileDescriptor fd = mFileDescriptor.getFileDescriptor();
			mInputStream = new FileInputStream(fd);
			mOutputStream = new FileOutputStream(fd);
			
			new WorkThread(mInputStream, mOutputStream).start();
			
			Log.d(TAG, "open accessory ok.");
			updateCheckLable(STATE_STR_CONNECTED);
		} else {
			Log.d(TAG, "open accessory fail.");
			updateCheckLable(STATE_STR_NOT_CONNECTED);
		}
	}

	private void closeAccessory() {
		try {
			if (mFileDescriptor != null) {
				mFileDescriptor.close();
			}
		} catch (IOException e) {
		} finally {
			mFileDescriptor = null;
			mAccessory = null;
		}

		updateCheckLable(STATE_STR_NOT_CONNECTED);
	}

	public void onSent(View view) {
		String message = mText.getText().toString();
		if (!TextUtils.isEmpty(message)) {
			mText.setText("");
			onSent(message);
		}
	}
	
	public void onSent(String mesage) {
		if (mOutputStream != null) {
			if (!TextUtils.isEmpty(mesage)) {
				byte[] buffer = mesage.getBytes();
				try {
					Log.d(TAG, "SND: " + mesage);
					
					int count = buffer.length;
					String log = "SND: 0x" + mesage;
					for (int i = 0 ; i < count; i++) {
						log += Integer.toHexString(buffer[i]);
					}
					Log.d(TAG, log);
					
					mOutputStream.write(buffer);
				} catch (IOException e) {
					Log.e(TAG, "IOException", e);
				}
			}
			
			SessionItem item = new SessionItem(System.currentTimeMillis(), SessionItem.DIRECTION_OUT, mesage);
			mAdapter.add(item);
			mAdapter.notifyDataSetChanged();
		}
	}
	
	void onRcvd(String mesage) {
		Log.d(TAG, "RCV: " + mesage);
		
		SessionItem item = new SessionItem(System.currentTimeMillis(), SessionItem.DIRECTION_IN, mesage);
		mAdapter.add(item);
		mAdapter.notifyDataSetChanged();
	}
	
	class WorkThread extends 
//	HandlerThread ,
	Thread
	{
		private static final int BUFFER_SIZE = 1024;
		private InputStream mIn;
		private OutputStream mOut;

		public WorkThread(InputStream in, OutputStream out) {
			super("WorkThread");
			
			mIn = in;
			mOut = out;
		}
		
		@Override
		public synchronized void start() {
			super.start();
		}
		
		
		@Override
		public void run() {
			super.run();

			byte[] buffer = new byte[BUFFER_SIZE];
			if (mIn != null) {
				try {
					int read = 0;
					while ((read = mIn.read(buffer)) != -1){	
						Log.d(TAG, "read count: " + read);
						final String mesage = new String(buffer, 0, read);
						runOnUiThread(new Runnable() {
							public void run() {
								onRcvd(mesage);
							}
						});
					}
				} catch (IOException e) {
					Log.e(TAG, "IOException", e);
				}
			}
		}
	}
	
	static class SessionItem {
		public static final int DIRECTION_IN = 1;
		public static final int DIRECTION_OUT = 2;
		
		private long mTime;
		private int mDirection;
		private String mMessage;

		public SessionItem(long time, int direction, String message) {
			mTime = time;
			mDirection = direction;
			mMessage = message;
		}
		
		@Override
		public String toString() {
			return (mDirection == DIRECTION_IN ? "RCV: " : "SND: ") +  mMessage;
		}
	}

}
