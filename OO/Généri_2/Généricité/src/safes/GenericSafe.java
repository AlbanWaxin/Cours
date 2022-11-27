/**
 * Free to reuse
 */
package safes;

import valuables.Gemstone;
import valuables.Valuable;

import java.util.ArrayList;
import java.util.Iterator;

import javax.print.PrintException;

/**
 * A simple safe
 * 
 * @author ceichler
 */
public class GenericSafe<T1> implements Valuable {

	/**
	 * Capacity of the safe (in gemstones)
	 */
	private final int capacity;

	/**
	 * Current number of gems stored in the safe
	 */
	private int currGemNb = 0;

	/**
	 * Boolean tracking the opened/closed state of the safe
	 */
	protected boolean opened = true;

	/**
	 * int which represent the current value of the valuables in the safe
	 */
	protected int value = 0;

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
	public GenericSafe(int capac) {
		capacity = capac;
		System.out.println("Safe constructor with capacity");
	}

	protected double sum() {
		double sum = 0;
		for (T1 d : this.myContent)
			if (d.getValue() == -1) {
				System.err.println("erreur expertize");
			} else {
				sum += d.getValue();
			}
		return sum;
	}

	/**
	 * Getter of the property <tt>value</tt>
	 * 
	 * @return value the safe's value
	 */
	public double getValue() {

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
	private ArrayList<T1> myContent = new ArrayList<T1>();

	/**
	 * Getter of the property <tt>myContent</tt>
	 * 
	 * @return Returns myContent.
	 */
	public ArrayList<T1> getMyContent() {
		return myContent;
	}

	/**
	 * Test wether the safe is full (if it contains a number of stones equal to its
	 * capacity)
	 * 
	 * @return boolean, whether safe is full
	 */

	public boolean isFull() {
		return this.currGemNb == this.capacity;
	}

	/**
	 * Add a gemstone in the safe
	 * 
	 * @param gem the gemstone to add
	 */

	public void addGem(T1 gem) {
		// Testing whether we can add a gem
		// Is the safe opened?
		if (!opened)
			System.err.println("Impossible to add a gem; the safe is closed!");
		// Is it full?
		else if (isFull())
			System.err.println("Impossible to add a gem; the safe is full!");
		// Is the Gem already in another Safe?
		else if (gem.getMySafe() != null)
			System.err.println("Impossible to add a gem; it's already in another safe!");
		// Good to go!
		else {
			myContent.add(gem);
			gem.setMySafe(this);
			this.currGemNb++;
		}
	}

	/**
	 * Removes a gemstone from the safe
	 * 
	 * @param gem the gemstone to remove
	 */

	public void removeGem(T1 gem) {
		// Testing whether we can remove the gem
		// Is the safe opened?
		if (!opened)
			System.err.println("Impossible to remove gem; the safe is closed!");
		// Good to go!
		else {
			if (myContent.remove(gem)) {
				gem.setMySafe(null);
				this.currGemNb--;
			} else
				System.err.println("Impossible to remove the specified gem; it is not in the safe!");
		}
	}

	public T1 findGemstone(int min_value) {
		T1 d;
		Iterator<T1> iterator = this.myContent.iterator();
		do {
			d = iterator.next();
			if (d.getValue() == -1) {
				System.err.println("erreur expertize");
			}
		} while (iterator.hasNext() && !(d.getValue() > min_value));
		if (d.getValue() > min_value) {
			return d;
		} else {
			d = new T1(-1);
			return d;
		}
	}
}