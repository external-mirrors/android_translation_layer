package android.preference;

import android.app.SharedPreferencesImpl;
import android.content.Context;
import android.content.SharedPreferences;

public class PreferenceManager {
	public static SharedPreferences getDefaultSharedPreferences(Context context) {
		return Context.this_application.getSharedPreferences(context.getPackageName() + "_preferences", 0);
	}

	public static void setDefaultValues(Context context, int i, boolean b) {
		System.out.println("android.preference.PrefereceManager.setDefaultValues: STUB");
	}
}
