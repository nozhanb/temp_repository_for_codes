
#include <cmath>
#include <string>
#include <cstdlib>
#include <iostream>


// Declaring global variables

const int P = 32;
double X[P], H[P];

// Declaring a global function

double comSimpson(const double& initial, const double& final, const int& N);

int main(){
    
    // Declaring variables

    int initial = 0, final = 1, points = 0, N = 0.0;
    double   dt = 0.0, dh = 0.0, answer = 0.0, a = 0, b = 0;
    std::string buf;
    std::cout << "Please enter the begining of the interval: " << std::endl;
    std::cin  >> a ; getline(std::cin, buf);
    std::cout << "Please enter the end of interva: " << std::endl;
    std::cin  >> b ; getline(std::cin, buf);
    std::cout << "Pleaes enter the number of intervals (one of 3, 7, 15, and 31)" << std::endl;
    std::cin  >> N ; getline(std::cin, buf);

    dt = (b - a)/N; // This line is only for the sake of part "C" of this exercise!
    
    answer = comSimpson(a, b, N);

    std::cout << "The answer is: " << answer << " and this is the 'h' value: " << dt <<std::endl;

} // end of main!

double comSimpson(const double& initial, const double& final, const int& N){
    
    int              i = 0;
    double          dh = 0.0, sum = 0.0, pi = 3.14, H1 = 0.0, H2 = 0.0, H3 = 0.0;
    double lastTermSum = 0.0, lastTermOne = 0.0, lastTermTwo = 0.0, lastTermThree = 0.0;
    double     termOne = 0.0, termTwo = 0.0, termThree = 0.0;
    double   finalSum  = 0.0, tempSumTwo = 0.0, tempSumThree = 0.0 , evenSum = 0.0;

    dh      = (final - initial)/N; // Size of each step.
    //counter   = (N - 1)/2;
    termOne = sin(pi * initial);   // because sin(0) = 0.0 so we start for from 1
    H2      = dh;
    H3      = 2 * dh;
    for(i = 1; i < N/2; i++){
        termTwo       = sin(pi * H2);
        termThree     = sin(pi * H3);
        tempSumTwo   += termTwo;
        tempSumThree += termThree;
        H1 = H3;
        H2 = H2 + (2 * dh);
        H3 = H3 + (2 * dh);
    } // end of for loop!

    evenSum = (dh/3) * (termOne + 4 * tempSumTwo + 2 * tempSumThree);

    // Calculating the last slab separately!
    H1 = H2;
    H2 = H3;
    H3 = final;
    lastTermOne   =   - sin(pi * H1);
    lastTermTwo   = 8 * sin(pi * H2);
    lastTermThree = 5 * sin(pi * H3);
    lastTermSum   = (dh/12) * (lastTermOne + lastTermTwo + lastTermThree);

    finalSum = evenSum + lastTermSum;
    return finalSum;
}