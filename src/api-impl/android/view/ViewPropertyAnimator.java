package android.view;

import android.animation.Animator;
import android.animation.TimeInterpolator;
import android.animation.ValueAnimator;
import android.os.Handler;

public class ViewPropertyAnimator {

	private View view;
	private Animator.AnimatorListener listener;
	private long startDelay;
	private long duration;

	public ViewPropertyAnimator(View view) {
		this.view = view;
	}

	public void cancel() {}

	public ViewPropertyAnimator setInterpolator(TimeInterpolator interpolator) {
		return this;
	}

	public ViewPropertyAnimator setListener(Animator.AnimatorListener listener) {
		this.listener = listener;
		return this;
	}

	public ViewPropertyAnimator alpha(float alpha) {
		view.setAlpha(alpha);
		return this;
	}

	public ViewPropertyAnimator setDuration(long duration) {
		this.duration = duration;
		return this;
	}

	public ViewPropertyAnimator setStartDelay(long startDelay) {
		this.startDelay = startDelay;
		return this;
	}

	public ViewPropertyAnimator x(float rotation) {
		return this;
	}

	public ViewPropertyAnimator y(float rotation) {
		return this;
	}

	public ViewPropertyAnimator rotation(float rotation) {
		return this;
	}

	public ViewPropertyAnimator translationX(float translationX) {
		return this;
	}

	public ViewPropertyAnimator translationY(float translationY) {
		return this;
	}

	public ViewPropertyAnimator scaleX(float scaleX) {
		return this;
	}

	public ViewPropertyAnimator scaleY(float scaleY) {
		return this;
	}

	public ViewPropertyAnimator translationXBy(float translationX) {
		return this;
	}

	public ViewPropertyAnimator rotationBy(float rotation) {
		return this;
	}

	public void start() {
		new Handler().postDelayed(new Runnable() {

			@Override
			public void run() {
				if (listener != null)
					listener.onAnimationEnd(new ValueAnimator());
			}
		}, startDelay+duration);
	}

	public ViewPropertyAnimator withEndAction(Runnable runnable) {
		return this;
	}

	public ViewPropertyAnimator withStartAction(Runnable runnable) {
		return this;
	}
}
