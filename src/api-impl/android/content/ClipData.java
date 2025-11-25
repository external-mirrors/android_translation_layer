package android.content;

import android.net.Uri;

public class ClipData {

	public static class Item {
	}

	String text;

	public static ClipData newPlainText(CharSequence label, CharSequence text) {
		ClipData clip = new ClipData();
		clip.text = text.toString();
		return clip;
	}

	public static ClipData newRawUri(CharSequence label, Uri uri) {
		ClipData clip = new ClipData();
		clip.text = uri.toString();
		return clip;
	}

	public void addItem(ContentResolver resolver, Item item) {
	}

	public Item getItemAt(int index) {
		return null;
	}

	public int getItemCount() {
		return 0;
	}
}
