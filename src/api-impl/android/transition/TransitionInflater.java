package android.transition;

import android.content.Context;

public class TransitionInflater {

	public static TransitionInflater from(Context context) {
		return new TransitionInflater();
	}

	public Transition inflateTransition(int resourceId) {
		return null;
	}
}
