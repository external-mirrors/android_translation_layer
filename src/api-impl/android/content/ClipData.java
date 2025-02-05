package android.content;

public class ClipData {

	String text;

	public static ClipData newPlainText(CharSequence label, CharSequence text) {
		ClipData clip = new ClipData();
		clip.text = text.toString();
		return clip;
	}
}
