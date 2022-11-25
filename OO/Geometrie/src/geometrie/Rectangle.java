package geometrie;

public class Rectangle extends Quadrilateral {

	public Rectangle(Point p1, Point p2, Point p3, Point p4,String couleur,String texture) {
		super(p1, p2, p3, p4,couleur,texture);
		// TODO Auto-generated constructor stub
	}

	public Rectangle(Point p1, Point p2,String couleur,String texture) {
		super(p1,new Point(p2.getX(),p1.getY()),p2,new Point(p1.getX(),p2.getY()),couleur,texture);
	}
	
	public Rectangle() {
		System.out.println("Rectangle constructor");
	}
	
	public void draw(Point p) {
		System.out.println("Drawing a rectangle");	
	}
	
	public double getPerimeter() {
		System.out.println("Computing the perimeter of a rectangle");
		return ((super.getTheSegments())[0].length() * 2) + ((super.getTheSegments())[2].length()*2) ;
	}
	
	
	

}
