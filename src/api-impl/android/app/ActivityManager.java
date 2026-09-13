package android.app;

import android.atl.ATLLoadedApp;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Parcel;
import android.os.Parcelable;
import android.os.Process;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Map;

public class ActivityManager {

	public static class RunningAppProcessInfo {
		public int importance;
		public int pid;
		public int uid;
		public String processName;

		public RunningAppProcessInfo(String processName, int pid, String[] pkgList) {
			this.processName = processName;
			this.pid = pid;
		}

		private RunningAppProcessInfo(int pid, String processName) {
			this.pid = pid;
			this.processName = processName;
		}
	}

	public static class TaskDescription {
		public TaskDescription(String name) {}
		public TaskDescription(String name, Bitmap icon, int color) {}
	}

	public List<RunningAppProcessInfo> getRunningAppProcesses() {
		return Arrays.asList(new RunningAppProcessInfo(Process.myPid(),
		                                               ATLLoadedApp.getPrimaryApplication().pkg.packageName));
	}

	public boolean isLowRamDevice() { return false; }

	public static class MemoryInfo implements Parcelable {
		/* For now, just always report there's 10GB free RAM */
		public long availMem = 10000;

		public long totalMem = 10000;

		public long threshold = 200;

		public boolean lowMemory = false;

		public int describeContents() {
			return 0;
		}

		public void writeToParcel(Parcel dest, int flags) {
			dest.writeLong(availMem);
			dest.writeLong(totalMem);
			dest.writeLong(threshold);
			dest.writeInt(lowMemory ? 1 : 0);
		}

		public void readFromParcel(Parcel source) {
			availMem = source.readLong();
			totalMem = source.readLong();
			threshold = source.readLong();
			lowMemory = source.readInt() != 0;
		}

		public static final Parcelable.Creator<MemoryInfo> CREATOR = new Parcelable.Creator<MemoryInfo>() {
			public MemoryInfo createFromParcel(Parcel in) {
				MemoryInfo info = new MemoryInfo();
				info.readFromParcel(in);
				return info;
			}

			public MemoryInfo[] newArray(int size) {
				return new MemoryInfo[size];
			}
		};
	}

	public void getMemoryInfo(MemoryInfo outInfo) {
		outInfo = new MemoryInfo();
	}

	public ConfigurationInfo getDeviceConfigurationInfo() {
		return new ConfigurationInfo();
	}

	public int getMemoryClass() { return 20; }      // suggested heap size in MB
	public int getLargeMemoryClass() { return 60; } // value chosen arbitrarily

	public static void getMyMemoryState(RunningAppProcessInfo outInfo) {}

	public boolean clearApplicationUserData() { return false; }

	public static class ProcessErrorStateInfo implements Parcelable {
		public int condition;
		public String processName;
		public int pid;
		public int uid;
		public String tag;
		public String shortMsg;
		public String longMsg;
		public byte[] crashData;
		public int uid_mm;
		public int etype;
		public int euid;
		public int epid;
		public String eproc;
		public String edata;
		public Map<String, Object> extras;

		public static final int CRASHED = 1;
		public static final int NOT_RESPONDING = 2;
		public static final int NO_ERROR = 0;

		public int describeContents() {
			return 0;
		}

		public void writeToParcel(Parcel dest, int flags) {
			dest.writeInt(condition);
			dest.writeString(processName);
		}

		public void readFromParcel(Parcel source) {
			condition = source.readInt();
			processName = source.readString();
		}

		public static final Parcelable.Creator<ProcessErrorStateInfo> CREATOR = new Parcelable.Creator<ProcessErrorStateInfo>() {
			public ProcessErrorStateInfo createFromParcel(Parcel in) {
				ProcessErrorStateInfo info = new ProcessErrorStateInfo();
				info.readFromParcel(in);
				return info;
			}

			public ProcessErrorStateInfo[] newArray(int size) {
				return new ProcessErrorStateInfo[size];
			}
		};
	}

	public static class AppTask {}
	public List<ActivityManager.AppTask> getAppTasks() {
		return new ArrayList<>();
	}

	public static class RecentTaskInfo implements Parcelable {
		public int id;
		public int persistentId;
		public android.content.Intent baseIntent;
		public android.content.ComponentName origActivity;
		public CharSequence description;
		public int userId;

		public int describeContents() {
			return 0;
		}

		public void writeToParcel(Parcel dest, int flags) {
			dest.writeInt(id);
			dest.writeLong(persistentId);
		}

		public void readFromParcel(Parcel source) {
			id = source.readInt();
			persistentId = (int)source.readLong();
		}

		public static final Parcelable.Creator<RecentTaskInfo> CREATOR = new Parcelable.Creator<RecentTaskInfo>() {
			public RecentTaskInfo createFromParcel(Parcel in) {
				RecentTaskInfo info = new RecentTaskInfo();
				info.readFromParcel(in);
				return info;
			}

			public RecentTaskInfo[] newArray(int size) {
				return new RecentTaskInfo[size];
			}
		};
	}

	public static class RunningTaskInfo implements Parcelable {
		public int id;
		public android.content.ComponentName baseActivity;
		public android.content.ComponentName topActivity;
		public int numActivities;
		public int numRunning;
		public android.graphics.Bitmap thumbnail;
		public CharSequence description;

		public int describeContents() {
			return 0;
		}

		public void writeToParcel(Parcel dest, int flags) {
			dest.writeInt(id);
			dest.writeInt(numActivities);
			dest.writeInt(numRunning);
		}

		public void readFromParcel(Parcel source) {
			id = source.readInt();
			numActivities = source.readInt();
			numRunning = source.readInt();
		}

		public static final Parcelable.Creator<RunningTaskInfo> CREATOR = new Parcelable.Creator<RunningTaskInfo>() {
			public RunningTaskInfo createFromParcel(Parcel in) {
				RunningTaskInfo info = new RunningTaskInfo();
				info.readFromParcel(in);
				return info;
			}

			public RunningTaskInfo[] newArray(int size) {
				return new RunningTaskInfo[size];
			}
		};
	}

	public List<RecentTaskInfo> getRecentTasks(int maxNum, int flags) {
		return new ArrayList<>();
	}

	public List<RunningTaskInfo> getRunningTasks(int maxNum) {
		return new ArrayList<>();
	}

	public List<ActivityManager.ProcessErrorStateInfo> getProcessesInErrorState() {
		return new ArrayList<>();
	}

	public static class RunningServiceInfo implements Parcelable {
		public android.content.ComponentName service;
		public int pid;
		public int uid;
		public String process;
		public boolean foreground;
		public long activeSince;
		public boolean started;
		public int clientCount;
		public int clientPackageCount;
		public int crashCount;
		public long restarting;
		public int flags;
		public String clientPackage;

		public RunningServiceInfo() {
		}

		public int describeContents() {
			return 0;
		}

		public void writeToParcel(Parcel dest, int flags) {
			return;
		}

		public void readFromParcel(Parcel source) {
			return;
		}
	}

	public List<RunningServiceInfo> getRunningServices(int maxNum)
	    throws SecurityException {
		return new ArrayList<>();
	}

	public List<ApplicationExitInfo> getHistoricalProcessExitReasons(String pkgname, int pid, int maxNum) {
		return Collections.emptyList();
	}

	public static boolean isUserAMonkey() { return false; }

	public void moveTaskToFront(int taskId, int flags, Bundle options) {
	}
}
