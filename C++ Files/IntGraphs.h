
/*    In order to get a random Interval Graph, declare : RandomIntGraph( number-of-vertexes (int) ,  upper bound for the Intervals  ) 
		
		In order to get specific Interval Graph, declare : RandomIntGraph( vector-of-your-intervals (Interval) )

*/



#pragma once

#include "Interval.h"
#include <random>
#include <string>
#include <iostream>
#include <algorithm>


class Int_Vertex
{
	Interval matched_int;
	int degree;
	int index;

public:
	Int_Vertex(Interval Int, int deg = 0, int ind = 0) : degree(deg), matched_int(Int), index(ind) {};

	const int& GetDeg() const { return degree; }

	void incDeg() { degree++; }

	const Interval& GetInt() const { return matched_int; }

	void setDeg(int newDeg) { degree = newDeg; }

	~Int_Vertex() { N.~vector(); }

	std::vector<int> N;

};


class RandomIntGraph
{
	std::vector<Int_Vertex> V;
	std::vector<Interval> IntFam;
	int size_v;
	int size_e;
	int max_deg_v;

	int chromatic_num;
	int biggest_deg;

	std::string degs_arr;

public:

	RandomIntGraph(int size, unsigned ll upperbound = 50) : size_v(size), size_e(0), max_deg_v(0), degs_arr("[ ")
	{
		int i = 0, max = 0;
		static std::random_device sid;
		static std::mt19937 rng(sid());


		std::uniform_int_distribution<long long> start(0-upperbound, upperbound-(ll)1);

		for (int i = 0; i < size; i++)
		{
			unsigned long long s = start(rng);
			std::uniform_int_distribution<long long> end(s, upperbound);
			Interval x(s, end(rng));
			this->IntFam.push_back(x);
		}
		
		std::sort(IntFam.begin(), IntFam.end());
		
		// Generating intervals randomly, and with doing so - creating vertexes:
		for (i = 0; i < size; i++) { V.push_back(Int_Vertex(IntFam[i], 0, i)); }


		for ( i = 0; i < size; i++)
		{
			for (int j = i+1; j < size; j++)
			{
				if (V[i].GetInt().DoesContain(V[j].GetInt()))
				{
					V[i].incDeg();
					V[j].incDeg();

					V[i].N.push_back(j);
					V[j].N.push_back(i);

					size_e++;

				}

			}

			if (V[i].GetDeg() > max) { max = V[i].GetDeg(); max_deg_v = i; }

		}

		biggest_deg = V[max_deg_v].GetDeg();
		chromatic_num = GreedyColoring();

		std::vector<int> deg_arr_given;

		for (int i = 0; i < (int)V.size(); i++) { deg_arr_given.push_back(V[i].GetDeg()); }

		sort(deg_arr_given.begin(), deg_arr_given.end());



		// Generating the array of degrees for the random graph:
		for (int i = 0; i < (int)deg_arr_given.size() - 1; i++) {
			this->degs_arr += std::to_string(deg_arr_given[i]);
			this->degs_arr += " ";
		}

		this->degs_arr += std::to_string(deg_arr_given[deg_arr_given.size() - 1]);
		this->degs_arr += " ]";



	}

	RandomIntGraph(const std::vector<Interval>& IntFam, bool for_poly) : size_v((int)IntFam.size()), size_e(0), max_deg_v(0), degs_arr("[ ")
	{
		int i = 0, max = 0;


		this->IntFam = IntFam;

		if (!for_poly) { sort(this->IntFam.begin(), this->IntFam.end()); }

		for ( i = 0; i < size_v; i++) {  V.push_back(Int_Vertex(this->IntFam[i]));	}

		for (i = 0; i < (int)V.size(); i++)
		{
			for (int j = i + 1; j < (int)V.size(); j++)
			{
				if (V[i].GetInt().DoesContain(V[j].GetInt()))
				{
					V[i].incDeg();
					V[j].incDeg();
					
					if (!for_poly)
					{
						V[i].N.push_back(j);
						V[j].N.push_back(i);
					}
					
					size_e++;
				}

			}

			if (V[i].GetDeg() > max) { max = V[i].GetDeg(); max_deg_v = i; }

		}

		
		if (!for_poly) {

			chromatic_num = GreedyColoring();
			biggest_deg = V[max_deg_v].GetDeg();

			std::vector<int> deg_arr_given;

			for (int i = 0; i < (int)V.size(); i++) { deg_arr_given.push_back(V[i].GetDeg()); }

			std::sort(deg_arr_given.begin(), deg_arr_given.end());


			// Generating the array of degrees for the non random graph:
			for (int i = 0; i < (int)deg_arr_given.size() - 1; i++) {
				this->degs_arr += std::to_string(deg_arr_given[i]);
				this->degs_arr += " ";
			}

			this->degs_arr += std::to_string(deg_arr_given[deg_arr_given.size() - 1]);
			this->degs_arr += " ]";

		}



	}

	bool isKn() const { return (size_e == size_v * (size_v - 1) / 2); }

	const std::vector<Int_Vertex>& GetV() const { return V; }

	RandomIntGraph subGraph(int index_of_vertex, bool x_or_nx) const
	{
		std::vector<Interval> tmpo;
		
		// G-x, xEV:
		if (x_or_nx)
		{

			for (int i = 0; i < (int)V.size(); i++) { if (i!= index_of_vertex) { tmpo.push_back(V[i].GetInt()); } }
			return RandomIntGraph(tmpo, true);

		}


		//G-N[x], xEV:

		for (int i = 0; i < (int)V.size(); i++)
		{
			if (i != index_of_vertex && !V[i].GetInt().DoesContain(V[index_of_vertex].GetInt()))
			{
				tmpo.push_back(V[i].GetInt());
			}
		}

		return RandomIntGraph(tmpo, true);


	}


	const Interval& GetSpecificInt(int index) const { return V[index].GetInt(); }
	const int& getsize() const { return size_v; }
	const int& getSizeE() const { return size_e; }
	const int& GetBigDelta() const { return biggest_deg; }

	const int& GetMax() const { return max_deg_v; }

	const int& GetCHI() const { return chromatic_num; }

	const std::string& GetDegsArr() const { return degs_arr; }

	void printIntervals()  const
	{
		int i = 0;

		for ( i = 0; i < size_v -1 ; i++) {	std::cout << V[i].GetInt() << ", "; }

		std::cout << V[i].GetInt() << std::endl;

	}

	bool ConnectionCheck(int spot1, int spot2) const { return V[spot1].GetInt().DoesContain(V[spot2].GetInt()); }


	~RandomIntGraph() { 
		V.clear(); V.shrink_to_fit(); 
		IntFam.~vector();
		degs_arr.~basic_string();
	
	}



	private:
		int GreedyColoring();
		int min_used(const Int_Vertex&, const int*) const;
		int find_max(int*);
};



int RandomIntGraph::find_max(int* arr)
{
	int max = 0;
	for (int i = 0; i < size_v; i++) { 	if (max < arr[i]) { max = arr[i]; } }
	return max;
}

int RandomIntGraph::min_used(const Int_Vertex& V, const int* colors) const
{
	int* used_color, i, j = 0;
	used_color = (int*)calloc(V.GetDeg(), 4);

	for (i = 0; i < V.GetDeg(); i++)
	{
		if (colors[V.N[i]] > 0 && colors[V.N[i]] <= V.GetDeg())
		{
			used_color[colors[V.N[i]] - 1] = 1;
		}

	}

	for (i = 0; i <= V.GetDeg(); i++)
	{
		if (!used_color[i])
		{
			free(used_color);
			return i + 1;
		}
	}

	free(used_color);
	return V.GetDeg()+ 1;
}

int RandomIntGraph::GreedyColoring()
{
	int  i, * color;
	color = (int*)calloc(size_v, 4);

	if (size_v <= 1)
	{
		return size_v;
	}

	color[0] = 1;


	for (i = 1; i < size_v; i++)
	{
		color[i] = min_used(V[i], color);
	}


	int max = find_max(color);
	free(color);
	return max;

}

