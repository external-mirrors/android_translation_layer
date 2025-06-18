package android.media;

public class AudioRecord {

	public static int getMinBufferSize(int sampleRateInHz, int channelConfig, int audioFormat) {
		return 1000;
	}
}
