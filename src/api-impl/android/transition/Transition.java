package android.transition;

import android.animation.TimeInterpolator;
import android.view.View;

public class Transition {

	public interface TransitionListener {}

	public Transition clone() {
		return new Transition();
	}

	public Transition addListener(TransitionListener listener) {
		return this;
	}

	public Transition excludeTarget(int targetId, boolean exclude) {
		return this;
	}

	public Transition addTarget(View target) {
		return this;
	}

	public Transition addTarget(String targetName) {
		return this;
	}

	public Transition setDuration(long duration) {
		return this;
	}

	public Transition setInterpolator(TimeInterpolator interpolator) {
		return this;
	}
}
