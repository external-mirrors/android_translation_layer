package android.view;

import android.content.Context;
import android.util.AttributeSet;

public class TextureView extends View {

	public TextureView(Context context) {
		super(context);
	}

	public TextureView(Context context, AttributeSet attributeSet) {
		super(context, attributeSet);
	}

	public interface SurfaceTextureListener {}

	public void setSurfaceTextureListener(SurfaceTextureListener surfaceTextureListener) {}

	public void setOpaque(boolean opaque) {}

}
