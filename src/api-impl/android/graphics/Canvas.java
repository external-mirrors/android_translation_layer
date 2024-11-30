package android.graphics;

public class Canvas {
	public static final int HAS_ALPHA_LAYER_SAVE_FLAG = (1 << 2);

	public long skia_canvas;
	public long widget;

	public Canvas() {}

	public Canvas(Bitmap bmp) {
		bmp.destroyTexture();  // invalidate cached texture
		this.skia_canvas = native_canvas_from_bitmap(bmp.pixbuf);
		this.widget = 0;
	}

	public Canvas(long skia_canvas, long widget) {
		this.skia_canvas = skia_canvas;
		this.widget = widget;
	}

	@Override
	@SuppressWarnings("deprecation")
	protected void finalize() throws Throwable {
		try {
			super.finalize();
		} finally {
			if (skia_canvas != 0) {
				native_destroy_canvas(skia_canvas);
				skia_canvas = 0;
			}
		}
	}

	// FIXME: are these _needed_ ?

	public int save() {
		native_save(skia_canvas, widget);
		return -1; // FIXME: wtf should we return
	}
	public void restore() {
		native_restore(skia_canvas, widget);
	}

	// ---

	/**
	 * Draw the specified Rect using the specified paint. The rectangle will
	 * be filled or framed based on the Style in the paint.
	 *
	 * @param rect  The rect to be drawn
	 * @param paint The paint used to draw the rect
	 */
	public void drawRect(RectF r, Paint paint) {
		drawRect(r.left, r.top, r.right, r.bottom, paint);
	}

	/**
	 * Draw the specified Rect using the specified Paint. The rectangle
	 * will be filled or framed based on the Style in the paint.
	 *
	 * @param r        The rectangle to be drawn.
	 * @param paint    The paint used to draw the rectangle
	 */
	public void drawRect(Rect r, Paint paint) {
		drawRect(r.left, r.top, r.right, r.bottom, paint);
	}

	/**
	 * Draw the specified Rect using the specified paint. The rectangle will
	 * be filled or framed based on the Style in the paint.
	 *
	 * @param left   The left side of the rectangle to be drawn
	 * @param top    The top side of the rectangle to be drawn
	 * @param right  The right side of the rectangle to be drawn
	 * @param bottom The bottom side of the rectangle to be drawn
	 * @param paint  The paint used to draw the rect
	 */
	public void drawRect(float left, float top, float right, float bottom, Paint paint) {
		native_drawRect(skia_canvas, left, top, right, bottom, paint.skia_paint);
	}

	// ---
	/**
	 * Preconcat the current matrix with the specified rotation.
	 *
	 * @param degrees The amount to rotate, in degrees
	 */
	public void rotate(float degrees) {
		native_rotate(skia_canvas, widget, degrees);
	}

	/**
	 * Preconcat the current matrix with the specified rotation.
	 *
	 * @param degrees The amount to rotate, in degrees
	 * @param px The x-coord for the pivot point (unchanged by the rotation)
	 * @param py The y-coord for the pivot point (unchanged by the rotation)
	 */
	public void rotate(float degrees, float px, float py) {
		native_rotate_and_translate(skia_canvas, widget, degrees, px, py);
	}
	// ---
	/**
	 * Draw the text, with origin at (x,y), using the specified paint. The
	 * origin is interpreted based on the Align setting in the paint.
	 *
	 * @param text  The text to be drawn
	 * @param x     The x-coordinate of the origin of the text being drawn
	 * @param y     The y-coordinate of the origin of the text being drawn
	 * @param paint The paint used for the text (e.g. color, size, style)
	 */
	public void drawText(String text, float x, float y, Paint paint) {
		native_drawText(skia_canvas, text, 0, text.length(), x, y, paint.skia_font, paint.skia_paint);
	}

	/**
	 * Draw the text, with origin at (x,y), using the specified paint.
	 * The origin is interpreted based on the Align setting in the paint.
	 *
	 * @param text  The text to be drawn
	 * @param start The index of the first character in text to draw
	 * @param end   (end - 1) is the index of the last character in text to draw
	 * @param x     The x-coordinate of the origin of the text being drawn
	 * @param y     The y-coordinate of the origin of the text being drawn
	 * @param paint The paint used for the text (e.g. color, size, style)
	 */
	public void drawText(String text, int start, int end, float x, float y, Paint paint) {
		/*      if ((start | end | (end - start) | (text.length() - end)) < 0) {
			  throw new IndexOutOfBoundsException();
		      }
		      native_drawText(mNativeCanvas, text, start, end, x, y, paint.mBidiFlags,
			      paint.mNativePaint);*/
	}

	/**
	 * Draw the specified range of text, specified by start/end, with its
	 * origin at (x,y), in the specified Paint. The origin is interpreted
	 * based on the Align setting in the Paint.
	 *
	 * @param text     The text to be drawn
	 * @param start    The index of the first character in text to draw
	 * @param end      (end - 1) is the index of the last character in text
	 *                 to draw
	 * @param x        The x-coordinate of origin for where to draw the text
	 * @param y        The y-coordinate of origin for where to draw the text
	 * @param paint The paint used for the text (e.g. color, size, style)
	 */
	public void drawText(CharSequence text, int start, int end, float x, float y, Paint paint) {
		/*if (text instanceof String || text instanceof SpannedString ||
		    text instanceof SpannableString) {
		    native_drawText(mNativeCanvas, text.toString(), start, end, x, y,
			    paint.mBidiFlags, paint.mNativePaint);
		} else if (text instanceof GraphicsOperations) {
		    ((GraphicsOperations) text).drawText(this, start, end, x, y,
			    paint);
		} else {
		    char[] buf = TemporaryBuffer.obtain(end - start);
		    TextUtils.getChars(text, start, end, buf, 0);
		    native_drawText(mNativeCanvas, buf, 0, end - start, x, y,
			    paint.mBidiFlags, paint.mNativePaint);
		    TemporaryBuffer.recycle(buf);
		}*/
	}
	// ---
	/**
	 * <p>Draw the specified arc, which will be scaled to fit inside the
	 * specified oval.</p>
	 *
	 * <p>If the start angle is negative or >= 360, the start angle is treated
	 * as start angle modulo 360.</p>
	 *
	 * <p>If the sweep angle is >= 360, then the oval is drawn
	 * completely. Note that this differs slightly from SkPath::arcTo, which
	 * treats the sweep angle modulo 360. If the sweep angle is negative,
	 * the sweep angle is treated as sweep angle modulo 360</p>
	 *
	 * <p>The arc is drawn clockwise. An angle of 0 degrees correspond to the
	 * geometric angle of 0 degrees (3 o'clock on a watch.)</p>
	 *
	 * @param oval       The bounds of oval used to define the shape and size
	 *                   of the arc
	 * @param startAngle Starting angle (in degrees) where the arc begins
	 * @param sweepAngle Sweep angle (in degrees) measured clockwise
	 * @param useCenter If true, include the center of the oval in the arc, and
			    close it if it is being stroked. This will draw a wedge
	 * @param paint      The paint used to draw the arc
	 */
	public void drawArc(RectF oval, float startAngle, float sweepAngle, boolean useCenter,
			    Paint paint) {
		if (oval == null) {
			throw new NullPointerException();
		}
		/*native_drawArc(mNativeCanvas, oval, startAngle, sweepAngle,
			useCenter, paint.mNativePaint);*/
	}
	// ---
	/**
	 * Preconcat the current matrix with the specified scale.
	 *
	 * @param sx The amount to scale in X
	 * @param sy The amount to scale in Y
	 */
	public /*native*/ void scale(float sx, float sy) {/*used by gd*/}

	/**
	 * Preconcat the current matrix with the specified scale.
	 *
	 * @param sx The amount to scale in X
	 * @param sy The amount to scale in Y
	 * @param px The x-coord for the pivot point (unchanged by the scale)
	 * @param py The y-coord for the pivot point (unchanged by the scale)
	 */
	public final void scale(float sx, float sy, float px, float py) {
		System.out.println("XXXXXXX scale(sx, sy, px, py)");
		/*translate(px, py);
		scale(sx, sy);
		translate(-px, -py);*/
	}
	// ---
	/**
	 * Draw the specified bitmap, with its top/left corner at (x,y), using
	 * the specified paint, transformed by the current matrix.
	 *
	 * <p>Note: if the paint contains a maskfilter that generates a mask which
	 * extends beyond the bitmap's original width/height (e.g. BlurMaskFilter),
	 * then the bitmap will be drawn as if it were in a Shader with CLAMP mode.
	 * Thus the color outside of the original width/height will be the edge
	 * color replicated.
	 *
	 * <p>If the bitmap and canvas have different densities, this function
	 * will take care of automatically scaling the bitmap to draw at the
	 * same density as the canvas.
	 *
	 * @param bitmap The bitmap to be drawn
	 * @param left   The position of the left side of the bitmap being drawn
	 * @param top    The position of the top side of the bitmap being drawn
	 * @param paint  The paint used to draw the bitmap (may be null)
	 */
	public void drawBitmap(Bitmap bitmap, float left, float top, Paint paint) {
		if(skia_canvas == 0) {
			System.out.println(this + " doesn't have a skia canvas");
			return;
		}
		native_drawBitmap(skia_canvas, widget, bitmap.pixbuf, 0, 0, bitmap.getWidth(), bitmap.getHeight(),
		                                                      left, top, left + bitmap.getWidth(), top + bitmap.getHeight(),
		                                                      (paint != null) ? paint.skia_paint : 0);
	}

	/**
	 * Draw the specified bitmap, scaling/translating automatically to fill
	 * the destination rectangle. If the source rectangle is not null, it
	 * specifies the subset of the bitmap to draw.
	 *
	 * <p>Note: if the paint contains a maskfilter that generates a mask which
	 * extends beyond the bitmap's original width/height (e.g. BlurMaskFilter),
	 * then the bitmap will be drawn as if it were in a Shader with CLAMP mode.
	 * Thus the color outside of the original width/height will be the edge
	 * color replicated.
	 *
	 * <p>This function <em>ignores the density associated with the bitmap</em>.
	 * This is because the source and destination rectangle coordinate
	 * spaces are in their respective densities, so must already have the
	 * appropriate scaling factor applied.
	 *
	 * @param bitmap The bitmap to be drawn
	 * @param src    May be null. The subset of the bitmap to be drawn
	 * @param dst    The rectangle that the bitmap will be scaled/translated
	 *               to fit into
	 * @param paint  May be null. The paint used to draw the bitmap
	 */
	public void drawBitmap(Bitmap bitmap, Rect src, RectF dst, Paint paint) {
		if (dst == null) {
			throw new NullPointerException();
		}
		if(src == null) {
			src = new Rect(0, 0, bitmap.getWidth(), bitmap.getHeight());
		}
		native_drawBitmap(skia_canvas, widget, bitmap.pixbuf, src.left, src.top, src.right, src.bottom,
		                                                      dst.left, dst.top, dst.right, dst.bottom,
		                                                      (paint != null) ? paint.skia_paint : 0);
	}

	/**
	 * Draw the specified bitmap, scaling/translating automatically to fill
	 * the destination rectangle. If the source rectangle is not null, it
	 * specifies the subset of the bitmap to draw.
	 *
	 * <p>Note: if the paint contains a maskfilter that generates a mask which
	 * extends beyond the bitmap's original width/height (e.g. BlurMaskFilter),
	 * then the bitmap will be drawn as if it were in a Shader with CLAMP mode.
	 * Thus the color outside of the original width/height will be the edge
	 * color replicated.
	 *
	 * <p>This function <em>ignores the density associated with the bitmap</em>.
	 * This is because the source and destination rectangle coordinate
	 * spaces are in their respective densities, so must already have the
	 * appropriate scaling factor applied.
	 *
	 * @param bitmap The bitmap to be drawn
	 * @param src    May be null. The subset of the bitmap to be drawn
	 * @param dst    The rectangle that the bitmap will be scaled/translated
	 *               to fit into
	 * @param paint  May be null. The paint used to draw the bitmap
	 */
	public void drawBitmap(Bitmap bitmap, Rect src, Rect dst, Paint paint) {
		System.out.println("XXXXXXX bitmap(bitmap, src, dst, paint)");
	 /*
		     if (dst == null) {
			     throw new NullPointerException();
		     }
		     native_drawBitmap(mNativeCanvas, bitmap.ni(), src, dst, paint != null ? paint.mNativePaint : 0, mScreenDensity, bitmap.mDensity);
	     */
	}

	/**
	 * Treat the specified array of colors as a bitmap, and draw it. This gives
	 * the same result as first creating a bitmap from the array, and then
	 * drawing it, but this method avoids explicitly creating a bitmap object
	 * which can be more efficient if the colors are changing often.
	 *
	 * @param colors Array of colors representing the pixels of the bitmap
	 * @param offset Offset into the array of colors for the first pixel
	 * @param stride The number of colors in the array between rows (must be
	 *               >= width or <= -width).
	 * @param x The X coordinate for where to draw the bitmap
	 * @param y The Y coordinate for where to draw the bitmap
	 * @param width The width of the bitmap
	 * @param height The height of the bitmap
	 * @param hasAlpha True if the alpha channel of the colors contains valid
	 *                 values. If false, the alpha byte is ignored (assumed to
	 *                 be 0xFF for every pixel).
	 * @param paint  May be null. The paint used to draw the bitmap
	 */
	public void drawBitmap(int[] colors, int offset, int stride, float x, float y,
			       int width, int height, boolean hasAlpha, Paint paint) {
			System.out.println("XXXXXXX bitmap(colors, offset, ...)");
		/*        // check for valid input
			if (width < 0) {
			    throw new IllegalArgumentException("width must be >= 0");
			}
			if (height < 0) {
			    throw new IllegalArgumentException("height must be >= 0");
			}
			if (Math.abs(stride) < width) {
			    throw new IllegalArgumentException("abs(stride) must be >= width");
			}
			int lastScanline = offset + (height - 1) * stride;
			int length = colors.length;
			if (offset < 0 || (offset + width > length) || lastScanline < 0
				|| (lastScanline + width > length)) {
			    throw new ArrayIndexOutOfBoundsException();
			}
			// quick escape if there's nothing to draw
			if (width == 0 || height == 0) {
			    return;
			}
			// punch down to native for the actual draw
			native_drawBitmap(mNativeCanvas, colors, offset, stride, x, y, width, height, hasAlpha,
				paint != null ? paint.mNativePaint : 0);*/
	}

	/**
	 * Legacy version of drawBitmap(int[] colors, ...) that took ints for x,y
	 */
	public void drawBitmap(int[] colors, int offset, int stride, int x, int y,
			       int width, int height, boolean hasAlpha, Paint paint) {
		// call through to the common float version
		drawBitmap(colors, offset, stride, (float)x, (float)y, width, height,
			   hasAlpha, paint);
	}

	/**
	 * Draw the bitmap using the specified matrix.
	 *
	 * @param bitmap The bitmap to draw
	 * @param matrix The matrix used to transform the bitmap when it is drawn
	 * @param paint  May be null. The paint used to draw the bitmap
	 */
	public void drawBitmap(Bitmap bitmap, Matrix matrix, Paint paint) {
			System.out.println("XXXXXXX bitmap(bitmap, matrix, paint)");
		/*       nativeDrawBitmapMatrix(mNativeCanvas, bitmap.ni(), matrix.ni(),
			       paint != null ? paint.mNativePaint : 0);*/
	}
	// ---
	/**
	 * Draw a line segment with the specified start and stop x,y coordinates,
	 * using the specified paint.
	 *
	 * <p>Note that since a line is always "framed", the Style is ignored in the paint.</p>
	 *
	 * <p>Degenerate lines (length is 0) will not be drawn.</p>
	 *
	 * @param startX The x-coordinate of the start point of the line
	 * @param startY The y-coordinate of the start point of the line
	 * @param paint  The paint used to draw the line
	 */
	public void drawLine(float startX, float startY, float stopX, float stopY, Paint paint) {
		native_drawLine(skia_canvas, widget, startX, startY, stopX, stopY, paint.skia_paint);
	}

	public void setBitmap(Bitmap bitmap) {
		if (skia_canvas != 0) {
			native_destroy_canvas(skia_canvas);
		}
		bitmap.destroyTexture();  // invalidate cached texture
		this.skia_canvas = native_canvas_from_bitmap(bitmap.pixbuf);
		this.widget = 0;
	}

	public void drawPath(Path path, Paint paint) {
		native_drawPath(skia_canvas, path.mNativePath, paint.skia_paint);
	}

	public boolean clipPath(Path path) {
		return false;
	}

	public void restoreToCount(int count) {}

	public void drawRoundRect(RectF rect, float rx, float ry, Paint paint) {}

	public void getMatrix(Matrix matrix) {
		matrix.reset();
	}

	public void translate(float dx, float dy) {}

	public void drawCircle(float cx, float cy, float radius, Paint paint) {}

	public Rect getClipBounds() {
		return new Rect(0, 0, 10, 10);
	}

	public boolean clipRect(Rect rect, Region.Op op) {
		return false;
	}

	public void concat(Matrix matrix) {}

	public boolean clipPath(Path path, Region.Op op) {
		return false;
	}

	public int getWidth() {
		return 10; //FIXME
	}

	public int getHeight() {
		return 10; //FIXME
	}

	public void drawColor(int dummy) {}

	public void drawARGB(int a, int r, int g, int b) {}

	public int saveLayer(RectF bounds, Paint paint, int flags) {
		return save();
	}

	public void drawOval(RectF oval, Paint paint) {}

	public boolean clipRect(int left, int top, int right, int bottom) {
		return false;
	}

	public void drawColor(int color, PorterDuff.Mode mode) {}

	public boolean clipRect(Rect rect) {
		return false;
	}

	private static native long native_canvas_from_bitmap(long pixbuf);

	private static native void native_save(long skia_canvas, long widget);
	private static native void native_restore(long skia_canvas, long widget);

	private static native void native_drawText(long skia_canvas, CharSequence text, int start, int end, float x, float y, long skia_font, long skia_paint);
	private static native void native_drawRect(long skia_canvas, float left, float top, float right, float bottom, long skia_paint);
	private static native void native_drawLine(long skia_canvas, long widget, float startX, float startY, float stopX, float stopY, long skia_paint);
	private static native void native_drawBitmap(long skia_canvas, long widget, long pixbuf, float src_left, float src_top, float src_right, float src_bottom, float dest_left, float dest_top, float dest_right, float dest_bottm, long skia_paint);
	private static native void native_rotate(long skia_canvas, long widget, float angle);
	private static native void native_rotate_and_translate(long skia_canvas, long widget, float angle, float tx, float ty);
	private static native void native_drawPath(long skia_canvas, long path, long skia_paint);
	private static native void native_destroy_canvas(long skia_canvas);
}
