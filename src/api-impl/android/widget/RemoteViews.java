package android.widget;

import android.app.PendingIntent;

public class RemoteViews {

	public RemoteViews(String packageName, int layoutId) {}

	public void setProgressBar(int viewId, int max, int progress, boolean indeterminate) {}

	public void setTextViewText(int viewId, CharSequence text) {}

	public void setImageViewResource(int viewId, int resId) {}

	public void setContentDescription(int viewId, CharSequence text) {}

	public void setOnClickPendingIntent(int viewId, PendingIntent pendingIntent) {}

	public void setViewVisibility(int viewId, int visibility) {}
}
