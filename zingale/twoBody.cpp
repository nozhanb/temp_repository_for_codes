// This code is the result of my failure in coding the three-body problem (i.e. hm2e2pa). To make things easier and find out what the 
// problem is with my three-body code I wrote this one. It certainly was a good idea to start from something simpler (i.e. two-body)!
// This code seems to be working but the results need to be verified!
// Note: this code is written on the remnants of my failed three-body attempt so there are still some traces of the third object/body 
// is left on this page (e.g. mass3). Just ignore them!

// Septemebr 05, 2020
// Nozhan

#include <cstdlib>
#include <string>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

// Global Declaration

const int N = 1000000;

double Rx1[N], Vx1[N], Ry1[N], Vy1[N];
double Rx2[N], Vx2[N], Ry2[N], Vy2[N];
double Rx3[N], Vx3[N], Ry3[N], Vy3[N];
double T[N],  Dis1[N], Dis2[N];

// double magnitude(const double & obj1x, const double &objx, const double &obj1y, const double &objy, const double &softLength);
// double fv(const double &obj1, const double &obj2, const double &obj, const int &obj1Mass, const int &obj2Mass, const double &distance1, const double &distance2, const double &dh);

double magnitude(const double & obj1x, const double &objx, const double &obj1y, const double &objy, const double &softLength);
double fv(const double &obj1, const double &obj, const int &obj1Mass, const double &distance1, const double &dh);

double fx(const double &v);

void gravityForce(const int &initial_time, const int &final_time, const double &dt, const double &steps, const int &G);

int main(){

int i = 0, G = 1;
double dt = 0.0, steps = 0.0, initial_time = 0, final_time = 0;

cout << "Please enter the length of your time interval (dt): " << endl;
cin  >> dt;
cout << "Please enter final time (tf): " << endl;
cin  >> final_time;

steps = (final_time - initial_time)/dt;
cout << "This is steps: " << steps << endl;

ofstream myfile("twoBody_Runge-Kutta_4th.csv");
myfile.precision(17);

gravityForce(initial_time, final_time, dt, steps, G);

for (i = 0; i <= steps; i++){
    myfile << T[i] << "," << Rx1[i] << "," << Ry1[i] << "," << Rx2[i] << "," << Ry2[i] << "," << Vx1[i] << "," << Vy1[i] << "," << Vx2[i] << "," << Vy2[i] << "," << Dis1[i] << endl;
    // myfile << T[i] << "," << Vx1[i] << "," << Vy1[i] << "," << Vx2[i] << "," << Vy2[i] << "," << Vx3[i] << "," << Vy3[i] << endl;

}

myfile.close();

} // main 


double magnitude(const double &obj1x, const double &objx, const double &obj1y, const double &objy, const double &softLength){
    double value = 0.0;
    value        = pow((obj1x - objx + softLength) * (obj1x - objx + softLength) + (obj1y - objy + softLength) * (obj1y - objy + softLength), 3.0/2.0);
    return value;
}

// double fv(const double &obj1, const double &obj2, const double &obj, const int &obj1Mass, const int &obj2Mass, const double &distance1, const double &distance2, const double &dh){
//     double value = 0.0;
//     const int  G = 1;
//     value        = G * ((obj1Mass * (obj1 - obj)/distance1) + (obj2Mass * (obj2 - obj)/distance2));
//     return value;
// }

double fv(const double &obj1, const double &obj, const int &obj1Mass, const double &distance1, const double &dh){
    double value = 0.0;
    const int  G = 1;
    value        = G * (obj1Mass * (obj1 - obj)/distance1);
    return value;
}

double fx(const double &v){
    return v;
}



void gravityForce(const int &initial_time, const int &final_time, const double &dt, const double &steps, const int &G){

    int j = 0;
    int mass1 = 25, mass2 = 50, mass3 = 100;

    double k11vx = 0.0, k12vx = 0.0, k13vx = 0.0, k14vx = 0.0;
    double k11vy = 0.0, k12vy = 0.0, k13vy = 0.0, k14vy = 0.0;

    double k11x = 0.0, k12x = 0.0, k13x = 0.0, k14x = 0.0;
    double k11y = 0.0, k12y = 0.0, k13y = 0.0, k14y = 0.0;

    double k21vx = 0.0, k22vx = 0.0, k23vx = 0.0, k24vx = 0.0;
    double k21vy = 0.0, k22vy = 0.0, k23vy = 0.0, k24vy = 0.0;

    double k21x = 0.0, k22x = 0.0, k23x = 0.0, k24x = 0.0;
    double k21y = 0.0, k22y = 0.0, k23y = 0.0, k24y = 0.0;

    double k31vx = 0.0, k32vx = 0.0, k33vx = 0.0, k34vx = 0.0;
    double k31vy = 0.0, k32vy = 0.0, k33vy = 0.0, k34vy = 0.0;

    double k31x = 0.0, k32x = 0.0, k33x = 0.0, k34x = 0.0;
    double k31y = 0.0, k32y = 0.0, k33y = 0.0, k34y = 0.0;

    double distance12 = 0.0, distance13 = 0.0;
    double distance21 = 0.0, distance23 = 0.0;
    double distance31 = 0.0, distance32 = 0.0;

    double softLength = 0.0, value = 0.0;
    const double dh   = dt;


    T[0]   = 0;

    Rx1[0] = 3.0;
    Ry1[0] = 3.0;
    Vx1[0] = 1.0;
    Vy1[0] = 0.0;

    Rx2[0] = 0.0;
    Ry2[0] = 0.0;
    Vx2[0] = 0.0;
    Vy2[0] = 0.0;

    Rx3[0] = -1.0;
    Ry3[0] = 1.0;
    Vx3[0] = 0.0;
    Vy3[0] = 0.0;
    
    Dis1[0] = magnitude(Rx2[0], Rx1[0], Ry2[0], Ry1[0], softLength);;

    for(j = 1; j <= steps; j++){
    
        //!!!!!!!!!!
        // planet 1:
        //!!!!!!!!!!

        // We have three sets of distances. One set for each object.
        distance12 = magnitude(Rx2[j - 1], Rx1[j - 1], Ry2[j - 1], Ry1[j - 1], softLength);
        Dis1[j]    = distance12;

        k11vx = fv(Rx2[j - 1], Rx1[j - 1], mass2, distance12, dh);
        k11vy = fv(Ry2[j - 1], Ry1[j - 1], mass2, distance12, dh);

        k21vx = fv(Rx1[j - 1], Rx2[j - 1], mass1, distance12, dh);
        k21vy = fv(Ry1[j - 1], Ry2[j - 1], mass1, distance12, dh);

        k11x  = fx(Vx1[j - 1]);
        k21x  = fx(Vx2[j - 1]);

        k11y  = fx(Vy1[j - 1]);
        k21y  = fx(Vy2[j - 1]);

        distance12 = magnitude(Rx2[j - 1] + 0.5 * dh * k21x, Rx1[j - 1] + 0.5 * dh * k11x, Ry2[j - 1] + 0.5 * dh * k21y, Ry1[j - 1] + 0.5 * dh * k11y, softLength);
        
        k12vx = fv(Rx2[j - 1] + 0.5 * dh * k21x, Rx1[j - 1] + 0.5 * dh * k11x, mass2, distance12, dh);
        k12vy = fv(Ry2[j - 1] + 0.5 * dh * k21y, Ry1[j - 1] + 0.5 * dh * k11y, mass2, distance12, dh);

        k22vx = fv(Rx1[j - 1] + 0.5 * dh * k11x, Rx2[j - 1] + 0.5 * dh * k21x, mass1, distance12, dh);
        k22vy = fv(Ry1[j - 1] + 0.5 * dh * k11y, Ry2[j - 1] + 0.5 * dh * k21y, mass1, distance12, dh);

        k12x  = fx(Vx1[j - 1] + 0.5 * dh * k11vx);
        k22x  = fx(Vx2[j - 1] + 0.5 * dh * k21vx);

        k12y  = fx(Vy1[j - 1] + 0.5 * dh * k11vy);
        k22y  = fx(Vy2[j - 1] + 0.5 * dh * k21vy);

        distance12 = magnitude(Rx2[j - 1] + 0.5 * dh * k22x, Rx1[j - 1] + 0.5 * dh * k12x, Ry2[j - 1] + 0.5 * dh * k22y, Ry1[j - 1] + 0.5 * dh * k12y, softLength);

        k13vx = fv(Rx2[j - 1] + 0.5 * dh * k22x, Rx1[j - 1] + 0.5 * dh * k12x, mass2, distance12, dh);
        k13vy = fv(Ry2[j - 1] + 0.5 * dh * k22y, Ry1[j - 1] + 0.5 * dh * k12y, mass2, distance12, dh);

        k23vx = fv(Rx1[j - 1] + 0.5 * dh * k12x, Rx2[j - 1] + 0.5 * dh * k22x, mass1, distance12, dh);
        k23vy = fv(Ry1[j - 1] + 0.5 * dh * k12y, Ry2[j - 1] + 0.5 * dh * k22y, mass1, distance12, dh);

        k13x  = fx(Vx1[j - 1] + 0.5 * dh * k12vx);
        k23x  = fx(Vx2[j - 1] + 0.5 * dh * k22vx);

        k13y  = fx(Vy1[j - 1] + 0.5 * dh * k12vy);
        k23y  = fx(Vy2[j - 1] + 0.5 * dh * k22vy);

        distance12 = magnitude(Rx2[j - 1] + 0.5 * dh * k23x, Rx1[j - 1] + 0.5 * dh * k13x, Ry2[j - 1] + 0.5 * dh * k23y, Ry1[j - 1] + 0.5 * dh * k13y, softLength);
 
        k14vx = fv(Rx2[j - 1] + dh * k22x, Rx1[j - 1] + dh * k12x, mass2, distance12, dh);
        k14vy = fv(Ry2[j - 1] + dh * k22y, Ry1[j - 1] + dh * k12y, mass2, distance12, dh);

        k24vx = fv(Rx1[j - 1] + dh * k12x, Rx2[j - 1] + dh * k22x, mass1, distance12, dh);
        k24vy = fv(Ry1[j - 1] + dh * k12y, Ry2[j - 1] + dh * k22y, mass1, distance12, dh);

        k14x  = fx(Vx1[j - 1] + dh * k13vx);
        k24x  = fx(Vx2[j - 1] + dh * k23vx);

        k14y  = fx(Vy1[j - 1] + dh * k13vy);
        k24y  = fx(Vy2[j - 1] + dh * k23vy);


        Vx1[j] = Vx1[j - 1] + dh * (k11vx + 2 * k12vx + 2 * k13vx + k14vx)/6.0;
        Vy1[j] = Vy1[j - 1] + dh * (k11vy + 2 * k12vy + 2 * k13vy + k14vy)/6.0;

        Rx1[j] = Rx1[j - 1] + dh * (k11x + 2 * k12x + 2 * k13x + k14x)/6.0;
        Ry1[j] = Ry1[j - 1] + dh * (k11y + 2 * k12y + 2 * k13y + k14y)/6.0;

        Vx2[j] = Vx2[j - 1] + dh * (k21vx + 2 * k22vx + 2 * k23vx + k24vx)/6.0;
        Vy2[j] = Vy2[j - 1] + dh * (k21vy + 2 * k22vy + 2 * k23vy + k24vy)/6.0;
        
        Rx2[j] = Rx2[j - 1] + dh * (k21x + 2 * k22x + 2 * k23x + k24x)/6.0;
        Ry2[j] = Ry2[j - 1] + dh * (k21y + 2 * k22y + 2 * k23y + k24y)/6.0;

        T[j]   = T[j - 1]   + dt;
    }
}
