// May 3, 2020

#include <iostream> // err
#include <fstream>  // ofstream myfile()
#include <string>   // string declaration
#include <cmath>
#include <cstdlib> // getline()
#include <iomanip> // precision()

using namespace std;


const double pi = 3.14159265358979324;
int main()
{
	// Declaration
	double Lx, Ly, x0, y0, v0x, v0y, t0, tf, dt, t;
	double x, y, vx, vy, r, cx, cy, v0, theta;
	int i, nx, ny;
	string buf, result;

	// Inputs by the user
	cout << "Enter Lx, Ly: " << "\n";
	cin  >> Lx >> Ly; getline(cin, buf);
	cout << "Enter x0, y0: " << "\n";
	cin  >> x0 >> y0; getline(cin, buf);
	cout << "Enter v0: " << "\n";
	cin  >> v0; getline(cin, buf);
	cout << "Enter t0, tf, dt: " << "\n";
	cin  >> t0 >> tf >> dt; getline(cin, buf);
	cout << "Enter theta (in degrees): " << "\n";
	cin  >> theta; getline(cin, buf);
	cout << "Enter Cx, Cy, and radius R: " << "\n";
	cin  >> cx >> cy >> r; getline(cin, buf);

	cout << "I assume you know what you have entered so I will not do any checkings!" << "\n";

	// Initialization

	t = t0;
	x = x0;
	y = y0;
	i = 0;
	nx = 0;
	ny = 0;
	theta = (pi/180.0) * theta;
	vx = v0 * cos(theta);
	vy = v0 * sin(theta);
	ofstream myfile("minigolf.dat");
	myfile.precision(17);

	// Computation
	while(t < tf)
	{
		myfile << setw(28) << t << " " << setw(28) << x << " " 
		<< setw(28) << y << " " << setw(vx) << vx << " " 
		<< setw(28) << vy << "\n";
		i++;
		t = t0 + i * dt;
		x = x + vx * dt;
		y = y + vy * dt;
		if(x > Lx)
		{
			vx = -vx;
			nx++;
		}
		if(y > Ly || y < 0.0)
		{
			vy = -vy;
			ny++;
		}
		if(x < 0.0)
		{
			result = "Failure"; 
			break;
		}
		if((x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r)
		{
			result = "Winner";
			break;
		}
	}
	myfile.close();
	cout << "Result and number of collisions: " << "\n";
	cout << "Result = " << result << "nx = " << nx << "ny = " << ny << "\n";
}

