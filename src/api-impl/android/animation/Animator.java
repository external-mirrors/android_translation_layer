package android.animation;

import android.os.Handler;
import android.os.Looper;

public class Animator {

	public interface AnimatorListener {
		public abstract void onAnimationEnd (Animator animation);
	}

	private AnimatorListener listener;

	public void setTarget(Object target) {}

	public void start() {
		if (listener == null)
			return;
		new Handler(Looper.getMainLooper()).post(new Runnable() {
			public void run() {
				if (listener != null)
					listener.onAnimationEnd(Animator.this);
			}
		});
	}

	public void addListener(AnimatorListener listener) {
		this.listener = listener;
	}

	public void cancel() {}

	public long getStartDelay() { return 0; }

	public long getDuration() { return 0; }

	public Animator setDuration(long duration) { return this; }

	public void setInterpolator(TimeInterpolator i) {}

	public void setStartDelay(long startDelay) {}

	public boolean isStarted() { return false; }

	public void end() {}

}
