package android.view;

public class WindowInsets {

	public static final WindowInsets CONSUMED = new WindowInsets();

	public WindowInsets() {}

	public WindowInsets(WindowInsets windowInsets) {}

	public WindowInsets consumeStableInsets() {
		return this;
	}

	public WindowInsets consumeSystemWindowInsets() {
		return this;
	}

	public WindowInsets replaceSystemWindowInsets(int left, int top, int right, int bottom) {
		return this;
	}

	public int getSystemWindowInsetLeft() {
		return 0;
	}

	public int getSystemWindowInsetTop() {
		return 0;
	}

	public int getSystemWindowInsetRight() {
		return 0;
	}

	public int getSystemWindowInsetBottom() {
		return 0;
	}

	public int getStableInsetLeft() {
		return 0;
	}

	public int getStableInsetTop() {
		return 0;
	}

	public int getStableInsetRight() {
		return 0;
	}

	public int getStableInsetBottom() {
		return 0;
	}

	public boolean isRound() {
		return false;
	}

	public boolean isConsumed() {
		return false;
	}

	public WindowInsets consumeDisplayCutout() {
		return this;
	}
}
