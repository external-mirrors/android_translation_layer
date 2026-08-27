package android.text;

import android.atl.annotation.Export;

public interface TextWatcher {

	public void beforeTextChanged(CharSequence s, int start, int count, int after);

	@Export
	public void onTextChanged(CharSequence s, int start, int before, int count);

	@Export
	public void afterTextChanged(Editable s);
}
