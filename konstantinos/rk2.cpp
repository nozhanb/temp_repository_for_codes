
// June 06, 2020

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

const int P = 1010000;
double T[P], X1[P], X2[P], V1[P], V2[P];
double k1, k2;

// Function declaration

double f1(const double& t, const double& x1, const double& x2, const double& v1, const double& V2);
double f2(const double& t, const double& x1, const double& x2, const double& v1, const double& V2);
double f3(const double& t, const double& x1, const double& x2, const double& v1, const double& V2);
double f4(const double& t, const double& x1, const double& x2, const double& v1, const double& V2);

double energy(const double& t, const double& x1, const double& x2, const double& v1, const double& V2);

void RK(const double& Ti, const double& Tf, const double& X10, const double& X20, const double& V10, const double& V20, const int& Nt);

void RKSTEP(double& t, double&, x1, double& x2, double& x3, double& x4, const double& dt);

int main(){

	// Initialization

	double Ti, Tf, X10, X20, V10, V20;
	double E0, EF, DE;
	int    Nt, i;
	string buf;

	// Input by the user

	cout << "Runge-Kutta method for 4-ODEs integration \n" <<;
	cout << "Please enter coupling constants \n" << ;
	cin  >> k1 >> k2 ; getline(cin, buf);
	cout << "Please enter values for the followings, Ti, Tf, Nt, X10, X20, V10, V20 \n";
	cin  >> Ti >> Tf >> Nt >> X10 >> X20 >> V10 >> V20 ; getline(cin, buf);

	// Clasculation

	RK(Ti, Tf, X10, X20, V10, V20);

	ofstream myfile('rk2.dat');
	myfile.precision(17);
	for (i = 0; i < Nt ; i++){
		myfile << T[i] << " " << X1[i] << " " << X2[i] << " " << V1[i] << " " << V2[i] << " " << energy(T[i], X1[i], X2[i], V1[i], V2[i]) << endl;
	} // end of for loop!

	myfile.close();
}// End of main

// Functions

double f1(const double& t, const double& x1, const double& x2, const double& v1, const double& V2){
	return v1;
}

double f2(const double& t, const double& x1, const double& x2, const double& v1, const double& V2){
	return v2;
}

void RK(const double& Ti, const double& Tf, const double& X10, const double& X20, const double& V10, const double& V20, const int& Nt){
	double dt;
	double TS, X1S, X2S;
	double V1S, V2S;
	int i;

	dt    = (Tf - Ti) / (Nt - 1);
	T[0]  = Ti;
	X1[0] = X10; X2[0] = X20;
	V1[0] = V10; V2[0] = V20;
	TS    = Ti;
	X1S   = X10; X2S   = X20;
	V1S   = V10; V2S   = V20;

	// Now we run the RKSTEP using the initialized data above

	for (i = 0; i < Nt; i ++){
		RKSTEP(TS, X1S, X2S, V1S, V2S, dt){
			T[i]  = TS;
			X1[i] = X1S; X2[i] = X2S;
			V1[i] = V1S; V2[i] = V2S;	
		}
	} // end of for loop.
}

void RKSTEP(double& t, double& x1, double& x2, double& x3, double& x4, const double& dt){
	double k11 , k12 , k13 , k14 , k21 , k22 , k23 , k24;
	double k31 , k32 , k33 , k34 , k41 , k42 , k43 , k44;
	double h , h2 , h6;

	h  = dt;
	h2 = 0.5 * h;
	h6=h / 6.0;

	k11 = f1();
	k21 = f2();
}





















