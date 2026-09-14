package android.util;

public class StringBuilderPrinter implements Printer {
	private final StringBuilder builder;

	public StringBuilderPrinter(StringBuilder builder) {
		this.builder = builder;
	}

	public void println(String x) {
		builder.append(x);
		if (!x.endsWith("\n")) {
			builder.append('\n');
		}
	}
}
