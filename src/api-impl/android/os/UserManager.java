package android.os;

public class UserManager {
	public boolean isUserUnlocked() {
		return true;
	}
	public static boolean supportsMultipleUsers() {
		return false;
	}
}
