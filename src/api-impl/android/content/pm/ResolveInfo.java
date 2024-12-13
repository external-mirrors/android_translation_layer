package android.content.pm;

import android.content.IntentFilter;

public class ResolveInfo {
	public ActivityInfo activityInfo = new ActivityInfo();
	public ServiceInfo serviceInfo = new ServiceInfo();
	public IntentFilter filter = new IntentFilter();

	public static class DisplayNameComparator {

		public DisplayNameComparator(PackageManager pm) {}

	}
}
