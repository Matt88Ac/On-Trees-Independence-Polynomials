/*  TEST */
#include <iostream>
#include "Polynomial.h"
#include <errno.h>
#include <sstream>
 //xx


int main()
{

	TreeGraph x(20);

	cout << x << endl;

	IndeP P(x);


	cout << P << endl;
	x.Draw_Graph();


	for (int i = 0; i < 10; i++) {
		stringstream ss;
		string via;
		TreeGraph temp(5+i);
		ss << i;
		via = ss.str();

		temp.Draw_Graph(via.c_str());
	}



	system("Test.jpg");

	system("pause");
	return 0;
}