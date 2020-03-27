import org.jetbrains.annotations.NotNull;

import java.lang.reflect.Array;
import java.util.*;
import java.lang.*;
import java.io.*;

@SuppressWarnings("unused")




public class Polynomial
{
    private ArrayList<Double> Coef;

    public Polynomial(ArrayList<Double> coef) {  this.Coef = coef; }

    public int Getlength() { return this.Coef.size(); }

    public void Add(ArrayList<Double> other){

        int min = other.size(), i;

        if (min > this.Coef.size()){
            min = this.Coef.size();
        }

        for (i=0; i<min; i++) Array.set(this.Coef, i, this.Coef.get(i) + other.get(i));

        for (i=i; i<other.size();i++) this.Coef.add(i, other.get(i));

    }

    //----------------------------------------------------------------------------------



    //------------------------------------------------------------------------------



    //-----------------------------------------------------------------



    //-------------------------------------------------------
    // ----------------------------------------





}




