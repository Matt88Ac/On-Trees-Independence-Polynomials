
/* For a Tree-Graph object, declare : TreeGraph( integer wanted-number-of-vertexes ) */




#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdbool.h>
#include <queue>
#include <random>
#include <sstream>
#include "Image_Header.h"
#include "Color_Catalog.h"

#define PLANER 914

using namespace std;



int count_bigger(const vector<int>& arr, int x)
{
	int count = 0;
	int i = 0;
	int sze = (int)arr.size();

	for (i = 0; i < sze; i++)
	{
		if (arr[i] < x) { count++; }
	}

	return count;

}



class vertex
{
public:
	vertex(int index = 0, int deg = 0) { ind = index; degree = deg; }
	~vertex() { Nindex.clear(); N.clear(); Nindex.shrink_to_fit(); N.shrink_to_fit(); }

	int ind;
	int degree;
	coordinate Position;
	vector<vertex> N;
	vector<int> Nindex;

};





class TreeGraph
{
	friend ostream& operator << (ostream&, const TreeGraph&);


public:

	// Tree Generator:
	TreeGraph(int size)
	{
		int no_of_nil = size;
		int no_of_e = 0;

		while (no_of_nil != 1 && (no_of_e != size - 1))
		{

			int much_left = 0, i, sA = 0, sB = 0, j;
			static random_device sid;
			static mt19937 rng(sid());

			uniform_int_distribution<int> uid(1, size - 1);

			sA = uid(rng);
			sB = size - sA;

			size_E = size - 1;
			size_v = size;
			Edges = new bool*[size];

			for (i = 0; i < sA; i++)
			{
				V.push_back(vertex(i, 0));
				Edges[i] = (bool*)calloc(size, sizeof(bool));
				A.push_back(V[i]);
				j = i;

			}

			j++;
			for (i = 0; i < sB; i++)
			{
				V.push_back(vertex(j, 0));
				Edges[j] = (bool*)calloc(size, sizeof(bool));
				B.push_back(V[j]);
				j++;
			}

			j = 0;

			max_deg_vrx = 0;
			int max = 0;

			much_left = size_E;

			if (sA >= sB)
			{
				for (i = 0; i < sB; i++)
				{
					Edges[A[i].ind][B[i].ind] = 1;
					Edges[B[i].ind][A[i].ind] = 1;

					V[A[i].ind].degree++;
					V[B[i].ind].degree++;


					A[i].degree++;
					B[i].degree++;

					B[i].N.push_back(A[i]);
					A[i].N.push_back(B[i]);

					V[A[i].ind].N.push_back(V[B[i].ind]);
					V[B[i].ind].N.push_back(V[A[i].ind]);

					A[i].Nindex.push_back(B[i].ind);
					B[i].Nindex.push_back(A[i].ind);

					V[A[i].ind].Nindex.push_back(B[i].ind);
					V[B[i].ind].Nindex.push_back(A[i].ind);

					much_left--;

				}

				for (i; much_left && i < sA; i++)
				{
					uniform_int_distribution<int> nei(0, sB - 1);
					int x = nei(rng);

					if (Edges[A[i].ind][B[x].ind]) { i--; continue; }

					sort(A[i].Nindex.begin(), A[i].Nindex.end());

					for (int k = 0; k < (int)B[x].Nindex.size(); k++) { if (binary_search(A[i].Nindex.begin(), A[i].Nindex.end(), B[x].Nindex[k])) { i--; continue; } }



					Edges[A[i].ind][B[x].ind] = 1;
					Edges[B[x].ind][A[i].ind] = 1;

					A[i].degree++;
					B[x].degree++;

					V[A[i].ind].degree++;
					V[B[x].ind].degree++;

					V[A[i].ind].N.push_back(V[B[x].ind]);
					V[B[x].ind].N.push_back(V[A[i].ind]);

					B[x].N.push_back(A[i]);
					A[i].N.push_back(B[x]);

					A[i].Nindex.push_back(B[x].ind);
					B[x].Nindex.push_back(A[i].ind);

					V[A[i].ind].Nindex.push_back(B[x].ind);
					V[B[x].ind].Nindex.push_back(A[i].ind);

					much_left--;

					if (max < A[i].degree) { max_deg_vrx = A[i].ind; max = A[i].degree; }
					if (max < B[x].degree) { max_deg_vrx = B[x].ind; max = B[x].degree; }

					if (much_left != 0 && i == sA - 1) { i = 0; }


				}





			}


			// B>A

			else
			{

				for (i = 0; i < sA; i++)
				{
					Edges[A[i].ind][B[i].ind] = 1;
					Edges[B[i].ind][A[i].ind] = 1;

					V[A[i].ind].degree++;
					V[B[i].ind].degree++;


					A[i].degree++;
					B[i].degree++;

					B[i].N.push_back(A[i]);
					A[i].N.push_back(B[i]);

					V[A[i].ind].N.push_back(V[B[i].ind]);
					V[B[i].ind].N.push_back(V[A[i].ind]);

					A[i].Nindex.push_back(B[i].ind);
					B[i].Nindex.push_back(A[i].ind);

					V[A[i].ind].Nindex.push_back(B[i].ind);
					V[B[i].ind].Nindex.push_back(A[i].ind);

					much_left--;

				}

				for (i; much_left && i < sB; i++)
				{
					uniform_int_distribution<int> nei(0, sA - 1);
					int x = nei(rng);

					if (Edges[A[x].ind][B[i].ind]) { i--; continue; }

					sort(B[i].Nindex.begin(), B[i].Nindex.end());

					for (int k = 0; k < (int)A[x].Nindex.size(); k++) { if (binary_search(B[i].Nindex.begin(), B[i].Nindex.end(), A[x].Nindex[k])) { i--; continue; } }

					Edges[A[x].ind][B[i].ind] = 1;
					Edges[B[i].ind][A[x].ind] = 1;

					A[x].degree++;
					B[i].degree++;

					V[A[x].ind].degree++;
					V[B[i].ind].degree++;

					V[A[x].ind].N.push_back(V[B[i].ind]);
					V[B[i].ind].N.push_back(V[A[x].ind]);

					B[i].N.push_back(A[x]);
					A[x].N.push_back(B[i]);

					A[x].Nindex.push_back(B[i].ind);
					B[i].Nindex.push_back(A[x].ind);

					V[A[x].ind].Nindex.push_back(B[i].ind);
					V[B[i].ind].Nindex.push_back(A[x].ind);

					much_left--;

					if (max < A[x].degree) { max_deg_vrx = A[x].ind; max = A[x].degree; }
					if (max < B[i].degree) { max_deg_vrx = B[i].ind; max = B[i].degree; }

					if (much_left != 0 && i == sB - 1) { i = 0; }

				}


			}




			BFS(no_of_nil, no_of_e);

			if (no_of_nil != 1 || no_of_e != (size - 1))
			{
				(*this).~TreeGraph();
				this->~TreeGraph();
				
				for (i = 0; i < size; i++)
				{
					delete Edges[i];
				}

				delete Edges;

				no_of_e = 0;
				no_of_nil = size;

			}

			else { return; }

		}




	}

	TreeGraph() : size_v(0), size_E(0), max_deg_vrx(0) {};


	// Used for Independence Polynomial computation;
	TreeGraph(const TreeGraph& T, const int index_to_remove, const bool x_or_nx) : max_deg_vrx(0)
	{


		// T-x, xEV
		if (x_or_nx == true)
		{

			int i = 0, j = 0;
			int max = 0;

			size_v = T.size_v - 1;
			size_E = T.size_E - T.V[index_to_remove].degree;


			for (i = 0; i < size_v; i++)
			{

				V.push_back(vertex(i, 0));
				if (i == index_to_remove) { j++; }

				if (j >= (int)T.V.size()) { break; }

				for (int k = 0; k < (int)T.V[j].Nindex.size(); k++)
				{
					if (T.V[j].Nindex[k] != index_to_remove) {
						V[i].degree++;  V[i].Nindex.push_back(T.V[j].Nindex[k]);

						if (T.V[j].Nindex[k] > index_to_remove)
						{
							V[i].Nindex[V[i].Nindex.size() - 1]--;
						}

					}

				}


				if (max < V[i].degree) { max = V[i].degree; max_deg_vrx = i; }
				j++;

			}

			return;

		}



		//T-N[x], xEV
		else
		{

			int i, j = 0;
			vector<int> tempo;
			int max = 0;
			int size, count = 0;

			size_v = T.size_v - 1 - T.V[index_to_remove].degree;
			size_E = T.size_E - T.V[index_to_remove].degree;

			size = T.size_v;



			tempo = T.V[index_to_remove].Nindex;

			for (i = 0; i < (int)tempo.size(); i++)
			{
				size_E -= T.V[tempo[i]].degree;
				size_E++;
			}


			tempo.push_back(index_to_remove);


			sort(tempo.begin(), tempo.end());


			for (i = 0; i < size_v; i++)
			{
				V.push_back(vertex(i, 0));


				int k = i;
				while (/*isIN(tempo, k)*/ binary_search(tempo.begin(), tempo.end(), k)) { j++; k++; }

				if (j >= (int)T.V.size()) { break; }


				for (k = 0; k < (int)T.V[j].Nindex.size(); k++)
				{
					if (!binary_search(tempo.begin(), tempo.end(), T.V[j].Nindex[k])) { V[i].degree++;  V[i].Nindex.push_back(T.V[j].Nindex[k] - count_bigger(tempo, T.V[j].Nindex[k])); }

				}

				if (V[i].degree > max) { max = V[i].degree; max_deg_vrx = i; }
				j++;
			}



		}



	}


	void BFS(int&, int&);

	int getMax() const { return max_deg_vrx; }

	bool isKn() const { return size_E == ((size_v)*(size_v - 1) / 2); }

	int getsize() const { return size_v; }

	bool ** GetMatrix() const { return Edges; }

	const vector<vertex>& GetV()const { return V; }

	~TreeGraph() { A.clear(); B.clear(); A.shrink_to_fit(); B.shrink_to_fit();  V.clear();  V.shrink_to_fit();  V.~vector(); A.~vector(); B.~vector(); }

	void Draw_Graph();
	void Draw_Graph(char const *f_name);
	void Draw_Graph(char const *f_name, int mod);



protected:
	vector<vertex> A;
	vector <vertex> B;
	
	int size_v;
	int size_E;
	bool **Edges;
	vector<vertex> V;
	int max_deg_vrx;

	Image ImageBody;
	Color_Palette CSET;
};





void TreeGraph::Draw_Graph() {
	this->ImageBody.Load_Blank_Canvas(this->size_v * 100, this->size_v * 100, CSET.Azure);
	random_device seed; //seed for psudo random engine 
	mt19937 random_number_generator(seed()); //merssene twisster using the PR seed
	uniform_int_distribution<size_t> indices(50,(this->size_v*100)-50 );
	int Px, Py;
	
	for(int i =0;i<this->size_v;i++){
		Px = indices(random_number_generator);
		Py = indices(random_number_generator);
		ImageBody.Draw_Circle(Px,Py, 5, CSET.Color_Serial_Number[i+5],"Fill");
		V[i].Position.x = Px;
		V[i].Position.y = Py;
	}

	for (int i = 0; i < this->size_v; i++) {
		for (int j = 0; j < i; j++) {
			if (Edges[i][j] == 1) {
				ImageBody.Draw_Line(V[i].Position.y, V[i].Position.x, V[j].Position.y, V[j].Position.x, CSET.Color_Serial_Number[i+5]);
			}
		}
	}


	ImageBody.Write_Image("Test");
}
void TreeGraph::Draw_Graph(char const *f_name) {
	this->ImageBody.Load_Blank_Canvas(this->size_v * 100, this->size_v * 100, CSET.Azure);
	random_device seed; //seed for psudo random engine 
	mt19937 random_number_generator(seed()); //merssene twisster using the PR seed
	uniform_int_distribution<size_t> indices(50, (this->size_v * 100) - 50);
	int Px, Py;
	ImageBody.Draw_Text(20, (this->size_v * 100) / 2, f_name, CSET.Black);
	for (int i = 0; i < this->size_v; i++) {
		Px = indices(random_number_generator);
		Py = indices(random_number_generator);
		ImageBody.Draw_Circle(Px, Py, 5, CSET.Color_Serial_Number[i + 5], "Fill");
		V[i].Position.x = Px;
		V[i].Position.y = Py;
	}

	for (int i = 0; i < this->size_v; i++) {
		for (int j = 0; j < i; j++) {
			if (Edges[i][j] == 1) {
				ImageBody.Draw_Line(V[i].Position.y, V[i].Position.x, V[j].Position.y, V[j].Position.x, CSET.Color_Serial_Number[i + 5]);
			}
		}
	}


	ImageBody.Write_Image(f_name);
}
void TreeGraph::Draw_Graph(char const *f_name,int mod) {
	this->ImageBody.Load_Blank_Canvas(this->size_v * 100, this->size_v * 100, CSET.Azure);
	random_device seed; //seed for psudo random engine 
	mt19937 random_number_generator(seed()); //merssene twisster using the PR seed
	uniform_int_distribution<size_t> indices(50, (this->size_v * 100) - 50);
	stringstream ss;
	string via;
	int Px, Py,planer_score=0,iterdebug=0;
	bool set = false;
	ImageBody.Draw_Text(20, (this->size_v * 100) / 2, f_name, CSET.Black);
	for (int i = 0; i < this->size_v; i++) {
		Px = indices(random_number_generator);
		Py = indices(random_number_generator);
		V[i].Position.x = Px;
		V[i].Position.y = Py;
	}

	while (true) {
		for (int i = 0; i < this->size_v; i++) {
			for (int j = 0; j < i; j++) {
				if (Edges[i][j] == 1) {
					PixelFrame Path = ImageBody.Get_Line_Pixels(V[i].Position.y, V[i].Position.x, V[j].Position.y, V[j].Position.x);
					for (int k = 0; k < Path.size(); k++) {
						if (k >5 && Path[k].r != CSET.Azure.r && Path[k].g != CSET.Azure.g &&Path[k].b != CSET.Azure.b) {
							V[j].Position.x = indices(random_number_generator);
							V[j].Position.y = indices(random_number_generator);
							set = true;
							break;
						}
					}
					if (set == true) {
						break;
					}
					else {
						ImageBody.Draw_Line(V[i].Position.y, V[i].Position.x, V[j].Position.y, V[j].Position.x, CSET.Color_Serial_Number[i + 5]);
						ImageBody.Update_Pixel_Matrix();
					}
					
					Path.clear();

				}
			}
			if (set == true) {
				break;
			}
		}
		if (set == true) {
			set = false;


		/*	ss << iterdebug;
			via = ss.str();
			ImageBody.Write_Image(via.c_str());
			ss.str(string());
			iterdebug++;*/

			if (this->ImageBody.Pixel_Matrix == nullptr) {
				ImageBody.init_pixel_matrix();
			}
			for (int i = 0; i < this->ImageBody.getHeight(); i++) {
				for (int j = 0; j < this->ImageBody.getWidth(); j++) {
					ImageBody.Color_Spec(ImageBody.Pixel_Matrix[i][j].index_range, CSET.Azure);
					ImageBody.Pixel_Matrix[i][j].r = CSET.Azure.r;
					ImageBody.Pixel_Matrix[i][j].g = CSET.Azure.g;
					ImageBody.Pixel_Matrix[i][j].b = CSET.Azure.b;

				}
			}
			planer_score = 0;
		}
		else {
			planer_score++;
			if (planer_score == size_v) {
				break;
			}
		}
	}





	for (int i = 0; i < this->size_v; i++) {
		ImageBody.Draw_Circle(V[i].Position.x, V[i].Position.y, 5, CSET.Color_Serial_Number[i + 5], "Fill");

	}
	for (int i = 0; i < this->size_v; i++) {
		for (int j = 0; j < i; j++) {
			if (Edges[i][j] == 1) {
				ImageBody.Draw_Line(V[i].Position.y, V[i].Position.x, V[j].Position.y, V[j].Position.x, CSET.Color_Serial_Number[i + 5]);
			}
		}
	}


	ImageBody.Write_Image(f_name);
}



ostream& operator << (ostream& os, const TreeGraph& x)
{


	int i, j;

	if (x.size_v == 0 || x.size_E == 0)
	{
		os << "Nothing to show here." << endl; return os;
	}


	os << "|V| = " << x.getsize() << endl;

	os << "E =  { ";

	for (i = 0; i < x.size_v; i++)
	{
		for (j = i; j < x.size_v; j++)
		{
			if (x.Edges[i][j])
			{
				os << "(V" << i + 1 << ", V" << j + 1 << "), ";
			}
		}
	}

	os << " }" << endl;

	return os;


}


void TreeGraph::BFS(int& number_of_nil, int& number_of_edges)
{
	queue<vertex> Queue;
	int *color;

	color = (int*)calloc(size_v, 4); /* white = 0,
											grey = 1,
												black = 2 */
	color[0] = 1;
	Queue.push(V[0]);

	while (!Queue.empty())
	{
		int i = 0;

		for (i = 0; i < (int)Queue.front().Nindex.size(); i++)
		{
			if (color[Queue.front().Nindex[i]] == 0)
			{
				color[Queue.front().Nindex[i]] = 1;
				Queue.push(V[Queue.front().Nindex[i]]);
				number_of_nil--;
				number_of_edges++;

			}
		}


		color[Queue.front().ind] = 2;
		Queue.pop();

	}

	delete color;

}