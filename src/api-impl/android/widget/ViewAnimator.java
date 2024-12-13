package android.widget;

import android.content.Context;
import android.util.AttributeSet;
import android.view.ViewGroup;

public class ViewAnimator extends ViewGroup {

	public ViewAnimator(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	public void setDisplayedChild(int index) {}

	public int getDisplayedChild() { return 0; }
}
