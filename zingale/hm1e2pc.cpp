
// Homework 1, exercise 2, partb.
// There are a few things I am confused about! I am using the equation 6 in the homework 1 sheet! Is that the right equation?
// Next, I am not sure what value I should use for C in that equation?
// Also, I am not sure whether I should round up or down in my "Nt = ((upper - lower)/dt)"!
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

// Body

int main(){
    
    // Declaration
    
    double lower = 0., upper = 0., dt = 0., answerInt = 0., err = 0., c = 0.;
    int i = 0, Nt = 0, Np = 0;
    std::string buf;

    std::cout << "Enter the lower bound: " << std::endl;
    std::cin  >> lower; getline(std::cin, buf);
    std::cout << "Enter the upper bound: " << std::endl;
    std::cin  >> upper; getline(std::cin, buf);
    std::cout << "Enter your error threshold: " << std::endl;
    std::cin  >> err; getline(std::cin, buf);
    c          = lower + (upper - lower)/2.;
    dt         = sqrt(err/c);
    Nt         = ((upper - lower)/dt);
    answerInt  = integral(lower, dt , Nt);
    std::cout << "Your required number of intervals is: " << Nt << std::endl;
    std::cout << "This is your result: " << answerInt << std::endl;

} // main

double integral(double &lower, const double &dt, const int Nt){

	// Declaration
    double sum = 0.;
    int i = 0;
    // Body
    X[0] = lower;
    T[0] = X[0];
    // I am not sure if I should subtract one from Nt or not in the loop condition part!
    for(i = 0; i < Nt - 1; i++){
    	T[i + 1] = T[i] + dt;
    	X[i]     = T[i] + T[i + 1];
    	T[i]     = T[i + 1];
        sum     += X[i];
    }
    return ((dt/2.) * sum);

} //original



