package Exceptions;

import valuables.Gemstone;

public class NotExpertisedException extends Exception {
	Gemstone errorGemstone = null;
	public NotExpertisedException() {
		super("Une gemme non évaluée n'a pas de valeur");
	}
	public NotExpertisedException(Gemstone object) {
		super("la gemme "+ object + "n'a pas de valeur");
		errorGemstone =  object;
	}
	
}
