package android.widget;

import android.content.Context;
import android.util.AttributeSet;

public class GridView extends AbsListView {
	public GridView(Context context) {
		super(context);
	}

	public GridView(Context context, AttributeSet attributeSet) {
		super(context, attributeSet);
	}

	public GridView(Context context, AttributeSet attributeSet, int defStyleAttr) {
		super(context, attributeSet, defStyleAttr);
	}

	@Override
	void fillGap(boolean down) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'fillGap'");
	}

	@Override
	int findMotionRow(int y) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'findMotionRow'");
	}

	@Override
	void setSelectionInt(int position) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'setSelectionInt'");
	}

	@Override
	public ListAdapter getAdapter() {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'getAdapter'");
	}

	@Override
	public void setSelection(int position) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'setSelection'");
	}
}
