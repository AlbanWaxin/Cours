package App;
import Browser.Browser;

public class App{
	
	public static void main(String[] args) {
		Browser browser = new Browser(10);
		browser.newAdress("google.fr");
		System.out.println(browser.getCurrentAdress());		
	}
}
