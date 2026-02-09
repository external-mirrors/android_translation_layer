package android.os;

import java.io.ByteArrayOutputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Base64;
import java.util.List;

public class Parcel {

	private long builder;
	private long iter;

	Parcel(long builder, long iter) {
		this.builder = builder;
		this.iter = iter;
	}

	public static Parcel obtain() {
		return new Parcel(0, 0);
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
		native_writeString(builder, s);
	}

	public void writeLong(long l) {
		System.out.println("Parcel.writeLong(" + l + ")");
	}

	public void writeInt(int i) {
		System.out.println("Parcel.writeInt(" + i + ")");
		native_writeInt(builder, i);
	}

	public byte[] marshall() {
		return new byte[0];
	}

	public int dataPosition() {
		return 0;
	}

	public void writeParcelable(Parcelable p, int flags) {
		System.out.println("Parcel.writeParcelable(" + p + ", " + flags + ")");
		native_writeString(builder, p != null ? p.getClass().getName() : null);
		if (p != null)
			p.writeToParcel(this, flags);
	}

	public void writeSerializable (Serializable s) {
		System.out.println("Parcel.writeSerializable(" + s + ")");
		try (ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
			ObjectOutputStream objectOutputStream = new ObjectOutputStream(byteArrayOutputStream)) {
			objectOutputStream.writeObject(s);
			byte[] byteArray = byteArrayOutputStream.toByteArray();
			native_writeString(builder, Base64.getEncoder().encodeToString(byteArray));
		} catch(Exception exception) {
			throw new RuntimeException("Parcel.writeSerializable failed", exception);
		}
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
		return native_readString(iter);
	}

	public byte readByte() {
		return 0;
	}

	public ArrayList<String> createStringArrayList() {
		return new ArrayList<String>();
	}

	public Parcelable readParcelable(ClassLoader loader) throws ReflectiveOperationException {
		String className = native_readString(iter);
		if (className == null)
			return null;
		@SuppressWarnings("unchecked")
		Parcelable.Creator<Parcelable> creator = loader.loadClass(className + "$Creator").asSubclass(Parcelable.Creator.class).getConstructor().newInstance();
		return creator.createFromParcel(this);
	}

	public void writeStrongBinder(IBinder binder) {}

	public void readException() {}

	public int readInt() {
		return native_readInt(iter);
	}

	public void writeStringArray(String[] strings) {
		System.out.println("Parcel.writeStringArray(" + strings + ")");
		if (strings == null)
			strings = new String[0];
		native_writeInt(builder, strings.length);
		for (String s : strings) {
			native_writeString(builder, s);
		}
	}

	public String[] createStringArray() {
		int len = native_readInt(iter);
		String[] strings = new String[len];
		for (int i = 0; i < len; i++) {
			strings[i] = native_readString(iter);
		}
		return strings;
	}

	public void writeValue(Object value) {
		System.out.println("Parcel.writeValue(" + value + ")");
		if (value instanceof String) {
			native_writeInt(builder, 0);
			native_writeString(builder, (String)value);
		} else if (value instanceof Integer) {
			native_writeInt(builder, 1);
			native_writeInt(builder, ((Integer)value).intValue());
		} else if (value == null || value instanceof Parcelable) {
			native_writeInt(builder, 2);
			writeParcelable((Parcelable)value, 0);
		} else if (value instanceof List) {
			native_writeInt(builder, 3);
			writeList((List<?>)value);
		} else {
			throw new RuntimeException("Unsupported value type: " + value.getClass().getName());
		}
	}

	public Object readValue(ClassLoader loader) throws ReflectiveOperationException {
		switch (native_readInt(iter)) {
		case 0:
			return native_readString(iter);
		case 1:
			return native_readInt(iter);
		case 2:
			return readParcelable(loader);
		case 3:
		default:
			throw new RuntimeException("Unsupported value type: " + native_readInt(iter));
		}
	}

	public void writeList(List<?> list) {
		System.out.println("Parcel.writeList(" + list + ")");
		if (list == null) {
			native_writeInt(builder, -1);
			return;
		}
		native_writeInt(builder, list.size());
		for (Object value : list) {
			writeValue(value);
		}
	}

	protected static native void native_writeInt(long builder, int i);
	protected static native void native_writeString(long builder, String s);
	protected static native int native_readInt(long iter);
	protected static native String native_readString(long iter);
}
