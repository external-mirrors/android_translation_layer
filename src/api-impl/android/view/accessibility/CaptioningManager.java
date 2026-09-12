package android.view.accessibility;

import java.util.Locale;

public class CaptioningManager {

	public boolean isEnabled() {
		return false;
	}

	public float getFontScale() {
		return 1.0f;
	}

	public static final class CaptionStyle {}

	public static abstract class CaptioningChangeListener {
		public void onEnabledChanged(boolean enabled) {}
		public void onUserStyleChanged(CaptionStyle userStyle) {}
		public void onLocaleChanged(Locale locale) {}
		public void onFontScaleChanged(float fontScale) {}
		public void onSystemAudioCaptioningChanged(boolean enabled) {}
		public void onSystemAudioCaptioningUiChanged(boolean enabled) {}
	}

	public void addCaptioningChangeListener(CaptioningChangeListener listener) {}
}
