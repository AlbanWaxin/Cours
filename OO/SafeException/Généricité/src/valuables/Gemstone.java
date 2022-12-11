package valuables;

import safes.GenericSafe;

import java.util.Objects;

import Exceptions.NotExpertisedException;

/**
 * A precious gemstone
 * 
 * @author ceichler
 * @version 1.0
 *
 */
public abstract class Gemstone implements Valuable,Storable<GenericSafe<Gemstone>>{

	/**
	 * Value of the gemstone
	 */
	protected double value = -1;

	/**
	 * Getter of the property <tt>value</tt>
	 * 
	 * @return Returns the value.
	 */
	public double getValue() throws NotExpertisedException{
		if (this.value == -1) {
			throw new NotExpertisedException(this);
		}
		else {
			return value;
		}
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
	private GenericSafe<Gemstone> mySafe = null;

	/**
	 * Getter of the property <tt>mySafe</tt>
	 * 
	 * @return Returns the mySafe.
	 * @uml.property name="mySafe"
	 */
	public GenericSafe<Gemstone> getMyContainer() {
		return mySafe;
	}

	/**
	 * Setter of the property <tt>monSafe</tt>
	 * 
	 * @param monSafe The monSafe to set.
	 * @uml.property name="monSafe"
	 */
	public void setMyContainer(GenericSafe<Gemstone> mySafe) {
		this.mySafe = mySafe;
	}

	@Override
	public String toString() {
		return this.getClass().getName() + " de volume " + this.getVolume();
	}

	@Override
	public int hashCode() {
		return Objects.hash(volume);
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Gemstone other = (Gemstone) obj;
		return Double.doubleToLongBits(volume) == Double.doubleToLongBits(other.volume);
	}
	
	public double compareTo(Object gem) {
		if (getClass() != gem.getClass())
			return this.getVolume() - ((Gemstone) gem).getVolume();
		else
			return -1;
	}
	

}