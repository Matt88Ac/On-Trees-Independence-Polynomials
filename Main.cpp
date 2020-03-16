/*  TEST */

#include <iostream>
#include "Polynomial.h"
#include "Additonal Headers/CPP_MP.h"
#include "Additonal Headers/CSV_Platform.h"


using namespace Platfrom;
using namespace Math;
using namespace std;

int main()
{
	TreeGraph T(10);

	cout << T << endl;

	CliqueP C(T);


	cout << C << endl;
	
	
	
	
	
	
	return 0;
	
	stringstream ss;
	ss << "Test_#" << Random_INT(10000);
	CSV file(ss.str());

	//CSV Row Definition
	file.Add_Row_Category("Vertices");
	file.Add_Row_Category("Alpha(g)");
	file.Add_Row_Category("Number Of Roots");
	file.Add_Row_Category("First Root Found");
	file.Add_Row_Category("Number Of Max Points");
	file.Add_Row_Category("Global Supremum X");
	file.Add_Row_Category("Gloabl Supremum Y");
	file.Add_Row_Category("Number Of Min Points");
	file.Add_Row_Category("Global Infima X");
	file.Add_Row_Category("Gloabl Infima Y");
	file.Add_Row_Category("Polynomial");
	file.Add_Row_Category("Degree Array");
	file.Add_Row_Category("Max Deg");
	file.Add_Row_Category("$");

	//

	//Timer Status
	#define TIMER_ON


	Function Symbolic_Frame;
	vector<TreeGraph> Trees;
	Timer timer;
	bool does_ex = false;


	// generation parameters
	int iterations =  500;
	int amount_of_vertcies = 15;
	//

	Trees.reserve(iterations);
	timer.Start_Timer();
	for (int i = 0; i < iterations; i++) {
		TreeGraph x(amount_of_vertcies);
		IndeP P(x);


		// isomorphism check
		for (int j = 0; j < Trees.size(); j++) 
		{  
			
			if (x.Are_Isomorphic(Trees[j])) { 
				does_ex = true;
				break; 
			}

		}

		if (does_ex) { does_ex = false;  	
#ifdef TIMER_ON
		cout << "Iteration [ " << i + 1 << " / " << iterations << " ] , Discarded by Isomorphism After - {" << timer << "}" << endl;

#endif // TIMER_ON
		continue; }

		Trees.push_back(x);



		Symbolic_Frame = Function(P.Get_Math_Format_IndeP().c_str());


		// symbolic calculations
		std::vector<double> roots = Symbolic_Frame.Get_Roots(0.001);
		std::vector<Point<double> > Maximum_Points = Symbolic_Frame.Get_Polynomial_Maximum();
		std::vector<Point<double> > Minimum_Points = Symbolic_Frame.Get_Polynomial_Minimum();


		//CSV formating

		//number of vertecis
		file.Add_Value(amount_of_vertcies);
		//alpha of graph 
		file.Add_Value(P.GetAlphaT());
		//number of roots if found at all
		file.Add_Value(roots.size());
		//first root found , if no root found a whitespace is added to CSV table
		roots.size() > 0 ? file.Add_Value(roots[0]) : file.Add_Value(" ");
		//amount of supremum points
		file.Add_Value(Maximum_Points.size());
		//supremum x
		Maximum_Points.size() > 0 ? file.Add_Value(Get_Largest_Point_In_Vector(Maximum_Points).x) : file.Add_Value(" ");
		//supremum y
		Maximum_Points.size() > 0 ? file.Add_Value(Get_Largest_Point_In_Vector(Maximum_Points).y) : file.Add_Value(" ");
		//amount of infima points
		file.Add_Value(Minimum_Points.size());
		//supremum x
		Maximum_Points.size() > 0 ? file.Add_Value(Get_Smallest_Point_In_Vector(Maximum_Points).x) : file.Add_Value(" ");
		//supremum y
		Maximum_Points.size() > 0 ? file.Add_Value(Get_Smallest_Point_In_Vector(Maximum_Points).y) : file.Add_Value(" ");
		//Unimodaly Polynom
		file.Add_Value((string)P);
		//degree array
		file.Add_Value(x.GetDegArr());
		//max deg of graph
		file.Add_Value(x.GetBigDelta());
		
		//



		//process notification
#ifdef TIMER_ON
		cout << "Iteration [ " << i + 1 << " / " << iterations << " ] , Finished After - {" << timer << "}" << endl;

#endif // TIMER_ON


		//
	}
	
	cout << "\n\n-Program Finished Running After-: -- " << "[" << timer << "]\n";
	cout << "\n\n[Test Run Saved As: " << ss.str() <<"]\n\n\n";
	system("pause");
	return 0;
}