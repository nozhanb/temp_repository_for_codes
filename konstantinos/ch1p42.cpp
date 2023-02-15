// This code contains a function that is capable of calculating 
// area and perimeter of a circle with a given radius while writes
// the output to a .dat file!

// April 23, 2020

#include <iostream>
#include <fstream> // ofstream() function
using namespace std;

const double PI = 3.1415926535897932;
void area_of_circle(const double &R, double &L, double &A);

int main()
{
	const int N  = 10;
	double    R[N];
	double area, perimeter;
	int i;

	for(i = 0; i < 10; i++)
	{
		cout << "Enter radius of the circle: ";
		cin  >> R[i];
		cout << "i = " << (i + 1) << "R(i) = " << R[i] << "\n";
	}
	ofstream myfile("AREA2.DAT");
	for(i = 0; i < N; i++)
	{
		area_of_circle(R[i], perimeter, area);
		myfile << (i + 1) << " R = " << R[i] << " Perimeter = " << perimeter << "\n";
		myfile << (i + 1) << " R = " << R[i] << " Area = " << area << "\n";
	}
	myfile.close();
}

void area_of_circle(const double &R, double &L, double &A)
{
	L = 2.0 * PI * R;
	A = PI * R *R;
}