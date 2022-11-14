package geometrie;

/**
 *  This class possesses two fields y de type double representing the coordinate of the Point and a String label. 
 *  It has 3 constructors; interestingly and to re-use code and avoid code duplication, constructors invok each other.
 * @author ceichler
 *
 */

public class Point {

	/** 
	 * Property x, absciss of the point
	 */
	private double x;

	/** 
	 * Getter of the property x
	 * @return  Returns the point's absciss.
	 */
	public double getX() {
		return x;
	}

	/** 
	 * Property y, ordinate of the point
	 */
	private double y;

	/** 
	 * Getter of the property y
	 * @return  Returns the point's ordinate.
	 */
	public double getY() {
		return y;
	}

	/**
	 * Computes the distance between this point and another
	 * @param aPoint the other point
	 * @return Distance between this and aPoint
	 */
	public double distance(Point aPoint){
		return Math.sqrt((x-aPoint.x)*(x-aPoint.x) + (y-aPoint.y)*(y-aPoint.y)); }

	/** 
	 * Setter of the property x
	 * @param x  The x to set.
	 */
	public void setX(double x) {
		this.x = x;
	}

	/** 
	 * Setter of the property y
	 * @param y  The y to set.
	 */
	public void setY(double y) {
		this.y = y;
	}

	@Override
	/**
	 * Redefine toString; affect the way points are printed
     * Cf next chapter on heritance
	 */
	public String toString(){


		return label + "(" + x +", " + y +  ")";

	}

	/**
	 * Label of the point
	 */
	private String label;

	/**
	 * Getter of the property abel
	 * @return  Returns the label.
	 */
	public String getLabel() {
		return label;
	}

	/**
	 * Setter of the property label
	 * @param label  The label to set.
	 */
	public void setLabel(String label) {
		this.label = label;
	}


	/**
	 * Default point constructor (gives origin). Relies on the constructor with 3 arguments
	 */
	public Point(){
		this(0.0,0.0,"O");
		System.out.println("using default constructor for Point");

	}


	/**
	 * Constructor with some coordinates. Relies on constructor with 3 arguments
	 * @param aX the absciss
	 * @param aY the ordinate
	 */
	public Point(double aX, double aY){
		this(aX, aY, null);
		System.out.println("using the point constructor with 2 arguments");
	}


	/**
	 * Constructor with coordinate and label
	 * @param aX the absciss
	 * @param aY the ordinate
	 * @param aLabel the label
	 */
	public Point(double aX, double aY, String aLabel){
		System.out.println("using the point constructor with 3 arguments");
		x = aX;
		y = aY;
		label = aLabel; }

}
