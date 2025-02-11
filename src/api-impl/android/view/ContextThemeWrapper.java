package android.view;

import android.content.Context;
import android.content.ContextWrapper;
import android.content.res.Resources;

public class ContextThemeWrapper extends ContextWrapper {

	private Resources.Theme theme = null;

	public ContextThemeWrapper(Context base) {
		super(base);
	}

	public ContextThemeWrapper(Context context, int themeResId) {
		super(context);
		setTheme(themeResId);
	}

	public ContextThemeWrapper(Context context, Resources.Theme theme) {
		super(context);
		this.theme = theme;
	}

	@Override
	public void setTheme(int resid) {
		if (theme == null) {
			theme = getResources().newTheme();
			theme.setTo(getBaseContext().getTheme());
		}
		theme.applyStyle(resid, true);
	}

	@Override
	public Resources.Theme getTheme() {
		if (theme != null)
			return theme;
		else
			return super.getTheme();
	}

}
