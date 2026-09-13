package android.os;

public abstract class CountDownTimer {
	private final long millisInFuture;
	private final long countDownInterval;
	private long stopTimeInFuture;
	private boolean cancelled;
	private Handler handler;

	public CountDownTimer(long millisInFuture, long countDownInterval) {
		this.millisInFuture = millisInFuture;
		this.countDownInterval = countDownInterval;
		handler = new Handler();
	}

	public final void cancel() {
		cancelled = true;
		handler.removeCallbacks(tickRunnable);
	}

	public abstract void onFinish();

	public abstract void onTick(long millisUntilFinished);

	public final CountDownTimer start() {
		cancelled = false;
		if (millisInFuture <= 0) {
			onFinish();
		} else {
			stopTimeInFuture = SystemClock.elapsedRealtime() + millisInFuture;
			handler.postDelayed(tickRunnable, countDownInterval);
		}
		return this;
	}

	private final Runnable tickRunnable = new Runnable() {
		public void run() {
			if (cancelled)
				return;

			long remaining = stopTimeInFuture - SystemClock.elapsedRealtime();

			if (remaining <= 0) {
				onFinish();
			} else {
				onTick(remaining);
				handler.postDelayed(this, Math.min(countDownInterval, remaining));
			}
		}
	};
}
