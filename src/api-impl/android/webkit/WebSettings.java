package android.webkit;

public class WebSettings {

	public static enum LayoutAlgorithm {
		NORMAL,
		NARROW_COLUMNS,
	}

	public static enum RenderPriority {
		HIGH,
	}

	public String getUserAgentString() {
		return "GDPR VIOLATION";
	}

	public void setUserAgentString(String userAgentString) {}

	public void setSupportMultipleWindows(boolean supportMultipleWindows) {}

	public void setJavaScriptEnabled(boolean javaScriptEnabled) {}

	public void setSavePassword(boolean savePassword) {}

	public void setGeolocationEnabled(boolean enabled) {}

	public void setCacheMode(int dummy) {}

	public void setLayoutAlgorithm(LayoutAlgorithm layoutAlgorithm) {}

	public void setAllowFileAccess(boolean allowFileAccess) {}

	public void setBuiltInZoomControls(boolean builtInZoomControls) {}

	public void setDisplayZoomControls(boolean displayZoomControls) {}

	public void setLoadsImagesAutomatically(boolean loadsImagesAutomatically) {}

	public void setSupportZoom(boolean supportZoom) {}

	public void setUseWideViewPort(boolean useWideViewPort) {}

	public void setTextZoom(int textZoom) {}

	public void setAppCacheEnabled(boolean enabled) {}

	public void setAppCachePath(String path) {}

	public void setLoadWithOverviewMode(boolean overview) {}

	public void setRenderPriority(RenderPriority priority) {}

	public void setBlockNetworkLoads(boolean block) {}

	public void setMixedContentMode(int mode) {}
}
