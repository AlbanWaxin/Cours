package boiteobj;

import java.util.ArrayList;

import valuables.Gemstone;

public class Boite {

	private boolean opened;
	private ArrayList<Object> myContent;
	private int currentGemsNb;
	private int capacity;
	
	public Boite(int capacity) {
		this.capacity = capacity;
		this.currentGemsNb = 0;
		this.opened = false;
		this.myContent = new ArrayList<Object>();
	}
	public void open() {
		this.opened = true;
	}
	
	public void close() {
		this.opened = false;
	}
	
	public void addGem(Object object) {
		
		if (((Gemstone) object).getMySafe() != null) {
			System.err.println("Object already stored");
			return;
		}
		if (!this.opened) {
			System.err.println("Volt Closed");
			return;
		}
		if (this.isFull()) {
			System.err.println("Je suis plein");
		}
		this.myContent.add(object);
		this.currentGemsNb += 1;
		((Gemstone) object).setMySafe(this);
	}
	
	public boolean isFull() {
		return (this.currentGemsNb == this.capacity);
	}
	
	public void removeGem(Object object) {
		if (!this.opened) {
			System.err.println("Volt Closed");
			return;
		}
		if (!this.myContent.contains(object)){
			System.err.println("This Object is not here");
			return;
		}
		this.myContent.remove(object);
		this.currentGemsNb--;
		
		((Gemstone) object).setMySafe(null);
		
	}

	}
