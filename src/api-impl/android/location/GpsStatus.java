package android.location;

import android.os.IBinder;

public class GpsStatus {
	public static final int GPS_EVENT_STARTED = 1;
	public static final int GPS_EVENT_STOPPED = 2;
	public static final int GPS_EVENT_FIRST_FIX = 3;
	public static final int GPS_EVENT_SATELLITE_STATUS = 4;

	public interface Listener {
		void onGpsStatusChanged(int event);
	}

	public interface NmeaListener {
		void onNmeaReceived(long timestamp, String nmea);
	}

	public GpsStatus() {}

	public int getTimeToFirstFix() {
		return 0;
	}

	public Iterable<GpsSatellite> getSatellites() {
		return new java.util.ArrayList<GpsSatellite>();
	}

	public int getMaxSatellites() {
		return 24;
	}
}
