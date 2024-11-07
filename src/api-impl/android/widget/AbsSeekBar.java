package android.widget;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;

public abstract class AbsSeekBar extends ProgressBar {

	public AbsSeekBar(Context context) {
		super(context);
	}

	public AbsSeekBar(Context context, AttributeSet attributeSet) {
		super(context, attributeSet);
	}

	public Drawable getThumb() {
		return new Drawable() {
			@Override
			public void draw(Canvas canvas) {
				// TODO Auto-generated method stub
				throw new UnsupportedOperationException("Unimplemented method 'draw'");
			}
		};
	}

	public void setKeyProgressIncrement(int keyProgressIncrement) {}

	public int getKeyProgressIncrement() {return 0;}
}
