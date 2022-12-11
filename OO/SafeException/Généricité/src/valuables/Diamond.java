package valuables;

/**
 * A diamond, very precious gemstone
 * @author ceichler
 *
 */
public class Diamond extends Gemstone {

	/**
	 * Constructor of diamond
	 * @param myVolume volume of the diamond
	 */
	public Diamond(double myVolume) {
		super(myVolume);
		
	}

	/**
	 * Assess the value of the diamond
	 */
	@Override
	public void expertize() {
		this.value = 1000*this.getVolume();
	}

}
