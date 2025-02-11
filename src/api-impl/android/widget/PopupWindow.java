package android.widget;

import android.content.Context;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Gravity;
import android.view.View;

public class PopupWindow {

	public PopupWindow(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
		popover = native_constructor();
	}

	public PopupWindow(Context context) {
		this(context, null, 0, 0);
	}

	public PopupWindow() {
		popover = native_constructor();
	}

	public PopupWindow(View contentView, int width, int height, boolean focusable) {
		popover = native_constructor();
		setContentView(contentView);
		setWidth(width);
		setHeight(height);
		setFocusable(focusable);
	}

	public PopupWindow(View contentView, int width, int height) {
		this(contentView, width, height, true);
	}

	private View contentView;
	private long popover;  // native pointer to GtkPopover

	public interface OnDismissListener {
		public void onDismiss();
	}

	protected native long native_constructor();
	protected native void native_setContentView(long widget, long contentView);
	protected native void native_showAsDropDown(long widget, long anchor, int xoff, int yoff, int gravity);
	protected native boolean native_isShowing(long widget);
	protected native void native_dismiss(long widget);

	public void setBackgroundDrawable(Drawable background) {}

	public void setInputMethodMode(int mode) {}

	public boolean isShowing() {
		return native_isShowing(popover);
	}

	public native void setOnDismissListener(OnDismissListener listener);

	public void setFocusable(boolean focusable) {}

	public Drawable getBackground() {return null;}

	public void setContentView(View view) {
		contentView = view;
		if (contentView != null) {
			contentView.attachToWindowInternal();
		}
		native_setContentView(popover, view == null ? 0 : view.widget);
	}

	public int getInputMethodMode() {return 0;}

	public int getMaxAvailableHeight(View anchor, int yOffset) {return 500;}

	public native void setWidth(int width);

	public native void setHeight(int height);

	public void setOutsideTouchable(boolean touchable) {}

	public void setTouchInterceptor(View.OnTouchListener listener) {}

	public void showAsDropDown(View anchor, int xoff, int yoff, int gravity) {
		native_showAsDropDown(popover, anchor.widget, xoff, yoff, gravity);
	}

	public View getContentView() {return contentView;}

	public void setTouchable(boolean touchable) {}

	public void showAsDropDown(View anchor, int xoff, int yoff) {
		if (!anchor.isAttachedToWindow()) {
			Log.e("PopupWindow", "anchor is not attached to window");
			return;
		}
		native_showAsDropDown(popover, anchor.widget, xoff, yoff, Gravity.NO_GRAVITY);
	}

	public void showAtLocation(View parent, int gravity, int x, int y) {
		native_showAsDropDown(popover, parent.widget, x, y, gravity);
	}

	public void dismiss() {
		native_dismiss(popover);
	}

	public void setAnimationStyle(int animationStyle) {}

	public void setTouchModal(boolean touchModal) {}

	public void setElevation(float elevation) {}
}
