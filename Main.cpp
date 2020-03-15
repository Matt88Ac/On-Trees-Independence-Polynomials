/*  TEST */

#include <iostream>
#include "Polynomial.h"
#include "Additonal Headers/CPP_MP.h"
#include "Additonal Headers/CSV_Platform.h"

using namespace Platfrom;
using namespace Math;
int main()
{
	CSV file("First_Test");
	file.Add_Row_Category("Vertices");
	file.Add_Row_Category("Alpha(g)");
	//file.Add_Row_Category("Number Of Roots");
	file.Add_Row_Category("Polynomial");
	file.Add_Row_Category("Degree Array");
	file.Add_Row_Category("Max Deg");
	file.Add_Row_Category("$");
	//file.Add_Row_Category("Polynomial");
	Function temp;


	for (int i = 0; i < 500; i++) {
		TreeGraph x(10);
		IndeP P(x);

		file.Add_Value(10);
		file.Add_Value(P.GetAlphaT());
		file.Add_Value((string)P);
		file.Add_Value(x.GetDegArr());
		file.Add_Value(x.GetBigDelta());
		

	}
	
	system("pause");
	return 0;
}