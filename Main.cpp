#include "Polys.h"

using namespace std;

int main() {

	Tree test(15);

	cout << test.Tree_Edges << endl;
	
	
	//IndeP p(test);

	//cout << p << endl;

	Draw_Tree_Bruteforce(test, "test2.jpg");

	cout << "\n\n\n\n";
	system("pause");
	return(0);



}

