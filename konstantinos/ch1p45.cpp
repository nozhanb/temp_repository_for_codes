// program to compute the root of a given 2nd degree polynomial

// April 24, 2020

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

double Discriminant(double a, double b, double c);
void   roots(double a, double b, double c, double &x1, double &x2);

int main()
{
	double a, b, c, D;
	double x1, x2;

	cout << "Enter a, b, c ";
	cin  >> a >> b >> c;
	cout << "You entered a = " << a << " b = " << b << " c = " << c << "\n";

	// Test if we have a well defined 2nd degree polynomial.
	if(a == 0.0)
	{
		cerr << "Terionymo: a cannot be 0!\n";
		exit(1);
	}

	// Compute the discriminant
	D = Discriminant(a, b, c);
	cout << "Discriminant D = " << D << "\n";

	// Compute the roor in all cases of D < 0 (no roots), D = 0, and D > 0

	if     (D > 0.0)
	{
		roots(a, b, c, x1, x2);
		cout << " and root x1 = " << x1 << " x2 = " << x2 << "\n";
	}

	else if(D == 0.0)
	{
		roots(a, b, c, x1, x2);
		cout << " and root x1 = x2 = " << x1 << "'\n";
	}

	else
	{
		cout << " , No real roots!" << "\n";
		exit(1);
	}
}

// You can see the body of the functions here.

double Discriminant(double a, double b, double c)
{
	return b * b - 4.0 * a * c;
}

void roots(double a, double b, double c, double& x1, double& x2)
{
	double D;

	D = Discriminant(a, b, c);
	if  (D >= 0.0)
	{
		D = sqrt(D);
	}
	else
	{
		cerr << " roots: Sorry, cannot compute roots, D < 0 = " << D << "\n";
	}

	x1 = (- b + D)/(2.0 * a);
	x2 = (- b - D)/(2.0 * a);
}



