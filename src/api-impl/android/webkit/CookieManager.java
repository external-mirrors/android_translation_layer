package android.webkit;

import android.content.Context;

public class CookieManager {

	public static CookieManager getInstance() {
		// HACK: disable NewPipe's WebView based PoToken generator for now
		if (Context.this_application.getPackageName().equals("org.schabi.newpipe")) {
			throw new RuntimeException("CookieManager not yet fully implemented");
		}
		try { // also handle NewPipe forks which can have a different packagename
			Class.forName("org.schabi.newpipe.util.potoken.PoTokenWebView");
			throw new RuntimeException("CookieManager not yet fully implemented");
		} catch (ClassNotFoundException e) {}
		return new CookieManager();
	}

	public void removeAllCookies(ValueCallback callback) {}

	public void removeSessionCookies(ValueCallback callback) {}

	public void flush() {}

	public String getCookie(String url) {
		return "";
	}

	public void setCookie(String url, String value) {}
}
