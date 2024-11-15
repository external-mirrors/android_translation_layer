package android.widget;

import android.content.Context;
import android.database.DataSetObserver;
import android.util.AttributeSet;
import android.view.ViewGroup;

public abstract class AbsListView extends AdapterView {

	public boolean mIsChildViewEnabled = false;  // this field gets directly accessed by androidx DropDownListView
	protected Observer observer = new Observer();

	public AbsListView(Context context) {
		super(context);
	}

	public AbsListView(Context context, AttributeSet attributeSet) {
		super(context, attributeSet);
	}

	public AbsListView(Context context, AttributeSet attributeSet, int defStyle) {
		super(context, attributeSet, defStyle);
	}

	@Override
	protected native long native_constructor(Context context, AttributeSet attrs);
	protected native void native_setAdapter(long widget, ListAdapter adapter);
	protected native void native_scrollTo(long widget, int position);

	public void setChoiceMode(int choiceMode) {}

	public void setOnScrollListener(OnScrollListener onScrollListener) {}

	public void setAdapter(ListAdapter adapter) {
		ListAdapter oldAdapter = getAdapter();
		if (oldAdapter != null)
			oldAdapter.unregisterDataSetObserver(observer);
		super.setAdapter(adapter);
		if (adapter != null)
			adapter.registerDataSetObserver(observer);
		native_setAdapter(this.widget, adapter);
	}

	public native void setItemChecked(int position, boolean value);

	@Override
	public native void setOnItemClickListener(OnItemClickListener listener);

	public native int getCheckedItemPosition();

	public void setCacheColorHint(int color) {}

	public int getListPaddingTop() {return paddingTop;}

	public int getListPaddingBottom() {return paddingBottom;}

	public ListAdapter getAdapter() {
		return (ListAdapter) super.getAdapter();
	}

	public int pointToPosition(int x, int y) {
		return -1;
	}

	public void setFastScrollEnabled(boolean enabled) {}

	public void setFastScrollAlwaysVisible(boolean alwaysVisible) {}

	public void setTranscriptMode(int mode) {}

	public int getTranscriptMode() {return 0;}

	public void setSelectionFromTop(int position, int y) {}

	public void smoothScrollBy(int position, int duration) {}

	public void smoothScrollToPositionFromTop(int position, int offset) {
		native_scrollTo(this.widget, position);
	}

	private int pendingSelection = -1;
	@Override
	public void setSelection(int position, boolean animate) {
		super.setSelection(position, animate);
		native_scrollTo(this.widget, position);
		if (getWidth() > 0 && getHeight() > 0)
			native_scrollTo(AbsListView.this.widget, position);
		else
			pendingSelection = position;
	}

	@Override
	public void layout(int l, int t, int r, int b) {
		super.layout(l, t, r, b);
		if (pendingSelection != -1) {
			native_scrollTo(AbsListView.this.widget, pendingSelection);
			pendingSelection = -1;
		}
	}

	@Override
	public ViewGroup.LayoutParams generateLayoutParams(AttributeSet attrs) {
		return new LayoutParams(getContext(), attrs);
	}

	public interface OnScrollListener {}

	public interface SelectionBoundsAdjuster {}

	class Observer extends DataSetObserver {

		@Override
		public void onChanged() {
			AbsListView.this.native_setAdapter(widget, getAdapter());
		}
		@Override
		public void onInvalidated() {
			AbsListView.this.native_setAdapter(widget, getAdapter());
		}
	}

	public class LayoutParams extends ViewGroup.LayoutParams {

		public LayoutParams(Context c, AttributeSet attrs) {
			super(c, attrs);
		}
	}
}
