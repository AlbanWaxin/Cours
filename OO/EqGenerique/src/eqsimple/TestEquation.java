package eqsimple;

import algebras.*;

public class TestEquation {

	public static void main(String[] args) {
		
		
		EgDegOneGenSimple eq = new EgDegOneGenSimple(new FloatCoeff(12),new FloatCoeff(-5));
		
		System.out.println("Basic tests");
		System.out.println(eq);
		System.out.println("Is the eq solved? " + eq.isSolved());
		System.out.println("Solving equation, X= " +eq.solve());
		System.out.println("Is the eq solved? " + eq.isSolved());
		
		System.out.println("Changing the coefficient A");
		eq.setCoeffA(new FloatCoeff(4));
		
		System.out.println("Is the eq solved? " + eq.isSolved());
		System.out.println("Solving equation, X= " +eq.solve());
		System.out.println("Is the eq solved? " + eq.isSolved());
				
		System.out.println("Testing with a non-invertible A");
		System.out.println("Changing the coefficient A");
		eq.setCoeffA(new FloatCoeff(0));
		
		FloatCoeff sol = eq.solve();
		if(sol != null)	System.out.println(eq.solve());
		System.out.println("Is the eq solved? " + eq.isSolved());
				

	}

}
