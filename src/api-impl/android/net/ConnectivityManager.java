package android.net;

import android.os.Handler;

public class ConnectivityManager {

	public class NetworkCallback {
		public void onAvailable(Network network) {}
		public void onLost(Network network) {}
	}

	public NetworkInfo getNetworkInfo(int networkType) {
		return new NetworkInfo(nativeGetNetworkAvailable());
	}

	public NetworkInfo getActiveNetworkInfo() {
		return new NetworkInfo(nativeGetNetworkAvailable());
	}

	public native void registerNetworkCallback(NetworkRequest request, NetworkCallback callback);

	public native boolean isActiveNetworkMetered();

	protected native boolean nativeGetNetworkAvailable();

	public NetworkInfo[] getAllNetworkInfo() {
		return new NetworkInfo[] { getActiveNetworkInfo() };
	}

	public Network getActiveNetwork() {
		return new Network();
	}

	public void registerDefaultNetworkCallback(NetworkCallback cb, Handler hdl) {}

}
