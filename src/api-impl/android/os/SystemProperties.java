package android.os;

public class SystemProperties {
	public static String get(String prop) {
		android.util.Log.i("SystemProperties", "Grabbing String prop " + prop);
		return "";
	}

	public static String get(String prop, String def) {
		android.util.Log.i("SystemProperties", "Grabbing String prop " + prop + ", default " + def);
		return def;
	}

	public boolean getBoolean(String prop, boolean def) {
		android.util.Log.i("SystemProperties", "Grabbing boolean prop " + prop + ", default " + def);
		return def;
	}

	public static int getInt(String prop, int def) {
		android.util.Log.i("SystemProperties", "Grabbing int prop " + prop + ", default " + def);
		return def;
	}

	public static long getLong(String prop, long def) {
		android.util.Log.i("SystemProperties", "Grabbing long prop " + prop + ", default " + def);
		return def;
	}
}
