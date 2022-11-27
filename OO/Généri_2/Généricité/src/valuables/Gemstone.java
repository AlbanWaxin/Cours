package valuables;

import safes.GenericSafe;

/**
 * A precious gemstone
 * 
 * @author ceichler
 * @version 1.0
 *
 */
public abstract class Gemstone implements Valuable {

	/**
	 * Value of the gemstone
	 */
	protected double value = -1;

	/**
	 * Getter of the property <tt>value</tt>
	 * 
	 * @return Returns the value.
	 */
	public double getValue() {
		return value;
	}

	/**
	 * Volume of the gemstone
	 */
	private final double volume;

	/**
	 * Getter of the property <tt>volume</tt>
	 * 
	 * @return Returns the volume.
	 */
	public double getVolume() {
		return volume;
	}

	/**
	 * Constructing a gemstone with some volume and weight
	 * 
	 * @param myVolume volume of the gemstone
	 */
	public Gemstone(double myVolume) {
		volume = myVolume;
	}

	/**
	 * Assess the value of the gemstone
	 */
	public abstract void expertize();

	/**
	 * Safe containing the gem
	 */
	private GenericSafe mySafe = null;

	/**
	 * Getter of the property <tt>mySafe</tt>
	 * 
	 * @return Returns the mySafe.
	 * @uml.property name="mySafe"
	 */
	public GenericSafe getMySafe() {
		return mySafe;
	}

	/**
	 * Setter of the property <tt>monSafe</tt>
	 * 
	 * @param monSafe The monSafe to set.
	 * @uml.property name="monSafe"
	 */
	public void setMySafe(GenericSafe mySafe) {
		this.mySafe = mySafe;
	}

	@Override
	public String toString() {
		return this.getClass().getName() + " de volume " + this.getVolume();
	}

}