/*  TEST */

#include <iostream>
#include "Polynomial.h"


int main()
{
	


	TreeGraph x(10);
	
	
	/*static random_device sid;
	static mt19937 rng(sid());
	uniform_int_distribution<int> uid(4, 20);


	IndeP P(x);

	while (P.isUni())
	{
		cout << (string)P << endl << endl;

		this_thread::sleep_for(chrono::seconds(1));
		
		P = IndeP(TreeGraph(uid(rng)));
	}


	cout << "****************************************" << P;*/

	TreeGraph y(10);

	IndeP Px(x);
	IndeP Py(y);

	cout << x << endl;

	cout << y << endl;
	
	cout << (x.Are_Isomorphic(y) ? "They are isomorphic." : "They aren't isomorphic.") << endl << endl;

	cout << Px << endl << endl;

	cout << Py << endl << endl;
	

	system("pause");
	return 0;
}