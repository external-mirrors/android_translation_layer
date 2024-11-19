package android.graphics.drawable;

import android.graphics.drawable.Drawable;

public class DrawableWrapper extends Drawable {
	private Drawable drawable;

	public DrawableWrapper(Drawable drawable) {
		this.drawable = drawable;
	}

	public Drawable getDrawable() {
		return drawable;
	}
}
