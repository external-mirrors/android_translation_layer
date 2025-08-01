package android.media;

import java.io.IOException;

import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;

public class SoundPool {

	private long nativePool;

	public interface OnLoadCompleteListener {
		/**
		 * Called when a sound has completed loading.
		 *
		 * @param soundPool SoundPool object from the load() method
		 * @param soundPool the sample ID of the sound loaded.
		 * @param status the status of the load operation (0 = success)
		 */
		public void onLoadComplete(SoundPool soundPool, int sampleId, int status);
	}

	public SoundPool(int maxStreams, int streamType, int srcQuality) {
		nativePool = native_constructor();
	}

	public int load(AssetFileDescriptor afd, int priority) throws IOException {
		AssetManager.extractFromAPK(Context.this_application.getPackageCodePath(), afd.fileName, afd.fileName);
		return nativeLoad(nativePool, android.os.Environment.getExternalStorageDirectory().getPath() + "/" + afd.fileName);
	}

	/**
	 * Sets the callback hook for the OnLoadCompleteListener.
	 */
	public void setOnLoadCompleteListener(OnLoadCompleteListener listener) {
		System.out.println("WARNING: SoundPool.setOnLoadCompleteListener not implemented yet");
	}

	public final int play(int soundID, float leftVolume, float rightVolume, int priority, int loop, float rate) {
		return nativePlay(nativePool, soundID);
	}

	public void autoResume() {
		System.out.println("WARNING: SoundPool.autoResume not implemented yet");
	}

	public void autoPause() {
		System.out.println("WARNING: SoundPool.autoPause not implemented yet");
	}

	public void setVolume(int streamType, float leftVolume, float rightVolume) {
		System.out.println("WARNING: SoundPool.setVolume not implemented yet");
	}

	public class Builder {
		public Builder setAudioAttributes(AudioAttributes attributes) {
			return this;
		}

		public Builder setMaxStreams(int maxStreams) {
			return this;
		}

		public SoundPool build() {
			return new SoundPool(0, 0, 0); // FIXME
		}
	}

	private static native long native_constructor();
	private static native int nativeLoad(long nativePool, String path);
	public static native int nativePlay(long nativePool, int soundID);
}
