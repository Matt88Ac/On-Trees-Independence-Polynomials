/*  TEST */

#include <iostream>
#include "Polynomial.h"
#include "Additonal Headers/CPP_MP.h"
#include "Additonal Headers/CSV_Platform.h"

using namespace Platfrom;
using namespace Math;
int main()
{
	CSV file("Test_Three");
	file.Add_Row_Category("Vertices");
	file.Add_Row_Category("Alpha(g)");
	file.Add_Row_Category("Number Of Roots");
	file.Add_Row_Category("Number Of Max Points");
	file.Add_Row_Category("Number Of Min Points");
	file.Add_Row_Category("Polynomial");
	file.Add_Row_Category("Degree Array");
	file.Add_Row_Category("Max Deg");
	file.Add_Row_Category("$");
	//file.Add_Row_Category("Polynomial");
	Function temp;
	vector<string> degsArray;

	bool does_ex = false;


	for (int i = 0; i < 500; i++) {
		TreeGraph x(10);
		IndeP P(x);

		for (int j = 0; j < degsArray.size(); j++) 
		{  
			
			if (x.GetDegArr().compare(degsArray[j]) == 0) { does_ex = true; break; }

		}

		if (does_ex) { does_ex = false; continue; }

		degsArray.push_back(x.GetDegArr());

		temp = Function(P.Get_Math_Format().c_str());
		file.Add_Value(10);
		file.Add_Value(P.GetAlphaT());
		file.Add_Value(temp.Get_Roots(0.001).size());
		file.Add_Value(temp.Get_Polynomial_Maximum().size());
		file.Add_Value(temp.Get_Polynomial_Minimum().size());
		file.Add_Value((string)P);
		file.Add_Value(x.GetDegArr());
		file.Add_Value(x.GetBigDelta());
		

		//cout << P.Get_Math_Format() << endl;
	}

	//system("pause");
	return 0;
}