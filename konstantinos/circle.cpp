// This code will take the initial valies below from the user and 
// will compute the trajectory and velocity of a particle,

// x, y, vx, vy, t0, R
// omega, theta

// April 25, 2020

#include <iostream>
#include <fstream> // ofstream() function
#include <cstdlib> // getline() function
#include <string>  // string varibles
#include <cmath>   // sin() and cos() functions

using namespace std;

const double PI = 3.1415926535897932;

int main(){
	// -----> Declation of varibles <-----

	double x0, y0, x, y, vx, vy, t, t0, tf, dt, R;
	double theta, omega;
	string buf, response;
	
	// -----> End of declaration of variables <-----

	// *************************

	// -----> User inputs <-----
	response = "N";
	while(response == "N")
	{
		cout << "Enter Omega: " << "\n";
		cin  >> omega; getline(cin, buf);
		cout << "Enter center of circle (x0, y0) and radius R: " << "\n";
		cin  >> x0 >> y0 >> R; getline(cin, buf);
		cout << "Enter t0, dt, tf: " << "\n";
		cin  >> t0 >> dt >> tf; getline(cin, buf);
		cout << "These are the values you entered: " << "\n";
		cout << "Omega = " << omega << "\n";
		cout << "x0 = " << x0 << " , y0 = " << y0 << " , R = " << R << "\n";
		cout << "t0 = " << t0 << " , dt = " << dt << " , tf = " << tf << "\n";
		cout << "Please type in 'Y' if the inserted values are correct and 'N' if you would like to repeat the process!" << "\n";
		cin  >> response;
	}
	// -----> End of user inputs <-----

	// ********************************

	// -----> Checking if the insered values are correct/make sense (e.g. R > 0) <-----
	if(R <= 0.0)
	{
		cerr << "Radius must be a value greater than zero (R > 0)!" << "\n";
		exit(1);
	}
	if(omega <= 0.0)
	{
		cerr << "Oemga must be a value greater than zero (Omega > 0)!" << "\n";
		exit(1);
	}
	// -----> End of checking <-----

	// *****************************

	// -----> Opening output file <-----

	ofstream myfile("circle.dat");
	myfile.precision(17); // setting the precision for numeric output to myfile up to 17 digits

	// -----> End of opening output file <-----

	// *****************************

	// -----> Computation part <-----

	t = t0;
	while(t <= tf)
	{
		x  = x0 + R * cos(omega * (t - t0));
		y  = y0 + R * sin(omega * (t - t0));
		vx = -omega * R * sin(omega * (t - t0));
		vy =  omega * R * cos(omega * (t - t0));
		myfile << t << " " << x << " " << y << " " << vx << " " << vy << endl;
		t = t + dt;
	}

	// -----> End of computation part <-----

	myfile.close(); // closing the file!

}