package android.content;

import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map;

import android.content.pm.PackageParser;
import android.content.pm.ProviderInfo;
import android.database.Cursor;
import android.net.Uri;
import android.os.ParcelFileDescriptor;

public abstract class ContentProvider {

	static Map<String, ContentProvider> providers = new HashMap<String, ContentProvider>();

	static void createContentProviders() {
		for (PackageParser.Provider provider_parsed : Context.pkg.providers) {
			try {
				String providerName = provider_parsed.className;
				System.out.println("creating " + providerName);
				Class<? extends ContentProvider> providerCls = Class.forName(providerName).asSubclass(ContentProvider.class);
				ContentProvider provider = providerCls.getConstructor().newInstance();
				provider.attachInfo(Context.this_application, provider_parsed.info);
				provider.onCreate();
				providers.put(provider_parsed.info.authority, provider);
			} catch(Exception e) { e.printStackTrace(); }
		}
	}

	public boolean onCreate() {return false;}

	public Context getContext() {
		return new Context();
	}

	public abstract Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sortOrder);

	public abstract Uri insert(Uri uri, ContentValues values);

	public abstract int delete(Uri uri, String selection, String[] selectionArgs);

	public abstract String getType(Uri uri);

	public abstract ParcelFileDescriptor openFile(Uri uri, String mode) throws FileNotFoundException;

	public void attachInfo(Context context, ProviderInfo provider) {}

}
