package android.text;

public class StaticLayout extends Layout {

	public StaticLayout(CharSequence source, int bufstart, int bufend,
						TextPaint paint, int outerwidth,
						Alignment align, TextDirectionHeuristic textDir,
						float spacingmult, float spacingadd,
						boolean includepad,
						TextUtils.TruncateAt ellipsize, int ellipsizedWidth, int maxLines) {
		super(source, paint, outerwidth, align, spacingmult, spacingadd);
	}

	public int getWidth() {
		return 200;  // arbitrary value for stub method
	}

	public int getHeight() {
		return 50;  // arbitrary value for stub method
	}

	public float getLineLeft(int line) {return 0;}

}
