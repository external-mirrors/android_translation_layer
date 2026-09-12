package android.text.util;

import android.text.Spannable;
import android.widget.TextView;
import java.util.regex.Pattern;

public class Linkify {

	public static MatchFilter sUrlMatchFilter = null;

	public static final boolean addLinks(Spannable text, int mask) { return true; }
	public static final boolean addLinks(TextView text, int mask) { return true; }
	public static final boolean addLinks(Spannable text, Pattern urlPattern, String urlScheme) { return true; }

	public interface MatchFilter {}
	public interface TransformFilter {}
}
