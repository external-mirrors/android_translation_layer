package android.os;

import java.util.ArrayList;
import java.util.List;

public class Parcel {

	public static Parcel obtain() {
		return new Parcel();
	}

	public void writeBundle(Bundle bundle) {}

	public Bundle readBundle(ClassLoader loader) {
		return new Bundle();
	}

	public void setDataPosition(int position) {}

	public void recycle() {}

	public void writeByte(byte b) {
		System.out.println("Parcel.writeByte(" + b + ")");
	}

	public void writeString(String s) {
		System.out.println("Parcel.writeString(" + s + ")");
	}

	public void writeLong(long l) {
		System.out.println("Parcel.writeLong(" + l + ")");
	}

	public void writeInt(int i) {
		System.out.println("Parcel.writeInt(" + i + ")");
	}

	public byte[] marshall() {
		return new byte[0];
	}

	public int dataPosition() {
		return 0;
	}

	public void writeParcelable(Parcelable p, int flags) {
		System.out.println("Parcel.writeParcelable(" + p + ", " + flags + ")");
	}

	public void writeInterfaceToken(String s) {
		System.out.println("Parcel.writeInterfaceToken(" + s + ")");
	}

	public void writeStrongInterface(IInterface i) {
		System.out.println("Parcel.writeStrongInterface(" + i + ")");
	}

	public int dataSize() {
		return 0;
	}

	public void writeStringList(List<String> list) {
		System.out.println("Parcel.writeStringList(" + list + ")");
	}

	public void unmarshall(byte[] data, int offset, int length) {}

	public String readString() {
		return "fixme: Parcel.readString()";
	}

	public byte readByte() {
		return 0;
	}

	public ArrayList<String> createStringArrayList() {
		return new ArrayList<String>();
	}

	public Parcelable readParcelable(ClassLoader loader) {
		return null;
	}
}
