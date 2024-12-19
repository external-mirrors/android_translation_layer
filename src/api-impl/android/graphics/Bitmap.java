package android.graphics;

/*
 * Bitmap is implemented as GdkTexture or GtkSnapshot. It can only be one of the two at a time.
 * The methods getTexture() and getSnapshot() automatically convert between the two as needed.
 */
public final class Bitmap {

	public enum Config {
		RGB_565,
		ARGB_8888,
	}

	private int width;
	private int height;
	private long texture;
	private long snapshot;

	Bitmap(long texture) {
		this.texture = texture;
		this.width = native_get_width(texture);
		this.height = native_get_height(texture);
	}

	private Bitmap(int width, int height) {
		this.width = width;
		this.height = height;
	}

	public static Bitmap createBitmap(int width, int height, Config config) {
		return new Bitmap(width, height);
	}

	public int getWidth() {
		return width;
	}

	public int getHeight() {
		return height;
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
}
