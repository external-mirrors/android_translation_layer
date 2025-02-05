package android.widget;

import android.content.Context;
import android.database.DataSetObserver;
import android.util.AttributeSet;

public class Spinner extends AbsSpinner {
	private Observer observer;

	public Spinner(Context context) {
		super(context);
		haveCustomMeasure = false;
	}

	public Spinner(Context context, AttributeSet attributeSet) {
		super(context, attributeSet);
		haveCustomMeasure = false;
	}

	public Spinner(Context context, AttributeSet attributeSet, int defStyle) {
		super(context, attributeSet, defStyle);
		haveCustomMeasure = false;
	}

	@Override
	protected native long native_constructor(Context context, AttributeSet attrs);
	protected native void native_setAdapter(long widget, SpinnerAdapter adapter);

	public void setAdapter(SpinnerAdapter adapter) {
		if (observer == null)
			observer = new Observer();
		SpinnerAdapter oldAdapter = getAdapter();
		if (oldAdapter != null)
			oldAdapter.unregisterDataSetObserver(observer);
		super.setAdapter(adapter);
		if (adapter != null)
			adapter.registerDataSetObserver(observer);
		native_setAdapter(this.widget, adapter);
	}

	public SpinnerAdapter getAdapter() {
		return (SpinnerAdapter) super.getAdapter();
	}

	@Override
	public native void setOnItemSelectedListener(AdapterView.OnItemSelectedListener listener);

	private class Observer extends DataSetObserver {

		@Override
		public void onChanged() {
			Spinner.this.native_setAdapter(widget, getAdapter());
		}
		@Override
		public void onInvalidated() {
			Spinner.this.native_setAdapter(widget, getAdapter());
		}
	}

	@Override
	void layout(int delta, boolean animate) {}

}
