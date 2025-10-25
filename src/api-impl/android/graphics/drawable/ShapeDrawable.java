package android.graphics.drawable;

import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.shapes.Shape;

public class ShapeDrawable extends Drawable {

	private Paint paint = new Paint();

	public ShapeDrawable() {}

	public ShapeDrawable(Shape shape) {}

	public Paint getPaint() {
		return paint;
	}

	public void setPadding(Rect padding) {}

	public void setShape(Shape shape) {}

	@Override
	public void draw(Canvas canvas) {
		canvas.drawRect(getBounds(), paint);
	}

}
