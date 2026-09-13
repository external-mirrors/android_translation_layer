package android.os;

public class ResultReceiver implements Parcelable {
	private Handler handler;

	public ResultReceiver(Handler handler) {
		this.handler = handler;
	}

	public void send(int resultCode, Bundle resultData) {
		if (handler != null)
			handler.post(new MyRunnable(resultCode, resultData));
		else
			onReceiveResult(resultCode, resultData);
	}

	protected void onReceiveResult(int resultCode, Bundle resultData) {
	}

	public int describeContents() {
		return 0;
	}

	public void writeToParcel(Parcel dest, int flags) {
	}

	public static final Parcelable.Creator<ResultReceiver> CREATOR = new Parcelable.Creator<ResultReceiver>() {
		public ResultReceiver createFromParcel(Parcel in) {
			return new ResultReceiver(null);
		}

		public ResultReceiver[] newArray(int size) {
			return new ResultReceiver[size];
		}
	};

	private class MyRunnable implements Runnable {
		private int resultCode;
		private Bundle resultData;

		public MyRunnable(int resultCode, Bundle resultData) {
			this.resultCode = resultCode;
			this.resultData = resultData;
		}

		public void run() {
			onReceiveResult(resultCode, resultData);
		}
	}
}
