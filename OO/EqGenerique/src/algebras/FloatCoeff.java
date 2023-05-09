package algebras;

/**
 * Classe d'encapsulation de floattant sans grand intérêt en dehors de la manipulation avec équation
 * @author ceichler
 *
 */
public class FloatCoeff {
	
	
	private float myF;

	/**
	 * Default constructor, initializes the wrapped float to 0
	 */
	public FloatCoeff() {
		myF = 0;
	}
	
	/**
	 * Constructor initializing the wrapped float
	 * @param f value to initialize the wrapped float with
	 */
	public FloatCoeff(float f) {
		myF = f;
	}
	
	public float getmyF() {
		return this.myF;
	}
	
	@Override
	public String toString() {
		return ""+ myF;
	}
	
	public FloatCoeff negateCoeff() {
		FloatCoeff coeffReturn = new FloatCoeff(-1*this.myF);
		return coeffReturn;
	}
	
	public FloatCoeff addTwoCoeff(FloatCoeff Coeff1, FloatCoeff Coeff2) {
		FloatCoeff coeffReturn = new FloatCoeff(Coeff1.myF + Coeff2.myF);
		return coeffReturn;
	}
	
	public FloatCoeff divideCoeff(FloatCoeff Coeff2) {
		FloatCoeff coeffReturn = new FloatCoeff(this.myF/Coeff2.myF);
		return coeffReturn;
	}
	
	public boolean compareCoeff(FloatCoeff Coeff2) {
		return (this.myF == Coeff2.myF);
	}
	
	

}
