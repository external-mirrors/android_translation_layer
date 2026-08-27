package android.content;

import android.atl.annotation.Export;

public interface DialogInterface {
	/** The identifier for the positive button. */
	int BUTTON_POSITIVE = -1;
	/** The identifier for the negative button. */
	int BUTTON_NEGATIVE = -2;
	/** The identifier for the neutral button. */
	int BUTTON_NEUTRAL = -3;

	@Export
	public void dismiss();

	public void cancel();

	public interface OnDismissListener {
		void onDismiss(DialogInterface dialog);
	}
	public interface OnClickListener {
		@Export
		void onClick(DialogInterface dialog, int which);
	}
	public interface OnShowListener {
		void onShow(DialogInterface dialog);
	}
	public interface OnCancelListener {
	}
	public interface OnMultiChoiceClickListener {
	}
	public interface OnKeyListener {
	}
}
