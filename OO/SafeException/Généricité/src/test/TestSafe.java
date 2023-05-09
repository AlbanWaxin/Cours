/**
 * 
 */
package test;

import java.util.Collections;

import Exceptions.NotExpertisedException;
import safes.*;
import valuables.*;

/**
 * @author ceichler
 *
 */
public class TestSafe {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		// Uncomment to synchronyze system out and err
		// System.setErr(System.out);

		// Let's create a safe with a capacity of 2 gems
		GenericSafe<Gemstone> mySafe;
		mySafe = new GenericSafeWithCode<>(2, 2345);
		mySafe.close();
		((GenericSafeWithCode<Gemstone>) mySafe).open(2345);
		System.out.println(mySafe.isOpened());

		Gemstone g = new Emerald(6);
		g.expertize();

		Gemstone g2 = new Diamond(2);
		g2.expertize();
		try {
			System.out.println(g2.getValue());
		} catch (NotExpertisedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		mySafe.addObject(g);

		System.out.println(g2);
		GenericSafe<GenericSafe<Gemstone>> gsg = new GenericSafe<GenericSafe<Gemstone>>(5,1);
		GenericSafe<GenericSafe<Gemstone>> ggg = new GenericSafe<GenericSafe<Gemstone>>(2,2);
		//Collections.sort(gsg.getMyContent());  était valable avant changement TreeSet
		System.out.println(gsg.getMyContent());
	}

}