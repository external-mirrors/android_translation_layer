package android.view;

import android.graphics.drawable.Drawable;

public interface MenuItem {

	public interface OnMenuItemClickListener {
		public boolean onMenuItemClick(MenuItem item);
	}

	public interface OnActionExpandListener {}

	public MenuItem setIcon(int iconRes);

	public MenuItem setVisible(boolean visible);

	public MenuItem setChecked(boolean checked);

	public MenuItem setEnabled(boolean enabled);

	public MenuItem setCheckable(boolean checkable);

	public MenuItem setTitleCondensed(CharSequence titleCondensed);

	public MenuItem setTitle(CharSequence title);

	public MenuItem setActionView(View actionView);

	public void setShowAsAction(int action);

	public int getItemId();

	public int getGroupId();

	public MenuItem setOnMenuItemClickListener(OnMenuItemClickListener listener);

	public MenuItem setTitle(int resId);

	public boolean isVisible();

	public Drawable getIcon();

	public SubMenu getSubMenu();

	public MenuItem setActionView(int resId);

	public View getActionView();

	public boolean hasSubMenu();

	public MenuItem setOnActionExpandListener(OnActionExpandListener listener);

	public MenuItem setIcon(Drawable icon);

	public boolean isChecked();

	public MenuItem setShowAsActionFlags(int action);

	public MenuItem setAlphabeticShortcut(char alphaChar);

	public MenuItem setShortcut(char numeric, char alpha);
}
