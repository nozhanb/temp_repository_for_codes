// May 2, 2020

#include <iostream>
#include <iomanip> // setprecision()
#include <fstream> // iofstream myfile()
#include <cstdlib> //
#include <string>  //
#include <cmath>

using namespace std;

int main()
{
	// Declaration
	double Lx, Ly, x0, y0, vx0, vy0, t0, tf, dt, t, x, y, vx, vy;
	int    i, nx, ny;
	string buf;

	// Inputs from the user

	cout << "Enter Lx, Ly:" << "\n";
	cin  >> Lx >> Ly; getline(cin, buf);
	cout << "Enter x0, y0: " << "\n";
	cin  >> x0 >> y0; getline(cin, buf);
	cout << "Enter vx0, vy0: " << "\n";
	cin  >> vx0 >> vy0; getline(cin, buf);
	cout << "Enter t0, tf, dt: " << "\n";
	cin  >> t0 >> tf >> dt; getline(cin, buf);

	// Check the validy of the input parameters

	if(Lx <= 0.0 || Ly <= 0.0)
	{
		cerr << "The length of the well cannot be zero or negative!" << "\n";
		exit(1);
 	}
 	if(vx0*vx0 + vy0*vy0 == 0.0)
 	{
 		cerr << "Initial velocities cannot be zero!" << "\n";
 		exit(1);
 	}

 	// Initialization
 	i  = 0;
 	nx = 0;
 	ny = 0;
 	t  = t0;
 	x  = x0;
 	y  = y0;
 	vx = vx0;
 	vy = vy0;
 	ofstream myfile("2dBox.dat");
 	myfile.precision(17);
 	// Computation

 	while(t <= tf)
 	{
 		myfile << setw(28) << t << " " << setw(28) << x << " " << setw(28) << y << " " << setw(28) << vx << " " << setw(28) << vy << "\n";
 		i += 1;
 		t = t0 + i  * dt;
 		x = x  + vx * dt;
 		y = y  + vy * dt;
 		
 		if(x > Lx || x < 0.0)
 		{
 			vx = -vx;
 			nx += 1 ;
 		}
 		if(y > Ly || y < 0.0)
 		{
 			vy = -vy;
 			ny ++;
 		}
 	}
 	myfile.close();
 	cout << "Number of collisions: " << "\n";
 	cout << "nx = " << nx << ", ny = " << ny << endl;
 }