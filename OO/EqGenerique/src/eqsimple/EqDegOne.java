package eqsimple;

/**
 * Simple equation solver. Represents an equation of the type AX + B = 0 with A and B floats
 * @author ceichler
 *
 */
public class EqDegOne {
	
	/**
	 * Coefficient a
	 */
	private float coeffA;
	/**
	 * Coefficient b
	 */
	private float coeffB;
	
	/**
	 * Solution of the equation
	 */
	private float solution;
	
	/**
	 * Boolean tracking whether the current solution is correct
	 */
	private boolean solved;
	
	

	/**
	 * Getter of coeffA
	 * @return the coeffA
	 */
	public float getCoeffA() {
		return coeffA;
	}

	/**
	 * Setter of coeffA, whose modification may lead the equation to be unsolved
	 * @param coeffA the coeffA to set
	 */
	public void setCoeffA(float coeffA) {
		if(this.coeffA!=coeffA){
			this.coeffA = coeffA;
			solved = false;
		}
		
	}

	/**
	 *  Getter of coeffB
	 * @return the coeffB
	 */
	public float getCoeffB() {
		return coeffB;
	}

	/**
	 * Setter of coeffB, whose modification may lead the equation to be unsolved
	 * @param coeffB the coeffB to set
	 */
	public void setCoeffB(float coeffB) {
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
	public EqDegOne(float coeffA, float coeffB) {
		this.coeffA = coeffA;
		this.coeffB = coeffB;
		solution = 0;
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
	public Float solve(){
		if(!solved){
			if(coeffA == 0) {
				System.err.println("A, " + coeffA + ", is not invertible. Impossible to solve" );
				return null;
			}
			else {
				solved  = true;
				solution = -coeffB / coeffA;
			}
		}
		return solution;
	}
	
	
	
	
}
