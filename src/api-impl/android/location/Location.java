package android.location;

public class Location {

	private double latitude;
	private double longitude;
	private double bearing;

	public Location (double latitude, double longitude, double bearing) {
		this.latitude = latitude;
		this.longitude = longitude;
		this.bearing = bearing;
	}

	public double getLatitude() {
		return latitude;
	}

	public double getLongitude() {
		return longitude;
	}

	public double getBearing() {
		return bearing;
	}

}
