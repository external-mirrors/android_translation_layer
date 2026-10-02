package com.google.android.gms.ads.measurement;

import android.os.IBinder;
import android.os.IInterface;
import android.os.Parcel;

public class DynamiteMeasurementManager implements IBinder {

	@Override
	public String getInterfaceDescriptor() {
		return "com.google.android.gms.ads.measurement.IMeasurementManager";
	}

	public void initialize() {
	}

	@Override
	public boolean transact(int code, Parcel data, Parcel reply, int flags) {
		return true;
	}

	@Override
	public IInterface queryLocalInterface(String descriptor) {
		return null;
	}
}
