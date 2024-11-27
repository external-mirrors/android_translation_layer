package android.graphics.drawable;

import android.content.res.ColorStateList;

public class RippleDrawable extends LayerDrawable {

	public RippleDrawable(ColorStateList colorStateList, Drawable drawable, Drawable drawable2) {
		super(drawable == null ? new Drawable[] {} : new Drawable[] {drawable});
	}

	public void setColor(ColorStateList colorStateList) {}

}
