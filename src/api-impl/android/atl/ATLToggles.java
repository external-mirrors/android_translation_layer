package android.atl;

public final class ATLToggles {
	public static final boolean ATL_GHAX = queryBooleanToggle("ATL_GHAX", true);

	private ATLToggles() {}

	private static boolean queryBooleanToggle(String name, boolean def) {
		String env = System.getenv(name);
		return env == null || env.isEmpty() ? def : "1".equals(env) || "true".equals(env);
	}
}
