//Binary Gravitational System Simulator
/*
The program seeks to model the result of gravitational interactions
in a two body system. This is accomplished by an implementation
of the Leapfrog numerical method, and a particle struct which is
updated by various functions whose side effects accomplish this.
Classes were not used, since the problem could easily be solved 
without them.
*/

/*
The following conditions model the Earth and Sun (ignoring
the other planets) over a period of approximately one year
#define dt 160

.
.
.

A.m = 1*TerrM;
A.v[0] = -(1*au*8*atan(1))/(TerrT);
A.v[1] = 0.0;
A.r[0] = 0.0;
A.r[1] = 1*au;
A.radius = 6371000;

B.m = 1*SolM;
B.v[0] = 0.0;
B.v[1] = 0.0;
B.r[0] = 0.0;
B.r[1] = 0.0;
B.radius = 1*SolR;

i < 200000
*/

#include <iostream>
#include <cmath>
#include <fstream>

//All calculations are in SI units
//defines the time increment
#define dt 100
//defines the inverse square force constant
#define G 6.67e-11
//defines the astronomical unit
#define au 149597871000
//defines the solar mass
#define SolM 1.9891e+30
//defines the solar radius
#define SolR 695500000
//defines the earth mass
#define TerrM 5.972e+24
//defines the Earth time period
#define TerrT 3.15569e+7

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
	//radius of the particle
	double radius;
};

void TimeStep (double &t) {
	t += 0.5*dt;
}

double distance (double deltaX, double deltaY) {
	double modulus = sqrt((deltaX*deltaX + deltaY*deltaY));
	return modulus;
}

//updates the acceleration vectors
void Find_a (particle& A, particle& B, bool &collision) {
	double deltaX, deltaY;
	deltaX = B.r[0] - A.r[0];
	deltaY = B.r[1] - A.r[1];
	double R = distance(deltaX, deltaY);
	//computes the force in the 'x' direction
	A.a[0] = (G*B.m*deltaX)/(R*R*R);
	//computes the force in the 'y' direction
	A.a[1] = (G*B.m*deltaY)/(R*R*R);
	
	//by Newton III
	B.a[0] = -(A.a[0]*A.m)/B.m;
	B.a[1] = -(A.a[1]*A.m)/B.m;
	
	/*
	this was implemented stop the calculations around a
	collision, not record the exact place. This allows for colliding
	initial conditions to be examined without unneeded data being generated
	*/
	if (R < A.radius + B.radius) {
		collision = true;
	}
}

//increments the velocity vector
void VelocityStep (particle& A) {
	double dv[2];
	dv[0] = A.a[0]*dt;
	dv[1] = A.a[1]*dt;
	A.v[0] += dv[0];
	A.v[1] += dv[1];
}

//increments the position vector
void PositionStep (particle& A) {
	double dr[2];
	dr[0] = 0.5*A.v[0]*dt;
	dr[1] = 0.5*A.v[1]*dt;
	A.r[0] += dr[0];
	A.r[1] += dr[1];
}

void EnergyData (particle& A, particle& B) {
	double deltaX, deltaY;
	deltaX = B.r[0] - A.r[0];
	deltaY = B.r[1] - A.r[1];
	double R = distance(deltaX, deltaY);
	A.V = -(A.m*B.m*G)/R;
	B.V = A.V;
	A.T = 0.5*A.m*(A.v[0]*A.v[0] + A.v[1]*A.v[1]);
	B.T = 0.5*B.m*(B.v[0]*B.v[0] + B.v[1]*B.v[1]);
}

/*
Follows the Leapfrog procedure. The side effects of this, and the other
functions, updates the variables contained in the particle struct
*/
void Leapfrog (particle& A, particle& B, double &t, bool &collision) {
	PositionStep(A);
	PositionStep (B);
	
	TimeStep(t);
	Find_a(A, B, collision);
	
	VelocityStep(A);
	VelocityStep(B);
	
	PositionStep(A);
	PositionStep (B);
	TimeStep(t);
}


int main () {
	particle A, B;
	bool collision = false;
	double t = 0.0;
	//sets the initial conditions of two particles
	A.m = 1.2*SolM;
	A.v[0] = (1*au*8*atan(1))/(10*TerrT);
	A.v[1] = 0.0;
	A.r[0] = 0.0;
	A.r[1] = 1*au;
	A.radius = 1*SolR;
	
	B.m = 1*SolM;
	B.v[0] = -(1*au*8*atan(1))/(10*TerrT);
	B.v[1] = 0.0;
	B.r[0] = 0.0;
	B.r[1] = -1*au;
	B.radius = 1*SolR;

	EnergyData(A, B);
	std::ofstream fout("BinSystem.dat");
	

	if(fout.is_open()) {

		//writes column headers to .dat file
		fout << "t "<< "x1 " << "y1 " << "x2 " << "y2 " << "T1 " << "V1 " <<
		"T2 " << "V2" << std::endl;
		
		for (int i = 0; i < 250000; i++) {
			//writes state of A and B to file
			fout << t << " " << A.r[0] << " " << A.r[1] << " " << B.r[0] << " "
			<< B.r[1] << " " << A.T << " " << A.V << " " << B.T << " " << B.V << std::endl;

			//updates A & B for the current time
			Leapfrog(A, B, t, collision);
			EnergyData(A, B);

			if (collision) {
				fout << t << " " << A.r[0] << " " << A.r[1] << " " << B.r[0] << " "
				<< B.r[1] << " " << A.T << " " << A.V << " " << B.T << " " << B.V << std::endl;
				std::cout << "A collision occurred within the last few points in the .dat file" << std::endl;
				break;
			}
		}
	}

	fout.close();
	return 0;
}