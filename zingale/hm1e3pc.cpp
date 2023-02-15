// Homework 1, exercise 3 part C.
// Based on my code it seems that the final value of our integral depends on the value of "a" assuming we set 
// C to (a - 1). Setting a to 2 the integral becomes 1, and setting a to 4 the integral becomes 3 and so on!x

// Nozhan, 24 July, 2020

#include <cmath>
#include <cstdlib>
#include <string>
#include <iostream>


// Declaration of global varibales

const int P = 500;
double Z[P], Y[P];

// Declaration of a global function

double gamma(int &a, const double &c, double &x, double &start, double &end, const double &dt, const int &N);

int main(){
    
    int N = 0, a = 0;
    double start = 0.0, end = 0.0, dt = 0.0, c = 0.0, z = 0.0, x = 0.0, answer = 0.0;
    std::string buf;

    std::cout << "please type in the beginning of the interval: " << std::endl;
    std::cin  >> start; getline(std::cin, buf);
    std::cout << "Please type in the end of your interval: " << std::endl;
    std::cin  >> end; getline(std::cin, buf);
    std::cout << "please type in the number of intervals: " << std::endl;
    std::cin  >> N; getline(std::cin, buf);
    std::cout << "pleae enter a value for the constant 'a' (it must fall in the interval (a value above 1): " << std::endl;
    std::cin  >> a; getline(std::cin, buf);

    dt = (end - start)/N;
    a  = 2.;
    c  = a - 1;
    x  = 0.0;
    answer = gamma(a, c, x, start, end, dt, N);

    std::cout << "This is your answer: " << answer << std::endl;

} // main

double gamma(int &a, const double &c, double &x, double &start, double &end, const double &dt, const int &N){

    // Remember that the true form of the function is as follows,

    // ((a - 1)*Z[i]/(1. - Z[i])) * ((a - 1)*Z[i]/(1. - Z[i]))* ... * exp(-((a - 1)*Z[i]/(1. - Z[i]))) * ((a - 1)./((1. - Z[i]) * (1. - Z[i])));

    // Where the ... part indicates the repetition of ((a - 1)*Z[i]/(1. - Z[i])) term as many times as it is the result of (a - 1). Because, the 
    // ((a - 1)*Z[i]/(1. - Z[i])) term is raised to the power of (a - 1). So if you give a the value 4 then a - 1 = 3 then one has to multiply
    // ((a - 1)*Z[i]/(1. - Z[i])) three times by itself!!! Also, note that the value of Y[0] always equals to 0 as long as we set the lower limit 
    // of our integral to 0.
    int i  = 0;
    double sum = 0.0;
    Z[0] = start;
    Y[0] = (2*Z[0]/(1. - Z[0])) * (2*Z[0]/(1. - Z[0])) * exp(-(2*Z[0]/(1. - Z[0]))) * (2./((1. - Z[0]) * (1. - Z[0])));;
    // We use the composite trapezoid rule!
    for (i = 1; i < N - 1; i++){
    	Z[i]     = Z[i - 1] + dt;
        Y[i]     = (2*Z[i]/(1. - Z[i])) * (2*Z[i]/(1. - Z[i])) * exp(-(2*Z[i]/(1. - Z[i]))) * (2./((1. - Z[i]) * (1. - Z[i])));
        sum     += Y[i];
    }
    return ((1/2.) * dt) * (Y[0] + Y[N - 1] + 2 * sum);
}