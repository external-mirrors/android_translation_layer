package android.widget;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.text.Editable;
import android.text.SpannableStringBuilder;
import android.text.TextWatcher;
import android.util.AttributeSet;

public class EditText extends TextView {
	public EditText(Context context) {
		super(context);
	}

	public EditText(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	@Override
	protected native long native_constructor(Context context, AttributeSet attrs);
	protected native String native_getText(long widget);
	protected native void native_addTextChangedListener(long widget, TextWatcher watcher);
	protected native void native_removeTextChangedListener(long widget, TextWatcher watcher);
	protected native void native_setOnEditorActionListener(long widget, OnEditorActionListener l);
	protected native void native_setText(long widget, String text);

	public Editable getText() {
		return new SpannableStringBuilder(native_getText(widget));
	}

	public Editable getEditableText() {
		return new SpannableStringBuilder(native_getText(widget));
	}

	@Override
	public void setText(CharSequence text) {
		native_setText(widget, String.valueOf(text));
	}
	@Override
	public void setTextSize(float size) {}

	@Override
	public void removeTextChangedListener(TextWatcher watcher) {
		native_removeTextChangedListener(widget, watcher);
	}

	@Override
	public void addTextChangedListener(TextWatcher watcher) {
		native_addTextChangedListener(widget, watcher);
	}

	@Override
	public void setOnEditorActionListener(OnEditorActionListener l) {
		native_setOnEditorActionListener(widget, l);
	}

	@Override
	public void setCompoundDrawables(Drawable left, Drawable top, Drawable right, Drawable bottom) {}

	public void selectAll() {}
}
