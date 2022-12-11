package test;

import safes.*;
import valuables.*;

public class Client {
	
	private int budget = 1000;

	public Client() {
	}

	public Client(int bud) {
		this.budget=bud;
	}
	
	public void acheter(Valuable v) {
		if(this.budget>= v.getValue()) {
			budget-=v.getValue();
		}
	}


}
