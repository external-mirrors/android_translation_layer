package android.text.format;

import java.util.Date;

import android.content.Context;

public class DateUtils {

	public static CharSequence getRelativeTimeSpanString(Context context, long millis, boolean withPreposition) {
		return new Date(millis).toString();
	}

	public static boolean isToday(long millis) {
		Date d1 = new Date(millis);
		Date d2 = new Date();
		
		return d1.getYear() == d2.getYear() && d1.getMonth() == d2.getMonth() && d1.getDate() == d2.getDate();
	}
}
