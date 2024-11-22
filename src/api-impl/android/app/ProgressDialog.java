package android.app;

import android.content.Context;

public class ProgressDialog extends AlertDialog {

	public ProgressDialog(Context context) {
		super(context, 0);
	}

	public ProgressDialog(Context context, int themeResId) {
		super(context, themeResId);
	}

	public void setIndeterminate(boolean indeterminate) {}

	public static ProgressDialog show(Context context, CharSequence title, CharSequence message, boolean indeterminate, boolean cancelable, OnCancelListener cancelListener) {
		return new ProgressDialog(context);
	}
}
