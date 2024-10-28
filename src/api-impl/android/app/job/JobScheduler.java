package android.app.job;

import java.util.ArrayList;
import java.util.List;

public class JobScheduler {
	/**
	 * Retrieve all jobs that have been scheduled by the calling application.
	 *
	 * @return a list of all of the app's scheduled jobs.  This includes jobs that are
	 *     currently started as well as those that are still waiting to run.
	 */
	public List<JobInfo> getAllPendingJobs() {
		return new ArrayList<JobInfo>();
	};

	public int enqueue(JobInfo job, JobWorkItem work) {
		return 1; //RESULT_SUCCESS
	}
}
