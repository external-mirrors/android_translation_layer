package android.text.style;

public class StyleSpan extends MetricAffectingSpan {

	private int style;

	public StyleSpan(int style) {
		this.style = style;
	}

	public int getStyle() {
		return style;
	}

}
