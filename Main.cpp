/*  TEST */

#include <iostream>
#include "Polynomial.h"


int main()
{
	
	TreeGraph x(10);
	
	TreeGraph y(10);

	IndeP Px(x);
	IndeP Py(y);

	cout << x << endl;

	cout << y << endl;
	
	cout << (x.Are_Isomorphic(y) ? "They are isomorphic." : "They aren't isomorphic.") << endl << endl;

	cout << Px << endl << endl;

	cout << Py << endl;
	

	system("pause");
	return 0;
}