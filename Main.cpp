/*  TEST */

#include <iostream>
#include "Polynomial.h"

int main()
{

	TreeGraph x(10);

	cout << x << endl;

	IndeP P(x);

	cout << P << endl;
	cout << (string)P << endl;


	system("pause");
	return 0;
}