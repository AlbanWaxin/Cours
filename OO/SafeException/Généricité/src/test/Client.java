package test;

import Exceptions.NotExpertisedException;
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
		try {
			if(this.budget>= v.getValue()) {
				budget-=v.getValue();
			}
		} catch (NotExpertisedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


}
