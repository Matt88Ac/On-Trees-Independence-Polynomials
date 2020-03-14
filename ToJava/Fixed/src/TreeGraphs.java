import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class TreeGraphs {
    private ArrayList<Vertex> V; // Graph's vertexes.
    private int size_v; // Number of vertexes.
    private int size_e; // Number of edges.
    private boolean[][] E; // The edges themselves.
    private Vertex max_deg_vrx; // One of the vertexes with the greatest degree.

    public TreeGraphs(int size)
    {
        RandomInt rand = new RandomInt();
        int much_left;
        int max = 0;
        int sA;
        int sB;

        boolean is_vaild = false;

        this.size_v = size;
        this.size_e = size - 1;
        much_left = size-1;

        this.V = new ArrayList<Vertex>(size);
        this.E = new boolean[size][];

        for(int i=0; i<size; i++) { this.E[i] = new boolean[size]; }


        while(!is_vaild) {

            // Setting up vertexes and allocating memory for the edges matrix:
            for(int i=0; i<size; i++)
            {
                Array.set(V, i, new Vertex(i,0));
                Arrays.fill(E[i], false);
            }

            sA = rand.GetRand(1, size-1); // A side size;
            sB= size - sA;

            int A_index=0, B_index = sA;


            if(sA>=sB)
            {

                for(int i = sA; i<size; i++)
                {
                    this.E[A_index][i] = true;
                    this.E[i][A_index] = true;

                    this.V.get(A_index).AddNeigh(i);
                    this.V.get(i).AddNeigh(A_index);

                    A_index++;
                    much_left--;
                }


                while(much_left != 0)
                {

                    if(A_index == sA) { A_index = 0; }

                    int x = rand.GetRand(sA, size-1);

                    if(this.E[x][A_index] == true) { continue; }

                    this.E[x][A_index] = true;
                    this.E[A_index][x] = true;

                    this.V.get(x).AddNeigh(A_index);
                    this.V.get(A_index).AddNeigh(x);

                    if(this.V.get(x).GetDeg() > max)
                    {
                        max =this.V.get(x).GetDeg();
                        this.max_deg_vrx = this.V.get(x);
                    }

                    if(this.V.get(A_index).GetDeg() > max)
                    {
                        max =this.V.get(A_index).GetDeg();
                        this.max_deg_vrx = this.V.get(A_index);
                    }

                    A_index++;
                    much_left--;

                }


            }



            else
            {


                for(int i = 0; i<sA; i++)
                {
                    this.E[B_index][i] = true;
                    this.E[i][B_index] = true;

                    this.V.get(B_index).AddNeigh(i);
                    this.V.get(i).AddNeigh(B_index);

                    B_index++;
                    much_left--;
                }


                while(much_left != 0)
                {

                    if(B_index == size) { B_index = sA; }

                    int x = rand.GetRand(0, sA-1);

                    if(this.E[x][B_index] == true) { continue; }

                    this.E[x][B_index] = true;
                    this.E[B_index][x] = true;

                    this.V.get(x).AddNeigh(B_index);
                    this.V.get(B_index).AddNeigh(x);

                    if(this.V.get(x).GetDeg() > max)
                    {
                        max =this.V.get(x).GetDeg();
                        this.max_deg_vrx = this.V.get(x);
                    }

                    if(this.V.get(B_index).GetDeg() > max)
                    {
                        max =this.V.get(B_index).GetDeg();
                        this.max_deg_vrx = this.V.get(B_index);
                    }

                    B_index++;
                    much_left--;

                }


            }

            is_vaild = this.CustBFS();

            if(is_vaild) { return; }

        }

    }


    public TreeGraphs()
    {
        size_v=0;
        size_e = 0;
    }


    public final int Get_size_V() { return this.size_v; }
    public final int Get_size_E() { return this.size_e; }
    public final Vertex Get_Max_Deg_ver() { return this.max_deg_vrx; }
    public final ArrayList<Vertex> GetV() { return this.V; }
    public final boolean Check_if_Nei(int first_index, int second_index) {  return this.E[first_index][second_index]; }

    public final TreeGraphs SubGraph(Vertex vertex_to_remove, boolean x_or_nx)
    {
        TreeGraphs newT = new TreeGraphs();

        int max = 0;

        // T-v, vEV;
        if(x_or_nx)
        {
            newT.size_v = this.size_v-1;
            newT.size_e = this.size_e;

            newT.V = this.GetV();

            newT.V.remove(vertex_to_remove);

            for(int i=0; i<newT.size_v; i++)
            {
                if(newT.V.get(i).isNeig(vertex_to_remove.GetInd()))
                {
                    newT.V.get(i).RemoveNeigh(vertex_to_remove.GetInd());
                    newT.size_e--;

                }

                if(max < newT.V.get(i).GetDeg()) { max = newT.V.get(i).GetDeg();
                    newT.max_deg_vrx = newT.V.get(i);
                }

            }

        }


        else
        {
            newT.size_v = this.size_v - 1 - vertex_to_remove.GetDeg();
            newT.size_e = this.size_e;



        }



        return newT;
    }

    // Check out if the outcome graph is a tree:
    private boolean CustBFS()
    {
        Queue<Vertex> q = new LinkedList<>();
        int color[] = new int[this.size_v];
        int number_of_nil = 1;
        int n_e=0;


        Arrays.fill(color, 0);
        color[0] = 1;
        q.add(this.V.get(0));

        while(!q.isEmpty())
        {
            for(int i=1; i<this.size_v; i++)
            {
                if( this.E[q.peek().GetInd()][i]==true && color[i] == 0)
                {
                    color[i] = 1;
                    q.add(this.V.get(i));
                    n_e++;
                }

            }

            color[q.peek().GetInd()] = 2;
            q.poll();
        }


        if(number_of_nil != 1 || n_e!=this.size_e) { return false; }

        return true;

    }

    public boolean isKn() {  return (this.size_e == this.size_v*(this.size_v-1)/2); }

}
