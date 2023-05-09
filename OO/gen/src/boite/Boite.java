package boite;

import java.util.ArrayList;

import valuables.Gemstone;

public class Boite {

	private boolean opened;
	private ArrayList<Gemstone> myContent;
	private int currentGemsNb;
	private int capacity;
	
	public Boite(int capacity) {
		this.capacity = capacity;
		this.currentGemsNb = 0;
		this.opened = false;
		this.myContent = new ArrayList<Gemstone>();
	}
	public void open() {
		this.opened = true;
	}
	
	public void close() {
		this.opened = false;
	}
	
	public void addGem(Gemstone gemstone) {
		if (gemstone.getMySafe() != null) {
			System.err.println("Gemstone already stored");
			return;
		}
		if (!this.opened) {
			System.err.println("Volt Closed");
			return;
		}
		if (this.isFull()) {
			System.err.println("Je suis plein");
		}
		this.myContent.add(gemstone);
		this.currentGemsNb += 1;
		gemstone.setMySafe(this);
	}
	
	public boolean isFull() {
		return (this.currentGemsNb == this.capacity);
	}
	
	public void removeGem(Gemstone gemstone) {
		if (!this.opened) {
			System.err.println("Volt Closed");
			return;
		}
		if (!this.myContent.contains(gemstone)){
			System.err.println("This Gemstone is not here");
			return;
		}
		this.myContent.remove(gemstone);
		this.currentGemsNb--;
		gemstone.setMySafe(null);
		
	}

	}
