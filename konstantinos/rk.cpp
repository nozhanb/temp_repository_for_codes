// This code will demonstrate the Runge-Kutta methods.

// May 17, 2020

#include <iostream>
#include <string>
#include <fstream> 
#include <cmath>
#include <cstdlib>

using namespace std;

//__________________
// Global Declaration

const int P = 110000;
double T[P], X1[P], X2[P];

//__________________
// Function Declaration

double   f1(const double& t, const double& x1, const double& x2);
double   f2(const double& t, const double& x1, const double& x2);
void     RK(const double& Ti,const double& Tf, const double& X10, const double& X20, const int& Nt);
void RKSTEP(double& t, double& x1, double& x2, const double& dt);
//__________________

int main(){
	double  Ti, Tf, X10, X20;
	int      Nt;
	int       i;
	string buf;

	// Input

	cout << "Enter Nt, Ti, Tf, X10, X20: " << endl;
	cin  >> Nt >> Ti >> Tf >> X10 >> X20; getline(cin, buf);

	// A quick check!
	if(Nt > P){
		cerr << "Error! Nt cannot be greater than/equal " << P << "\n";
		exit(1);
	}

	// Calculate RK
	RK(Ti, Tf, X10, X20, Nt);

	// Output
	ofstream myfile("rk.dat");
	myfile.precision(17);
	for(i = 0; i < Nt; i++){
		myfile << T[i] << " " << X1[i] << " " << X2[i] << "\n";
	}
	myfile.close();
}

// ========================================================
// The f u n c t i o n s f1 , f2 ( t , x1 , x2 ) provided by the user
// ========================================================

double f1(const double& t, const double& x1, const double& x2){
	return x2; // This is the derivative of dx1/dt = x2 or v! We are looking for X(t). Remember that Runge-Kutta is a method for solving differential equation like dx/dt!
}

double f2(const double& t, const double& x1, const double& x2){
	return -10.0 * x1; // This is the derivative of dx2/dt = acceleration or a! We are looking for V(t). Remember that Runge-Kutta is a method for solving differential equation like dv/dt!
}

// ========================================================
// Runge-Kutta 
// ========================================================

void RK(const double& Ti, const double& Tf, const double& X10, const double& X20, const int& Nt){

	// Declaration
	double dt;
	double TS, X1S, X2S;
	int i;

	// Initialization
	dt    = (Tf - Ti)/(Nt - 1);
	T[0]  = Ti;
	X1[0] = X10;
	X2[0] = X20;
	TS    = Ti;
	X1S   = X10;
	X2S   = X20;
    
	// Calculation
	for(i = 1; i < Nt; i++){
		RKSTEP(TS, X1S, X2S, dt);
		T[i]  = TS;
		X1[i] = X1S;
		X2[i] = X2S;
	}
} // End of RK

// ========================================================
// Runge-Kutta Calculation
// ========================================================

void RKSTEP(double& t, double& x1, double& x2, const double& dt){

double k11 , k12 , k13 , k14 , k21 , k22 , k23 , k24 ;
double h, h2, h6;

h   = dt;
h2  = 0.5 * h;
h6  = h/6.0;

k11 = f1(t, x1, x2);
k21 = f2(t, x1, x2);
k12 = f1(t + h2, x1 + h2 * k11, x2 + h2 * k21);
k22 = f2(t + h2, x1 + h2 * k11, x2 + h2 * k21);
k13 = f1(t + h2, x1 + h2 * k12, x2 + h2 * k22);
k23 = f2(t + h2, x1 + h2 * k12, x2 + h2 * k22);
k14 = f1(t + h , x1 + h  * k13, x2 + h  * k23);
k24 = f2(t + h , x1 + h  * k13, x2 + h  * k23);

t   = t  + h;
x1  = x1 + h6 * (k11 + 2.0 * (k12 + k13) + k14);
x2  = x2 + h6 * (k21 + 2.0 * (k22 + k23) + k24);

}


















