package android.provider;

import android.net.Uri;

public class MediaStore {
	
	public static class Images {
		
		public static class Media {

			public static final Uri EXTERNAL_CONTENT_URI = Uri.parse("content://media/external/images/media");
		}
	}
}
