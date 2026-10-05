package android.media;

public class AudioAttributes {

	public static final int USAGE_MEDIA = 1;

	int streamType;

	public int getFlags() { return 0; }

	public int getUsage() { return 0; }

	public static class Builder {

		public Builder setContentType(int content_type) {
			return this;
		}

		public Builder setUsage(int usage) {
			return this;
		}

		public Builder setFlags(int flags) {
			return this;
		}

		public Builder setLegacyStreamType(int legacy_stream_type) {
			return this;
		}

		public AudioAttributes build() {
			return new AudioAttributes();
		}
	}
}
