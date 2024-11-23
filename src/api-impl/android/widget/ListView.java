package android.widget;

import java.util.ArrayList;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.View;

public class ListView extends AbsListView {

	static class FixedViewInfo {
		public View view;
		public Object data;
		public boolean isSelectable;

		public FixedViewInfo(View view, Object data, boolean isSelectable) {
			this.view = view;
			this.data = data;
			this.isSelectable = isSelectable;
		}
	}

	private ArrayList<FixedViewInfo> headerViews = new ArrayList<FixedViewInfo>();
	private ArrayList<FixedViewInfo> footerViews = new ArrayList<FixedViewInfo>();

	public ListView(Context context) {
		super(context);
	}

	public ListView(Context context, AttributeSet attributeSet) {
		super(context, attributeSet);
	}

	public ListView(Context context, AttributeSet attributeSet, int defStyleAttr) {
		super(context, attributeSet, defStyleAttr);
	}

	@Override
	public void setAdapter(ListAdapter adapter) {
		if (getHeaderViewsCount() > 0 || getFooterViewsCount() > 0) {
			adapter = new HeaderViewListAdapter(headerViews, footerViews, adapter);
		}
		super.setAdapter(adapter);
	}

	public int getDividerHeight() {return 0;}

	public Drawable getDivider() {return null;}

	public void setTextFilterEnabled(boolean enabled) {}

	public void addHeaderView(View v, Object data, boolean isSelectable) {
		headerViews.add(new FixedViewInfo(v, data, isSelectable));
		if (getAdapter() instanceof HeaderViewListAdapter) {
			observer.onChanged();
		} else if (getAdapter() != null) {
			setAdapter(getAdapter());
		}
	}

	public void setDrawSelectorOnTop(boolean dummy) {}

	public void addHeaderView(View view) {
		addHeaderView(view, null, true);
	}

	public boolean removeHeaderView(View view) {
		boolean result = false;
		if (getAdapter() instanceof HeaderViewListAdapter)
			result = ((HeaderViewListAdapter)getAdapter()).removeHeader(view);
		if (result)
			observer.onChanged();
		return result;
	}

	public int getHeaderViewsCount() {
		return headerViews.size();
	}

	public int getFooterViewsCount() {
		return footerViews.size();
	}

	public void setDivider(Drawable drawable) {}

	public void setSelectionFromTop(int position, int y) {}

	public void addFooterView(View v, Object data, boolean isSelectable) {
		footerViews.add(new FixedViewInfo(v, data, isSelectable));
		if (getAdapter() instanceof HeaderViewListAdapter) {
			observer.onChanged();
		} else if (getAdapter() != null) {
			setAdapter(getAdapter());
		}
	}

	public void addFooterView(View v) {
		addFooterView(v, null, true);
	}

	public void setDividerHeight(int height) {}

	@Override
	public void setSelection(int position, boolean animate) {
		super.setSelection(position + getHeaderViewsCount(), animate);
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
