package android.accounts;

import android.os.Parcel;
import android.os.Parcelable;

public class Account implements Parcelable {
	public final String name;
	public final String type;

	public Account(String name, String type) {
		this.name = name;
		this.type = type;
	}

	public Account(Parcel in) {
		this.name = in.readString();
		this.type = in.readString();
	}

	@Override
	public void writeToParcel(Parcel dest, int flags) {
		dest.writeString(name);
		dest.writeString(type);
	}

	public static final Creator<Account> CREATOR = new Creator<Account>() {
		public Account createFromParcel(Parcel source) {
			return new Account(source);
		}

		public Account[] newArray(int size) {
			return new Account[size];
		}
	};

	public boolean equals(Object o) {
		if (o == this)
			return true;
		if (!(o instanceof Account))
			return false;
		final Account other = (Account)o;
		return name.equals(other.name) && type.equals(other.type);
	}

	public int hashCode() {
		int result = 17;
		result = 31 * result + name.hashCode();
		result = 31 * result + type.hashCode();
		return result;
	}
}
