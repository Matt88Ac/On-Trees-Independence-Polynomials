#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Cpp_SIPL.h"



struct Vert {
	Vert(){}
	Vert(int const &Vert_index,std::vector<int> neigh) {
		this->Vert_index = Vert_index;
		this->Neighbours = neigh;
	}
	int Vert_index;
	std::vector<int> Neighbours;
};


struct Tree {

	std::vector<std::pair<int, int> > Tree_Edges;
	std::vector<int> Degrees;
	std::vector<Vert> Vert_Info;
	Matrix<int> Adj_Matrix;
	int Max_Degree;
	int vert;
	void Remove_Vert(int const &index) {

		for (int i = index; i < vert; i++) {
			Vert_Info[i].Vert_index--;
		}

		for (int i = 0; i < vert; i++) {
			if(Adj_Matrix[index][i]==1){
				Degrees[i]--;
			}
		}

		this->Degrees.erase(Degrees.begin() + index);
		this->Vert_Info.erase(Vert_Info.begin() + index);
		this->Adj_Matrix.Remove_Row(index);
		this->Adj_Matrix.Remove_Column(index);




	}
	Tree(int const &edges) {
		Random_Utilitis rnd;
		int length = edges - 2;
		int *prufer = new int[length];
		vert = edges;
		for (int i = 0; i < length; i++)
		{
			prufer[i] = rnd.Random_INT(1,edges);
		}
	
		int vertices = edges;

		std::vector<int> vertex_set(vertices, 0);

		for (int i = 0; i < vertices - 2; i++)
			vertex_set[prufer[i] - 1] += 1;

		int j = 0;

		for (int i = 0; i < vertices - 2; i++)
		{
			for (j = 0; j < vertices; j++)
			{

				if (vertex_set[j] == 0)
				{

					vertex_set[j] = -1;
					Tree_Edges.push_back(std::pair<int, int>((j + 1), prufer[i]));
					vertex_set[prufer[i] - 1]--;

					break;
				}
			}
		}

		j = 0;
		int pa=-1, pb=-1;
		// For the last element 
		for (int i = 0; i < vertices; i++)
		{
			if (vertex_set[i] == 0 && j == 0)
			{


				pa = (i + 1);
				j++;
			}
			else if (vertex_set[i] == 0 && j == 1)
				pb = (i + 1);
		}

		Tree_Edges.push_back(std::pair<int, int>(pa, pb));


		Adj_Matrix = Matrix<int>(vert, vert);


		for (int i = 0; i < Tree_Edges.size(); i++) {
			Adj_Matrix[Tree_Edges[i].second - 1][Tree_Edges[i].first - 1] = 1;
			Adj_Matrix[Tree_Edges[i].first - 1][Tree_Edges[i].second - 1] = 1;

		}
		Max_Degree = 0;
		int holder = 0;
		for (int i = 0; i < vert; i++) {
			std::vector<int> N;
			int count = 0;
			for (int j = 0; j < vert; j++) {
				if (Adj_Matrix[i][j] == 1) {
					N.push_back(j);
					count++;
				}
			}

			this->Vert_Info.push_back(Vert(i, N));

			if (count > holder) {
				holder = count;
				Max_Degree = i;
			}
			//Max_Degree = count ? count > Max_Degree: Max_Degree;
			Degrees.push_back(count);
		}

		

	
	}

	Tree(const Tree& T, int which, bool v_or_nv) {

		this->Adj_Matrix = T.Adj_Matrix;
		this->Degrees = T.Degrees;


		if (v_or_nv)
		{
			this->vert = T.vert-1;
			int max = 0;
			for (int i = 0; i < T.vert; i++) {
				if(this->Adj_Matrix[i][which])
				{
					this->Degrees[i]--;
				}
				this->Max_Degree = max ? this->Degrees[i] <= max : i;
				max = this->Max_Degree;
			}

			
			this->Adj_Matrix.Remove_Column(which);
			this->Adj_Matrix.Remove_Row(which);


		}

		else
		{




		}


	}

};




std::ostream &operator<<(std::ostream &out, std::pair<int, int> const &data) {
	out << "( " << data.first << ", " << data.second<<" ) ";
	return out;
}
std::ostream &operator<<(std::ostream &out, std::vector<std::pair<int, int>> const &data) {
	for (int i = 0; i < data.size(); i++) {
		out << data[i];
	}
	return out;
}

std::ostream &operator<<(std::ostream &out, Vert const &data) {
	out << "Vert Index: " << data.Vert_index << "\n";
	out << "Neighbours : {";
	for (int i = 0; i < data.Neighbours.size(); i++) {
		out << data.Neighbours[i] << ", ";
	}
	out << " }\n";

		return out;
}

Image Draw_Tree(Tree const &tree) {

	Image TD;
	Color_Palette CSET;
	Random_Utilitis rnd;
	std::vector<std::pair<std::pair<int, int>,int> > locations(tree.vert);


	Matrix<int> Adj((int)tree.Tree_Edges.size() + 1, (int)tree.Tree_Edges.size() + 1);

	for (int i = 0; i < tree.Tree_Edges.size(); i++) {
		Adj[tree.Tree_Edges[i].second - 1][tree.Tree_Edges[i].first - 1] = 1;
		Adj[tree.Tree_Edges[i].first - 1][tree.Tree_Edges[i].second - 1] = 1;

	}


	TD.Load_Blank_Canvas(tree.vert * 60, tree.vert * 60, CSET.Azure);
	bool status = false;
	int p = 0;
	for (int i = 0; i < tree.vert; i++) {

		
		std::pair<std::pair<int, int>,int> loc(std::pair<int,int>(rnd.Random_INT(10,tree.vert*40), rnd.Random_INT(10, tree.vert* 40)),i) ;

			for (int j = 0; j < locations.size(); j++) {
				if (loc == locations[i]) {
					j = 0;
					loc = std::pair<std::pair<int, int>, int>(std::pair<int,int>(rnd.Random_INT(10, tree.vert * 40), rnd.Random_INT(10, tree.vert * 40)),i);
					break;
				}
			}
			locations[i] = (loc);



	}
	std::vector<Pixel> colors(tree.vert);
	for (int i = 0; i < tree.vert; i++) {
		colors[i] = CSET.Color_Serial_Number[3+i];
	}


	for (int i = 0; i < locations.size(); i++) {
		TD.Draw_Circle(locations[i].first.first, locations[i].first.second, tree.vert, colors[i], S_FILL);

	}


	for (int i = 0; i < tree.vert; i++) {
		for (int j = 0; j < tree.vert; j++) {
			if (Adj[i][j] == 1) {
				TD.Draw_Line(locations[i].first.first, locations[i].first.second, locations[j].first.first, locations[j].first.second, colors[i],S_AA_LINE);
			}
		}
	}

	TD.Write_Image("Test.jpg");

	
	return TD;


}