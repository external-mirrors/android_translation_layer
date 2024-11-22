package android.location;

import android.os.Bundle;

import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class LocationManager {

	static Set<LocationListener> listeners = new HashSet<>();

	public String getBestProvider(Criteria criteria, boolean enabledOnly) {
		return "xdgportal";
	}

	public Location getLastKnownLocation(String provider) {
		return null;
	}

	public void requestLocationUpdates (String provider, long minTimeMs, float minDistanceM, LocationListener listener) {
		listeners.add(listener);
		nativeGetLocation();
	}

	private native void nativeGetLocation();

	private static void locationUpdated(double latitude, double longitude, double heading) {
		for (LocationListener locationListener : listeners) {
			locationListener.onLocationChanged(new Location(latitude, longitude, heading));
		}
	}

	public boolean sendExtraCommand(String provider, String command, Bundle extras) {
		return true;
	}

	public void removeUpdates(LocationListener listener) {
	}

	public List<String> getAllProviders() {
		return Collections.emptyList();
	}
}
