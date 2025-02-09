package android.app;

import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

import android.app.Notification.MediaStyle;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Looper;

public class NotificationManager {

	private static int mpris_notification_id = -1;

	// store Intents in map, as long as Parcelable serialization is not yet implemented
	private static Map<Integer, Intent> intents = new HashMap<Integer, Intent>();

	public void cancelAll() {}

	public void notify(String tag, int id, Notification notification) {
		if (notification.style instanceof MediaStyle) {  // MPRIS content is handled by MediaSession implementation
			if (mpris_notification_id == -1) {
				nativeShowMPRIS(Context.this_application.getPackageName(), Context.this_application.get_app_label());
				mpris_notification_id = id;
			}
			return;
		}

		System.out.println("notify(" + tag + ", " + id + ", " + notification + ") called");
		long builder = nativeInitBuilder();
		for (Notification.Action action : notification.actions) {
			int intentType = -1;
			String actionName = null;
			String className = null;
			if (action.intent != null) {
				intentType = action.intent.type;
				actionName = action.intent.intent.getAction();
				className = action.intent.intent.getComponent() != null ? action.intent.intent.getComponent().getClassName() : null;
			}
			nativeAddAction(builder, action.title, intentType, actionName, className);
		}
		int intentType = -1;
		String actionName = null;
		String className = null;
		if (notification.intent != null) {
			intentType = notification.intent.type;
			actionName = notification.intent.intent.getAction();
			className = notification.intent.intent.getComponent() != null ? notification.intent.intent.getComponent().getClassName() : null;
			intents.put(id, notification.intent.intent);
		}
		nativeShowNotification(builder, id, notification.title, notification.text, notification.iconPath, notification.ongoing, intentType, actionName, className);
	}

	public void notify(int id, Notification notification) {
		notify(null, id, notification);
	}

	public void cancel(String tag, final int id) {
		// remove_notification doesn't work reliably when sent directly after add_notification in GNOME session.
		// So we give some extra delay here.
		new Handler(Looper.getMainLooper()).postDelayed(new Runnable() {
			@Override
			public void run() {
				if (mpris_notification_id == id) {
					mpris_notification_id = -1;
					nativeCancelMPRIS();
				} else {
					nativeCancel(id);
				}
			}
		}, 100);
	}

	public void cancel(int id) {
		cancel(null, id);
	}

	protected static void notificationActionCallback(int id, int intentType, String action, String className) {
		Context context = Context.this_application;
		action = "".equals(action) ? null : action;
		className = "".equals(className) ? null : className;
		Intent intent = intents.remove(id);
		if (intent == null || !Objects.equals(action, intent.getAction()) || !Objects.equals(className, intent.getComponent() == null ? null : intent.getComponent().getClassName())) {
			intent = new Intent(action);
			if (className != null) {
				intent.setComponent(new ComponentName(context, className));
			}
		}
		if (intentType == 0) { // type Activity
			context.startActivity(intent);
		} else if (intentType == 1) { // type Service
			context.startService(intent);
		} else if (intentType == 2) { // type Broadcast
			context.sendBroadcast(intent);
		}
	}

	public void createNotificationChannel(NotificationChannel channel) {}

	protected native long nativeInitBuilder();
	protected native void nativeAddAction(long builder, String title, int intentType, String action, String className);
	protected native void nativeShowNotification(long builder, int id, String title, String text, String iconPath, boolean ongoing, int intentType, String action, String className);
	protected native void nativeShowMPRIS(String packageName, String identiy);
	protected native void nativeCancel(int id);
	protected native void nativeCancelMPRIS();

	public void createNotificationChannelGroup(NotificationChannelGroup v) {}

	public List<NotificationChannel> getNotificationChannels() {
		return Collections.emptyList();
	}

	public List<NotificationChannelGroup> getNotificationChannelGroups() {
		return Collections.emptyList();
	}
}
