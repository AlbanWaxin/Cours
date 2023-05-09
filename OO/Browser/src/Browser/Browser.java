package Browser;
import stacks.Stack;

public class Browser{
	
	private Stack prev,next;
	private String current;
	/**
	 * Ceci est le constructeur de la classe Browser
	 * @param size donne la taille des piles prev et next
	 */
	public Browser(int size){
		this.prev = new Stack(size);
		this.current = "";
		this.next = new Stack(size);
	}
	
	/**
	 * Methode getter de l'adresse actuelle
	 * @return un string qui contient l adresse actuelle
	 */
	public String getCurrentAdress() {
		return this.current;
	}
	/**
	 * Methode qui change de site
	 * @param newsite string qui contient la nouvelle adresse
	 */
	public void newAdress(String newsite) {
		if (!this.prev.isFull()) {
			this.prev.push(this.current);
			this.current = newsite;
			this.next.flush();
		}
	}
	
	/**
	 * Methode qui change l'adresse pour la precedente
	 */
	public void previousAdress() {
		if (!this.prev.isEmpty() && !this.next.isFull()) {
			this.next.push(this.current);
			this.current = this.prev.pop();
		}
	}
	
	/**
	 * Methode qui change l'adresse pour la precedente 
	 */
	public void nextAdress() {
		if (!this.next.isEmpty() && !this.prev.isFull()) {
			this.prev.push(this.current);
			this.current = this.next.pop();
		}
	}
}