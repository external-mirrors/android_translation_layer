package android.text;

import android.graphics.Canvas;

public class Layout {
	
	public enum Alignment {
		ALIGN_NORMAL,
		ALIGN_OPPOSITE,
		ALIGN_CENTER,
		ALIGN_LEFT,
		ALIGN_RIGHT,
	}

	private CharSequence text;
	private TextPaint paint;

	protected Layout(CharSequence text, TextPaint paint, int width, Layout.Alignment align, float spacingMult, float spacingAdd) {
		this.text = text;
		this.paint = paint;
	}

	public int getLineCount() {return 1;}

	public float getLineWidth(int line) {return 10;}

	public TextPaint getPaint() {return new TextPaint();}

	public int getEllipsisCount(int line) {return 0;}

	public CharSequence getText() {return text;}

	public int getWidth() {return 10;}

	public int getHeight() {
		return (int)(paint.measureText("_") * 3);
	}

	public void draw(Canvas canvas) {
		canvas.drawText(text.toString(), 0, 0, paint);
	}

	public int getParagraphDirection(int line) {return 0;}

	public static float getDesiredWidth(CharSequence source, int start, int end, TextPaint paint) {
		return paint.measureText(source, start, end);
	}

	public int getLineEnd(int line) {return 100;}

	public int getLineStart(int line) {return 0;}

	public int getLineAscent(int line) {return 0;}

	public int getLineDescent(int line) {return 0;}

	public int getTopPadding() {return 0;}

	public int getBottomPadding() {return 0;}

	public float getLineLeft(int line) {return 0;}

	public int getLineBottom(int line) {return 0;}

	public int getLineBaseline(int line) {return 0;}

	public boolean isRtlCharAt(int offset) {return false;}

	public float getSecondaryHorizontal(int line) {return 0;}

	public int getLineForVertical(int y) {return 0;}

	public int getOffsetForHorizontal(int line, float x) {return 0;}

	public float getPrimaryHorizontal(int line) {return 0;}

	public int getLineForOffset(int offset) {return 0;}

	public int getLineTop(int line) {return 0;}
}
