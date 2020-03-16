#pragma once
#include "Polynomial.h"

class FullTree
{
public:
	
	TreeGraph TheTree;
	 TreeGraph OppositeGraph;

	IndeP The_Inde_Poly_of_the_Tree;
	IndeP The_Opps_Poly;
	
	FullTree(int size) {
		TheTree = TreeGraph(size);

		OppositeGraph = TheTree.GetTOpp();

		The_Inde_Poly_of_the_Tree = IndeP(TheTree);

		The_Opps_Poly = IndeP(OppositeGraph);


	}

};