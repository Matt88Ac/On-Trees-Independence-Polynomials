#pragma once

#include "Polynomial.h"
#include <fstream>
#include <string>
using namespace std;

class tester
{
public:

	// The Trees will go from 4 vertexes to 20.

	tester();

	void AddToDB(const TreeGraph&);
	bool CheckIfUsed(bool **, const int size);

	~tester() { TreesData.close(); UsedTrees.close(); }


protected:
	fstream TreesData;
	fstream UsedTrees;


};

tester::tester() : TreesData("Trees and Polynomials.txt"), UsedTrees("Matrixes.txt")
{
	static random_device sid;
	static mt19937 rng(sid());
	uniform_int_distribution<int> uid(4, 20);

	while (true)
	{
		AddToDB(TreeGraph(uid(rng)));
	}

}


bool tester::CheckIfUsed(bool ** matrix, const int size)
{
	bool to_ret = false;
	string lines;
	fstream tmp("tmp.txt");


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			tmp << matrix[i][j] << " ";
		}

		tmp << '\n';
	}

	tmp << "\n";


	while (getline(UsedTrees, lines))
	{
		if (lines == "\n") { continue; }
		
		tmp.seekg(0, ios::beg);
		string tmp_string;

		while (getline(tmp, tmp_string))
		{
			to_ret = !(tmp_string == lines);
			if (to_ret) { break; }
			getline(UsedTrees, lines);
		}

		if (!to_ret) { return false; }

	}

	tmp.clear();
	tmp.close();
		
	return to_ret;

}

void tester::AddToDB(const TreeGraph& tree)
{
	if (CheckIfUsed(tree.GetMatrix(), tree.getsize())) { return; }

	bool ** tmp = tree.GetMatrix();
	int i, j;

	
	UsedTrees.seekg(0, ios::end);
	UsedTrees << "\n";

	for ( i = 0; i < tree.getsize(); i++)
	{
		for ( j = 0; j < tree.getsize(); j++)
		{
			UsedTrees << tmp[i][j] << " ";
		}

		UsedTrees << '\n';
	}
	
	TreesData.seekg(0, ios::end);
	UsedTrees << "\n";
	TreesData << tree << endl << IndeP(tree) << endl << endl;

}