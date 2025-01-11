package android.view.animation;

import android.os.Handler;
import android.os.Looper;

public class Animation {

	public interface AnimationListener {
		public void onAnimationEnd(Animation animation);
		public void onAnimationRepeat(Animation animation);
		public void onAnimationStart(Animation animation);
	}

	public void setDuration(long durationMillis) {}

	public void setInterpolator(Interpolator i) {}

	public void cancel() {}

	public void setFillBefore(boolean dummy) {}
	public void setFillAfter(boolean dummy) {}

	public void setStartOffset(long offset) {}

	public void setAnimationListener(AnimationListener l) {
		new Handler(Looper.getMainLooper()).post(new Runnable() {
			@Override
			public void run() {
				l.onAnimationEnd(Animation.this); // FIXME
			}
		});
	}

	public void setRepeatCount(int count) {}

	public void reset() {}

	public void start() {}
}
