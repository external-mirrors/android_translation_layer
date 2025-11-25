package android.app;

import android.content.Context;
import android.widget.TimePicker;

public class TimePickerDialog extends AlertDialog {
	public TimePickerDialog(Context context, OnTimeSetListener listener, int hourOfDay, int minute, boolean is24HourView) {
		super(context);
	}
	
	public interface OnTimeSetListener {
		void onTimeSet(TimePicker view, int hourOfDay, int minute);
	}
}
