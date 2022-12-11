package valuables;

import Exceptions.NotExpertisedException;

/**
 * Interface for valuable object 
 * @author ceichler
 *
 */
public interface Valuable {

	/**
	 * 
	 * @return the value of the object
	 * @throws NotExpertisedException 
	 */
	public abstract double getValue() throws NotExpertisedException;

	public default void expertise(){
		
	}
}
