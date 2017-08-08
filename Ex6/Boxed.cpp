//Box-o-Particles

#include<iostream>
#include<fstream>
#include<random>
#include<chrono>

/*
In order to detect any collisions dt*v (highest possible v) must
be smaller than the radius of the smallest particle. This will prevent particles
which are close from tunnelling, or swapping order in a step
*/
#define dt 0.00005

/*
Since all the variables are public, a struct might be more appropriate.
But it does not make a real difference to the program.
I decided against the use of inverse mass, and instead used a Boolean type
to differentiate between particles and walls, as it felt more natural to use mass.

Like particles, walls must have finite radii to pervent 'tunelling'. So the
effective position of the wall is a radius away from the nominal position.
*/
class Particle {
	public:
 		double x; // position
	  	double p;// momentum
	  	double m; // mass
	  	double v; // velocity
	  	double T; // kinetic energy
	  	double r; // radius of particle
		bool wall;
		
		//Using a normal constructor led to problems with the box[] array
		//So a function was defined to do the same job.
		void initP(double x, double m, double v, double r, bool w);

		void xStep() {
			x += v*dt;
		}
		void pCalc() {
			p = v*m;
	 	}
		void Tcalc() {
			T = 0.5*m*v*v;
		}
};

void Particle::initP(double initX, double mass, double initV, double radius, bool isWall) {
	x = initX;
	m = mass;
	v = initV;
	r = radius;
	wall = isWall;
}

//performs the collison calculations to update the velocities
void resolution(Particle& A, Particle& B) {
	//The given cases handle reflection off the wall
	//If the particles are moving less quickly than the 
	if (A.wall) {
		if (A.v == 0) {
			B.v = -1*B.v;
		} else {
			//this is the limiting case of the equations below as m -> inf
			B.v = 2*A.v - B.v;
		}
	} else if (B.wall) {
		if (B.v == 0) {
			A.v = -1*A.v;
		} else {
			//this is the limiting case of the equations below as m -> inf
			A.v = 2*B.v - A.v;
		}
	} else {
		double v1, w1; //inital velocities
		double v2, w2; //final velocities
		v1 = A.v;
		w1 = B.v;
		//follows from conservation of (linear) momentum and (kinetic) energy
		v2 = (2*B.m*B.v + A.v*(A.m - B.m))/(B.m + A.m);
		w2 = (2*A.m*A.v + B.v*(B.m - A.m))/(B.m + A.m);
		A.v = v2;
		B.v = w2;
	}
}

//This method depends on box[]'s elements to be ordered in x
//n is the number of elements in box[]
void collision(Particle box[], int n) {
	for (int i = 0; i < n - 1; i++) {
			double deltaX = box[i + 1].x - box[i].x;
			double sumRadii = box[i].r + box[i + 1].r;
			
			//ie when a collision occurs, resolve it
			if (deltaX < sumRadii) {
				resolution(box[i], box[i + 1]);
			}
	}
}

void tStep (double &t) {
	t += dt;
}

void updateState(Particle box[], int n) {
	for (int i = 0; i < n; i++) {
		box[i].xStep();
		box[i].pCalc();
		box[i].Tcalc();
	}
}

//Generates random particles to put in the walled box.
void makeBox(Particle box[], int n){
	double start, end, mlim, vlim;
	//The start and end points must be within the sum of the appropriate
	//radii from the wall positions
	start = 0.10;
	end = 0.90;
	mlim = 2.0;
	vlim = 0.2;
	
	//The seed line is arbitrary, but to guarantee uniqueness, the system time is used
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator_1 (seed);
	std::default_random_engine generator_2 (seed + 1);
	std::uniform_real_distribution<double> mass_dist(0.0, mlim);
	std::uniform_real_distribution<double> speed_dist(-vlim, vlim);
	
	//this is the first wall
	box[0].initP(0.0, 0.0, 0.05, 0.01, true);
	
	for (int i = 1; i < n - 1; i++) {
		double x = start + (i/(n - 2.0))*(end - start);
		double m = mass_dist(generator_1);
		double v = speed_dist(generator_2);
		box[i].initP(x, m, v, 0.001, false);
	}
	//this is the second wall
	box[n - 1].initP(1.0, 0.0, -0.05, 0.01, true);
}

//n is the number of particles
int main () {
	//n must be at least 2 (which would only be the walls)
	int n = 12;
	double t = 0.0;
	Particle box[n];
	/*
	//The particles in box MUST be ordered (ascending) in x
	Particle box[n];
	box[0].initP(0.0, 1.0, 0, 0.01, true);
	box[1].initP(0.3, 1.0, 0.5, 0.01, false);
	box[2].initP(0.5, 3.0, -0.7, 0.01, false);
	box[3].initP(0.9, 0.1, 2.0, 0.01, false);
	box[4].initP(1.0, 1.0, 0, 0.01, true);
	*/
	makeBox(box, n);
	
	std::ofstream fout("BoxOparticles.dat");
	if(not fout.is_open()) {
		std::cout << "There was a problem with opening the file" << std::endl;
	} else {
		fout << "t ";
		for (int i = 0; i < n; i++) {
			fout << "x" << i << " ";
		}
		fout << std::endl;
		
		for (int i = 0; i < 100000; i++) {
			collision(box, n);

			//We assume instant collisons, so the output should be here
			fout << t << " ";
			for (int j = 0; j < n; j++) {
				fout << box[j].x << " ";
			}
			fout << std::endl;
			
   			updateState(box, n);
			tStep(t);
		}
	}
	return 0;
}
