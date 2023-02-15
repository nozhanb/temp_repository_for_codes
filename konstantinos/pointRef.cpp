// Just a few tests of pointers and references!
//
// May 19, 2020

#include <iostream>
#include <cassert>
#include <typeinfo>
#include <fstream>

using namespace std;

void RK(double& w);

int main(){
	int L = 5;
	int i;
	double T[L];
	double XS;
	int x   = 1;
	int &r  = x;
	int *p  = &x;
	int *p2 = &r;
	int t   = *p;
	assert(p == p2);

	std::cout << "x   = "   << x  << "\n";
	std::cout << "&r  = x  ---> "  << &r << "\n";
	std::cout << "*p  = &x ---> " << *p << "\n";
	std::cout << "P   = ===>    " << p <<"\n";
	std::cout << "*p2 = &r ---> " << *p2<< "\n";
	std::cout << "t   =   " << t  << "\n";
	std::cout << "r   =   " << r  << "\n";
	std::cout << "type of &r ---> " << " " << typeid(&r).name() << "\n";
	std::cout << "type of p  ---> " << " " << typeid(p).name()  << "\n";
	std::cout << "type of *p ---> " << " " << typeid(*p).name() << "\n";

	ofstream myfile("referenceTest.dat");
	myfile.precision(8);

	XS = 0;
	for(i = 0; i < 5; i ++){
		RK(XS);
		T[i] = XS;
		myfile << T[i] << '\n';
	}
	myfile.close();
}
void RK(double& w){
	double dt;
	dt = 0.5;
	w  = w + dt; 
}

