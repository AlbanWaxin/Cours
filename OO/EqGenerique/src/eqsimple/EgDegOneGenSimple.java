package eqsimple;

import algebras.FloatCoeff;

public class EgDegOneGenSimple {

	/**
	 * Coefficient a
	 */
	private FloatCoeff coeffA;
	/**
	 * Coefficient b
	 */
	private FloatCoeff coeffB;
	
	/**
	 * Solution of the equation
	 */
	private FloatCoeff solution;
	
	/**
	 * Boolean tracking whether the current solution is correct
	 */
	private boolean solved;
	
	

	/**
	 * Getter of coeffA
	 * @return the coeffA
	 */
	public FloatCoeff getCoeffA() {
		return coeffA;
	}

	/**
	 * Setter of coeffA, whose modification may lead the equation to be unsolved
	 * @param coeffA the coeffA to set
	 */
	public void setCoeffA(FloatCoeff coeffA) {
		if(this.coeffA!=coeffA){
			this.coeffA = coeffA;
			solved = false;
		}
		
	}

	/**
	 *  Getter of coeffB
	 * @return the coeffB
	 */
	public FloatCoeff getCoeffB() {
		return coeffB;
	}

	/**
	 * Setter of coeffB, whose modification may lead the equation to be unsolved
	 * @param coeffB the coeffB to set
	 */
	public void setCoeffB(FloatCoeff coeffB) {
		if(this.coeffB!=coeffB){
			this.coeffB = coeffB;
			solved = false;
		}
	}

	/**
	 * Checker for solved
	 * @return whether the current solution is correct
	 */
	public boolean isSolved() {
		return solved;
	}



	/**
	 * Construction d'une équation nécessitant des valeurs pour a et b
	 * @param coeffA
	 * @param coeffB
	 */
	public EgDegOneGenSimple(FloatCoeff coeffA, FloatCoeff coeffB) {
		this.coeffA = coeffA;
		this.coeffB = coeffB;
		solution = null;
		solved = false;
	}

	/**
	 * Improved equation display
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "Equation : " + coeffA + " X + " + coeffB + " = 0";
	}
	
	/**
	 * Getter of solution, may imply solving the equation to get a correct solution
	 * @return the solution, or null if there is none
	 */
	public FloatCoeff solve(){
		if(!solved){
			if(coeffA.compareCoeff(new FloatCoeff(0))) {
				System.err.println("A, " + coeffA + ", is not invertible. Impossible to solve" );
				return null;
			}
			else {
				solved  = true;
				solution = (coeffB.negateCoeff()).divideCoeff(coeffA);
			}
		}
		return solution;
	}

	

}
