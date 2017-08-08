#include <iostream>
#include <random>
#include <cmath>
#include <chrono>

int main () {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::uniform_real_distribution<double> distribution(0,1);
	
	int n = 1000000;
	int m = 0;
	for (int i = 0; i != n; i++){
		double x = distribution(generator);
		double y = distribution(generator);
		double radius = pow(x, 2) + pow(y, 2);
		if (radius <= 1) 
		{
			++m;
		}
		else 
		{
		}
	}
	
	double piApprox = 4 * (static_cast<double>(m)/n);
	printf("%.20g", piApprox);
	return 0;
}
