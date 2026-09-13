package android.app;

import android.os.Bundle;
import android.view.View;
import android.widget.TabHost;
import android.widget.TabWidget;

public class TabActivity extends ActivityGroup {
	private TabHost tabHost;
	private TabWidget tabWidget;

	public TabActivity() {}

	public void setDefaultTab(String tag) {
		getTabHost().setCurrentTabByTag(tag);
	}

	public void setDefaultTab(int index) {
		getTabHost().setCurrentTab(index);
	}

	public TabHost getTabHost() {
		if (tabHost == null) {
			tabHost = new TabHost(this);
		}
		return tabHost;
	}

	public TabWidget getTabWidget() {
		if (tabWidget == null) {
			tabWidget = new TabWidget(this);
		}
		return tabWidget;
	}

	public void onContentChanged() {
		super.onContentChanged();
		TabHost host = (TabHost)findViewById(com.android.internal.R.id.tabhost);
		if (host != null) {
			tabHost = host;
			tabHost.setup();
		}
	}

	protected void onRestoreInstanceState(Bundle state) {
	}

	protected void onPostCreate(Bundle icicle) {
		super.onPostCreate(icicle);
	}
}
