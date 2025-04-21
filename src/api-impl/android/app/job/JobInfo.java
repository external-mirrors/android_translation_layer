package android.app.job;

import android.content.ComponentName;
import android.os.PersistableBundle;

public class JobInfo {

	public JobInfo() {}

	public static final class Builder {
		public Builder(int jobId, ComponentName jobService) {}

		public Builder setBackoffCriteria(long initialBackoffMillis, int backoffPolicy) {
			return this;
		}

		public Builder setExtras(PersistableBundle extras) {
			return this;
		}

		public Builder setMinimumLatency(long minLatencyMillis) {
			return this;
		}

		public Builder setOverrideDeadline(long a) {
			return this;
		}

		public Builder setPeriodic(long dummy) {
			return this;
		}

		public Builder setPersisted(boolean persisted) {
			return this;
		}

		public Builder setRequiredNetworkType(int networkType) {
			return this;
		}

		public Builder setRequiresCharging(boolean requires_charging) {
			return this;
		}

		public Builder setRequiresDeviceIdle(boolean requires_device_idle) {
			return this;
		}

		public Builder setRequiresBatteryNotLow(boolean requires_battery_not_low) {
			return this;
		}

		public Builder setRequiresStorageNotLow(boolean requires_storage_not_low) {
			return this;
		}

		public JobInfo build() {
			return new JobInfo();
		}
	}
}
