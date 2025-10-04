package android.graphics;

import java.util.Arrays;

/**
 * GskCanvas:
 *   - implements Canvas for onscreen rendering inside GTKs snapshot function
 */
public class GskCanvas extends Canvas {
	public long snapshot;
	private int save_count = 1;
	private int[] push_history = null;

	private static Paint default_paint = new Paint();

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
		if (push_history != null && push_history.length > save_count && push_history[save_count] > 0) {
			native_pop(snapshot, push_history[save_count]);
			push_history[save_count] = 0;
		}
		save_count--;
		native_restore(snapshot);
	}

	@Override
	public void restoreToCount(int count) {
		if (count < 1) {
			throw new IllegalArgumentException("count must be >= 1");
		}
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
		native_drawBitmap(snapshot, bitmap.getTexture(), dst.left, dst.top, dst.width(), dst.height(), paint != null ? paint.paint : default_paint.paint);
	}

	@Override
	public void drawPath(Path path, Paint paint) {
		if (path != null)
			native_drawPath(snapshot, path.getGskPath(), paint != null ? paint.paint : default_paint.paint);
	}

	@Override
	public void drawRect(float left, float top, float right, float bottom, Paint paint) {
		native_drawRect(snapshot, left, top, right, bottom, paint != null ? paint.paint : default_paint.paint);
	}

	@Override
	public void rotate(float degrees, float px, float py) {
		native_translate(snapshot, px, py);
		native_rotate(snapshot, degrees);
		native_translate(snapshot, -px, -py);
	}

	@Override
	public void drawText(String text, float x, float y, Paint paint) {
		if(text == null) {
			new Exception("drawText: text is null; stack trace:").printStackTrace();
			return;
		}
		native_drawText(snapshot, text, x, y, paint != null ? paint.paint : default_paint.paint);
	}

	@Override
	public void drawText(String text, int start, int end, float x, float y, Paint paint) {
		drawText(text.substring(start, end), x, y, paint);
	}

	@Override
	public void drawLine(float startX, float startY, float stopX, float stopY, Paint paint) {
		native_drawLine(snapshot, startX, startY, stopX, stopY, paint != null ? paint.paint : default_paint.paint);
	}

	@Override
	public void drawLines(float[] points, Paint paint) {
		drawLines(points, 0, points.length, paint);
	}

	@Override
	public void drawLines(float[] points, int offset, int count, Paint paint) {
		if (offset + count < 0 /* overflow */ || offset + count > points.length)
			throw new IndexOutOfBoundsException();
		native_drawLines(snapshot, points, offset, count, paint != null ? paint.paint : default_paint.paint);
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
	public void drawBitmap(Bitmap bitmap, Matrix matrix, Paint paint) {
		save();
		concat(matrix);
		drawBitmap(bitmap, 0, 0, paint);
		restore();

	}

	@Override
	public void drawRoundRect(float left, float top, float right, float bottom, float rx, float ry, Paint paint) {
		native_drawRoundRect(snapshot, left, top, right, bottom, rx, ry, paint != null ? paint.paint : default_paint.paint);
	}

	@Override
	public void drawCircle(float cx, float cy, float radius, Paint paint) {
		drawRoundRect(cx - radius, cy - radius, cx + radius, cy + radius, radius, radius, paint);
	}

	@Override
	public void scale(float sx, float sy) {
		native_scale(snapshot, sx, sy);
	}

	@Override
	public void concat(Matrix matrix) {
		native_concat(snapshot, matrix.native_instance);
	}

	@Override
	public void drawText(CharSequence text, int start, int end, float x, float y, Paint paint) {
		drawText(text.toString().substring(start, end), x, y, paint);
	}

	@Override
	public boolean clipRect(float left, float top, float right, float bottom) {
		native_clipRect(snapshot, left, top, right, bottom);
		if (push_history == null)
			push_history = new int[save_count+1];
		else if (push_history.length <= save_count)
			push_history = Arrays.copyOf(push_history, save_count+1);
		push_history[save_count]++;
		return right > left && bottom > top;
	}

	protected native void native_drawBitmap(long snapshot, long texture, int x, int y, int width, int height, long paint);
	protected native void native_drawRect(long snapshot, float left, float top, float right, float bottom, long paint);
	protected native void native_drawPath(long snapshot, long path, long paint);
	protected native void native_translate(long snapshot, float dx, float dy);
	protected native void native_rotate(long snapshot, float degrees);
	protected native void native_save(long snapshot);
	protected native void native_restore(long snapshot);
	protected native void native_drawLine(long snapshot, float startX, float startY, float stopX, float stopY, long paint);
	protected native void native_drawLines(long snapshot, float[] points, int offset, int count, long paint);
	protected native void native_drawText(long snapshot, String text, float x, float y, long paint);
	protected native void native_drawRoundRect(long snapshot, float left, float top, float right, float bottom, float rx, float ry, long paint);
	protected native void native_scale(long snapshot, float sx, float sy);
	protected native void native_concat(long snapshot, long matrix);
	protected native void native_clipRect(long snapshot, float left, float top, float right, float bottom);
	protected native void native_pop(long snapshot, int pop_count);
}
