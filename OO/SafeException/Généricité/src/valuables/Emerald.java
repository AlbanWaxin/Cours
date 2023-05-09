package valuables;

/**
 * An emerald, special kind of gemstone
 * @author ceichler
 *
 */
public class Emerald extends Gemstone {

	/**
	 * Constructor of Emerald
	 * @param myVolume volume of the emerald
	 */
	public Emerald(double myVolume) {
		super(myVolume);
	}
	
	
	/**
	 * Assess the value of the Emerald
	 */
	@Override
	public void expertize() {
		this.value= 20 + 10*this.getVolume();
		System.out.println("New value = " + value);
	}

}
