// I made a minor mistake but it took me quite some time figure my mistake out. The mistake was unit conversion from degree to radian. I figure
// my mistake thanks to garcia's book! ...

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// Global position, velocity, and acceleration vectors

const int N = 10000;
double    theta[N], theta_ra[N], omega[N], energy[N], T[N], K[N], P[N];

// Global function declaration

void euler(const double& initial_theta, const double& initial_velocity, const double& dt, const int& Nt, const int& g, const int& length, const double& mass);
void eulerCromer(const double& initial_theta, const double& initial_velocity, const double& dt, const int& Nt, const int& g, const int& length, const double& mass);
// double velocity(const double& initial_velocity, const double& dt);
// double acceleration(const double& initial_theta, const double& dt);


int main(){

	// Local variable declaration
    int length = 10, g = 10, Nt = 0, i = 0;
    double initial_theta = 0.0, initial_velocity = 0.0;
    double t_final = 0.0, dt = 0.0, mass = 0.0;
    string buf;

    cout << "Please enter a value for the initial angle: " << endl;
    cin  >> initial_theta; getline(cin, buf);
    cout << "Please enter a value for the initial velocity of the bob: " << endl;
    cin  >> initial_velocity; getline(cin, buf);
    cout << "Please enter a value for mass of the bob: " << endl;
    cin  >> mass; getline(cin, buf);
    cout << "Please enter your time interval (dt): " << endl;
    cin  >> dt; getline(cin, buf);
    cout << "Please enter the end of your time interval (the beginning is set to 0): " << endl;
    cin  >> t_final; getline(cin, buf);

    Nt = t_final/dt; // length of each time interval

	// open a file to write into
	ofstream myfile("euler10Deg.csv");
    // myfile.open("euler10Deg.dat");
    myfile.precision(17);

    euler(initial_theta, initial_velocity, dt, Nt, g, length, mass);

    for(i = 0; i <= Nt; i ++){
    	myfile << T[i] << "," << theta[i] << "," << omega[i] << "," << energy[i] << "," << K[i] << "," << P[i] << endl;
    }
    myfile.close();


    // Euler-Cromer Method

    myfile.open("eulerCromer10Deg.csv");
    myfile.precision(17);
    eulerCromer(initial_theta, initial_velocity, dt, Nt, g, length, mass);

    for(i = 0; i <= Nt; i++){
    	myfile << T[i] << "," << theta[i] << "," << omega[i] <<  "," << energy[i] << "," << K[i] << "," << P[i] << endl;
    }

    myfile.close();

} // main


void euler(const double& initial_theta, const double& initial_velocity, const double& dt, const int& Nt, const int& g, const int& length, const double& mass){

    double    coeff = 0.0, kinetic = 0.0, potential = 0.0;
    int           j = 0;
    const double pi = 3.14159265;

    theta_ra[0] = initial_theta * (pi/180.0);
    theta[0]  = initial_theta;
    omega[0]  = initial_velocity;
    T[0]      = 0.0;
    coeff     = - 1  * (g/length);
    kinetic   = 0.5  * mass * length   * length;
    potential = mass * g    * length;
    K[0]      = kinetic     * omega[0] * omega[0];
    P[0]      = potential   * (1 - cos(theta_ra[0]));
    energy[0] = (kinetic    * omega[0] * omega[0]) + (potential * (1 - cos(theta_ra[0])));
    for (j    = 1; j <= Nt; j++ ){
    	T[j]  = T[j - 1] + dt;
        omega[j]    = omega[j - 1]    + dt * coeff * sin(theta_ra[j - 1]);
        theta_ra[j] = theta_ra[j - 1] + dt * omega[j - 1];
        theta[j]    = theta_ra[j]     * (180.0/pi); // converting radian to degree!
        if(theta[j] * theta[j - 1] <= 0.0){
        	cout << "This is T[j]: " << 0.5 * (T[j] + T[j - 1]) << endl;
        }

        K[j]        = kinetic * omega[j - 1] * omega[j - 1];
        P[j]        = potential * (1 - cos(theta_ra[j - 1]));
        energy[j]   = (kinetic * omega[ j - 1] * omega[j - 1]) + (potential * (1 - cos(theta_ra[j - 1]))); // I am not sure if this equation of energy is correct or not!
        // energy[j]   = energy[j - 1] + mass * g * length * 0.5 * ((g/length) * (theta_ra[j - 1] * theta_ra[j - 1]) + omega[j - 1] * omega[j - 1]) * dt * dt;
    }
}


void eulerCromer(const double& initial_theta, const double& initial_velocity, const double& dt, const int& Nt, const int& g, const int& length, const double& mass){

    double    coeff = 0.0, kinetic = 0.0, potential = 0.0;
    int           j = 0;
    const double pi = 3.14159265;

    theta_ra[0] = initial_theta * (pi/180.0);
    theta[0]  = initial_theta;
    omega[0]  = initial_velocity;
    T[0]      = 0.0;
    coeff     = - 1   * (g/length);
    kinetic   = 0.5   * mass * length   * length;
    potential = mass  * g    * length;
    K[0]      = kinetic      * omega[0] * omega[0];
    P[0]      = potential    * (1 - cos(theta_ra[0]));
    energy[0] = (kinetic     * omega[0] * omega[0]) + (potential * (1 - cos(theta_ra[0])));
    for (j    = 1; j <= Nt; j++ ){
    	T[j]  = T[j - 1] + dt;
        omega[j]    = omega[j - 1]    + dt * coeff * sin(theta_ra[j - 1]);
        theta_ra[j] = theta_ra[j - 1] + dt * omega[j]; // Here we changed omega[j - 1] to omega[j] to use the Euler-Cromer method.
        theta[j]    = theta_ra[j]     * (180.0/pi);     // converting radian to degree!

        K[j]     = kinetic   * omega[j] * omega[j];
        P[j]     = potential * (1 - cos(theta_ra[j]));
        energy[j]= (kinetic  * omega[j] * omega[j]) + (potential * (1 - cos(theta_ra[j]))); // I am not sure if this equation of energy is correct or not!
        // energy[j]   = energy[j - 1] + mass * g * length * 0.5 * ((g/length) * (theta_ra[j - 1] * theta_ra[j - 1]) + omega[j - 1] * omega[j - 1]) * dt * dt;
    }
}
