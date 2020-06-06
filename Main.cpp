#include "RandomTreeGenerator.h"


using namespace std;

int main() {

	  
	Tree test(5);
	cout << test.Adj_Matrix << endl << endl;

	for (int i = 0; i < test.Degrees.size(); i++) {
		cout << test.Degrees[i] << " ";
	}

	cout << endl << "Max Deg: " << test.Max_Degree;


	cout << "\n\n\n\n";
	system("pause");
	return(0);



}