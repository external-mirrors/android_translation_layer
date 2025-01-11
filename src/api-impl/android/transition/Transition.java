package android.transition;

public class Transition {

	public interface TransitionListener {}

	public Transition clone() {
		return new Transition();
	}

	public Transition addListener(TransitionListener listener) {
		return this;
	}
}
