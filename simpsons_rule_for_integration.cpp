// An implementation of a three-point Simpson's rule for integration.

// Septemeber 08, 2021
// Nozhan 

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <array>

// Initialising the function

double simpson_rule(const double a, const double b, const int N, double *F);


// Defining the main block.

int main(){
    // We initiate the arguments!
    int         N = 0;
    double      a = 0.0, b = 0.0;
    double answer = 0.0;
    double *F = new double[100000];
    std::string buf;

    // We take the values of a and b from the user.
    std::cout << "Enter your a value: " << std::endl;
    std::cin  >> a; getline(std::cin, buf);
    std::cout << "Enter your b value: " << std::endl;
    std::cin  >> b; getline(std::cin, buf);
    std::cout << "Enter the number of interval (N):" << std::endl;
    std::cin  >> N; getline(std::cin, buf);

    answer = simpson_rule(a, b, N, F);

    std::cout << "This is the answer: " << std::endl;
    std::cout << answer << std::endl;

    return 0;
}

// Defining the function.

double simpson_rule(const double a, const double b, const int N, double *F){
    
    int i = 0, j = 0;
    double dx    = 0.0;
    double temp  = 0.0, answer2 = 0.0;

    dx = (b - a)/N;

    std::cout << "This is dx ---> " << dx << std::endl;
    std::cout << "This is sin (pi/3) ---> " << sin(3.14/3.) << std::endl;

    F[0] = sin(a) * sin(a) + 4 * sin(a + dx) * sin(a + dx) + sin(a + 2 * dx) * sin(a + 2 * dx);

    for(i = 1; i < N/2 - 1; i++){
  
        F[i] =  sin(2 * i * dx) * sin(2 * i * dx) + 4 * sin((2 * i + 1) * dx) * sin((2 * i + 1) * dx) + sin((2 * i + 2) * dx) * sin((2 * i + 2) * dx);
    }
    
    for(j = 0; j < N; j++){
    	temp   = F[j];
    	answer2 = answer2 + temp;
    }
    return answer2 * (dx/3.0);
}