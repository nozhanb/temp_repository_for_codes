// Homework 1, exercise 2, partb.

// Nozhan
// July 14, 2020

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>


// Global Declaration

const int P = 10000;
double X[P], Y[P], T[P], U[P];

// Function Declaration

double integral(double &lower, const double &dt, const int Nt);
double halfInt(double &lower, const double &dh, const int Np);
// Body

int main(){
    
    // Declaration
    
    double lower = 0., upper = 0., dt = 0., answerInt = 0., answerHalf = 0., final = 0., dh = 0.;
    int i = 0, Nt = 0, Np = 0;
    std::string buf;

    std::cout << "Enter the lower bound: " << std::endl;
    std::cin  >> lower; getline(std::cin, buf);
    std::cout << "Enter the upper bound: " << std::endl;
    std::cin  >> upper; getline(std::cin, buf);
    std::cout << "Enter number of steps: " << std::endl;
    std::cin  >> Nt; getline(std::cin, buf);
    Np = 2 * Nt;
    dt         = (upper - lower)/Nt;
    dh         = (upper - lower)/(Np);
    answerInt  = integral(lower, dt , Nt);
    answerHalf = halfInt(lower, dh , Np);
    final      = (1./3.) * (answerHalf - answerInt);
    std::cout << "This is the result of Ih: " << answerInt << std::endl;
    std::cout << "This is the result of Ih/2: " << answerHalf << std::endl;
    std::cout << "This is (1/3) * (Ih2 - Ih) or error of Ih/2: " << final << std::endl;

} // main

double integral(double &lower, const double &dt, const int Nt){

	// Declaration
    double sum = 0.;
    int i = 0;
    // Body
    X[0] = lower;
    T[0] = X[0];
    // We are using the Trapezoid integration rule so we need to add Nt - 1!
    for(i = 0; i < Nt - 1; i++){
    	T[i + 1] = T[i] + dt;
    	X[i]     = T[i] + T[i + 1];
    	T[i]     = T[i + 1];
        sum     += X[i];
    }
    return ((dt/2.) * sum);
} //original

double halfInt(double &lower, const double &dh, const int Np){

	// Declaration
    double sum = 0.;
    int i = 0;
    // Body
    Y[0] = lower;
    U[0] = Y[0];
    // We are using the Trapezoid integration rule so we need to add Np - 1!
    // I am adding this line some days later! I an not sure why i starts from 0. Should it not start from 1? It is the trapezoid rule after all!!
    for(i = 0; i < Np - 1; i++){
    	U[i + 1] = U[i] + dh;
    	Y[i]     = U[i] + U[i + 1];
    	U[i]     = U[i  + 1];
        sum     += Y[i];
    }
    return ((dh/2.) * sum);
} // half Integral



