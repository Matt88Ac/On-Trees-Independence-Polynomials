/*  TEST */

#include <iostream>
#include "Polynomial.h"


int main()
{
	
	TreeGraph x(30);
	
	IndeP P(x);

	cout << x << endl;

	cout << P << endl;


	/*static random_device sid;
	static mt19937 rng(sid());

	uniform_int_distribution<int> uid(5, 60);


	while (P.isUni())
	{
		cout << P << endl << endl;
		x = TreeGraph(uid(rng));
		cout << x << endl << endl;

		P.~IndeP();
		P = IndeP(x);
		x.~TreeGraph();
		
	}*/

	//cout << "******************" << P << "********************" << endl;

	system("pause");
	return 0;
}