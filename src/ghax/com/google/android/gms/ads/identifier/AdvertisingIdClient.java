package com.google.android.gms.ads.identifier;

import android.content.Context;

public class AdvertisingIdClient {

	public static Info getAdvertisingIdInfo(Context context) {
		return new Info("00000000-0000-0000-0000-000000000000", false);
	}

	public static class Info {
		private final String id;
		private final boolean isLimitAdTrackingEnabled;

		public Info(String id, boolean isLimitAdTrackingEnabled) {
			this.id = id;
			this.isLimitAdTrackingEnabled = isLimitAdTrackingEnabled;
		}

		public String getId() {
			return id;
		}

		public boolean isLimitAdTrackingEnabled() {
			return isLimitAdTrackingEnabled;
		}
	}
}
