package android.view;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.transition.Transition;
import android.view.SurfaceHolder;
import android.widget.FrameLayout;

public class Window {
	public static final int FEATURE_OPTIONS_PANEL = 0;
	public static final int FEATURE_NO_TITLE = 1;

	public static interface Callback {
		public void onContentChanged();

		public abstract boolean onCreatePanelMenu(int featureId, Menu menu);

		public View onCreatePanelView(int featureId);

		public boolean onPreparePanel(int featureId, View view, Menu menu);

		public boolean onMenuItemSelected(int featureId, MenuItem item);

		public void onPanelClosed(int featureId, Menu menu);

		public boolean onMenuOpened(int featureId, Menu menu);
	}

	public long native_window;
	private ViewGroup decorView;

	private Window.Callback callback;
	private Context context;

	public Window(Context context, Window.Callback callback) {
		this.callback = callback;
		this.context = context;
		decorView = new FrameLayout(context);
		decorView.setId(android.R.id.content);
		decorView.onAttachedToWindow();
	}

	public void addFlags(int flags) {}
	public void setFlags(int flags, int mask) {}
	public void clearFlags(int flags) {}

	public final Callback getCallback() {
		return this.callback;
	}
	public void setCallback(Window.Callback callback) {
		this.callback = callback;
	}

	public void setContentView(View view) {
		decorView.removeAllViews();
		decorView.addView(view);
		if (view != null) {
			set_widget_as_root(native_window, decorView.widget);
		}
	}

	public View getDecorView() {
		return decorView;
	}

	public native void set_widget_as_root(long native_window, long widget);
	private native void set_title(long native_window, String title);

	public native void take_input_queue(long native_window, InputQueue.Callback callback, InputQueue queue);
	public native void set_layout(long native_window, int width, int height);

	public void takeInputQueue(InputQueue.Callback callback) {
		take_input_queue(native_window, callback, new InputQueue());
	}

	public boolean requestFeature(int featureId) {
		return false;
	}

	public View findViewById(int id) {
		return decorView.findViewById(id);
	}

	public View peekDecorView() {
		return null;
	}

	public WindowManager.LayoutParams getAttributes() {
		return new WindowManager.LayoutParams();
	}

	public void setBackgroundDrawable(Drawable drawable) {
		decorView.setBackgroundDrawable(drawable);
	}

	public void setAttributes(WindowManager.LayoutParams params) {
		setLayout(params.width, params.height);
	}

	public void takeSurface(SurfaceHolder.Callback2 callback) {}

	public void setStatusBarColor(int color) {}

	public void setNavigationBarColor(int color) {}

	public void setFormat(int format) {}

	public void setLayout(int width, int height) {
		if (height == 0)  // FIXME: remove this hack once measurement error with composeUI dialogs is fixed
			height = 500;
		set_layout(native_window, width, height);
	}

	public WindowManager getWindowManager() {
		return new WindowManagerImpl();
	}

	public void setSoftInputMode(int dummy) {}

	public int getNavigationBarColor() {
		return 0xFF888888;  // gray
	}

	public void setBackgroundDrawableResource(int resId) {}

	public int getStatusBarColor() { return 0xFFFF0000; }

	public Context getContext() {
		return context;
	}

	public boolean hasFeature(int featureId) {
		return false;
	}

	public void setTitle(CharSequence title) {
		set_title(native_window, title != null ? title.toString() : context.getPackageName());
	}

	public Transition getSharedElementEnterTransition() {
		return new Transition();
	}

	public void setSharedElementExitTransition(Transition transition) {}

	public void setSharedElementReenterTransition(Transition transition) {}

	public void setSharedElementReturnTransition(Transition transition) {}

	public Transition getSharedElementExitTransition() {
		return new Transition();
	}

	public Transition getSharedElementReenterTransition() {
		return new Transition();
	}

	public void setReturnTransition(Transition transition) {}

	public void setEnterTransition(Transition transition) {}
}
