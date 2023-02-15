// I wrote this code to make sure I understand the concept of Runge-kutta 4th order and its implementation.
// It seems to be working but the results need to be verified!

// September 1, 2020
// Nozhan

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
// Global variable declaration

const int N = 50000;

double T[N], theta[N], omega[N], accel[N], energy[N];

// Function declaration

double fv(const int &G, const int &L, const double &angle);
double fx(const double &vel);
void RK(const double& final, const double& Nt, const double& initial_theta, const double& l, const double& m, const double& v0, const int& g);


int main(){

    int  i = 0, Nt = 0, g = 10;
    double initial = 0.0, final = 0.0, h = 0.0;
    double l = 0.0, m = 0.0, v0 = 0.0, initial_theta = 0.0;
    const double pi = 3.14159265;
    string buf;

    cout << "Pleaes enter the initial theta: " << endl;
    cin  >> initial_theta;
    cout << "Please enter a value for final time (initial time is 0): " << endl;
    cin  >> final;
    cout << "Number of steps: " << endl;
    cin  >> Nt;
    cout << "Please enter length of pendulum, mass of bob, and initial velocity:" << endl;
    cin  >> l >> m >> v0; getline(cin, buf);
    cout << "These are l, m, and v0 values " << l << m << v0 << endl;

    if(Nt >= N){
    	cerr << "Number of steps is greater than allocated memory N!" << endl;
    	exit(1);
    }

    ofstream myfile("pendulum_Runge_Kutta_4th.csv");
    myfile.precision(17);

    RK(final, Nt, initial_theta, l, m, v0, g);

    for (i = 0; i <= Nt; i++){

    	myfile << T[i] << "," << theta[i] * (180.0/pi) << "," << omega[i] << "," <<energy[i] << endl;
    }

    myfile.close();

} // main


double fv(const int &G, const int &L, const double &angle){
    double value = 0.0;
    value = - 1 * (G/L) * sin(angle);
    return value;
};

double fx(const double &vel){
    return vel;
};

void RK(const double& final, const double& Nt, const double& initial_theta, const double& l, const double& m, const double& v0, const int& g){

	int j    = 0;
	double h = 0.0, theta_half = 0.0, omega_half = 0.0, coeff = 0.0;
	double kinetic = 0.0, potential = 0.0;
	const double pi = 3.14159265;
    const int G = 10, L = 10;

    double k1omega = 0.0, k2omega = 0.0, k3omega = 0.0, k4omega = 0.0;
    double k1th    = 0.0, k2th    = 0.0, k3th    = 0.0, k4th    = 0.0;

    h = final/Nt;
    theta[0]  = initial_theta * (pi/180.0);
    omega[0]  = v0;
    T[0]      = 0.0;
    coeff     = - 1  * (g/l);
    kinetic   = 0.5  * m * l * l;
    potential = m    * g * l;
    energy[0] = (kinetic * omega[0] * omega[0]) + (potential * (1 - cos(theta[0])));

	for(j = 1; j  <= Nt; j++){
        T[j]       = T[j - 1]     + h;
        
        k1omega  = fv(G, L, theta[j - 1]);
        k2omega  = fv(G, L, theta[j - 1] + 0.5 * k1omega);
        k3omega  = fv(G, L, theta[j - 1] + 0.5 * k2omega);
        k4omega  = fv(G, L, theta[j - 1] + k3omega);

        omega[j] = omega[j - 1] + (k1omega + 2 * k2omega + 2 * k3omega + k4omega)/6.0;

        k1th     = fx(omega[j - 1]);
        k2th     = fx(omega[j - 1] + 0.5 * k1th);
        k3th     = fx(omega[j - 1] + 0.5 * k2th);
        k4th     = fx(omega[j - 1] + k3th);

        theta[j] = theta[j - 1] + (k1th + 2 * k2th + 2  * k3th + k4th)/6.0; 

        energy[j]  = (kinetic   * omega[j]  * omega[j]) + (potential * (1 - cos(theta[j]))); // I am not sure whether I should use omega[j - 1] or omega[j]!

        // if(theta[j] * theta[j - 1] <= 0.0){
        // 	cout << "This is period (T[j]): " << 0.5 * (T[j] + T[j - 1])<< endl;
        // }

	}
}















