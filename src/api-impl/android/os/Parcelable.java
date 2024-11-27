package android.os;

public interface Parcelable {
	public static interface Creator<T> {
		public T createFromParcel(Parcel parcel);
	}

	public static interface ClassLoaderCreator<T> extends Creator<T> {}

	public default void writeToParcel(Parcel dest, int flags) {
		System.out.println("Parcelable.writeToParcel(" + this + ", " + dest + ", " + flags + ")");
	}
}
