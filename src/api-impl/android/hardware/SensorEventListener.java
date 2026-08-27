package android.hardware;

import android.atl.annotation.Export;

public interface SensorEventListener {

	@Export
	public void onSensorChanged(SensorEvent event);
}
