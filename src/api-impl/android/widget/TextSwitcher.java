package android.widget;

import android.content.Context;
import android.util.AttributeSet;

public class TextSwitcher extends ViewSwitcher {

	public TextSwitcher(Context context) {
		this(context, null);
	}

	public TextSwitcher(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	public void setText(CharSequence text) {
		final TextView t = (TextView)getNextView();
		t.setText(text);
		showNext();
	}

	public void setCurrentText(CharSequence text) {
		((TextView)getCurrentView()).setText(text);
	}
}
