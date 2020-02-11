/*  TEST */

#include <iostream>
#include "Polynomial.h"


int main()
{
	
	TreeGraph x(10);
	
	IndeP P(x);

	static random_device sid;
	static mt19937 rng(sid());

	uniform_int_distribution<int> uid(4, 20);

	while (P.isUni())
	{
		cout << P << endl << endl;
		TreeGraph T(uid(rng));
		P.~IndeP();
		P = IndeP(T);
		T.~TreeGraph();

	}

	cout << "******************" << P << "********************" << endl;

	system("pause");
	return 0;
}