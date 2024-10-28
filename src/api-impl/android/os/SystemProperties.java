package android.os;

public class SystemProperties {
	public static String get(String prop) {
		android.util.Log.i("SystemProperties", "Grabbing prop " + prop);
		return null;
	}

	public boolean getBoolean(String prop, boolean def) {
		android.util.Log.i("SystemProperties", "Grabbing prop " + prop + ", default " + def);
		return def;
	}
}
