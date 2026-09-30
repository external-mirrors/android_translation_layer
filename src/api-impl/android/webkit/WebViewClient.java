package android.webkit;

public class WebViewClient {
	public void onPageStarted(WebView view, String url) {}
	public void onPageFinished(WebView view, String url) {}
	public boolean shouldOverrideUrlLoading(WebView view, String url) {
		return false; // continue loading the URL
	}
}
