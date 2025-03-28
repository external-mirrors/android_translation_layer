package android.app;

import android.content.Context;
import android.content.ContextWrapper;
import android.content.Intent;
import android.os.IBinder;

public abstract class Service extends ContextWrapper {

	/* HACK for InputMethodService */
	public Service(Context baseContext) {
		super(baseContext);
	}

	public Service() {
		super(null);
	}

	public void onCreate() {
		System.out.println("Service.onCreate() called");
	}

	public void onDestroy() {
		System.out.println("Service.onDestroy() called");
	}

	public abstract IBinder onBind(Intent intent);

	public int onStartCommand(Intent intent, int flags, int startId) {
		System.out.println("Service.onStartCommand(" + intent + ", " + flags + ", " + startId + ") called");
		return 0;
	}

	public void startForeground(int id, Notification notification) {
		System.out.println("startForeground(" + id + ", " + notification + ") called");
	}

	public void stopForeground(boolean remove) {
		System.out.println("stopForeground(" + remove + ") called");
	}

	public void stopForeground(int remove) {
		System.out.println("stopForeground(" + remove + ") called");
	}

	public Application getApplication() {
		return this_application;
	}

	public void stopSelf(int startId) {
		System.out.println("Service.stopSelf(" + startId + ") called");
	}

	public void stopSelf() {
		System.out.println("Service.stopSelf() called");
	}

	public void attachBaseContext(Context newBase) {
		System.out.println("Service.attachBaseContext(" + newBase + ") called");
	}
}
