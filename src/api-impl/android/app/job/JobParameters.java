package android.app.job;

import android.os.PersistableBundle;

public class JobParameters {

	JobInfo jobInfo;

	JobParameters(JobInfo jobInfo) {
		this.jobInfo = jobInfo;
	}

	public PersistableBundle getExtras() {
		return jobInfo.getExtras();
	}
}
