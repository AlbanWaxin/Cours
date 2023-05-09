/**
 * Free to reuse
 */
package safes;

import valuables.Gemstone;
import valuables.Storable;
import valuables.Valuable;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.TreeSet;

import Exceptions.NotExpertisedException;


/**
 * A simple safe
 * 
 * @author ceichler
 */
public class GenericSafe<T1 extends Valuable & Storable<GenericSafe<T1>>> implements Valuable,Storable<GenericSafe<GenericSafe<T1>>>{

	/**
	 * Capacity of the safe (in gemstones)
	 */
	private final int capacity;

	/**
	 * Current number of gems stored in the safe
	 */
	private int currObjNb = 0;

	/**
	 * Boolean tracking the opened/closed state of the safe
	 */
	protected boolean opened = true;

	/**
	 * int which represent the current value of the valuables in the safe
	 */
	protected int value = 0;
	private int instanciate_count = 0;
	/**
	 * Instantiate a default safe; capacity=1
	 * The safe is built opened and empty
	 */
	public GenericSafe() {
		capacity = 1;
		System.out.println("Default safe constructor");
	}

	/**
	 * Instantiate a safe with a specified capacity
	 * The safe is built opened and empty
	 * 
	 * @param capac capacity of the created safe
	 */
	public GenericSafe(int capac,int count) {
		capacity = capac;
		instanciate_count = count;
		System.out.println("Safe constructor with capacity");
	}


	protected double sum(){
		T1 d = null;
		double sum = 0;
		Iterator<T1> iterator = this.myContent.iterator();
		if (iterator.hasNext()) {
			d = iterator.next();
		}		
		while (iterator.hasNext()){
			try {
				sum += d.getValue();
				d = iterator.next();
			}
			catch (NotExpertisedException e) {
				e.printStackTrace();
				d.expertise();
			}
		}
		return sum;
	}

	/**
	 * Getter of the property <tt>value</tt>
	 * 
	 * @return value the safe's value
	 */
	public double getValue(){

		double value = 0;
		value = sum();
		return value;
	}

	/**
	 * Getter of the property <tt>capacity</tt>
	 * 
	 * @return capacity the max capacity
	 */
	public int getCapacity() {
		return capacity;
	}

	/**
	 * Getter of the property <tt>opened</tt>
	 * 
	 * @return opened
	 */
	public boolean isOpened() {
		return opened;
	}
	
	public int getInstanciatecount() {
		return instanciate_count;
	}

	/**
	 * Opening the safe
	 */
	public void open() {
		if (opened)
			System.err.println("Trying to open an opened safe...");
		this.opened = true;
	}

	/**
	 * Closing the safe
	 */
	public void close() {
		if (!isOpened())
			System.err.println("Trying to close a closed safe...");
		this.opened = false;
	}

	/**
	 * Content of the safe
	 */
	private TreeSet<T1> myContent = new TreeSet<T1>();

	/**
	 * Getter of the property <tt>myContent</tt>
	 * 
	 * @return Returns myContent.
	 */
	public TreeSet<T1> getMyContent() {
		return myContent;
	}

	/**
	 * Test wether the safe is full (if it contains a number of stones equal to its
	 * capacity)
	 * 
	 * @return boolean, whether safe is full
	 */

	public boolean isFull() {
		return this.currObjNb == this.capacity;
	}

	/**
	 * Add a object in the safe
	 * 
	 * @param object the object to add
	 */

	public void addObject(T1 object) {
		// Testing whether we can add a object
		// Is the safe opened?
		if (!opened)
			System.err.println("Impossible to add a object; the safe is closed!");
		// Is it full?
		else if (isFull())
			System.err.println("Impossible to add a object; the safe is full!");
		// Is the object already in another Safe?
		else if (object.getMyContainer() != null)
		System.err.println("Impossible to add a object; it's already in another safe!");
		// Good to go!
		else {
			myContent.add(object);
			object.setMyContainer(this);
			this.currObjNb++;
		}
	}

	/**
	 * Removes a object from the safe
	 * 
	 * @param object the object to remove
	 */
	
	public void removeObject(T1 object) {
		// Testing whether we can remove the object
		// Is the safe opened?
		if (!opened)
			System.err.println("Impossible to remove object; the safe is closed!");
		// Good to go!
		else {
			if (myContent.remove(object)) {
				object.setMyContainer(null);
				this.currObjNb--;
			} else {
				System.err.println("Impossible to remove the specified object; it is not in the safe!");
		}
		}
	}

	public T1 findGemstone(int min_value) throws NotExpertisedException {
		T1 d;
		Iterator<T1> iterator = this.myContent.iterator();
		do {
			d = iterator.next();
			try {
				if (d.getValue() == -1) {
					System.err.println("erreur expertize");
				}
			}
			catch(NotExpertisedException e)
			{
				e.printStackTrace();
			}
		} while (iterator.hasNext() && !(d.getValue() > min_value));
		try {
			if (d.getValue() > min_value) {
				return d;
			} else {
				//d = new T1(-1);
				return d;
			}
		}
		catch(NotExpertisedException e)
		{
			e.printStackTrace();
		}
		finally {
			return d;
		}
	}
	private GenericSafe<GenericSafe<T1>> myContainer = null;
	
	public void setMyContainer(GenericSafe<GenericSafe<T1>> container) {
		this.myContainer = container;
	}
	
	public GenericSafe<GenericSafe<T1>> getMyContainer(){
		return this.myContainer;
	}
	
	public int compareTo(GenericSafe<T1> safe) {
		if (getClass() != safe.getClass())
			return this.getInstanciatecount() - safe.getInstanciatecount();
		else
			return 0;
	}
}
		