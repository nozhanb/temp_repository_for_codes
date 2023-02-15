// This code will find the location of a ginven particle in 1-D potential well.
// Also, the aim of this code is to show the limited accuracy of floating point
// numbers, how it can affect our results and how we can abate the problem.

// April 28, 2020

#include <iostream>
#include <fstream> // ofstream() function
#include <cstdlib>
#include <iomanip> // setw() function, setprecision() function
#include <cstring> // string declaration
#include <cmath>

using namespace std;

int main()
{
	// Declaration of variables
	float  L, x0, v0, t0, tf, dt, t, x, v;
	string buf;

	// Ask user for input

	cout << "Enter L: " << "\n";
	cin  >> L; getline(cin, buf);
	cout << "Enter x0, v0: " << "\n";
	cin  >> x0 >> v0; getline(cin, buf);
	cout << "Enter t0, tf, dt: " << "\n";
	cin  >> t0 >> tf >> dt; getline(cin, buf);
	cout << "You entered the following values: " << "\n";
	cout << "L = " << L << " , x0 = " << x0 << " , v0 = " << \
	v0 << "t0 = " << t0 << " , tf = " << tf << " , dt = " << \
	dt <<"\n";

	// Check the values inserted by the user

	if(L <= 0.0f)
	{
		cerr << "Length L cannot be <= 0.0!" << "\n";
		exit(1);
	}
	if(x0 < 0.0f )
	{
		cerr << "Initial location cannot be < 0.0!" << "\n";
		exit(1);
	}
	if(x0 > L)
	{
		cerr << "Initila location cannot be greater than length of the well L!" << "\n";
		exit(1);
	}
	if(v0 <= 0.0f)
	{
		cerr << "Initial velocity cannot be <= 0.0!" << "\n";
		exit(1);
	}

	// Initialize the values

	t = t0;
	x = x0;
	v = v0;
	ofstream myfile("box1D_1.dat");
	myfile.precision(9); // float precision

	// Computation part

	while(t <= tf)
	{
		myfile << setw(17) << t << " " << setw(17) << x << " " << setw(17) << v <<"\n" ;
		x += v * dt;
		t += dt;
		if(x <0.0f || x > L)
		{
			v = -v;
		}
	}
	myfile.close();
}