

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>


// Function Delaration

double root1(const double &a, const int &b, const double &c);
double root2(const double &a, const int &b, const double &c);
double root3(const double &a, const int &b, const double &c);
double root4(const double &a, const int &b, const double &c);

int main(){

// Declaration
    const double a = 0.001 , c = 0.001;
    double root = 0., answer1 = 0., answer2 = 0., answer3 = 0., answer4 = 0.;
    const int b = 1000;
    std::string buf;

// Body

    answer1 = root1(a, b, c);
    answer2 = root2(a, b, c);
    answer3 = root3(a, b, c);
    answer4 = root4(a, b, c);
    std::cout << "This is root 1 (-b + sqrt): " << answer1 << std::endl;
	std::cout << "This is root 2 (-b - sqrt): " << answer2 << std::endl;
	std::cout << "This is root 3 (1)/(-b - sqrt): " << answer3 << std::endl;
	std::cout << "This is root 4 (1)/(-b + sqrt): " << answer4 << std::endl;
} // main

double root1(const double &a, const int &b, const double &c){

    double root = 0;
	root = (-b + sqrt(((b * b) - 4 * a * c)))/(2 * a);
    
    return root;
}

double root2(const double &a, const int &b, const double &c){

    double root = 0;
	root = (-b - sqrt(((b * b) - 4 * a * c)))/(2 * a);
    
    return root;
}

double root3(const double &a, const int &b, const double &c){

    double root = 0;
	root = (2 * c)/(-b - sqrt(((b * b) - 4 * a * c)));
    
    return root;
}

double root4(const double &a, const int &b, const double &c){

    double root = 0;
	root = (2 * c)/(-b + sqrt(((b * b) - 4 * a * c)));
    
    return root;
}