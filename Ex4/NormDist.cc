//Normal Distribution Integrator
/*
The program uses a simple implementation of the
trapezium rule to estimate the area, i.e. the probability
between two points, under the normalized Gaussian.

The program will likely give spurious results for very large
values of sigma. This can be compensated by using more
trapezia. However if sigma is extremely high, then there 
may be problems with number representation. If this is the case,
then the program may not be suitable for the problem in the current form.

Although a formal error analysis is not present, I have found 
100 trapezia to me sufficient for most uses.
*/

#include<iostream>
#include<cmath>
#include<stdio.h>
double Prob(double stdDev, double mean, double start, double end, int N);
double Gaussian(double z);


int main() {
	double mu, sigma, a, b;
	int n;
	
	std::cout << "For a Normally distributed random variable, X, you can compute" << std::endl;
	std::cout << "P(a <= X <= b) using this program. This is implemented numerically" << std::endl;
	std::cout << "through the use of the Trapezium Rule." << std::endl << std::endl;
	
	bool loop = true;
	while (loop) {
		std::cout << "Please enter the mean of your distribution" << std::endl;
		std::cin >> mu;
		std::cout << "Please enter the standard deviation of your distribution" << std::endl;
		std::cin >> sigma;
		std::cout << "Please enter 'a'" << std::endl;
		std::cin >> a;
		std::cout << "Please enter 'b'" << std::endl;
		std::cin >> b;
		std::cout << "How many trapezia would you like to use?" << std::endl;
		std::cout << "More means greater accuracy, but longer computing time" << std::endl;
		std::cin >> n;

		
		//Just to catch common errors; type based errors will still cause issues however.
		if (sigma <= 0) {
			std::cout << "The standard deviation must be greater than zero" << std::endl << std::endl;
		} else if (a >= b) {
			std::cout << "We must have a < b." << std::endl << std::endl;
		} else {
			loop = false;
		}
	}
	
	//Computes  P(a <= X <= b)
	double s = Prob(sigma, mu, a, b, n);
	
	//in addition to the value promised, few others are computed for the user.
	//Symmetry is used to find other combinations of limits.
	//AS they are only printed to 5 dp, rounding errors may be present
	if ( a > mu && b > mu) {
		//computes P(mean <= X <= a)
		double p = Prob(sigma, mu, mu, a, n);
		//computes P(X >= b)
		double q = 0.5 - (s + p);
		//computes P(X <= a)
		double r = 0.5 + p;
		
		printf("P(X >= b) = %.5g \n", q);
		printf("P(a <= X <= b) = %.5g \n", s);
		printf("P(X <= a) = %.5g \n", r);
		printf("P(mean <= X <= a) = %.5g \n", p);
	} else if (a < mu && b < mu) {
		//computes P(b <= X <= mean)
		double p = Prob(sigma, mu, b, mu, n);
		//computes P(X >= b)
		double q = 0.5 + p;
		//computes P(X <= a)
		double r = 0.5 - (s + p);
		
		printf("P(X >= b) = %.5g \n", q);
		printf("P(a <= X <= b) = %.5g \n", s);
		printf("P(X <= a) = %.5g \n", r);
		printf("P(b <= X <= mean) = %.5g \n", p);
	} else {
		//computes P(a <= X <= Mean)
		double p = Prob(sigma, mu, a, mu, n);
		//computes P(X >= b)
		double q = 0.5 - (s - p) ;
		//computes P(X <= a)
		double r = 0.5 - p;
		
		printf("P(X >= b) = %.5g \n", q);
		printf("P(a <= X <= b) = %.5g \n", s);
		printf("P(X <= a) = %.5g \n", r);
		printf("P(a <= X <= Mean) = %.5g \n", p);
	}
	
	return 0;
}



//Defines the Normalised Gaussian function used in the program.
double Gaussian(double z) {
	//A value of Pi is not, it seems, included in the standard library.
	//So this 'trick' was used to get a value instead.
	const double pi = 4*atan(1);
	double value = (1.0/(sqrt(2*pi))) * (exp(- (z*z)/2));
	return value;
}


//Defines the function used to estimate the probability.
//The trapezium rule is used to estimate the Gaussian integral.
double Prob(double stdDev, double mean, double start, double end, int N) {
	double I, prefactor, z;
	
	//Normalizes start and end for the Gaussian function we have used.
	start = ((start - mean)/stdDev);
	end = ((end - mean)/stdDev);
	prefactor = (end - start)/(2*N);
	
	//Adds the starting and end values for the trapezia heights into I.
	I = Gaussian(start) + Gaussian(end);
	
	//We start with i of one going up to N - 1, so as not to re-include the start or end points.
	//Adds the intermediary trapezia heights to I, accounting for the double counting.
	for (int i = 1; i != N; i++) {
		z = start + 2*prefactor*i;
		I += 2*Gaussian(z);
	}
	
	//Multiplies I by the common half interval to transform the heights to areas.
	//The sum of the areas to form I is implicit.
	I *= prefactor;
	return I;
}
