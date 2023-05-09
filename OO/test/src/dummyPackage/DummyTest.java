package dummyPackage;

/**
 * Une classe de test triviale
 * @author student
 *
 */
public class DummyTest {

	public static void main(String[] args) {
		// Instanciation et manipulation classe dummy class
		System.out.println("TEST MANIPULAT DUMMYCLASS");
		DummyClass dm = new DummyClass();
		System.out.println(dm.getDummyAtt());
		dm.setDummyAtt(2);
		System.out.println(dm.getDummyAtt());
		
		// Petit test sur les références et l'égalité
		System.out.println("\n TEST EGALITE ET REF");
		String s1, s2, s3, s4;
		s1 = new String("string");
		s2 = s1;
		s3 = new String(s1);
		s4 = "string";
		System.out.println("s1 = " + s1 + "\n" + "s2 = " + s2 + "\n" + "s3 = " + s3+ "\n" + "s4 = " + s4);
		
		System.out.println("s1 equals s4  : " + s1.equals(s4));
		System.out.print("s1 == s4  : ");
		System.out.println(s1 == s4);
		//Comment expliquer ce résultat?
	}

}
