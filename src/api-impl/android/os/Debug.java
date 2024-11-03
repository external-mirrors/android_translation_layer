package android.os;
public final class Debug {
	public static class MemoryInfo {
	}
	/**
	 * Wait until a debugger attaches.  As soon as the debugger attaches,
	 * this returns, so you will need to place a breakpoint after the
	 * waitForDebugger() call if you want to start tracing immediately.
	 */
	public static class InstructionCount {
		public InstructionCount() {
		}
	}

	public static boolean isDebuggerConnected() {
		return false;
	}

	public static long getNativeHeapFreeSize() {
		return 0;
	}

	public static long getNativeHeapAllocatedSize() {
		return 0;
	}

	public static boolean waitingForDebugger() {
		return false;
	}
}
