package android.os;

public final class PowerManager {
	public final class WakeLock {
		private boolean held;
		private boolean refCounted = true;
		private int count;

		public void setReferenceCounted(boolean referenceCounted) {
			refCounted = referenceCounted;
		}

		public void acquire() {
			if (refCounted) {
				count++;
			}
			held = true;
		}

		public void release() {
			if (refCounted) {
				count--;
				if (count > 0)
					return;
			}
			held = false;
		}

		public boolean isHeld() {
			return held;
		}

		public void acquire(long timeout) {
			acquire();
			new Thread(new Runnable() {
				public void run() {
					try {
						Thread.sleep(timeout);
					} catch (InterruptedException e) {
					}
					release();
				}
			}).start();
		}
	}

	public WakeLock newWakeLock(int levelAndFlags, String tag) {
		return new WakeLock();
	}

	public void goToSleep(long time) {
		// This requires DEVICE_POWER permission which is only possible for system processes. Any normal application gets a SecurityException.
		throw new SecurityException();
	}

	public void userActivity(long dummy, boolean dummy2) {}

	public static final int FULL_WAKE_LOCK = 0x1a;

	public boolean isPowerSaveMode() {
		return false;
	}

	public boolean isScreenOn() {
		return true;
	}

	public boolean isIgnoringBatteryOptimizations(String packageName) {
		return true;
	}
}
