package android.widget;

import java.util.ArrayList;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.View;

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
	public View getSelectedView() {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'getSelectedView'");
	}

	@Override
	public void setSelection(int position) {
		setSelection(position, false);
	}
}
