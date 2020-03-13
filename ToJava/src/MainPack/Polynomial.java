package MainPack;

import java.util.ArrayList;
import java.lang.reflect.Array;
import java.util.Arrays;


class Monomial
{
	private long coeff;
	private int power;
	
	Monomial(long co, int pow){ this.coeff = co; this.power = pow; }
	
	public final int GetPow() { return this.power; }
	public final long GetCo() { return this.coeff; }
	
	public void add(Monomial x) { if(this.power == x.power) { this.coeff+=x.coeff; } }
	public void multi(Monomial x) { this.coeff*=x.coeff; this.power+=x.power; } 	
	
}


public class Polynomial
{
	Polynomial() { this.Poly = new ArrayList<Monomial>(); }
	
	
	
	private ArrayList<Monomial> Poly;
}




