package android.content.pm;

public class ResolveInfo {
	public ActivityInfo activityInfo = new ActivityInfo();
	public ServiceInfo serviceInfo = new ServiceInfo();

	public static class DisplayNameComparator {

		public DisplayNameComparator(PackageManager pm) {}

	}
}
