package MainPack;

import java.util.ArrayList;

class RandomInt // Generating random integer out of specific range:
{
	RandomInt(){};
	public int GetRand(int min, int max) { 
		int x =  max-((int)(Math.random()*(max-min +1)));
		return x; 
		
	}
	
}

public class Vertex {

	private int index;
	private int degree;
	private ArrayList<Integer> nei_index;
	
	public Vertex(int ind, int deg) { this.index = ind; this.degree=deg;  nei_index = new ArrayList<Integer>(); }
	
	public void AddNeigh(int ind) { this.nei_index.add(ind); this.degree++; }
	public void RemoveNeigh(int which_one) { this.nei_index.remove(which_one); this.degree--; }
	
	public final int GetDeg() { return this.degree; } 
	public final int GetInd() { return this.index; }
	
	public boolean isNeig(final int ind) 
	{ 
		for (int i = 0; i < this.nei_index.size(); i++)  { 	if(this.nei_index.get(i) == ind) { return true; } }
		
		return false;
	}
	
}



