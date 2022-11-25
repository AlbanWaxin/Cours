package executable;

import geometrie.*;


public class TestTP {

	
	public static void main(String[] args) {
		
		//Using some point constructors 
		//Point p1 = new Point(5.1, 2.0, "A");
		//Point p2 = new Point();
		//Point p3 = new Point(1.1,6.0);
		//Segment s = new Segment(p1,p3);
		
		//System.out.println("AFFICHAGE");
		//Printing for fun
		//System.out.println(p1.toString() );
		//System.out.println(p1);
		//System.out.println(s.length());
		Rectangle r = new Rectangle();
		r.draw(4);
		r.draw();
		r.draw(new Point());
		Quadrilateral quad = new Quadrilateral();
		double perquad = quad.getPerimeter();
		quad = new Rectangle();
		double perrect = quad.getPerimeter();
		GeometricalShape [] listFig = new GeometricalShape[3];
		listFig[0] = new Rectangle();
		listFig[1] = new Quadrilateral();
		listFig[2] = new Ellipse();
		//Rectangle rec = new Quadrilateral();
		GeometricalShape [] listFig = new GeometricalShape[3];
		listFig[0] = new Rectangle();
		listFig[1] = new Quadrilateral();
		listFig[2] = new Ellipse();
		for (int i=0;i<=2;i++) {
			listFig[i].draw(); 
		}
		listFig[0].getPerimeter();
	
	}

}
