package valuables;
import Safe.Safe;

public class Gemstone {
	private double value;
	private final double volume;
	private Safe mySafe;
	
	public Gemstone(double myVolume) {
		this.value = 0;
		this.volume = myVolume;
		this.mySafe = null;		
	}
	
	public void expertize() {
		this.value = this.volume*200;
	}
	
	public Safe getMySafe() {
		return this.mySafe;
	}
	
	public void setMySafe(Safe safe) {
		this.mySafe= safe;
	}
	
	public double getValue() {
		return this.value;
	}
	public double getVolume() {
		return this.volume;
	}
}
