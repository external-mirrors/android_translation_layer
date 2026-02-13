package android.widget;

import android.content.Context;
import android.util.AttributeSet;

public class DatePicker extends FrameLayout {

	public interface OnDateChangedListener {
		void onDateChanged(DatePicker view, int year, int monthOfYear, int dayOfMonth);
	}

	public DatePicker(Context context) {
		this(context, null);
	}

	public DatePicker(Context context, AttributeSet attrs) {
		this(context, attrs, 0);
	}

	public DatePicker(Context context, AttributeSet attrs, int defStyleAttr) {
		this(context, attrs, defStyleAttr, 0);
	}

	public DatePicker(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
		super(context, attrs, defStyleAttr, defStyleRes);
	}

	public void setMinDate(long minDate) {}

	public void setMaxDate(long maxDate) {}

	public void init(int year, int monthOfYear, int dayOfMonth, OnDateChangedListener listener) {}

	public void setFirstDayOfWeek(int dayOfWeek) {}
}
