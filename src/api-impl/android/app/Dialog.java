package android.app;

import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;

public class Dialog implements Window.Callback, DialogInterface {
	protected long nativePtr;

	private native long nativeInit();
	private native void nativeSetTitle(long ptr, String title);
	private native void nativeSetContentView(long ptr, long widget);
	private native void nativeShow(long ptr);
	private native void nativeClose(long ptr);

	private Context context;
	private Window window;
	private OnDismissListener onDismissListener;
	private OnShowListener onShowListener;

	public Dialog(Context context, int themeResId) {
		this.context = context;
		nativePtr = nativeInit();
		window = new Window(context, this);
		window.native_window = nativePtr;
	}

	public Dialog(Context context) {
		this(context, 0);
	}

	public final boolean requestWindowFeature(int featureId) {
		return false;
	}

	public Context getContext() {
		return context;
	}

	public void setContentView(View view) {
		getWindow().setContentView(view);
	}

	public void setTitle(CharSequence title) {
		nativeSetTitle(nativePtr, String.valueOf(title));
	}

	public void setTitle(int titleId) {
		nativeSetTitle(nativePtr, context.getString(titleId));
	}

	public void setOwnerActivity(Activity activity) {}

	public void setCancelable(boolean cancelable) {}

	public void setOnCancelListener(OnCancelListener onCancelListener) {}

	public void setOnDismissListener(OnDismissListener onDismissListener) {
		this.onDismissListener = onDismissListener;
	}

	public View findViewById(int id) {
		return window.findViewById(id);
	}

	public void show() {
		System.out.println("showing the Dialog " + this);
		Runnable action = new Runnable() {
			@Override
			public void run() {
				onCreate(null);
				nativeShow(nativePtr);
				if (onShowListener != null)
					onShowListener.onShow(Dialog.this);
			}
		};
		if(Looper.myLooper() == Looper.getMainLooper()) {
			action.run();
		} else {
			new Handler(Looper.getMainLooper()).post(action);
		}
	}

	public boolean isShowing() {
		return false;
	}

	public void dismiss() {
		System.out.println("dismissing the Dialog " + Dialog.this);
		// HACK: dismissing the Dialog takes some time in AOSP, as the request goes back and forth between the application
		// and the system server. We replicate this behavior by adding 10 ms delay.
		// This Hack is required for NewPipe RouterActivity which has a race condition. It subscribes an rxJava observable
		// and immediately calls Dialog.dismiss(). The OnDismissListener would unsubscribes the observable again.
		new Handler(Looper.getMainLooper()).postDelayed(new Runnable() {
			@Override
			public void run() {
				nativeClose(nativePtr);
				if (onDismissListener != null)
					onDismissListener.onDismiss(Dialog.this);
			}
		}, 10);
	}

	public Window getWindow() {
		return window;
	}

	public void setCanceledOnTouchOutside(boolean cancel) {}

	public class Builder {
		public Builder(Context context) {
			System.out.println("making a Dialog$Builder");
		}
	}

	@Override
	public void onContentChanged() {
	}
	@Override
	public boolean onCreatePanelMenu(int featureId, Menu menu) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'onCreatePanelMenu'");
	}
	@Override
	public View onCreatePanelView(int featureId) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'onCreatePanelView'");
	}
	@Override
	public boolean onPreparePanel(int featureId, View view, Menu menu) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'onPreparePanel'");
	}
	@Override
	public boolean onMenuItemSelected(int featureId, MenuItem item) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'onMenuItemSelected'");
	}
	@Override
	public void onPanelClosed(int featureId, Menu menu) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'onPanelClosed'");
	}

	@Override
	public boolean onMenuOpened(int featureId, Menu menu) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'onMenuOpened'");
	}

	protected void onCreate (Bundle savedInstanceState) {
		System.out.println("- onCreate - Dialog!");
	}

	public void hide() {
		System.out.println("hiding the Dialog " + this);
		nativeClose(nativePtr);
	}

	@Override
	public void cancel() {
		dismiss();
	}

	public void setOnShowListener(OnShowListener onShowListener) {
		this.onShowListener = onShowListener;
	}

	public void setCancelMessage(Message msg) {}

	public boolean onTouchEvent(MotionEvent event) {
		return false;
	}
}
