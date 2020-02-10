/*  TEST */
#include <iostream>
#include "Polynomial.h"
#include <errno.h>
 //xx


int main()
{

	TreeGraph x(10);

	cout << x << endl;

	IndeP P(x);

	cout << P << endl;
	x.Draw_Graph();

	system("Test.jpg");

	system("pause");
	return 0;
}