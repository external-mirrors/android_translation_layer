package android.widget;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;

public class Button extends TextView {

	public Button(Context context) {
		super(context);
	}

	public Button(Context context, AttributeSet attributeSet) {
		super(context, attributeSet);

		TypedArray a = context.obtainStyledAttributes(attributeSet, com.android.internal.R.styleable.TextView, 0, 0);
		if (a.hasValue(com.android.internal.R.styleable.TextView_text)) {
			setText(a.getText(com.android.internal.R.styleable.TextView_text));
		}

		if(getBackground() != null){
			native_addClass(widget, "ATL-no-border");
		}
		a.recycle();
	}

	@Override
	protected native long native_constructor(Context context, AttributeSet attrs);
	public native final void native_setText(long widget, String text);
	@Override
	protected native void nativeSetOnClickListener(long widget);

	@Override
	public void setText(CharSequence text) {
		native_setText(widget, String.valueOf(text));
	}

	@Override
	public native CharSequence getText();

	@Override
	public void setTextSize(float size) {}

	@Override
	public void setCompoundDrawables(Drawable left, Drawable top, Drawable right, Drawable bottom) {}

}
