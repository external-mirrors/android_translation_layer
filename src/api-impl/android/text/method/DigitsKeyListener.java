package android.text.method;

import android.text.method.NumberKeyListener;

public class DigitsKeyListener extends NumberKeyListener {
	public DigitsKeyListener() {}

	public DigitsKeyListener(boolean sign, boolean decimal) {}

	public static DigitsKeyListener getInstance(String locale) {
		return new DigitsKeyListener();
	}
}
