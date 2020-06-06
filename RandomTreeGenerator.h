#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Cpp_SIPL.h"

struct Tree {

	std::vector<std::pair<int, int> > Tree_Edges;
	int vert;
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

	
	}
	void Print_Adj_Matrix() const {

		Matrix<int> Adj((int)Tree_Edges.size() + 1, (int)Tree_Edges.size() + 1);

		for (int i = 0; i < Tree_Edges.size(); i++) {
			Adj[Tree_Edges[i].second - 1][Tree_Edges[i].first - 1] = 1;
			Adj[Tree_Edges[i].first - 1][Tree_Edges[i].second - 1] = 1;

		}
		std::cout << Adj << std::endl << std::endl;

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