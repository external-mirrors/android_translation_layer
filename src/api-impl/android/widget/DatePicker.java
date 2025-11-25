package android.widget;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;

public class DatePicker extends View {

	public interface OnDateChangedListener {
		void onDateChanged(DatePicker view, int year, int monthOfYear, int dayOfMonth);
	}

	public DatePicker(Context context) {
		super(context);
	}

	public DatePicker(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	public DatePicker(Context context, AttributeSet attrs, int defStyleAttr) {
		super(context, attrs, defStyleAttr);
	}

	public void setMinDate(long minDate) {}

	public void setMaxDate(long maxDate) {}

	public void init(int year, int monthOfYear, int dayOfMonth, OnDateChangedListener listener) {}
}
