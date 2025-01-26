package android.media;

public class MediaCodecList {

	public static int getCodecCount() {
		return 4;
	}

	public static MediaCodecInfo getCodecInfoAt(int index) {
		switch (index) {
		case 0:
			return new MediaCodecInfo("aac", "audio/mp4a-latm");
		case 1:
			return new MediaCodecInfo("h264", "video/avc");
		case 2:
			return new MediaCodecInfo("mp3", "audio/mpeg");
		case 3:
			return new MediaCodecInfo("opus", "audio/opus");
		default:
			return null;
		}
	}

}
