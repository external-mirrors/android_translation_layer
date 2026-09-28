package android.text.format;

import android.content.Context;

public class Formatter {

	public static String formatShortFileSize(Context context, long size) {
		return formatFileSize(context, size);
	}

	public static String formatFileSize(Context context, long size) {
		if (size > 1024 * 1024 * 1024) {
			return String.format("%.1f GiB", size / 1024.0 / 1024.0 / 1024.0);
		} else if (size > 1024 * 1024) {
			return String.format("%.1f MiB", size / 1024.0 / 1024.0);
		} else if (size > 1024) {
			return String.format("%.1f KiB", size / 1024.0);
		} else {
			return String.format("%d B", size);
		}
	}

	@Deprecated
	public static String formatIpAddress(int ipv4Address) {
		return String.format("%d.%d.%d.%d",
		                     ipv4Address & 0xff,
		                     (ipv4Address >> 8) & 0xff,
		                     (ipv4Address >> 16) & 0xff,
		                     (ipv4Address >> 24) & 0xff);
	}
}
