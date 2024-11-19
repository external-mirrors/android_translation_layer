package android.graphics.drawable;

import android.graphics.Rect;
import android.graphics.drawable.DrawableWrapper;

public class InsetDrawable extends DrawableWrapper {

	public InsetDrawable(Drawable drawable, int insetLeft, int insetTop, int insetRight, int insetBottom) {
		super(drawable);
	}

	public InsetDrawable(Drawable drawable, int inset) {
		super(drawable);
	}

	public boolean getPadding(Rect padding) { return false; }
}
