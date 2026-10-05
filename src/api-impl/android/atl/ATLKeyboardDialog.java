package android.atl;

import android.app.Dialog;
import android.content.Context;

public class ATLKeyboardDialog extends Dialog {
	@Override
	protected native long nativeInit(long decor_view);

	public ATLKeyboardDialog(Context context) {
		super(context);
	}
}
