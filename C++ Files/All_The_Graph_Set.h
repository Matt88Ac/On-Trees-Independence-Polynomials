#pragma once
#include "Polynomial.h"

class FullTree
{
public:
	
	TreeGraph TheTree;
	 TreeGraph OppositeGraph;

	IndeP The_Inde_Poly_of_the_Tree;
	
	FullTree(int size) {
		TheTree = TreeGraph(size);

		OppositeGraph = TheTree.GetTOpp();

		The_Inde_Poly_of_the_Tree = IndeP(TheTree);

	}

};