/*  TEST */

#include <iostream>
#include "Polynomial.h"


int main()
{
	
	TreeGraph x(10);
	TreeGraph y(10);

	cout << x << endl << endl;

	cout << y << endl;

	bool bla = x.Are_Isomorphic(y);

	cout << bla << endl;

	if (bla) { IndeP P(x); cout << P << endl; }

	system("pause");
	return 0;
}