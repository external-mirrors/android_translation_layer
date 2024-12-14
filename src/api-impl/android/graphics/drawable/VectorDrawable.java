package android.graphics.drawable;

import java.io.IOException;
import java.util.Locale;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

import com.android.internal.R;

import android.content.res.Resources;
import android.content.res.Resources.Theme;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.ColorFilter;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.Rect;
import android.content.res.TypedArray;
import android.util.AttributeSet;

public class VectorDrawable extends Drawable {

	private Bitmap bitmap;
	private Paint paint = new Paint();
	private float viewportWidth;
	private float viewportHeight;
	private float width;
	private float height;
	private String svg;

	public VectorDrawable() {
		super();
	}

	public void inflate(Resources r, XmlPullParser parser, AttributeSet attrs, Theme theme) throws XmlPullParserException, IOException {
		final int innerDepth = parser.getDepth() + 1;
		int type;
		TypedArray a = r.obtainAttributes(attrs, R.styleable.VectorDrawable);
		if (a.hasValue(R.styleable.VectorDrawable_tint)) {
			setColorFilter(a.getColor(R.styleable.VectorDrawable_tint, 0),
			               PorterDuff.Mode.values()[a.getInt(R.styleable.VectorDrawable_tintMode, DEFAULT_TINT_MODE.nativeInt)]);
		}
		viewportWidth = a.getFloat(R.styleable.VectorDrawable_viewportWidth, 24);
		viewportHeight = a.getFloat(R.styleable.VectorDrawable_viewportHeight, 24);
		width = a.getDimension(R.styleable.VectorDrawable_width, 24);
		height = a.getDimension(R.styleable.VectorDrawable_height, 24);
		a.recycle();
		StringBuilder sb = new StringBuilder();
		while ((type = parser.next()) != XmlPullParser.END_DOCUMENT
				&& (parser.getDepth() >= innerDepth
				|| type != XmlPullParser.END_TAG)) {

			if (type == XmlPullParser.START_TAG && parser.getName().equals("path")) {
				a = r.obtainAttributes(attrs, R.styleable.VectorDrawablePath);
				String pathData = a.getString(R.styleable.VectorDrawablePath_pathData);
				int fillColor = a.getColor(R.styleable.VectorDrawablePath_fillColor, 0);
				int strokeColor = a.getColor(R.styleable.VectorDrawablePath_strokeColor, 0);
				float strokeWidth = a.getFloat(R.styleable.VectorDrawablePath_strokeWidth, 0);
				a.recycle();
				sb.append(String.format(Locale.ENGLISH, "<path fill=\"#%06x%02x\" stroke=\"#%06x%02x\" stroke-width=\"%f\" d=\"%s\"/>",
						fillColor & 0xFFFFFF, (fillColor >> 24) & 0xFF, strokeColor & 0xFFFFFF, (strokeColor >> 24) & 0xFF, strokeWidth, pathData));
			}
		}
		svg = sb.toString();
		setBounds(0, 0, (int)width, (int)height);
	}

	@Override
	public void setBounds(int left, int top, int right, int bottom) {
		super.setBounds(left, top, right, bottom);
		if (bitmap == null || bitmap.getWidth() != right - left || bitmap.getHeight() != bottom - top) {
			if (bitmap != null)
				bitmap.recycle();
			String s = String.format(Locale.ENGLISH, "<svg id=\"vector\" xmlns=\"http://www.w3.org/2000/svg\" width=\"%f\" height=\"%f\" viewBox=\"0 0 %f %f\">%s</svg>",
					(float)(right - left), (float)(bottom - top), viewportWidth, viewportHeight, svg);
			byte[] bytes = s.getBytes();
			bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
		}
	}

	@Override
	public int getIntrinsicWidth() {
		return (int)width;
	}

	@Override
	public int getIntrinsicHeight() {
		return (int)height;
	}

	@Override
	public void setColorFilter(ColorFilter filter) {
		paint.setColorFilter(filter);
	}

	@Override
	public void draw(Canvas canvas) {
		canvas.drawBitmap(bitmap, new Rect(0, 0, bitmap.getWidth(), bitmap.getHeight()), getBounds(), paint);
	}
}
