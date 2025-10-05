package android.text.style;

public interface LeadingMarginSpan {

	public static class Standard implements LeadingMarginSpan {

		public Standard(int indent) {}

		public Standard(int first_indent, int rest_indent) {}
	}
}
