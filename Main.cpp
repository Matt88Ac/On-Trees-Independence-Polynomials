#include "RandomTreeGenerator.h"


using namespace std;

int main() {

	cout << "==============Before Remove: \n";
	Tree test(5);

	cout << test.Adj_Matrix << endl;


	for (int i = 0; i < test.Degrees.size(); i++) {
		cout << test.Vert_Info[i] << " ";
	}

	cout << endl << "Max Deg: " << test.Max_Degree;


	cout << "\n\n\n==============After Remove: \n";

	test.Remove_Vert(0);

	cout << test.Adj_Matrix << endl;

	for (int i = 0; i < test.Degrees.size(); i++) {
		cout << test.Vert_Info[i] << " ";
	}


	cout << endl << "Max Deg: " << test.Max_Degree;


	cout << "\n\n\n\n";
	system("pause");
	return(0);



}