package EqDegOne;

class Equation
{
	private float a,b,solution;
	private boolean solved;
    
	Equation(int initA,int initB)
    {
	  this.a =  initA;
	  this.b = initB;
    }
    
	public void setA(int newA)
	{
		this.a = newA;
	}
	public void setB(int newB)
	{
		this.b = newB; 
	}
	public boolean isSolved()
	{
		return this.solved;
	}
	public float solve()
	{
		if (!this.solved)
		{
			this.solution = - this.a/this.b;
			this.solved = true;
		}
		return solution;
	}
	
}