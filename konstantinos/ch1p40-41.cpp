// Finding the area and perimeter of circles with the values of radii
// given by the user and then the results output to a file.

// April 23, 2020

#include <iostream>
#include <fstream> // ofstream() function

using namespace std;

int main()
{
	const int N     = 10;
	const double PI = 3.1415926535897932;
	double R[N];
	double area, perimeter;
	int i;

	for (i = 0; i < 10 ; i++)
	{
		cout << "Enter radius of the circles: ";
		cin  >> R[i];
		cout << "The value of " << R[i] << " was entered for radius of the circle " << (i + 1) << "\n";
	}

	ofstream myfile("AREA.DAT");

	for (i = 0; i < 10; i++)
	{
		perimeter = 2 * PI * R[i];
		area      = PI * R[i] * R[i];
		myfile << (i + 1) << ") R = " << R[i] << "perimeter = " << perimeter << "\n";
		myfile << (i + 1) << ") R = " << R[i] << "area = " << area << "\n";
	}

	myfile.close();
}