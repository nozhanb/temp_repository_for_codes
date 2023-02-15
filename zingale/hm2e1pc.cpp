
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

void leapFrog(const double& final, const double& Nt, const double& initial_theta, const double& l, const double& m, const double& v0, const int& g);

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

    ofstream myfile("leapfrog10DegDt1to1000.csv");
    myfile.precision(17);

    leapFrog(final, Nt, initial_theta, l, m, v0, g);

    for (i = 0; i <= Nt; i++){

    	myfile << T[i] << "," << theta[i] * (180.0/pi) << "," << omega[i] << "," <<energy[i] << endl;
    }

    myfile.close();

} // main



void leapFrog(const double& final, const double& Nt, const double& initial_theta, const double& l, const double& m, const double& v0, const int& g){

	int j    = 0;
	double h = 0.0, theta_half = 0.0, omega_half = 0.0, coeff = 0.0;
	double kinetic = 0.0, potential = 0.0;
	const double pi = 3.14159265;

    h = final/Nt;
    theta[0]  = initial_theta * (pi/180.0);
    omega[0]  = v0;
    T[0]      = 0.0;
    coeff     = - 1  * (g/l);
    kinetic   = 0.5  * m * l * l;
    potential = m    * g * l;
    energy[0] = (kinetic * omega[0] * omega[0]) + (potential * (1 - cos(theta[0])));
    // For the purpose of leapfrog method we need to have the value of dependent variable at times t and t + dt/2.
    // so,
    omega_half = omega[0] + 0.5 * h * coeff * sin(theta[0] * (pi/180.0));
    theta_half = theta[0] + 0.5 * h * omega[0];

	for(j = 1; j  <= Nt; j++){
        T[j]       = T[j - 1]     + h;
        omega[j]   = omega[j - 1] + h * coeff * sin(theta_half); 
        theta[j]   = theta[j - 1] + h * omega_half;
        energy[j]  = (kinetic     * omega[j] * omega[j]) + (potential * (1 - cos(theta[j]))); // I am not sure whether I should use omega[j - 1] or omega[j]!
        omega_half = omega_half   + h * coeff * sin(theta[j]);
        theta_half = theta_half   + h * omega[j];
        if(theta[j] * theta[j - 1] <= 0.0){
        	cout << "This is period (T[j]): " << 0.5 * (T[j] + T[j - 1])<< endl;
        }

	}
}















