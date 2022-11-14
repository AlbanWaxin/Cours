package App;
import Safe.Safe;
import valuables.Gemstone;

public class App{
	
	public static void main(String[] args) {
		Safe safe = new Safe(10);
		Gemstone gemstone1 = new Gemstone(10);
		Gemstone gemstone2 = new Gemstone(9);
		Gemstone gemstone3 = new Gemstone(8);
		Gemstone gemstone4 = new Gemstone(7);
		gemstone1.expertize();
		gemstone2.expertize();
		gemstone3.expertize();
		gemstone4.expertize();
		safe.open();
		safe.addGem(gemstone1);
		safe.addGem(gemstone2);
		safe.addGem(gemstone3);
		safe.addGem(gemstone4);
		System.out.println(safe.getValue());
		safe.removeGem(gemstone3);
		safe.close();
		System.out.println(safe.getValue());
		safe.addGem(gemstone3);
		safe.addGem(gemstone4);
	}
}
