package algebras;

/**
 * Represent complex numbers using the exponential form r*e^{i theta}
 * @author ceichler
 *
 */
public class Complex {
	
	/**
	 * Modulus of the number
	 */
	private double r;
	
	/**
	 * Getter of r, the modulus
	 * @return r the modulus
	 */
	public double getR() {
		return r;
	}

	/**
	 * Setter of r, the modulus
	 * @param r the r to set
	 */
	public void setR(double r) {
		this.r = r;
	}

	/**
	 * Getter of theta, the argument divided by PI
	 * @return the theta
	 */
	public double getTheta() {
		return theta;
	}

	/**
	 * Setter of theta, the argument divided by PI
	 * @param the theta to set
	 */
	public void setTheta(double theta) {
		this.theta = theta%2;
	}

	/**
	 * Argument of the number divided by Pi
	 * Takes value in [|O,2|]
	 */
	private double theta;

	/**
	 * Builds a complex equals to 1
	 */
	public Complex() {
		r=1;
		theta = 0;
	}
	
	/**
	 * Builds a complex modulus * e^{i argument PI} with the provided arguments
	 * @param modulus the modulus of the complexe
	 * @param argument the argument divided by Pi
	 */
	public Complex(double modulus, double argument) {
		r=modulus;
		theta = argument%2;
	}
	
	/**
	 * Overriding to string for enhance printing
	 * @return a string representing the complex
	 */
	@Override
	public String toString() {
		return "" + r + " * exp(i * " +theta + "PI)";
		
	}
	/**
	 * Compute the conjugate of the current object
	 * @return the current object's conjugate
	 */
	public Complex conjugate() {
		return new Complex(this.r, -this.theta);
	}
	
	/**
	 * Compute the opposite of the current object
	 * @return the current object's conjugate
	 */
	public Complex opposite() {
		return new Complex(this.r, this.theta+1);
	}
	
	/**
	 * Compute the opposite of the current object
	 * @return the current object's conjugate
	 */
	public Complex inverse() {
		if(this.isInvertible())	return new Complex(((double)1)/this.r, -this.theta);
		else return null;
	}
	
	/**
	 * COmpute the addition of two complexs
	 * @param b the complex to sum
	 * @return this + b
	 */
	public Complex addition(Complex b) {
		//This seems very wrong
		// might have to do further tests and change implementation if the method is needed
		return new Complex(this.r + b.r, this.theta + b.theta);
	}
	
	/**
	 * Mutliplies with a complex given in argument
	 * assumes commutativity
	 * @param b the complex to multiply with
	 * @return result of the multiplication of the current object and b
	 */
	public Complex multiply(Complex b) {
		return new Complex(this.r * b.r, this.theta + b.theta );
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		long temp;
		temp = Double.doubleToLongBits(r);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(theta);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Complex other = (Complex) obj;
		if (Double.doubleToLongBits(r) != Double.doubleToLongBits(other.r))
			return false;
		if (Double.doubleToLongBits(theta) != Double.doubleToLongBits(other.theta))
			return false;
		return true;
	}
	
	/**
	 * Test whether the current complex is invertible (i.e. its module is not 0)
	 * @return whether the current complex is invertible
	 */
	public boolean isInvertible() {
		return !(this.r==0);
	}
	
	
	

}
