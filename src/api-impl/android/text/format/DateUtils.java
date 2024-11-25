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

	public static String formatElapsedTime(long elapsedMillis) {
		final long days = elapsedMillis / (24 * 60 * 60L);
		final long hours = elapsedMillis / (60 * 60L) % 24L;
		final long minutes = elapsedMillis / 60L % 60L;
		final long seconds = elapsedMillis % 60L;

		if (elapsedMillis < 0) {
			return "0:00";
		} else if (days > 0) {
			return String.format("%d:%02d:%02d:%02d", days, hours, minutes, seconds);
		} else if (hours > 0) {
			return String.format("%d:%02d:%02d", hours, minutes, seconds);
		} else {
			return String.format("%d:%02d", minutes, seconds);
		}
	}
}
