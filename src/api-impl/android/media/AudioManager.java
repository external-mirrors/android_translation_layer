package android.media;

import android.media.AudioDeviceInfo;
import android.media.AudioDeviceCallback;
import android.os.Handler;

public class AudioManager {
	public static final String PROPERTY_OUTPUT_FRAMES_PER_BUFFER = "android.media.property.OUTPUT_FRAMES_PER_BUFFER";
	public static final String PROPERTY_OUTPUT_SAMPLE_RATE = "android.media.property.OUTPUT_SAMPLE_RATE";

	public static final int STREAM_MUSIC = 0x3;

	private native void nativeSetStreamVolume(int volume);

	public boolean isBluetoothA2dpOn() {
		return false;
	}

	public String getProperty(String name) {
		System.out.println("### AudioManager! getProperty ->" + name);
		switch (name) {
			case PROPERTY_OUTPUT_FRAMES_PER_BUFFER:
				return "256"; // FIXME arbitrary
			case PROPERTY_OUTPUT_SAMPLE_RATE:
				return "44100"; // FIXME arbitrary
			default:
				System.out.println("AudioManager.getProperty: >" + name + "< not handled");
				return "";
		}
	}

	public interface OnAudioFocusChangeListener {
	}

	public static final int GET_DEVICES_INPUTS  = 0x0001;
	public static final int GET_DEVICES_OUTPUTS = 0x0002;
	public static final int GET_DEVICES_ALL     = GET_DEVICES_OUTPUTS | GET_DEVICES_INPUTS;

	public AudioDeviceInfo[] getDevices(int flags) {
		System.out.println("### AudioManager! getDevices=" + flags);

		AudioDeviceInfo info = new AudioDeviceInfo();
		AudioDeviceInfo[] arr = new AudioDeviceInfo[2];
		arr[0] = info;
		arr[1] = info;

		return arr;
	}

	public void registerAudioDeviceCallback(AudioDeviceCallback callback, android.os.Handler handler) {
		System.out.println("### AudioManager! registerAudioDeviceCallback");
		callback.onAudioDevicesAdded(getDevices(3));
	}

	public int getRingerMode() {
		System.out.println("### AudioManager! 3");
		return 0;
	}

	public int getStreamVolume(int streamType) {
		System.out.println("### AudioManager! 4");
		return 0; // arbitrary, shouldn't matter too much?
	}

	public int getStreamMaxVolume(int streamType) {
		System.out.println("### AudioManager! 5");
		return 100;
	}

	public int requestAudioFocus(OnAudioFocusChangeListener listener, int streamType, int durationHint) {
		System.out.println("### AudioManager! 6");
		return /*AUDIOFOCUS_REQUEST_GRANTED*/ 1;
	}

	public int abandonAudioFocus(OnAudioFocusChangeListener listener) {
		System.out.println("### AudioManager! 7");
		return /*AUDIOFOCUS_REQUEST_GRANTED*/ 1;
	}

	public boolean isWiredHeadsetOn() {
		System.out.println("### AudioManager! 8");
		return false;
	}

	public void setStreamVolume(int streamType, int index, int flags) {
		System.out.println("### AudioManager! 9");
		nativeSetStreamVolume(index);
	}

	public boolean isStreamMute(int streamType) {
		System.out.println("### AudioManager! 10");
		return false;
	}

	public boolean isMusicActive() {
		System.out.println("### AudioManager! 11");
		return false;
	}

	public void setSpeakerphoneOn(boolean on) {
		System.out.println("### AudioManager! 12");
	}

	public boolean isSpeakerphoneOn() {
		System.out.println("### AudioManager! 13");
		return false;
	}

	public void setBluetoothScoOn(boolean on) {}

	public boolean isBluetoothScoOn() {
		System.out.println("### AudioManager! ");
		return false;
	}

	public void stopBluetoothSco() {
		System.out.println("### AudioManager! ");
	}

	public void setMode(int mode) {
		System.out.println("### AudioManager! 14");
	}

	public int getMode() {
		System.out.println("### AudioManager! ");
		return /*MODE_NORMAL*/ 0;
	}

	public boolean isMicrophoneMute() {
		System.out.println("### AudioManager! ");
		return false;
	}

	public void setMicrophoneMute(boolean on) {
		System.out.println("AudioManager.setMicrophoneMute(" + on + ")");
	}
	public void unloadSoundEffects() {
		System.out.println("### AudioManager! 18");
	}

	public int generateAudioSessionId() {
		System.out.println("### AudioManager! 19");
		return 0;
	}
}
