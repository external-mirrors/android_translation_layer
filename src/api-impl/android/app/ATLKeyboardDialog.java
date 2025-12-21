package android.app;

import android.content.Context;

public class ATLKeyboardDialog extends Dialog {
	@Override
	protected native long nativeInit(boolean is_floating);

	public ATLKeyboardDialog(Context context) {
		super(context);
	}
}
