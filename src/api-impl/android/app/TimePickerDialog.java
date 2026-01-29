package android.app;

import android.content.Context;
import android.widget.TimePicker;

public class TimePickerDialog extends AlertDialog {
	public TimePickerDialog(Context context, OnTimeSetListener listener, int hourOfDay, int minute, boolean is24HourView) {
		this(context, 0, listener, hourOfDay, minute, is24HourView);
	}

	public TimePickerDialog(Context context, int themeResId, OnTimeSetListener listener, int hourOfDay, int minute, boolean is24HourView)  {
		super(context, themeResId);

		setTitle("Time Picker");
		setView(new TimePicker(context));
	}
	
	public void onTimeSet(TimePicker view, int hourOfDay, int minute) {

	}

	public static interface OnTimeSetListener {
		void onTimeSet(TimePicker view, int hourOfDay, int minute);
	}
}
