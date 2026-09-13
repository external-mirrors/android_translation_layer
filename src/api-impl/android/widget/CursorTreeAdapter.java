package android.widget;

import android.database.Cursor;
import android.database.DataSetObserver;
import android.view.View;
import android.view.ViewGroup;

public abstract class CursorTreeAdapter extends BaseExpandableListAdapter implements Filterable {
	private Cursor cursor;
	private Cursor groupCursor;
	private Cursor[] childCursors;
	private DataSetObserver groupObserver;
	private DataSetObserver childObserver;
	private FilterQueryProvider filterQueryProvider;

	public CursorTreeAdapter(Cursor cursor, android.content.Context context) {
		init(cursor);
	}

	public CursorTreeAdapter(Cursor cursor, android.content.Context context, boolean autoRequery) {
		init(cursor);
	}

	private void init(Cursor cursor) {
		groupCursor = cursor;
		this.cursor = cursor;
		childCursors = new Cursor[0];
		groupObserver = new DataSetObserver() {
			@Override
			public void onChanged() {
				notifyDataSetChanged();
			}

			@Override
			public void onInvalidated() {
				notifyDataSetInvalidated();
			}
		};
		childObserver = new DataSetObserver() {
			@Override
			public void onChanged() {
				notifyDataSetChanged();
			}

			@Override
			public void onInvalidated() {
				notifyDataSetInvalidated();
			}
		};
	}

	public Cursor getChild(int groupPosition, int childPosition) {
		Cursor cursor = getChildrenCursor(groupPosition);
		if (cursor != null && cursor.moveToPosition(childPosition)) {
			return cursor;
		}
		return null;
	}

	public long getChildId(int groupPosition, int childPosition) {
		Cursor cursor = getChildrenCursor(groupPosition);
		if (cursor != null && cursor.moveToPosition(childPosition)) {
			return cursor.getLong(cursor.getColumnIndexOrThrow("_id"));
		}
		return 0;
	}

	public int getChildrenCount(int groupPosition) {
		Cursor cursor = getChildrenCursor(groupPosition);
		return cursor != null ? cursor.getCount() : 0;
	}

	public Cursor getChildrenCursor(int groupPosition) {
		Cursor cursor = getGroup(groupPosition);
		return cursor != null ? getChildrenCursor(cursor) : null;
	}

	public abstract Cursor getChildrenCursor(Cursor groupCursor);

	public Cursor getGroup(int groupPosition) {
		if (groupCursor != null && groupCursor.moveToPosition(groupPosition)) {
			return groupCursor;
		}
		return null;
	}

	public int getGroupCount() {
		return groupCursor != null ? groupCursor.getCount() : 0;
	}

	public long getGroupId(int groupPosition) {
		if (groupCursor != null && groupCursor.moveToPosition(groupPosition)) {
			return groupCursor.getLong(groupCursor.getColumnIndexOrThrow("_id"));
		}
		return 0;
	}

	public View getGroupView(int groupPosition, boolean isExpanded, View convertView, ViewGroup parent) {
		Cursor cursor = getGroup(groupPosition);
		if (cursor != null) {
			return newGroupView(parent.getContext(), cursor, isExpanded, parent);
		}
		return newGroupView(parent.getContext(), null, isExpanded, parent);
	}

	public View getChildView(int groupPosition, int childPosition, boolean isLastChild,
	                         View convertView, ViewGroup parent) {
		Cursor cursor = getChild(groupPosition, childPosition);
		if (cursor != null) {
			return newChildView(parent.getContext(), cursor, isLastChild, parent);
		}
		return newChildView(parent.getContext(), null, isLastChild, parent);
	}

	public abstract View newChildView(android.content.Context context, Cursor cursor, boolean isLastChild,
	                                  ViewGroup parent);

	public abstract View newGroupView(android.content.Context context, Cursor cursor, boolean isExpanded,
	                                  ViewGroup parent);

	public boolean isChildSelectable(int groupPosition, int childPosition) {
		return true;
	}

	public boolean hasStableIds() {
		return true;
	}

	public Cursor getCursor() {
		return cursor;
	}

	public void setGroupCursor(Cursor cursor) {
		if (cursor != groupCursor && groupCursor != null) {
			groupCursor.unregisterDataSetObserver(groupObserver);
		}
		groupCursor = cursor;
		if (cursor != null) {
			cursor.registerDataSetObserver(groupObserver);
		}
	}

	public void setChildrenCursor(int groupPosition, Cursor childrenCursor) {
		if (childCursors.length <= groupPosition) {
			Cursor[] newCursors = new Cursor[groupPosition + 1];
			System.arraycopy(childCursors, 0, newCursors, 0, childCursors.length);
			childCursors = newCursors;
		}
		if (childCursors[groupPosition] != null && childCursors[groupPosition] != childrenCursor) {
			childCursors[groupPosition].unregisterDataSetObserver(childObserver);
		}
		childCursors[groupPosition] = childrenCursor;
		if (childrenCursor != null) {
			childrenCursor.registerDataSetObserver(childObserver);
		}
	}

	public void changeCursor(Cursor cursor) {
		Cursor old = groupCursor;
		if (old != cursor) {
			groupCursor = cursor;
			if (old != null) {
				old.unregisterDataSetObserver(groupObserver);
			}
			if (cursor != null) {
				cursor.registerDataSetObserver(groupObserver);
			}
			notifyDataSetChanged();
		}
	}

	public CharSequence convertToString(Cursor cursor) {
		return cursor == null ? "" : cursor.toString();
	}

	public Cursor runQueryOnBackgroundThread(CharSequence constraint) {
		if (filterQueryProvider != null) {
			return filterQueryProvider.runQuery(constraint);
		}
		return cursor;
	}

	public Filter getFilter() {
		return null;
	}

	public FilterQueryProvider getFilterQueryProvider() {
		return filterQueryProvider;
	}

	public void setFilterQueryProvider(FilterQueryProvider filterQueryProvider) {
		this.filterQueryProvider = filterQueryProvider;
	}

	protected void onContentChanged() {}
}
