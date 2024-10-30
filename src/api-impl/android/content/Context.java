package android.content;

import android.R;
import android.app.Activity;
import android.app.ActivityManager;
import android.app.AlarmManager;
import android.app.Application;
import android.app.KeyguardManager;
import android.app.NotificationManager;
import android.app.Service;
import android.app.SharedPreferencesImpl;
import android.app.UiModeManager;
import android.bluetooth.BluetoothManager;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageParser;
import android.content.res.AssetManager;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.content.res.TypedArray;
import android.content.res.XmlResourceParser;
import android.database.DatabaseErrorHandler;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.drawable.Drawable;
import android.hardware.input.InputManager;
import android.hardware.SensorManager;
import android.hardware.display.DisplayManager;
import android.hardware.usb.UsbManager;
import android.location.LocationManager;
import android.media.AudioManager;
import android.media.MediaRouter;
import android.net.ConnectivityManager;
import android.net.Uri;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.os.ParcelFileDescriptor;
import android.os.PowerManager;
import android.os.Vibrator;
import android.telephony.TelephonyManager;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.util.Slog;
import android.view.Display;
import android.view.LayoutInflater;
import android.view.WindowManagerImpl;
import android.view.accessibility.AccessibilityManager;
import android.view.inputmethod.InputMethodManager;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;
import java.io.IOException;

public class Context extends Object {
	private final static String TAG = "Context";

	public static final int MODE_PRIVATE = 0;
	public static final String LOCATION_SERVICE = "location";
	public static final String AUDIO_SERVICE = "audio";
	public static final String DISPLAY_SERVICE = "display";
	public static final String MEDIA_ROUTER_SERVICE = "media_router";
	public static final String WINDOW_SERVICE = "window";
	public static final String INPUT_METHOD_SERVICE = "input";
	public static final String POWER_SERVICE = "power";
	public static final String VIBRATOR_SERVICE = "vibrator";

	public static Vibrator vibrator;

	static AssetManager assets;
	static DisplayMetrics dm;
	public static Resources r;
	static ApplicationInfo application_info;
	static Resources.Theme theme;
	private static Map<Class<? extends Service>,Service> runningServices = new HashMap<>();
	public static PackageParser.Package pkg;
	public static PackageManager package_manager;

	public /*← FIXME?*/ static Application this_application;

	File data_dir = null;
	File prefs_dir = null;
	File files_dir = null;
	File obb_dir = null;
	File cache_dir = null;
	File nobackup_dir = null;

	private static Map<IntentFilter, BroadcastReceiver> receiverMap = new HashMap<IntentFilter, BroadcastReceiver>();

	static {
		assets = new AssetManager();
		dm = new DisplayMetrics();
		Configuration config = new Configuration();
		native_updateConfig(config);
		r = new Resources(assets, dm, config);
		theme = r.newTheme();
		application_info = new ApplicationInfo();
		try (XmlResourceParser parser = assets.openXmlResourceParser("AndroidManifest.xml")) {
			PackageParser packageParser = new PackageParser(native_get_apk_path());
			String[] parseError = new String[1];
			pkg = packageParser.parsePackage(r, parser, 0, parseError);
			if (parseError[0] != null) {
				Slog.e(TAG, parseError[0]);
				System.exit(1);
			}
			
			packageParser.collectCertificates(pkg, 0);
			application_info = pkg.applicationInfo;
		} catch (Exception e) {
			e.printStackTrace();
		}
		application_info.dataDir = Environment.getExternalStorageDirectory().getAbsolutePath();
		application_info.nativeLibraryDir = (new File(Environment.getExternalStorageDirectory(), "lib")).getAbsolutePath();
		application_info.sourceDir = native_get_apk_path();
		package_manager = new PackageManager();
	}

	private static native String native_get_apk_path();
	protected static native void native_updateConfig(Configuration config);
	private static native void nativeOpenFile(int fd);

	static Application createApplication(long native_window) throws Exception {
		Application application;

		if (pkg.applicationInfo.className != null) {
			Class<? extends Application> cls = Class.forName(pkg.applicationInfo.className).asSubclass(Application.class);
			Constructor<? extends Application> constructor = cls.getConstructor();
			application = constructor.newInstance();
		} else {
			application = new Application();
		}
		if (pkg.applicationInfo.theme != 0)
			application.setTheme(pkg.applicationInfo.theme);
		application.native_window = native_window;
		this_application = application;
		application.attachBaseContext(new Context());
		// HACK: Set WhatsApp's custom logging mechanism to verbose for easier debugging. Should be removed again once WhatsApp is fully supported
		try {
			Class.forName("com.whatsapp.util.Log").getField("level").setInt(null, 5);
		} catch (Exception e) {} // ignore for other apps
		return application;
	}

	public Context() {
		Slog.v(TAG, "new Context! this one is: " + this);
	}

	public int checkPermission(String permission, int pid, int uid) {
		return getPackageManager().checkPermission(permission, "dummy");
	}

	public Resources.Theme getTheme() {
		return theme;
	}

	public ApplicationInfo getApplicationInfo() {
		return application_info;
	}

	public Context getApplicationContext() {
		return (Context)this_application;
	}

	public ContentResolver getContentResolver() {
		return new ContentResolver();
	}

	public Object getSystemService(String name) {
		switch (name) {
			case "window":
				return new WindowManagerImpl();
			case "clipboard":
				return new ClipboardManager();
			case "sensor":
				return new SensorManager();
			case "connectivity":
				return new ConnectivityManager();
			case "keyguard":
				return new KeyguardManager();
			case "phone":
				return new TelephonyManager();
			case "audio":
				return new AudioManager();
			case "activity":
				return new ActivityManager();
			case "usb":
				return new UsbManager();
			case "vibrator":
				return (vibrator != null) ? vibrator : (vibrator = new Vibrator());
			case "power":
				return new PowerManager();
			case "display":
				return new DisplayManager();
			case "media_router":
				return new MediaRouter();
			case "notification":
				return new NotificationManager();
			case "alarm":
				return new AlarmManager();
			case "input":
				return new InputManager();
			case "location":
				return new LocationManager();
			case "uimode":
				return new UiModeManager();
			case "input_method":
				return new InputMethodManager();
			case "accessibility":
				return new AccessibilityManager();
			case "layout_inflater":
				return new LayoutInflater(getApplicationContext());
			case "wifi":
				return new WifiManager();
			case "bluetooth":
				return new BluetoothManager();
			default:
				Slog.e(TAG, "!!!!!!! getSystemService: case >" + name + "< is not implemented yet");
				return null;
		}
	}

	public final <T> T getSystemService(Class<T> serviceClass) {
		return null;
	}

	public Intent registerReceiver(BroadcastReceiver receiver, IntentFilter filter) {
		receiverMap.put(filter, receiver);
		return new Intent();
	}

	public Looper getMainLooper() {
		return Looper.getMainLooper();
	}

	public String getPackageName() {
		return getApplicationInfo().packageName;
	}

	public String getPackageCodePath() {
		return getApplicationInfo().sourceDir;
	}

	public int getColor(int resId) {
		return r.getColor(resId);
	}

	public final String getString(int resId) {
		return r.getString(resId);
	}

	public final String getString (int resId, Object... formatArgs) {
		return r.getString(resId, formatArgs);
	}

	public PackageManager getPackageManager() {
		return package_manager;
	}

	public Resources getResources() {
		return r;
	}

	public AssetManager getAssets() {
		return assets;
	}

	private File makeFilename(File base, String name) {
		if (name.indexOf(File.separatorChar) < 0) {
			return new File(base, name);
		}
		throw new IllegalArgumentException(
		    "File " + name + " contains a path separator");
	}

	private File getDataDirFile() {
		if (data_dir == null) {
			data_dir = android.os.Environment.getExternalStorageDirectory();
		}
		return data_dir;
	}

	public File getFilesDir() {
		if (files_dir == null) {
			files_dir = new File(getDataDirFile(), "files");
		}
		if (!files_dir.exists()) {
			if (!files_dir.mkdirs()) {
				if (files_dir.exists()) {
					// spurious failure; probably racing with another process for this app
					return files_dir;
				}
				Slog.w(TAG, "Unable to create files directory " + files_dir.getPath());
				return null;
			}
		}
		return files_dir;
	}

	public File getExternalFilesDir(String type) {
		return getFilesDir();
	}

	public File[] getExternalFilesDirs(String type) {
		return new File[] {getExternalFilesDir(type)};
	}

	public File getObbDir() {
		if (obb_dir == null) {
			obb_dir = new File(getDataDirFile(), "Android/obb/" + getPackageName());
		}
		if (!obb_dir.exists()) {
			if (!obb_dir.mkdirs()) {
				if (obb_dir.exists()) {
					// spurious failure; probably racing with another process for this app
					return obb_dir;
				}
				Slog.w(TAG, "Unable to create obb directory >" + obb_dir.getPath() + "<");
				return null;
			}
		}
		return obb_dir;
	}

	public File[] getObbDirs() {
		return new File[] {getObbDir()};
	}

	public File getCacheDir() {
		if (cache_dir == null) {
			cache_dir = new File("/tmp/atl_cache/" + getPackageName());
		}
		if (!cache_dir.exists()) {
			if (!cache_dir.mkdirs()) {
				if (cache_dir.exists()) {
					// spurious failure; probably racing with another process for this app
					return cache_dir;
				}
				Slog.w(TAG, "Unable to create cache directory >" + cache_dir.getPath() + "<");
				return null;
			}
		}
		return cache_dir;
	}

	public File getExternalCacheDir() {
		return getCacheDir();
	}

	public File getNoBackupFilesDir() {
		if (nobackup_dir == null) {
			nobackup_dir = new File(getDataDirFile(), "no_backup/" + getPackageName());
		}
		if (!nobackup_dir.exists()) {
			if (!nobackup_dir.mkdirs()) {
				if (nobackup_dir.exists()) {
					// spurious failure; probably racing with another process for this app
					return nobackup_dir;
				}
				Slog.w(TAG, "Unable to create no_backup directory >" + nobackup_dir.getPath() + "<");
				return null;
			}
		}
		return nobackup_dir;
	}

	private File getPreferencesDir() {
		if (prefs_dir == null) {
			prefs_dir = new File(getDataDirFile(), "shared_prefs");
		}
		return prefs_dir;
	}

	public File getDir(String name, int mode) {
		File dir = new File(getFilesDir(), name);
		if (!dir.exists()) {
			if (!dir.mkdirs()) {
				if (dir.exists()) {
					// spurious failure; probably racing with another process for this app
					return dir;
				}
				Slog.w(TAG, "Unable to create directory >" + dir.getPath() + "<");
				return null;
			}
		}
		return dir;
	}

	public File getFileStreamPath(String name) {
		return makeFilename(getFilesDir(), name);
	}

	public File getSharedPrefsFile(String name) {
		return makeFilename(getPreferencesDir(), name + ".xml");
	}

	private static Map<String, SharedPreferences> sharedPrefs = new HashMap<String, SharedPreferences>();

	public SharedPreferences getSharedPreferences(String name, int mode) {
		Slog.v(TAG, "\n\n...> getSharedPreferences(" + name + ")\n\n");
		if (sharedPrefs.containsKey(name)) {
			return sharedPrefs.get(name);
		} else {
			File prefsFile = getSharedPrefsFile(name);
			SharedPreferences prefs = new SharedPreferencesImpl(prefsFile, mode);
			sharedPrefs.put(name, prefs);
			return prefs;
		}
	}

	public ClassLoader getClassLoader() {
		// not perfect, but it's what we use for now as well, and it works
		return ClassLoader.getSystemClassLoader();
	}

	public ComponentName startService(Intent intent) {
		ComponentName component = intent.getComponent();
		if(component == null) {
			Slog.w(TAG, "startService: component is null");
			return null;
		}

		new Handler(Looper.getMainLooper()).post(new Runnable() {
			@Override
			public void run() {
				try {
					Class<? extends Service> cls = Class.forName(component.getClassName()).asSubclass(Service.class);
					if (!runningServices.containsKey(cls)) {
						Service service = cls.getConstructor().newInstance();
						service.attachBaseContext(new Context());
						service.onCreate();
						runningServices.put(cls, service);
					}
					
					runningServices.get(cls).onStartCommand(intent, 0, 0);
				} catch (ReflectiveOperationException e) {
					e.printStackTrace();
				}
			}
		});

		return component;
	}

	// TODO: do these both work? make them look more alike
	public FileInputStream openFileInput(String name) throws FileNotFoundException {
		Slog.v(TAG, "openFileInput called for: '" + name + "'");
		File file = new File(getFilesDir(), name);

		return new FileInputStream(file);
	}

	public FileOutputStream openFileOutput(String name, int mode) throws java.io.FileNotFoundException {
		Slog.v(TAG, "openFileOutput called for: '" + name + "'");
		return new FileOutputStream(android.os.Environment.getExternalStorageDirectory().getPath() + "/files/" + name);
	}

	public int checkCallingOrSelfPermission(String permission) {
		Slog.w(TAG, "!!! app wants to know if it has a permission: >" + permission + "< (returning PERMISSION_DENIED)");

		return PackageManager.PERMISSION_DENIED;
	}

	public void registerComponentCallbacks(ComponentCallbacks callbacks) {}

	public boolean bindService(final Intent intent, final ServiceConnection serviceConnection, int dummy3) {
		if(intent.getComponent() == null) {
			Slog.w(TAG, "Context.bindService: intent.getComponent() is null");
			return false;
		}

		new Handler(Looper.getMainLooper()).post(new Runnable() { // run this asynchron so the caller can finish its setup before onServiceConnected is called
			@Override
			public void run() {
				try {
					Class<? extends Service> cls = Class.forName(intent.getComponent().getClassName()).asSubclass(Service.class);
					if (!runningServices.containsKey(cls)) {
						Service service = cls.getConstructor().newInstance();
						service.onCreate();
						runningServices.put(cls, service);
					}
					serviceConnection.onServiceConnected(intent.getComponent(), runningServices.get(cls).onBind(intent));
				} catch (ReflectiveOperationException e) {
					e.printStackTrace();
				}
			}
		});
		return true;
	}

	public void startActivity(Intent intent) {
		Slog.i(TAG, "startActivity(" + intent + ") called");
		if (intent.getAction() != null && intent.getAction().equals("android.intent.action.CHOOSER")) {
			intent = (Intent) intent.getExtras().get("android.intent.extra.INTENT");
		}
		if (intent.getComponent() == null) {
			if(intent.getAction() != null && intent.getAction().equals("android.intent.action.SEND")) {
				Slog.i(TAG, "starting extern activity with intent: " + intent);
				String text = intent.getStringExtra("android.intent.extra.TEXT");
				if (text == null)
					text = String.valueOf(intent.getExtras().get("android.intent.extra.STREAM"));
				if (text != null)
					ClipboardManager.native_set_clipboard(text);
			} else if (intent.getData() != null) {
				Slog.i(TAG, "starting extern activity with intent: " + intent);
				if (intent.getData().getScheme().equals("content")) {
					try {
						ParcelFileDescriptor fd = getContentResolver().openFileDescriptor(intent.getData(), "r");
						nativeOpenFile(fd.getFd());
						return;
					} catch (FileNotFoundException e) {
						e.printStackTrace();
					}
				}
				Activity.nativeOpenURI(String.valueOf(intent.getData()));
			}
			return;
		}
		final Intent intent_ = intent;
		Runnable runnable = new Runnable() {
			@Override
			public void run() {
				try {
					Class<? extends Activity> cls = Class.forName(intent_.getComponent().getClassName()).asSubclass(Activity.class);
					Constructor<? extends Activity> constructor = cls.getConstructor();
					Activity activity = constructor.newInstance();
					activity.intent = intent_;
					activity.getWindow().native_window = this_application.native_window;
					Activity.nativeStartActivity(activity);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		};
		if (Looper.myLooper() == Looper.getMainLooper()) {
			runnable.run();
		} else {
			new Handler(Looper.getMainLooper()).post(runnable);
		}
	}

	public void startActivity(Intent intent, Bundle options) {
		startActivity(intent);
	}

	public final TypedArray obtainStyledAttributes(AttributeSet set, int[] attrs) {
		return getTheme().obtainStyledAttributes(set, attrs, 0, 0);
	}
	public final TypedArray obtainStyledAttributes(AttributeSet set, int[] attrs, int defStyleAttr, int defStyleRes) {
		return getTheme().obtainStyledAttributes(set, attrs, defStyleAttr, defStyleRes);
	}
	public final TypedArray obtainStyledAttributes(int resid, int[] attrs) {
		return getTheme().obtainStyledAttributes(resid, attrs);
	}
	public final TypedArray obtainStyledAttributes(int[] attrs) {
		return getTheme().obtainStyledAttributes(attrs);
	}

	public void setTheme(int resId) {
		theme.applyStyle(resId, true);
	}

	public final CharSequence getText(int resId) {
		return getResources().getText(resId);
	}

	public final Drawable getDrawable(int resId) {
		return getResources().getDrawable(resId);
	}

	public boolean isRestricted() {return false;}

	public File getDatabasePath(String dbName) {
		File databaseDir = new File(getDataDirFile(), "databases");
		if (!databaseDir.exists())
			databaseDir.mkdirs();
		return new File(databaseDir, dbName);
	}

	public void sendBroadcast(Intent intent) {
		for (IntentFilter filter : receiverMap.keySet()) {
			if (filter.matchAction(intent.getAction())) {
				receiverMap.get(filter).onReceive(this, intent);
			}
		}
	}

	public boolean stopService(Intent intent) throws ClassNotFoundException {
		Class<? extends Service> cls = Class.forName(intent.getComponent().getClassName()).asSubclass(Service.class);
		Service service = runningServices.remove(cls);
		if (service != null) {
			service.onDestroy();
			return true;
		}
		return false;
	}

	public void unbindService(ServiceConnection serviceConnection) {}

	public void unregisterReceiver(BroadcastReceiver receiver) {}

	public Context createPackageContext(String dummy, int dummy2) {
		return this; // FIXME?
	}

	public void grantUriPermission(String dummy, Uri dummy2, int dummy3) {
		System.out.println("grantUriPermission(" + dummy + ", " + dummy2 + ", " + dummy3 + ") called");
	}

	public SQLiteDatabase openOrCreateDatabase(String name, int mode, SQLiteDatabase.CursorFactory factory) {
		return openOrCreateDatabase(name, mode, factory, null);
	}

	public SQLiteDatabase openOrCreateDatabase(String filename, int mode, SQLiteDatabase.CursorFactory factory, DatabaseErrorHandler errorHandler) {
		int flags = SQLiteDatabase.CREATE_IF_NECESSARY;
		if ((mode & (1 <<3) /*MODE_ENABLE_WRITE_AHEAD_LOGGING*/) != 0) {
			flags |= SQLiteDatabase.ENABLE_WRITE_AHEAD_LOGGING;
		}
		SQLiteDatabase db = SQLiteDatabase.openDatabase(filename, factory, flags, errorHandler);
		return db;
	}

	public Context createConfigurationContext(Configuration configuration) {
		return new Context();
	}

	public void sendOrderedBroadcast(Intent intent, String receiverPermission, BroadcastReceiver resultReceiver, Handler handler, int flags, String extra, Bundle options) {
		System.out.println("sendOrderedBroadcast(" + intent + ", " + receiverPermission + ", " + resultReceiver + ", " + handler + ", " + flags + ", " + extra + ", " + options + ") called");
	}

	public Context createDisplayContext(Display display) {
		return new Context();
	}

	public Intent registerReceiver(BroadcastReceiver receiver, IntentFilter filter, String broadcastPermission, Handler scheduler) {
		return registerReceiver(receiver, filter);
	}

	public String[] fileList() {
		return new String[0];
	}

	public void revokeUriPermission(Uri uri, int mode) {
		System.out.println("revokeUriPermission(" + uri + ", " + mode + ") called");
	}
}
