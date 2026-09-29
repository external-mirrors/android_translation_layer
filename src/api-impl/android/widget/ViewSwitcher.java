package android.widget;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;

public class ViewSwitcher extends ViewAnimator {

	public interface ViewFactory {
		public View makeView();
	}

	private ViewFactory factory;

	public ViewSwitcher(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	public ViewSwitcher(Context context) {
		super(context);
	}

	public void setFactory(ViewFactory factory) {
		this.factory = factory;
	}

	@Override
	public View getCurrentView() {
		View view = super.getCurrentView();
		if (view == null && factory != null) {
			view = factory.makeView();
			addView(view);
		}
		return view;
	}

	public View getNextView() {
		int which = mWhichChild == 0 ? 1 : 0;
		View view = getChildAt(which);
		if (view == null && factory != null) {
			view = factory.makeView();
			addView(view);
		}
		return view;
	}
}
