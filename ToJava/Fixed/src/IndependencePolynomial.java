public class IndependencePolynomial {

    private Polynomial PolyHolder;

    public IndependencePolynomial(TreeGraphs T) {  this.PolyHolder = this.ComputePoly(T); }

    public Polynomial ComputePoly(TreeGraphs T)
    {
        Polynomial tmp = new Polynomial();

        if(T.Get_size_V() == 0)
        {
            tmp.addMono(new Monomial(1,0));
            return tmp;
        }

        if(T.isKn())
        {
            tmp.addMono(new Monomial(1,0));
            tmp.addMono(new Monomial(T.Get_size_V(),1));

            return tmp;
        }


        tmp = ComputePoly(T.SubGraph(T.Get_Max_Deg_ver(),true));

        tmp.addPoly(ComputePoly(T.SubGraph(T.Get_Max_Deg_ver(),false)).mulMono_to_ret(new Monomial(1,1)));

        return tmp;
    }


}
