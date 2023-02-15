#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	float x = 0.123456;//0.199998;
	float y = 0.123455;//;0.199997;
	float t = 0.00012734767;
	float c;
	float T[1], X[1], D[1], V[1];
	c = x - y;
	T[0] = t;
	X[0] = x;
	V[0] = y;
	D[0] = c;
	cout << "This is it --->" << c << "\n";
	ofstream myfile("accuracyTest.dat");
	//myfile.precision(10);
	myfile << T[0] << " " << X[0] << " " << V[0] << " " << D[0] << "\n";
	myfile.close();
}

// 	float x = 0.1999999856955222699017582;
//	float y = 0.2000000000000000111022302;
//	float t = 0.0001200012000120001179467;