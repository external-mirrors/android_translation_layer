package android.view;

import android.graphics.SurfaceTexture;

public class Surface {
	public long widget;

	public Surface() {}

	public Surface(SurfaceTexture surfaceTexture) {}

	public boolean isValid() {
		return widget != 0;
	}

	public void release() {}
}
