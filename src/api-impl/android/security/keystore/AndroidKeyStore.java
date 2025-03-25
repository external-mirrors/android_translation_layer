package android.security.keystore;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.security.Key;
import java.security.KeyStoreException;
import java.security.KeyStoreSpi;
import java.security.NoSuchAlgorithmException;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.util.Date;
import java.util.Enumeration;
import java.util.HashMap;

public class AndroidKeyStore extends KeyStoreSpi {

	HashMap<String, String> map = new HashMap<>();

	@Override
	public Key engineGetKey(String alias, char[] password) throws NoSuchAlgorithmException, UnrecoverableKeyException {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineGetKey'");
	}

	@Override
	public Certificate[] engineGetCertificateChain(String alias) {
		// TODO Auto-generated method stub
		System.out.println("engineGetCertificateChain(" + alias + ") called");
		return new Certificate[0];
	}

	@Override
	public Certificate engineGetCertificate(String alias) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineGetCertificate'");
	}

	@Override
	public Date engineGetCreationDate(String alias) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineGetCreationDate'");
	}

	@Override
	public void engineSetKeyEntry(String alias, Key key, char[] password, Certificate[] chain)
			throws KeyStoreException {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineSetKeyEntry'");
	}

	@Override
	public void engineSetKeyEntry(String alias, byte[] key, Certificate[] chain) throws KeyStoreException {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineSetKeyEntry'");
	}

	@Override
	public void engineSetCertificateEntry(String alias, Certificate cert) throws KeyStoreException {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineSetCertificateEntry'");
	}

	@Override
	public void engineDeleteEntry(String alias) throws KeyStoreException {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineDeleteEntry'");
	}

	@Override
	public Enumeration<String> engineAliases() {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineAliases'");
	}

	@Override
	public boolean engineContainsAlias(String alias) {
		// TODO Auto-generated method stub
		System.out.println("engineContainsAlias(" + alias + ") called");
		return map.containsKey(alias);
	}

	@Override
	public int engineSize() {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineSize'");
	}

	@Override
	public boolean engineIsKeyEntry(String alias) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineIsKeyEntry'");
	}

	@Override
	public boolean engineIsCertificateEntry(String alias) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineIsCertificateEntry'");
	}

	@Override
	public String engineGetCertificateAlias(Certificate cert) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineGetCertificateAlias'");
	}

	@Override
	public void engineStore(OutputStream stream, char[] password)
			throws IOException, NoSuchAlgorithmException, CertificateException {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'engineStore'");
	}

	@Override
	public void engineLoad(InputStream stream, char[] password)
			throws IOException, NoSuchAlgorithmException, CertificateException {
	}
	
}
