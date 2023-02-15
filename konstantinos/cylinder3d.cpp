// May 5, 2020

#include <iostream> // err
#include <fstream>  // ofstream myfile()
#include <string>   // string declaration
#include <cmath>
#include <cstdlib> // getline()
#include <iomanip> // precision()

using namespace std;

void reflectVonCircle(double& vx, double& vy, double& x, double& y,
			const double& xc, const double& yc, const double& R);

int main()
{
	// Declaration
	double x0, y0, z0, v0x, v0y, v0z, t0, tf, dt, t;
	double x, y, z, vx, vy, vz, R, xc, yc, L, vxy, rxy;
	int i, nr, nz;
	string buf;

	// Inputs by the user
	cout << "Enter Height and Radius of the cylinder:"<< "\n";
	cin  >> L >> R; getline(cin, buf);
	cout << "Enter x0, y0, z0: " << "\n";
	cin  >> x0 >> y0 >> z0; getline(cin, buf);
	cout << "Enter v0x, v0y, v0z: " << "\n";
	cin  >> v0x >> v0y >> v0z; getline(cin, buf);
	cout << "Enter t0, tf, dt: " << "\n";
	cin  >> t0 >> tf >> dt; getline(cin, buf);
	rxy = sqrt(x0 * x0 + y0 * y0); // Distance in the x-y plane!
	if(rxy > R)
	{
		cerr << "x0, y0 are located beyond the radius of the cylinder!" << "\n";
		exit(1);
	}

	cout << "I assume you know what you have entered so I will not do any checkings!" << "\n";

	// Initialization
	i = 0;
	nr= 0;
	nz = 0;
	t = t0;
	x = x0;
	y = y0;
	z = z0;
	vx = v0x;
	vy = v0y;
	vz = v0z;
	xc = 0.0;
	yc = 0.0;
	ofstream myfile("cylinder3d.dat");
	myfile.precision(17);

	// Computation
	while(t <= tf)
	{
		myfile << setw(28) << t << " " << setw(28) << x << " " << setw(28) << y << " " << setw(28) << z << " " <<
			      setw(28) << vx << " " << setw(28) << vy << " " << setw(28) << vz << "\n";
		i++ ;
		t = t0 + i  * dt;
		x = x  + vx * dt ;
		y = y  + vy * dt ;
		z = z  + vz * dt ;
		if(z > L || z < 0.0)
		{
			vz = -vz;
			nz++;
		}
		if(((x * x) + (y * y)) > R * R)
		{
			reflectVonCircle(vx, vy, x, y, xc, yc, R);
			nr++;
		}
	}
	myfile.close();
	cout << "# Number of collisions :\n";
	cout << "# nr= " << nr << " nz= " << nz << endl;
} //main
//________________________________________________________________________________________________________________________
 
//============================================================
//________________________________________________________________________________________________________________________

void reflectVonCircle(double& vx, double& vy, double& x, double& y, const double& xc, const double& yc, const double& R)
{
	double theta, cth, sth, vr, vth;
	theta = atan2(y - yc, x - xc);

	cth = cos(theta);
	sth = sin(theta);

	vr  = vx  * cth + vy  * sth;
	vth = -vx * sth + vy  * cth;

	vx  = -vr * cth - vth * sth;
	vy  = -vr * sth + vth * cth;

	x   = xc  +         R * cth;
	y   = yc  +         R * sth;
} // reflectVonCircle
