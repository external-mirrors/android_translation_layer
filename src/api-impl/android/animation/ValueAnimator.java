package android.animation;

public class ValueAnimator extends Animator {

	private AnimatorUpdateListener update_listener;
	private Object value_end;

	public static ValueAnimator ofFloat(float... values) {
		ValueAnimator animator = new ValueAnimator();
		animator.value_end = values[values.length - 1];
		return animator;
	}

	public static ValueAnimator ofObject(TypeEvaluator evaluator, Object[] values) {
		ValueAnimator animator = new ValueAnimator();
		animator.value_end = values[values.length - 1];
		return animator;
	}

	public static ValueAnimator ofInt(int... values) {
		ValueAnimator animator = new ValueAnimator();
		animator.value_end = values[values.length - 1];
		return animator;
	}

	public ValueAnimator setDuration(long duration) {
		return this;
	}

	public void addUpdateListener(AnimatorUpdateListener listener) {
		this.update_listener = listener;
	}

	public static long getFrameDelay() {
		return 20; // 20ms frame interval
	}

	public PropertyValuesHolder[] getValues() {
		return null;
	}

	public long getStartDelay() {return 0;}
	public long getDuration() {return 0;}
	public TimeInterpolator getInterpolator() {return null;}
	public int getRepeatCount() {return 0;}
	public int getRepeatMode() {return 0;}
	public void setInterpolator(TimeInterpolator interpolator) {}
	public void setFloatValues(float[] values) {
		value_end = values[values.length - 1];
	}
	public boolean isRunning() {return false;}
	public void setIntValues(int[] values) {
		value_end = values[values.length - 1];
	}
	public void setRepeatCount(int value) {}
	public void setRepeatMode(int value) {}
	public void cancel() {}
	public void setEvaluator(TypeEvaluator evaluator) {}
	public void setStartDelay(long startDelay) {}

	@Override
	public void start() {
		if (update_listener != null)
			update_listener.onAnimationUpdate(this);
		super.start();
	}

	public Object getAnimatedValue() {
		return value_end;
	}

	public float getAnimatedFraction() {
		return 1.0f;
	}

	public void setObjectValues(Object[] values) {}

	/**
	 * Implementors of this interface can add themselves as update listeners
	 * to an <code>ValueAnimator</code> instance to receive callbacks on every animation
	 * frame, after the current frame's values have been calculated for that
	 * <code>ValueAnimator</code>.
	 */
	public static interface AnimatorUpdateListener {
		/**
		 * <p>Notifies the occurrence of another frame of the animation.</p>
		 *
		 * @param animation The animation which was repeated.
		 */
		void onAnimationUpdate(ValueAnimator animation);
	}
}
