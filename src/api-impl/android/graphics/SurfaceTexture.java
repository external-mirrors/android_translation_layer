package android.graphics;

public class SurfaceTexture {

	public static interface OnFrameAvailableListener {}

	public SurfaceTexture(int texName) {}

	public void setOnFrameAvailableListener(OnFrameAvailableListener listener) {}

	public void release() {}
}
