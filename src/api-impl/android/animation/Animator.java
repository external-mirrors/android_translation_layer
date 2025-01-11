package android.animation;

import android.os.Handler;
import android.os.Looper;

public class Animator {

	public interface AnimatorListener {
		public abstract void onAnimationEnd (Animator animation);
	}

	private long duration = 50;
	private AnimatorListener listener;

	public void setTarget(Object target) {}

	public void start() {
		if (listener == null)
			return;
		new Handler(Looper.getMainLooper()).postDelayed(new Runnable() {
			public void run() {
				if (listener != null)
					listener.onAnimationEnd(Animator.this);
			}
		}, duration);
	}

	public void addListener(AnimatorListener listener) {
		this.listener = listener;
	}

	public void cancel() {}

	public long getStartDelay() { return 0; }

	public long getDuration() { return duration; }

	public Animator setDuration(long duration) {
		this.duration = duration;
		return this;
	}

	public void setInterpolator(TimeInterpolator i) {}

	public void setStartDelay(long startDelay) {}

	public boolean isStarted() { return false; }

	public void end() {}

	public TimeInterpolator getInterpolator() { return null; }

	public boolean isRunning() { return false; }

}
