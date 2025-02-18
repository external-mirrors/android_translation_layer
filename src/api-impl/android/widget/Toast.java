package android.widget;

import android.content.Context;
import android.view.View;

public class Toast {

	public Toast(Context context) {
		/* TODO */
	}

	private String text;

	public static Toast makeText(Context context, int resId, int duration) {
		return makeText(context, context.getString(resId), duration);
	}

	public static Toast makeText(Context context, CharSequence text, int duration) {
		Toast toast = new Toast(context);
		toast.text = String.valueOf(text);
		return toast;
	}

	public void show() {
		System.out.println("showing toast: " + text);
	}

	public void setView(View view) {}
}
