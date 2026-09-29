package android.animation;

public class TimeAnimator extends Animator {

	public interface TimeListener {}

	public void setTimeListener(TimeListener listener) {}

	@Override
	public long getStartDelay() {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'getStartDelay'");
	}

	@Override
	public void setStartDelay(long startDelay) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'setStartDelay'");
	}

	@Override
	public Animator setDuration(long duration) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'setDuration'");
	}

	@Override
	public long getDuration() {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'getDuration'");
	}

	@Override
	public void setInterpolator(TimeInterpolator value) {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException("Unimplemented method 'setInterpolator'");
	}

	@Override
	public boolean isRunning() {
		return false;
	}
}
