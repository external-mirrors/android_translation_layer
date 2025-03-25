package android.view.animation;

public class Animation {

	public interface AnimationListener {
		public void onAnimationEnd(Animation animation);
		public void onAnimationRepeat(Animation animation);
		public void onAnimationStart(Animation animation);
	}

	private AnimationListener listener;

	public void setDuration(long durationMillis) {}

	public void setInterpolator(Interpolator i) {}

	public void cancel() {}

	public void setFillBefore(boolean dummy) {}
	public void setFillAfter(boolean dummy) {}

	public void setStartOffset(long offset) {}

	public void setAnimationListener(AnimationListener l) {
		this.listener = l;
	}

	public void setRepeatCount(int count) {}

	public void setRepeatMode(int mode) {}

	public void reset() {}

	public void start() {
		if (listener != null) {
			listener.onAnimationStart(this);
			listener.onAnimationEnd(this);
		}
	}

	public boolean hasStarted() {
		return false;
	}
}
