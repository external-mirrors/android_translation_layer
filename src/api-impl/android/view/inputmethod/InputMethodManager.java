package android.view.inputmethod;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import android.os.IBinder;
import android.view.View;

public class InputMethodManager {

	private ArrayList<InputMethodInfo> input_method_list = new ArrayList<InputMethodInfo>();

	public boolean hideSoftInputFromWindow(IBinder windowToken, int flags) {return false;}

	public boolean showSoftInput(View view, int flags) {return false;}

	public boolean isFullscreenMode() {return false;}

	public boolean isActive(View view) {return false;}

	public List<InputMethodInfo> getEnabledInputMethodList() {
		return input_method_list;
	}

	public List<InputMethodInfo> getInputMethodList() {
		return input_method_list;
	}

	public void restartInput(View view) {}

	public void updateSelection(View view, int selStart, int selEnd, int candidatesStart, int candidatesEnd) {}

}
