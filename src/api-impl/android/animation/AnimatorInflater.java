package android.animation;

import android.content.Context;

public class AnimatorInflater {

	public static Animator loadAnimator(Context context, int resId) {
		return new AnimatorSet();
	}

	public static StateListAnimator loadStateListAnimator(Context context, int resId) {
		return new StateListAnimator();
	}

}
