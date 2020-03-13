import org.jetbrains.annotations.NotNull;

import java.util.*;
import java.lang.*;
import java.io.*;

@SuppressWarnings("unused")

class Monomial
{
    private long coeff;
    private int power;

    public Monomial(long co, int pow){ this.coeff = co; this.power = pow; }

    public final int GetPow() { return this.power; }
    public final long GetCo() { return this.coeff; }

    public void add(final Monomial x) { if(this.power == x.power) { this.coeff+=x.coeff; } }
    public void multi(final Monomial x) { this.coeff*=x.coeff; this.power+=x.power; }

}

class CompMono implements Comparator<Monomial>
{
    public int compare(Monomial first, Monomial sec) {

        if(first.GetPow() == sec.GetPow())
        {

            if(first.GetCo() > sec.GetCo()) { return 1; }

            if(first.GetCo() == sec.GetCo()) { return 0; }

            else { return -1; }
        }

        if(first.GetPow() > sec.GetPow()) { return 1; }

        return -1;
    }

}


public class Polynomial
{
    private ArrayList<Monomial> Poly;

    public Polynomial() { this.Poly = new ArrayList<Monomial>(); }

    public int Getlength() { return this.Poly.size(); }

    //----------------------------------------------------------------------------------

    public void addMono(Monomial x)
    {
        if(this.Poly.size()==0) { this.Poly.add(x); }

        for(int i=0; i< this.Poly.size(); i++)
        {
            if(x.GetPow() == this.Poly.get(i).GetPow()) {
                this.Poly.get(i).add(x);
                return;
            }
        }

        this.Poly.add(x);
        this.Poly.sort(new CompMono());

    }

    //------------------------------------------------------------------------------

    public void addPoly(Polynomial P)
    {
        for(int i=0; i<P.Getlength(); i++) { this.addMono(P.Poly.get(i)); }

    }

    //-----------------------------------------------------------------

    public void mulMono(Monomial x)
    {
        for(int i=0; i<this.Poly.size(); i++)
        {
            this.Poly.get(i).multi(x);
        }
    }

    //-------------------------------------------------------

    public Polynomial mulMono_to_ret(Monomial x)
    {
        Polynomial tmp = new Polynomial();

        tmp.Poly = this.Poly;

        for(int i=0; i<tmp.Getlength(); i++)
        {
            tmp.Poly.get(i).multi(x);
        }

        return tmp;
    }

    // ----------------------------------------

    public void mulPoly(Polynomial P)
    {
        Polynomial tmp = new Polynomial();

        for(int i=0; i<P.Getlength(); i++)
        {
            tmp.addPoly(this.mulMono_to_ret(P.Poly.get(i)));
        }

        this.Poly = tmp.Poly;

    }







}




