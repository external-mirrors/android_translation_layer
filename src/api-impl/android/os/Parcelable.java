package android.os;

public interface Parcelable {
	public static final int CONTENTS_FILE_DESCRIPTOR = 1;

	public static interface Creator<T> {
		public T createFromParcel(Parcel parcel);

		public T[] newArray(int size);
	}

	public static interface ClassLoaderCreator<T> extends Creator<T> {}

	// unlike AOSP, we have a default implementations, so we don't need to stub it in every individual class
	public default int describeContents() {
		return 0;
	}

	// unlike AOSP, we have a default implementations, so we don't need to stub it in every individual class
	public default void writeToParcel(Parcel dest, int flags) {
	}
}
