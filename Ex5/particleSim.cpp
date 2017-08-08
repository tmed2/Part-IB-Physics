#include <iostream>
#include <cmath>
#include <fstream>

//defines the dimention of the space we are using
#define D 2
//defines the time increment
#define dt 0.01
//defines the inverse square force constant (-k*r/R*3)
//this is GMm for gravity
#define k 10
struct particle {
	//position vector
	double r[D];
	//velocity vector
	double v[D];
	//acceleration vector
	double a[D];
	//mass of the particle
	double m;
	//inital time condition
	double t;
	//potential energy
	double V;
	//kinetic energy
	double T;
	//Angular momentum. Defined as a scalar as r[] & v[] are
	//coplanar, so only one dimention is needed to descibe it
	double L;
};

//computes the distance from the origin
double distance (double r[]) {
	double modulus = sqrt((r[0]*r[0]) + (r[1]*r[1]));
	return modulus;
}

//Increments the time
void TimeStep (double &t) {
	t += 0.5*dt;
}

//updates the acceleration vector
void Find_a (double r[], double a[], double m) {
	double R;
	R = distance(r);
	//computes the force in the 'x' direction
	a[0] = -(k*r[0])/(m*R*R*R);
	//computes the force in the 'y' direction
	a[1] = -(k*r[1])/(m*R*R*R);
}

//increments the velocity vector
void VelocityStep (double v[], double a[]) {
	double dv[D];
	dv[0] = a[0]*dt;
	dv[1] = a[1]*dt;
	v[0] = v[0] + dv[0];
	v[1] = v[1] + dv[1];
}

//increments the position vector
void PositionStep (double r[], double v[]) {
	double dr[D];
	dr[0] = 0.5*v[0]*dt;
	dr[1] = 0.5*v[1]*dt;
	r[0] = r[0] + dr[0];
	r[1] = r[1] + dr[1];
}

void MotionData (particle& a) {
	double R;
	R = distance(a.r);
	a.V = -(a.m*k)/R;
	a.T = 0.5*a.m*(a.v[0]*a.v[0] + a.v[1]*a.v[1]);
	a.L = a.r[0]*a.v[1] - a.r[1]*a.v[0];
}

//Follows the Leapfrog procedure. The side effects of this, and the other
//functions, updates the variables contained in the particle struct
void Leapfrog (particle& a) {
	PositionStep(a.r, a.v);
	TimeStep(a.t);
	Find_a(a.r, a.a, a.m);
	VelocityStep(a.v, a.a);
	PositionStep(a.r, a.v);
	TimeStep(a.t);
}

int main () {
	particle a;	

	a.t = 0;
	a.m = 1;
	a.v[0] = 0.0;
	a.v[1] = 0.9;
	a.r[0] = 10.0;
	a.r[1] = 0.0;
	Find_a (a.r, a.a, a.m);
	
	std::ofstream fout("positionData.dat");
	std::ofstream fout1("energyData.dat");
	
	if(fout.is_open() && fout1.is_open()) {
		fout << "t "<< "x " << "y" << std::endl;
		fout1 << "t "<< "V " << "T" << std::endl;
		for (int i = 0; i < 13000; i++) {
			MotionData(a);
			/*
			std::cout << a.t << """		 """  << a.r[0] << """	     """ 
			<< a.r[1] << std::endl;
			*/
			fout << a.t << " " << a.r[0] << " " << a.r[1] << std::endl;
			fout1 << a.t << " " << a.V << " " << a.T << std::endl;
			Leapfrog(a);
		}
	}
	
	fout.close();
	fout1.close();
	return 0;
}
