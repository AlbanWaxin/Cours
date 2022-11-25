package valuables;
import boite.Boite;

public class Gemstone {
	private double value;
	private final double volume;
	private Boite mySafe;
	
	public Gemstone(double myVolume) {
		this.value = 0;
		this.volume = myVolume;
		this.mySafe = null;		
	}
	
	public void expertize() {
		this.value = this.volume*200;
	}
	
	public Boite getMySafe() {
		return this.mySafe;
	}
	
	public void setMySafe(Boite safe) {
		this.mySafe= safe;
	}
	
	public double getValue() {
		return this.value;
	}
	public double getVolume() {
		return this.volume;
	}
}
