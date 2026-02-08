package android.view;

public class WindowManagerImpl implements WindowManager, ViewManager {

	private static class WindowViewParent implements ViewParent {

		@Override
		public android.view.ViewParent getParent() {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'getParent'");
		}

		@Override
		public boolean isLayoutRequested() {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'isLayoutRequested'");
		}

		@Override
		public void requestDisallowInterceptTouchEvent(boolean disallowIntercept) {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'requestDisallowInterceptTouchEvent'");
		}

		@Override
		public boolean onStartNestedScroll(View child, View target, int nestedScrollAxes) {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'onStartNestedScroll'");
		}

		@Override
		public boolean onNestedPreFling(View target, float velocityX, float velocityY) {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'onNestedPreFling'");
		}

		@Override
		public boolean onNestedFling(View target, float velocityX, float velocityY, boolean consumed) {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'onNestedFling'");
		}

		@Override
		public void onNestedScrollAccepted(View child, View target, int nestedScrollAxes) {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'onNestedScrollAccepted'");
		}

		@Override
		public void onNestedPreScroll(View target, int dx, int dy, int[] consumed) {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'onNestedPreScroll'");
		}

		@Override
		public void onNestedScroll(View target, int dxConsumed, int dyConsumed, int dxUnconsumed, int dyUnconsumed) {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'onNestedScroll'");
		}

		@Override
		public void onStopNestedScroll(View target) {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'onStopNestedScroll'");
		}

		@Override
		public void onDescendantInvalidated(View child, View target) {
			// TODO Auto-generated method stub
			throw new UnsupportedOperationException("Unimplemented method 'onDescendantInvalidated'");
		}
	}

	public android.view.Display getDefaultDisplay() {
		return new android.view.Display();
	}

	@Override
	public void addView(View view, android.view.ViewGroup.LayoutParams params) {
		System.out.println("WindowManagerImpl.addView(" + view + ", " + params + ") called");
		if (params.height == 0)  // FIXME: remove this hack once measurement error with composeUI popups is fixed
			params.height = 200;
		view.setLayoutParams(params);
		view.parent = new WindowViewParent();
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
		view.parent = null;
	}

	@Override
	public void removeViewImmediate(View view) {
		removeView(view);
	}

	private static native void native_addView(long widget, int type, int x, int y, int width, int height);
	private static native void native_updateViewLayout(long widget, int x, int y, int width, int height);
	private static native void native_removeView(long widget);
}
