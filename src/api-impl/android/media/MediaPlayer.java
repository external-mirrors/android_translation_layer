package android.media;

import android.content.Context;
import java.io.FileDescriptor;

public class MediaPlayer {
	private long gtk_media_stream;

	public interface OnCompletionListener {
		void onCompletion(MediaPlayer media_player);
	}
	public interface OnErrorListener {
	}
	public interface OnPreparedListener {
	}
	public interface OnBufferingUpdateListener {
	}
	public interface OnInfoListener {
	}
	public interface OnSeekCompleteListener {
	}
	public interface OnVideoSizeChangedListener {
	}
	public interface MediaPlayerControl {
	}

	public static MediaPlayer create(Context context, int dummy) { return new MediaPlayer(); }

	public void setDataSource(FileDescriptor src, long offset, long length) {}

	public void setDataSource(String path) {
		gtk_media_stream = native_setDataSource(path);
	}

	public void setLooping(boolean dummy) {}

	public void setOnCompletionListener(MediaPlayer.OnCompletionListener listener) {
		native_setOnCompletionListener(gtk_media_stream, listener);
	}

	public void setOnErrorListener(MediaPlayer.OnErrorListener dummy) {}
	public void setOnPreparedListener(MediaPlayer.OnPreparedListener dummy) {}
	public void setOnBufferingUpdateListener(MediaPlayer.OnBufferingUpdateListener dummy) {}
	public void setOnInfoListener(MediaPlayer.OnInfoListener dummy) {}
	public void setOnSeekCompleteListener(MediaPlayer.OnSeekCompleteListener dummy) {}
	public void setOnVideoSizeChangedListener(MediaPlayer.OnVideoSizeChangedListener dummy) {}
	public void setAudioAttributes(AudioAttributes attributes) {}
	public void setAudioStreamType(int dummy) {}

	public void start() {
		native_start(gtk_media_stream);
	}

	public void stop() {}
	public void pause() {}

	public void prepare() {
		native_prepare(gtk_media_stream);
	}

	public void prepareAsync() {}
	public void reset() {}
	public void release() {}

	public static native void native_prepare(long gtk_media_stream);
	public native long native_setDataSource(String path);
	public static native void native_setOnCompletionListener(long gtk_media_stream, MediaPlayer.OnCompletionListener listener);
	public static native void native_start(long gtk_media_stream);
}
