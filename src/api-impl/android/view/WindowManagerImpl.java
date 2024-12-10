package android.view;

public class WindowManagerImpl implements WindowManager, ViewManager {
	public android.view.Display getDefaultDisplay() {
		return new android.view.Display();
	}

	@Override
	public void addView(View view, android.view.ViewGroup.LayoutParams params) {
		System.out.println("WindowManagerImpl.addView(" + view + ", " + params + ") called");
	}

	@Override
	public void updateViewLayout(View view, android.view.ViewGroup.LayoutParams params) {
		System.out.println("WindowManagerImpl.updateViewLayout(" + view + ", " + params + ") called");
	}

	@Override
	public void removeView(View view) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'removeView'");
	}
}
