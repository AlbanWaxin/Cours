package executable;

import geometrie.*;


public class TestTP {

	
	public static void main(String[] args) {
		
		//Using some point constructors 
		Point p1 = new Point(5.1, 2.0, "A");
		Point p2 = new Point();
		Point p3 = new Point(1.1,6.0);
		Segment s = new Segment(p1,p3);
		
		System.out.println("AFFICHAGE");
		//Printing for fun
		System.out.println(p1.toString() );
		System.out.println(p1);
		System.out.println(s.length());
		Integer i;
		

	}

}
