package android.view;

public class WindowManagerImpl implements WindowManager, ViewManager {
	public android.view.Display getDefaultDisplay() {
		return new android.view.Display();
	}

	@Override
	public void addView(View view, android.view.ViewGroup.LayoutParams params) {
		System.out.println("WindowManagerImpl.addView(" + view + ", " + params + ") called");
		if (params.height == 0)  // FIXME: remove this hack once measurement error with composeUI popups is fixed
			params.height = 200;
		view.setLayoutParams(params);
		view.onAttachedToWindow();
		WindowManager.LayoutParams windowParams = (WindowManager.LayoutParams)params;
		native_addView(view.widget, windowParams.type, windowParams.x, windowParams.y, params.width, params.height);
	}

	@Override
	public void updateViewLayout(View view, android.view.ViewGroup.LayoutParams params) {
		System.out.println("WindowManagerImpl.updateViewLayout(" + view + ", " + params + ") called");
		if (params.height == 0)  // FIXME: remove this hack once measurement error with composeUI popups is fixed
			params.height = 200;
		WindowManager.LayoutParams windowParams = (WindowManager.LayoutParams)params;
		view.setLayoutParams(params);
		native_updateViewLayout(view.widget, windowParams.x, windowParams.y, params.width, params.height);
	}

	@Override
	public void removeView(View view) {
		native_removeView(view.widget);
	}

	@Override
	public void removeViewImmediate(View view) {
		removeView(view);
	}

	private static native void native_addView(long widget, int type, int x, int y, int width, int height);
	private static native void native_updateViewLayout(long widget, int x, int y, int width, int height);
	private static native void native_removeView(long widget);
}
