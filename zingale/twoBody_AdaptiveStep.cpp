// Similar to twoBody.cpp but with Adaptive setp-size method!

// Septemebr 05, 2020
// Nozhan

#include <cstdlib>
#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

// Global Declaration

const int N = 4;
const int MG[3] = { 1, 25, 50}; // Gravity, Mass 1, Mass 2

int single_step(const double *X10, const double *X20, double *X1new, double *X2new, const double dt);
int rhs(const double *X1, const double *X2, double *X1dot, double *X2dot, const int *MG);
int orbit(double *X10, double *X20, const double dt_in, const double tmax);
int orbit_adaptive(double *X10, double *X20, const double dt_in, const double tmax, const double eps);

int main(){

int i = 0;
double dt = 0.0, final_time = 0.0;
const double x10 = 3;
const double y10 = 3;
const double u10 = 1;
const double v10 = 0;

const double x20 = 0;
const double y20 = 0;
const double u20 = 0;
const double v20 = 0;

std::cout << "Please enter the length of your time steps (dt): " << std::endl;
std::cin  >> dt;
std::cout << "Please enter final time (tf): " << std::endl;
std::cin  >> final_time;

// Initial vectors of the two objects.
double X10[N];
  X10[0] = x10;
  X10[1] = y10;
  X10[2] = u10;
  X10[3] = v10;

double X20[N];
  X20[0] = x20;
  X20[1] = y20;
  X20[2] = u20;
  X20[3] = v20;

// orbit(X10, X20, dt, final_time);
orbit_adaptive(X10, X20, dt, final_time, 1.e-7);

} // main 


int single_step(const double *X10, const double *X20, double *X1new, double *X2new, const double dt){

    double k11[N];
    double k12[N];
    double k13[N];
    double k14[N];

    double k21[N];
    double k22[N];
    double k23[N];
    double k24[N];
    
    double xtemp1[N];
    double xtemp2[N];

    rhs(X10, X20, k11, k21, MG);
    for (int j = 0; j < N; j++){
        xtemp1[j] = X10[j] + 0.5 * dt * k11[j];
        xtemp2[j] = X20[j] + 0.5 * dt * k21[j];
    }

    rhs(xtemp1, xtemp2, k12, k22, MG);
    for (int j = 0; j < N; j++){
        xtemp1[j] = X10[j] + 0.5 * dt * k12[j];
        xtemp2[j] = X20[j] + 0.5 * dt * k22[j];
    }

    rhs(xtemp1, xtemp2, k13, k23, MG);
    for(int j = 0; j < N; j++){
        xtemp1[j] = X10[j] + dt * k13[j];
        xtemp2[j] = X20[j] + dt * k23[j];
    }

    rhs(xtemp1, xtemp2, k14, k24, MG);
    for (int j=0; j<N; j++) {
        X1new[j] = X10[j] + (dt/6.0) * (k11[j] + 2 * k12[j] + 2 * k13[j] + k14[j]);
        X2new[j] = X20[j] + (dt/6.0) * (k21[j] + 2 * k22[j] + 2 * k23[j] + k24[j]);
    }
    return 0;
}


int rhs(const double *X1, const double *X2, double *X1dot, double *X2dot, const int *MG){

    int G = MG[0], m1 = MG[1], m2 = MG[2];

    double x1 = X1[0];
    double y1 = X1[1];
    double u1 = X1[2];
    double v1 = X1[3];

    double x2 = X2[0];
    double y2 = X2[1];
    double u2 = X2[2];
    double v2 = X2[3];

    // New positions
    X1dot[0] = u1;
    X1dot[1] = v1;

    X2dot[0] = u2;
    X2dot[1] = v2;

    // Distance

    double r = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    // New velocities
    X1dot[2] = G * m2 * (x2 - x1)/(r * r * r);
    X1dot[3] = G * m2 * (y2 - y1)/(r * r * r);

    X2dot[2] = G * m1 * (x1 - x2)/(r * r * r);
    X2dot[3] = G * m1 * (y1 - y2)/(r * r * r);

    return 0;
}


int orbit(double *X10, double *X20, const double dt_in, const double tmax){

    double t = 0;
    double X1new[N];
    double X2new[N];
    double dt = dt_in;
    
    std::ofstream myfile("runge4.csv");
    myfile.precision(16);

    while(t < tmax){
        single_step(X10, X20, X1new, X2new, dt);
        for(int j  = 0; j < N; j++){
            X10[j] = X1new[j];
            X20[j] = X2new[j];
        }
        myfile << t << "," << X10[0] << "," << X10[1] << "," << X20[0] << "," << X20[1] << "," << X10[2] << "," << X10[3] << "," << X20[2] << "," << X20[3] <<std::endl;
        t += dt;
    }
    myfile.close();
    return 0;
}

int orbit_adaptive(double *X10, double *X20, const double dt_in, const double tmax, const double eps){

    double X1new[N];
    double X2new[N];
    double t           = 0.0;
    double temp_error1 = 1.e10;
    double temp_error2 = 1.e10;
    double temp_error  = 1.e10;
    double dt          = dt_in;
    double dt_new      = dt;

    const double S1 = 0.9;
    const double S2 = 4.0;

    std::ofstream myfile("runge4Adaptive.csv");
    myfile.precision(16);
    while(t < tmax){
        double temp_error = 1.e10;
        while(temp_error > eps){
            dt = dt_new;
            if (t + dt > tmax){
                dt = tmax - t;
            }
            // two half/small steps
            double Xtemp1[N];
            double Xtemp2[N];
            single_step(X10, X20, Xtemp1, Xtemp2, 0.5 * dt);
            single_step(Xtemp1, Xtemp2,  X1new, X2new, 0.5 * dt);

            // one single/big step
            double Xsingle1[N];
            double Xsingle2[N];
            single_step(X10, X20, Xsingle1, Xsingle2, dt);

            // estimating the error
            temp_error1 = -1.e10;
            temp_error2 = -1.e10;
            for (int m = 0; m < N; m++){
                temp_error1 = std::max(temp_error1, fabs((X1new[m] - Xsingle1[m])/X1new[m]));
                temp_error2 = std::max(temp_error2, fabs((X2new[m] - Xsingle2[m])/X2new[m]));
                temp_error  = std::max(temp_error1, temp_error2);
            }
            double dt_est = dt*pow(fabs(eps/temp_error), 0.2);
            dt_new = std::min(std::max(S1*dt_est, dt/S2), S2*dt);
        }//while
        
        for (int m=0; m < N; m++) {
            X10[m] = X1new[m];
            X20[m] = X2new[m];
        }
        myfile << t << "," << X10[0] << "," << X10[1] << "," << X20[0] << "," << X20[1] << "," << X10[2] << "," << X10[3] << "," << X20[2] << "," << X20[3] <<std::endl;

        t += dt;
    }
    myfile.close();
    return 0;
}

