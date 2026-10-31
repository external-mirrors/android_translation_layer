package android.accounts;

import android.content.Context;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.FutureTask;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

/*
 * Accounts are stored in the Secret Service keyring and shared between all apps,
 * the same way they are shared on Android.
 */
public class AccountManager {

	/**
	 * Account is always visible to given application and only authenticator can revoke visibility.
	 */
	public static final int VISIBILITY_VISIBLE = 1;

	/**
	 * Account is visible to given application, but user can revoke visibility.
	 */
	public static final int VISIBILITY_USER_MANAGED_VISIBLE = 2;

	/**
	 * Account is not visible to given application and only authenticator can grant visibility.
	 */
	public static final int VISIBILITY_NOT_VISIBLE = 3;

	private static final AccountManager instance = new AccountManager();

	public static AccountManager get(Context context) {
		return instance;
	}

	public Account[] getAccounts() {
		return getAccountsByType(null);
	}

	public Account[] getAccountsByType(String type) {
		ArrayList<Account> accounts = new ArrayList<>();
		String[] list = nativeListAccounts().split("\n");
		for (int i = 0; i + 1 < list.length; i += 2) {
			if (type == null || type.equals(list[i]))
				accounts.add(new Account(list[i + 1], list[i]));
		}
		return accounts.toArray(new Account[0]);
	}

	public Account[] getAccountsByTypeForPackage(String type, String packageName) {
		return getAccountsByType(type);
	}

	public int getAccountVisibility(Account account, String packageName) {
		return VISIBILITY_VISIBLE;
	}

	public boolean addAccountExplicitly(Account account, String password, Bundle extras) {
		if (nativeGet(account.type, account.name, "account") != null)
			return false;
		if (!nativeSet(account.type, account.name, "account", ""))
			return false;
		setPassword(account, password);
		if (extras != null) {
			for (String key : extras.keySet())
				setUserData(account, key, extras.getString(key));
		}
		return true;
	}

	/**
	 * Removes an account from the AccountManager.  Does nothing if the account
	 * does not exist.  Does not delete the account from the server.
	 * The authenticator may have its own policies preventing account
	 * deletion, in which case the account will not be deleted.
	 *
	 * <p>This method requires the caller to have a signature match with the
	 * authenticator that manages the specified account.
	 *
	 * <p><b>NOTE:</b> If targeting your app to work on API level 22 and before,
	 * MANAGE_ACCOUNTS permission is needed for those platforms. See docs for
	 * this function in API level 22.
	 *
	 * @param account The {@link Account} to remove
	 * @param callback Callback to invoke when the request completes,
	 *     null for no callback
	 * @param handler {@link Handler} identifying the callback thread,
	 *     null for the main thread
	 * @return An {@link AccountManagerFuture} which resolves to a Boolean,
	 *     true if the account has been successfully removed
	 */
	public AccountManagerFuture<Boolean> removeAccount(Account account, AccountManagerCallback<Boolean> callback, Handler handler) {
		// no lambda here, dx can't handle invokedynamic for our min sdk version
		return runAsync(new Callable<Boolean>() {
			@Override
			public Boolean call() {
				return nativeRemove(account.type, account.name);
			}
		}, callback, handler);
	}

	/*
	 * Runs work off the calling thread like AOSP does, so native keyring calls don't block the UI.
	 * The callback is invoked on the handler's thread (main thread if null) once the work is done.
	 */
	private static <V> AccountManagerFuture<V> runAsync(Callable<V> work, final AccountManagerCallback<V> callback, final Handler handler) {
		class Future extends FutureTask<V> implements AccountManagerFuture<V> {
			Future() {
				super(work);
			}

			@Override
			protected void done() {
				if (callback == null)
					return;
				(handler != null ? handler : new Handler(Looper.getMainLooper())).post(new Runnable() {
					@Override
					public void run() {
						callback.run(Future.this);
					}
				});
			}

			public V getResult() {
				try {
					return get();
				} catch (InterruptedException | ExecutionException e) {
					throw new RuntimeException(e);
				}
			}

			public V getResult(long timeout, TimeUnit unit) {
				try {
					return get(timeout, unit);
				} catch (InterruptedException | ExecutionException | TimeoutException e) {
					throw new RuntimeException(e);
				}
			}
		}
		Future future = new Future();
		AsyncTask.THREAD_POOL_EXECUTOR.execute(future);
		return future;
	}

	public String getPassword(Account account) {
		return nativeGet(account.type, account.name, "password");
	}

	public void setPassword(Account account, String password) {
		nativeSet(account.type, account.name, "password", password);
	}

	public String getUserData(Account account, String key) {
		return nativeGet(account.type, account.name, "userdata:" + key);
	}

	public void setUserData(Account account, String key, String value) {
		nativeSet(account.type, account.name, "userdata:" + key, value);
	}

	public String peekAuthToken(Account account, String authTokenType) {
		return nativeGet(account.type, account.name, "authtoken:" + authTokenType);
	}

	public void setAuthToken(Account account, String authTokenType, String authToken) {
		nativeSet(account.type, account.name, "authtoken:" + authTokenType, authToken);
	}

	public boolean setAccountVisibility(Account account, String packageName, int visibility) {
		return true;
	}

	public void addOnAccountsUpdatedListener(final OnAccountsUpdateListener listener,
	                                         Handler handler, boolean updateImmediately, String[] accountTypes) {
	}

	public void removeOnAccountsUpdatedListener(OnAccountsUpdateListener listener) {
	}

	public Map<Account, Integer> getAccountsAndVisibilityForPackage(String packageName,
	                                                                String accountType) {
		HashMap<Account, Integer> result = new HashMap<Account, Integer>();
		Account[] accounts = getAccounts();
		for (Account acc : accounts) {
			result.put(acc, VISIBILITY_VISIBLE);
		}
		return result;
	}

	public AccountManagerFuture<Boolean> hasFeatures(Account account, String[] features, AccountManagerCallback<Boolean> callback, Handler handler) {
		return runAsync(new Callable<Boolean>() {
			@Override
			public Boolean call() throws Exception {
				return false;
			}
		}, callback, handler);
	}

	private static native String nativeGet(String type, String name, String key);
	// value == null removes the entry, returns false on keyring errors
	private static native boolean nativeSet(String type, String name, String key, String value);
	// returns false if the account didn't exist or on keyring errors
	private static native boolean nativeRemove(String type, String name);
	// returns "type\nname\n" for every account
	private static native String nativeListAccounts();
}
