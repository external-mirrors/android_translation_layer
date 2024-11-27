package android.text;

public class BoringLayout extends Layout {

	public static class Metrics {};

	public static Metrics isBoring(CharSequence source, TextPaint paint, Metrics metrics) {
		return metrics;
	}
}
