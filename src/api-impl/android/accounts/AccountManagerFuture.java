package android.accounts;

import java.util.concurrent.TimeUnit;

public interface AccountManagerFuture<V> {
	boolean cancel(boolean mayInterruptIfRunning);

	boolean isCancelled();

	boolean isDone();

	V getResult();

	V getResult(long timeout, TimeUnit unit);
}
