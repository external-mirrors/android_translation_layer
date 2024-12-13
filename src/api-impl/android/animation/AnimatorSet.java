package android.animation;

import java.util.ArrayList;
import java.util.Collection;

public class AnimatorSet extends Animator {

	public class Builder {

		public Builder with(Animator animator) {
			return this;
		}
	}

	public Builder play(Animator animator) {
		return new Builder();
	}

	public void setInterpolator(TimeInterpolator value) {}

	public void playSequentially(Animator[] animators) {}

	public boolean isStarted() {
		return false;
	}

	public void playTogether(Collection<Animator> animators) {}

	public AnimatorSet setDuration(long duration) { return this; }

	public void playTogether(Animator[] animators) {}

	public ArrayList<Animator> getChildAnimations() {
		return new ArrayList<Animator>(0);
	}

}
