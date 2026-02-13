package android.widget;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;

public class EdgeEffect extends View {

	public EdgeEffect(Context context) {
		super(context);
	}

	public EdgeEffect(Context context, AttributeSet attributeSet) {
		super(context, attributeSet);
	}

	public void setSize(int width, int height) {}
	public void onPull(float deltaDistance) {}
	public void onPull(float deltaDistance, float displacement) {}
	public boolean isFinished() { return true; }
	public void onRelease() {}
	public void onAbsorb(int velocity) {}
	public int getColor() { return 0; }
	public void setColor(int color) {}
}
