//Box-o-Particles

#include<iostream>
#include<fstream>
#include<random>
#include<chrono>

/*
In order to detect any collisions dt*v (highest possible v) must
be smaller than the radius of the smallest particle. This will prevent particles
which are close from tunnelling, ie swapping order in a step.
*/

#define dt 0.0001
//A static definition for n is easier to implement than dynamic array sizes.
#define n 20

/*
I decided against the use of inverse mass, and instead used a Boolean type
to differentiate between particles and walls, as it felt more natural to use mass.
Since the bulk of calculations are going to be colllision tests, the use of a
bool, rather than inverse mass, leads to little increase in runtime. The walls
are always given nominally zero mass, so they don't contributes to the kinetic
energy.

Like particles, walls must have finite radii to pervent 'tunelling'. So the
effective position (ie surface) of the wall is a radius away from the nominal position.

To change the conditions of the experiment, one need only change the values
used in LineWord's constructor.

Currently the momentum property is redundant. I had used it in earlier
investiagtions but not in the one presented.

The mass genrator has been commened out and repaced with 1kg masses for
my investiagtion

The position data writes has beem commented out, as we are not interested in
that data for this investigation (I know the conditions are stable)

The calculations are nominally in SI.
*/

class Particle {
	friend class LineWorld;
	private:
		double p;// momentum
	  	double m; // mass
	  	double v; // velocity
	  	double r; // radius of particle
		bool wall;

	public:
		double x; // position
		double T; // kinetic energy
		//Using a normal constructor led to problems with the elements array
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

//Class used to define the space we work in
class LineWorld {
	public:
		//Number of elements (n + 2, for the walls).
		int noE;
		//Elapsed time for instance of a LineWord instance.
		double time;
		//the elements array of Particles forms the spacce of the simulation.
		Particle elements[n + 2];
		//The constructor for LineWorld is always default.
		LineWorld();
		
		/*
		The member functions of LineWorld & Particle form the Laws of Physics in
		LineWorld. They seek to simulate ideallised ellastic collisions in one
		dimention using Newtonian Mechanics.
		*/

		//performs the collison calculations to update the velocities.
		void resolution(Particle& A, Particle& B);

		//tests for collison between adjacent particles when called.
		void collision();
		
		//updates the energy and momentum of each particle.
		void momEnergyCalc();

  		//updates the time, and postion of all the particles.
		void updateState();

		//Runs the simulation, and writes the position data to a file.
		void writeData();
};


//This default constuctor will generate n particles between two 'wall' particles.
//NB the random mass generator has been commented out, as for the investiagtion
//I require identically massed particles to model an ideal gas.
LineWorld::LineWorld () {
	noE = n + 2;
	time = 0.0;
	
	//Generates random particles to put in the walled box.
	double start, end, mlim, vlim, radius;
	//The start and end points must be within the sum of the appropriate
	//radii from the wall positions.
	
	radius = 0.001;
	start = 0.10; //Lower bound for the position
	end = 0.90; //Upper bound for the position
	//mlim = 2.0; //Upper bound for mass
	vlim = 0.2; //Upper (and - lower) bound for velocity

	//The seed line is arbitrary, but to guarantee uniqueness, the system time is used.
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator_1 (seed);

	//A 'cheap' way of getting a different seed
	//std::default_random_engine generator_2 (seed + 1);
	//std::uniform_real_distribution<double> mass_dist(0.0, mlim);
	
	std::uniform_real_distribution<double> speed_dist1(-vlim, vlim);
	//std::normal_distribution<double> speed_dist2(0.0, 0.5);

	//this is the first wall
	elements[0].initP(0.0, 0.0, 0.0, 0.01, true);

	for (int i = 1; i < noE - 1; i++) {
		//The particles have equally spaced initial positions.
		double x = start + (i/(noE - 2.0))*(end - start);
		double m = 1.0 ; //mass_dist(generator_2);
		double v = speed_dist1(generator_1);
		elements[i].initP(x, m, v, radius, false);
	}
	//this is the second, rightmost, wall
	elements[noE - 1].initP(1.0, 0.0, -0.001, 0.01, true);
}


void LineWorld::resolution(Particle& A, Particle& B) {
	//The given cases handle reflection off the wall.
	if (A.wall) {
		if (A.v == 0) {
			B.v = -1*B.v;
		} else {
			//this is the limiting case of the equations below as (wall) m -> inf.
			B.v = 2*A.v - B.v;
		}
	} else if (B.wall) {
		if (B.v == 0) {
			A.v = -1*A.v;
		} else {
			//this is the limiting case of the equations below as (wall) m -> inf.
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

//This method depends on the elements of LineWorld to be ordered in x
void LineWorld::collision() {
	for (int i = 0; i < noE - 1; i++) {
			double deltaX = elements[i + 1].x - elements[i].x;
			double sumRadii = elements[i].r + elements[i + 1].r;

			//ie when a collision occurs, resolve it
			if (deltaX < sumRadii) {
				resolution(elements[i], elements[i + 1]);
			}
	}
}

void LineWorld::momEnergyCalc() {
	for (int i = 0; i < noE; i++) {
 		elements[i].pCalc();
		elements[i].Tcalc();
	}
}

void LineWorld::updateState() {
	for (int i = 0; i < noE; i++) {
		elements[i].xStep();
	}
	time += dt;
}

//This will write two files. One with the position data for the parcticles,
//and one with the total energy of the system. Both with time.

//NB in my solution the position data writes have been commented out.
//so as not to waste time. An (empty) position data file is still created however.
//Uncomment the lines marked between #@# if the positon data are required.
void LineWorld::writeData() {
	std::ofstream fout1("PositionData.dat");
	std::ofstream fout2("EnergyData.dat");
	
	if(not fout1.is_open() || not fout2.is_open()) {
		std::cout << "There was a problem with opening the file(s)." << std::endl;
		std::cout << "Please restart the simulation." << std::endl;
	} else {
		momEnergyCalc();
		
		fout2 << "t " << "SysEnergy" << std::endl;
		
		//#@#
		//fout1 << "t ";
		/*
		for (int i = 0; i < noE; i++) {
			fout1 << "x" << i << " ";
		}
		fout1 << std::endl;
		*/
		//#@#
		
  		//The total time elasped in a LineWorld object is numberofsteps*dt
		//                  ¬This¬ changes the number of steps
		for (int i = 0; i < 400000; i++) {
			double totalE = 0.0;
			collision();
			//We assume instant collisons, so the output should be here.
			
			//#@#
			//fout1 << time << " ";
			//#@#
			
			fout2 << time << " ";
			for (int j = 0; j < noE; j++) {
				//#@#
				//fout1 << elements[j].x << " ";
				//#@#
				
				totalE += elements[j].T;
			}
			
			//#@#
			//fout1 << std::endl;
			//#@#
			
			fout2 << totalE << std::endl;
			
			momEnergyCalc();
   			updateState();
		}
	}
	
	fout1.close();
	fout2.close();
}

int main() {
	LineWorld box;
	box.writeData();
	return 0;
}
