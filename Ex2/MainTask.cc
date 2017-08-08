//Probability finder
/*
Sums the probabilities for certain values of
some random variable, x, occurring. This can be
done for the binomial and Poisson distributions

The program gives seemingly accurate values (tested 
with a coin flipping example. But will fail as 
the factorials becomes very large.

After playing around with the Factorial function
I found that it could represent up to 170! inclusive
(Interestingly Google will only return up to
170!) So, so long as you never enter more than 
170 for any number that is factorialised, then it should
be ok, ish.

The program produces interesting results when the 
wrong type is given in the input. I can't implement 
type based exceptions now; I don't know how.
*/
#include <iostream>
#include <cmath>
#include <stdio.h>


/*Simple factorial function used in the program
Doubles are used as the values need not be integrals,
and higher numbers can be represented */
double Factorial(unsigned int n) {
	double fact, i;
	fact = 1;
	for (i = 0; i !=n; i++) {
		fact *= (i + 1);
	}
	return fact;
}

/*Combinations function made, mainly, to make
the main() tidier*/
double Combo(unsigned int n, unsigned int r) {
	double nF = Factorial(n);
	double rF = Factorial(r);
	double n_rF = Factorial(n-r);
	
	return nF/(rF*n_rF);
}

int main () {
	char dist;
	std::cout << "This program will compute P(X <= n) for some given value." << std::endl;
	std::cout << "You can do this for the discrete random variable X which," << std::endl;
	std::cout << "has a binomial (b), or Poisson (p) distribution." << std::endl;
	std::cout << "Enter you distribution choice character now:" << std::endl;
	
	//starts a loop to find the user's choice, or ask again if there is a problem
	bool loop = true;
	while (loop) {
		std::cin >> dist;
		
		//switch statement allows for false input to be recognised
		switch (dist) {
			
			//the binomial case
			case 'b':
				/*block defined so as not to raise errors when variables
				are defined in the scope of switch, but not used outside 
				of a single case. I can also re-use variable names as long
				as they are different block scopes :D*/
				{
					double prob;
					int trials, n, i;
					
					bool loop2 = true;
					while (loop2) {
						std::cout << "What is the probability of success?" << std::endl;
						std::cin >> prob;
						std::cout << "How many trials are you running?" << std::endl;
						std::cin >> trials;
						std::cout << "What is the maximum number of successes you want?" << std::endl;
						std::cin >> n;
						
						//Catches for various error making sad things
						//can't catch type based errors yet, e.g. n = 0.5, prob = lol ....
						if (n > 170 || trials > 170) {
							std::cout << "I'm sorry, 171 or more trials or successes is too large to handle" << std::endl;
						}
						else if (n < 0 || trials < 0) {
							std::cout << "Are you sure about the successes or trials?" << std::endl;

						}
						else if (n > trials) {
							std::cout << "Don't choose more successes that trials" << std::endl;
						}
						else if (prob <= 0 || prob >= 1) {
							std::cout << "Think twice about that probability" << std::endl;
						}
						else {
							loop2 = false;
						}
						
					}
					
					
					double sumOf = 0;
					for (i = 0; i != (n + 1); i++) {
						//calculation of P(X == n)
						double combo = Combo(trials, i);
						double XeqlN = combo*(pow(prob, i))*(pow(1 - prob, trials - i));
						
						//printf used for interpolation and precision
						printf("P(X == %d) = %.10g \n", i, XeqlN);
						//summing for P(X <= n)
						sumOf += XeqlN;
						}
						
						printf("P(X <= %d) = %.10g", n, sumOf);
						loop = false;
						break;
				}
				
			//the Poisson case
			case 'p':
				{
					double rate;
					int n, i;
					
					bool loop2 = true;
					while (loop2) {
						std::cout << "What is the mean rate of X?" << std::endl;
						std::cin >> rate;
						std::cout << "What is the maximum number of successes you want?" << std::endl;
						std::cin >> n;
						
						
						/*i can't be greater than 170, and a double can't be greater
						than ~1.8 x10^308, and NthRoot(m) -> 1 for large N, so the maximum rate must be:*/
						float ratelim = pow(10, 308.0/170);
						//Catches for various error making sad things
						if (rate <= 0) {
							std::cout << "Think twice about the rate" << std::endl;
						}
						else if (rate >= ratelim) {
							std::cout << "I'm sorry the max rate is circa 64.8, consider looking over a longer period" << std::endl;
						}
						else if (n > 170 ) {
							std::cout << "I'm sorry, 171 events or more is too large to handle" << std::endl;
						}
						else if (n < 0) {
							std::cout << "Think twice about the number of successes" << std::endl;
						}
						else {
							loop2 = false;
						}
					}
					
					double sumOf = 0;
					for (i = 0; i!= (n + 1); i++) {
						//calculation of P(X == n)
						double XeqlN = (exp(-rate)*pow(rate, i))/(Factorial(i));
						
						//printf used for interpolation and precision
						printf("P(X == %d) = %.10g \n", i, XeqlN);
						//summing for P(X <= n)
						sumOf += XeqlN;
					}
					
					//May give 1 for large values of n
					printf("P(X <= %d) = %.10g in the given period for the rate" , n, sumOf);
					loop = false;
					break;
				}
				
			//forces the user to input 'p' or 'b'
			default:
				std::cout << "Please enter b or p" << std::endl;
				break;
		}
	}
	
	return 0;
}
