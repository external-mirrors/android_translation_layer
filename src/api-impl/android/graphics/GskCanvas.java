package android.graphics;

/**
 * GskCanvas:
 *   - implements Canvas for onscreen rendering inside GTKs snapshot function
 */
public class GskCanvas extends Canvas {
	public long snapshot;
	private int save_count = 0;

	public GskCanvas(long snapshot) {
		this.snapshot = snapshot;
	}

	@Override
	public int save() {
		native_save(snapshot);
		return save_count++;
	}

	@Override
	public void restore() {
		save_count--;
		native_restore(snapshot);
	}

	@Override
	public void restoreToCount(int count) {
		while (save_count > count) {
			restore();
		}
	}

	@Override
	public void translate(float dx, float dy) {
		native_translate(snapshot, dx, dy);
	}

	@Override
	public void rotate(float degrees) {
		native_rotate(snapshot, degrees);
	}

	@Override
	public void drawBitmap(Bitmap bitmap, Rect src, Rect dst, Paint paint) {
		int color = 0;
		if (paint != null && paint.colorFilter instanceof PorterDuffColorFilter) {
			color = ((PorterDuffColorFilter) paint.colorFilter).getColor();
		}
		native_drawBitmap(snapshot, bitmap.getTexture(), dst.left, dst.top, dst.width(), dst.height(), color);
	}

	@Override
	public void drawPath(Path path, Paint paint) {
		native_drawPath(snapshot, path.mNativePath, paint.skia_paint);
	}

	@Override
	public void drawRect(float left, float top, float right, float bottom, Paint paint) {
		native_drawRect(snapshot, left, top, right, bottom, paint.getColor());
	}

	@Override
	public void rotate(float degrees, float px, float py) {
		native_translate(snapshot, px, py);
		native_rotate(snapshot, degrees);
		native_translate(snapshot, -px, -py);
	}

	@Override
	public void drawText(String text, float x, float y, Paint paint) {
		native_drawText(snapshot, text, x, y, paint.skia_paint, paint.skia_font);
	}

	@Override
	public void drawLine(float startX, float startY, float stopX, float stopY, Paint paint) {
		native_drawLine(snapshot, startX, startY, stopX, stopY, paint.skia_paint);
	}

	@Override
	public void drawBitmap(Bitmap bitmap, float left, float top, Paint paint) {
		Rect src = new Rect(0, 0, bitmap.getWidth(), bitmap.getHeight());
		Rect dst = new Rect((int)left, (int)top, (int)left + bitmap.getWidth(), (int)top + bitmap.getHeight());
		drawBitmap(bitmap, src, dst, paint);
	}

	@Override
	public void drawBitmap(Bitmap bitmap, Rect src, RectF dst, Paint paint) {
		drawBitmap(bitmap, src, new Rect((int)dst.left, (int)dst.top, (int)dst.right, (int)dst.bottom), paint);
	}

	@Override
	public void drawRoundRect(float left, float top, float right, float bottom, float rx, float ry, Paint paint) {
		native_drawRoundRect(snapshot, left, top, right, bottom, rx, ry, paint.getColor(), paint.getStrokeWidth(), paint.getStyle().nativeInt);
	}

	protected native void native_drawBitmap(long snapshot, long texture, int x, int y, int width, int height, int color);
	protected native void native_drawRect(long snapshot, float left, float top, float right, float bottom, int color);
	protected native void native_drawPath(long snapshot, long path, long paint);
	protected native void native_translate(long snapshot, float dx, float dy);
	protected native void native_rotate(long snapshot, float degrees);
	protected native void native_save(long snapshot);
	protected native void native_restore(long snapshot);
	protected native void native_drawLine(long snapshot, float startX, float startY, float stopX, float stopY, long paint);
	protected native void native_drawText(long snapshot, String text, float x, float y, long paint, long font);
	protected native void native_drawRoundRect(long snapshot, float left, float top, float right, float bottom, float rx, float ry, int color, float strokeWidth, int style);
}
