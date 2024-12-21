package android.graphics;

import android.util.DisplayMetrics;

/*
 * Bitmap is implemented as GdkTexture or GtkSnapshot. It can only be one of the two at a time.
 * The methods getTexture() and getSnapshot() automatically convert between the two as needed.
 */
public final class Bitmap {

	public enum Config {
		RGB_565,
		ARGB_8888,
		ARGB_4444,
		ALPHA_8,
	}

	private int width;
	private int height;
	private long texture;
	private long snapshot;
	private Config config = Config.ARGB_8888;

	Bitmap(long texture) {
		this.texture = texture;
		this.width = native_get_width(texture);
		this.height = native_get_height(texture);
	}

	private Bitmap(int width, int height, Config config) {
		this.config = config;
		this.width = width;
		this.height = height;
	}

	public static Bitmap createBitmap(int width, int height, Config config) {
		return new Bitmap(width, height, config);
	}

	public static Bitmap createBitmap(DisplayMetrics metrics, int width, int height, Config config) {
		return new Bitmap(width, height, config);
	}

	public static Bitmap createBitmap(DisplayMetrics metrics, int width, int height, Config config, boolean hasAlpha, ColorSpace colorSpace) {
		return new Bitmap(width, height, config);
	}

	public static Bitmap createBitmap(Bitmap src, int x, int y, int width, int height) {
		Bitmap dest = new Bitmap(width, height, src.getConfig());
		new Canvas(dest).drawBitmap(src, new Rect(x, y, x + width, y + height), new Rect(0, 0, width, height), null);
		return dest;
	}

	public static Bitmap createBitmap(Bitmap src, int x, int y, int width, int height, Matrix matrix, boolean filter) {
		Bitmap dest = new Bitmap(width, height, src.getConfig());
		Canvas canvas = new Canvas(dest);
		canvas.concat(matrix);
		canvas.drawBitmap(src, new Rect(x, y, x + width, y + height), new Rect(0, 0, width, height), null);
		return dest;
	}

	public static Bitmap createBitmap(Bitmap src) {
		return new Bitmap(native_ref_texture(src.getTexture()));
	}

	public static Bitmap createScaledBitmap(Bitmap src, int dstWidth, int dstHeight, boolean filter) {
		Bitmap dest = new Bitmap(dstWidth, dstHeight, src.getConfig());
		new Canvas(dest).drawBitmap(src, new Rect(0, 0, src.getWidth(), src.getHeight()), new Rect(0, 0, dstWidth, dstHeight), null);
		return dest;
	}

	public int getWidth() {
		return width;
	}

	public int getHeight() {
		return height;
	}

	public Config getConfig() {
		return config;
	}

	public synchronized long getTexture() {
		if (texture == 0) {
			texture = native_create_texture(snapshot, width, height);
			snapshot = 0;
		}
		return texture;
	}

	synchronized long getSnapshot() {
		if (snapshot == 0) {
			snapshot = native_create_snapshot(texture);
			texture = 0;
		}
		return snapshot;
	}

	public void eraseColor(int color) {
		recycle();
		snapshot = native_erase_color(color, width, height);
		texture = 0;
	}

	public void recycle() {
		native_recycle(texture, snapshot);
		texture = 0;
		snapshot = 0;
	}

	public int getAllocationByteCount() {
		return width * height * 4;
	}

	public void prepareToDraw() {
		getTexture();
	}

	public void setDensity(int density) {}

	public int getScaledWidth(int density) {
		return width;
	}

	public int getScaledHeight(int density) {
		return height;
	}

	public boolean isRecycled() {
		return texture == 0 && snapshot == 0;
	}

	public void setHasAlpha(boolean hasAlpha) {}

	public Bitmap copy(Bitmap.Config config, boolean hasAlpha) {
		Bitmap bitmap = new Bitmap(width, height, config);
		bitmap.texture = native_ref_texture(getTexture());
		return bitmap;
	}

	public void getPixels(int[] pixels, int offset, int stride, int x, int y, int width, int height) {
		native_get_pixels(getTexture(), pixels, offset, stride, x, y, width, height);
	}

	@SuppressWarnings("deprecation")
	@Override
	protected void finalize() throws Throwable {
		try {
			recycle();
		} finally {
			super.finalize();
		}
	}

	private static native long native_create_snapshot(long texture);
	private static native long native_create_texture(long snapshot, int width, int height);
	private static native int native_get_width(long texture);
	private static native int native_get_height(long texture);
	private static native long native_erase_color(int color, int width, int height);
	private static native void native_recycle(long texture, long snapshot);
	private static native long native_ref_texture(long texture);
	private static native void native_get_pixels(long texture, int[] pixels, int offset, int stride, int x, int y, int width, int height);
}
