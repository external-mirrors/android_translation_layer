package android.text.style;

import android.content.Context;
import android.graphics.drawable.Drawable;

public class ImageSpan extends DynamicDrawableSpan {

	public ImageSpan(Context context, int resId) {}

	private Drawable drawable;

	public ImageSpan(Drawable d) {
		drawable = d;
	}

	public ImageSpan(Drawable d, String source) {
		drawable = d;
	}

	public ImageSpan(Drawable d, int verticalAlignment) {
		drawable = d;
	}

	public Drawable getDrawable() {
		return drawable;
	}
}
