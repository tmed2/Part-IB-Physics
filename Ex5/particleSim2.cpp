#include <iostream>
#include <cmath>
#include <fstream>


//defines the time increment
#define dt 0.01
//defines the inverse square force constant (-k*r/R*3)
//this is G for gravity
#define k 6.63e-10

struct particle {
	//position vector
	double r[2];
	//velocity vector
	double v[2];
	//acceleration vector
	double a[2];
	//mass of the particle
	double m;
	//potential energy
	double V;
	//kinetic energy
	double T;
	//Angular momentum. Defined as a scalar as r[] & v[] are
	//coplanar, so only one dimention is needed to descibe it
	double L;
};

void TimeStep (double &t) {
	t += 0.5*dt;
}

double distance (double deltaX, double deltaY) {
	double modulus = sqrt((deltaX*deltaY + deltaY*deltaY));
	return modulus;
}

//updates the acceleration vectors
void Find_a (particle& A, particle& B) {
	double deltaX, deltaY;
	deltaX = b.r[0] - a.r_1[0];
	deltaY = b.r_2[1] - a.r_1[1];
	double R = distance(deltaX, deltaY);
	//computes the force in the 'x' direction
	A.a[0] = (k*B.m*deltaX)/(A.m*R*R*R);
	//computes the force in the 'y' direction
	A.a[1] = (k*B.m*deltaY)/(*A.m*R*R*R);
	
	//by symmetry
	B.a[0] = -(A.a[0]*A.m)/B.m
	B.a[1] = -(A.a[1]*A.m)/B.m
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
