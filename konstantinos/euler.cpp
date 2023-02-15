// Comparing three different Euler, Euler-Cromer, and Euler-Verlet methods for finding X[t] and V[t].

// May 07, 2020

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

//______________________________________________________________________

// Global Declaration

const int P = 110000;
double T[P], X[P], V[P], E[P]; // For test of Error you need to change this to float!

//______________________________________________________________________

// Function Declaration

void euler       (const double& Xin, const double& Vin, const double& Tfi, const int& Nt);

void euler_cromer(const double& Xin, const double& Vin, const double& Tfi, const int& Nt);

void euler_verlet(const double& Xin, const double& Vin, const double& Tfi, const int& Nt);

double accel	 (const double& x);

//______________________________________________________________________

// Body

int main()
{
	double Xin, Vin, Tfi;
	int Nt, i;
	string buf;

// User inputs

cout << "Type in Xin, Vin, Tfi, and Nt: " << "\n";
cin  >> Xin >> Vin >> Tfi >> Nt; getline(cin, buf);

// Check if Nt is greater than P!
if(Nt >= P)
{
	cerr << "Nt is greater than allocated memory P!" << "\n";
	exit(1); 
}
//______________________________________________________________________
// Euler Method

euler(Xin, Vin, Tfi, Nt);
ofstream myfile("euler.dat");
myfile.precision(17);

for(i = 0; i < Nt; i++)
{
	myfile << T[i] << " " << X[i] << " " << V[i] << endl;
}

myfile.close();
//______________________________________________________________________
// Euler-cromer Method

euler_cromer(Xin, Vin, Tfi, Nt);
myfile.open("euler-cromer.dat");
myfile.precision(17);

for(i = 0; i < Nt; i++)
{
	myfile << T[i] << " " << X[i] << " " << V[i] << endl;
}

myfile.close();
//______________________________________________________________________
// Euler-Verlet Method

euler_verlet(Xin, Vin, Tfi, Nt);
myfile.open("euler-verlet.dat");
myfile.precision(17);

for(i = 0; i < Nt; i++)
{
	myfile << T[i] << " " << X[i] << " " << V[i] << " " << E[i] << endl;
}

myfile.close();

} // End of int main()

//______________________________________________________________________
// Acceleration at point x is calculated by the following function

double accel(const double& x)
{
	return -10.0 * sin(x);
}
//______________________________________________________________________
// Euler function

void euler(const double& Xin, const double& Vin, const double& Tfi, const int& Nt)
{
	int i;
	double h;
	// Setting initial conditions
	T[0]  = 0.0;
	X[0]  = Xin;
	V[0]  = Vin;
	h     = Tfi/(Nt - 1);
	for(i = 1; i < Nt; i++)
	{
		T[i] = T[i - 1] + h;
		X[i] = X[i - 1] + V[i - 1] * h;
		V[i] = V[i - 1] + accel(X[i - 1]) * h;
	}
}
//______________________________________________________________________
// Euler-Cromer function
void euler_cromer(const double& Xin, const double& Vin, const double& Tfi, const int& Nt)
{
	int i;
	double h;
	// Setting initial conditions here
	T[0] = 0.0;
	X[0] = Xin;
	V[0] = Vin;
	h    = Tfi/(Nt - 1);
	for(i = 1; i < Nt; i++)
	{
		T[i] = T[i - 1] + h;
		V[i] = V[i - 1] + accel(X[i - 1]) * h;
		X[i] = X[i - 1] + V[i] * h;
 	}
}
//______________________________________________________________________
// Euler-Verlet function
void euler_verlet(const double& Xin, const double& Vin, const double& Tfi, const int& Nt)
{
	int i;
	double h, h2, X0, o2h; // For test of Error you need to change this to float!
	// Setting initial conditions here
	T[0] = 0.0;
	X[0] = Xin;
	V[0] = Vin;
	E[0] = 0.0;	// I added this line for test of ERORR.
	h    = Tfi/(Nt - 1);
	h2   = h * h;
	o2h  = 0.5 / h; // denominator of the equtation Vn = (X(n + 1) - X(n - 1))/(2 * h);
	// We have to initialize the step X0 = X[-1]
	X0   = X[0] - V[0] * h + accel(X[0]) * h2/2.0;
	T[1] = h;
	X[1] = 2.0 * X[0] - X0 + accel(X[0]) * h2;

 	for(i = 2; i < Nt; i++)
	{
		T[i]     = T[i - 1] + h;
		X[i]     = 2.0 * X[i - 1] - X[i - 2]; //+ accel(X[i - 1]) * h2;
		V[i - 1] = o2h * (X[i] - X[i - 2]);
		E[i]     = X[i] - X[i - 2]; // I added this line for test of ERORR.
 	}
 	V[Nt - 1]    = (X[Nt - 1] - X[Nt - 2])/h;
 	E[Nt - 1]    = (X[Nt - 1] - X[Nt - 2]); // I added this line for test of ERORR.
}
