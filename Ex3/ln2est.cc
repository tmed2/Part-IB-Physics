//Estimate of ln(2)
/*
random() does not work on non Unix systems, like mine.
<random> was used instead, along with a time based seed.
Apparently, rand() has been rendered obsolete by <random>,
which is why it is not being used.
*/

//A brief note on the method
/*
The integral of y=1/x between 1 and 2 is ln(2). Thus, by
adapting the method that was used to find pi, we can estimate 
the integral and therefore ln(2). 

I reasoned that if we have some random (and uniformly distributed)
x, and the same for y, then by comparing y <= 1/x we can see if the 
point that was generated lies under the curve, or over it. In the limit
of an infinite number of points, the integral is given by the ratio of
the points under the curve to the total number of points made.
*/

//A brief note on the accuracy
/*
In order to get 2 dp accuracy a sigma for ln2Approx of 0.002 was
chosen. As Ln2Approx = m/n, and n is known with complete accuracy:
Var(ln2Approx) ~ Var(m)/n  from simple error analysis. So the
n required of a given Var(ln2Approx) is Var(m)/Var(ln2Approx).
		If we approximate Var(m) as 1/12 (ie Var for the underlying 
uniform distribution(s), and require that Var(ln2Approx) ~ 0.002^2
then we get n = 20833.33. So by using this n, we should find that 
0.69115 < ln2Approx < 0.69515 about 68% of the time. So (as we have 
more clearance than is required on the lower bounds) we should find
that the value yielded is accurate to 2dp (after rounding) at least 
68% of the time. In fact, as 0.685 is about 4sigma down, and 0.695 about
1sigma up. So we might expect it to be accurate about 84% of the time.
		Quadrupling n should make it accurate at least 95% of the
time. Increasing n by  a factor of 9 should increase it to >99%.
*/

#include <random>
#include <chrono>


int main () {
	//The seed line is arbitrary, but to guarantee uniqueness, the system time is used
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);
	std::uniform_real_distribution<double> distribution(0,1);
	
	int n = 20833;
	int m = 0;
	for (int i = 0; i != n; i++){
		//+1 for x so it covers the limits of integration
		double x = distribution(generator) + 1;
		double y = distribution(generator);
		double reciprocal_x = 1/x;
		//simple increment for when y lies in the area of ln(2)
		if (y <= reciprocal_x) 
		{
			++m;
		}
	}
	
	//casting to make the division work
	double ln2Approx = (static_cast<double>(m)/n);
	printf("%.5g", ln2Approx);
	return 0;
}
