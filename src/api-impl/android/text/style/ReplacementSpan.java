package android.text.style;

import android.graphics.Paint;

public abstract class ReplacementSpan extends MetricAffectingSpan {

	public abstract int getSize(Paint paint, CharSequence text, int start, int end, Paint.FontMetricsInt fm);
}
