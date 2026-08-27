package android.hardware;

import android.atl.annotation.Export;

public class SensorEvent {

	public final float[] values;

	public Sensor sensor;

	@Export
	public SensorEvent(float[] values, Sensor sensor) {
		this.values = values;
		this.sensor = sensor;
	}
}
