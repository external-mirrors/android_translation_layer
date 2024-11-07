package android.view;

import android.content.Context;

/**
 * default values are mainly based on AOSPs defaults. Does not account for scaling yet.
 */
public class ViewConfiguration {
	
	public static ViewConfiguration get(Context context) {
		return new ViewConfiguration();
	}

	public int getScaledTouchSlop() {
		return 8;
	}

	public int getScaledMaximumFlingVelocity() {
		return 8000;
	}

	public int getScaledMinimumFlingVelocity() {
		return 50;
	}

	public static int getTapTimeout() {
		return 100;
	}

	public static int getLongPressTimeout() {
		return 400;
	}

	public int getScaledPagingTouchSlop(){
		return 16;
	}

	public boolean hasPermanentMenuKey() {
		return false;
	}

	public static int getDoubleTapTimeout() {
		return 300;
	}

	public int getScaledDoubleTapSlop() {
		return 100;
	}

	public static float getScrollFriction() {
		return 0.015f;
	}

	public int getScaledWindowTouchSlop() {
		return 8;
	}

	public float getScaledHorizontalScrollFactor() {
		return 1;
	}

	public float getScaledVerticalScrollFactor() {
		return 1;
	}
}
