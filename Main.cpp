/*  TEST */

#include <iostream>
#include "Polynomial.h"
#include <errno.h>
//xxxxxxxxxxxxxxxxxxxx


int main()
{

	TreeGraph x(20);

	cout << x << endl;

	IndeP P(x);

	cout << P << endl;


	system("pause");
	return 0;
}