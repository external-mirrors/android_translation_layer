package android.app.job;

import android.content.ComponentName;

public class JobInfo {
	public static final class Builder {
		public Builder(int jobId, ComponentName jobService) {}

		public Builder setMinimumLatency(long minLatencyMillis) {
			return this;
		}

		public Builder setRequiredNetworkType(int networkType) {
			return this;
		}
	}
}
