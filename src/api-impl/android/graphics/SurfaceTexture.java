package android.graphics;
import android.os.Handler;

public class SurfaceTexture {

	public interface OnFrameAvailableListener {
		void onFrameAvailable(SurfaceTexture surfaceTexture);
	}

	public interface OnSetFrameRateListener {
		void onSetFrameRate(SurfaceTexture surfaceTexture, float frameRate, int compatibility, int changeFrameRateStrategy);
	}

	public static class OutOfResourcesException extends Exception {
		public OutOfResourcesException() {
		}
		public OutOfResourcesException(String name) {
			super(name);
		}
	}

	public SurfaceTexture(int texName) {
		this(texName, false);
	}

	public SurfaceTexture(int texName, boolean singleBufferMode) {}
	public SurfaceTexture(boolean singleBufferMode) {}
	public void setOnFrameAvailableListener(OnFrameAvailableListener listener) {
		setOnFrameAvailableListener(listener, null);
	}
	public void setOnFrameAvailableListener(final OnFrameAvailableListener listener, Handler handler) {}
	public void setOnSetFrameRateListener(final OnSetFrameRateListener listener, Handler handler) {}
	public void setDefaultBufferSize(int width, int height) {}
	public void updateTexImage() {}
	public void releaseTexImage() {}
	public void detachFromGLContext() {}
	public void attachToGLContext(int texName) {}
	public void getTransformMatrix(float[] mtx) {}
	public long getTimestamp() {
		return 0; //FIXME
	}
	public int getDataSpace() {
		return 0; //FIXME
	}
	public void release() {}
	public boolean isReleased() {
		return false; //FIXME
	}
	protected void finalize() throws Throwable {}
	public boolean isSingleBuffered() {
		return true; //FIXME
	}
}
