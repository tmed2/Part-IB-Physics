#include <iostream>
#include <stdio.h>
#include <cmath>

/*
//Sum of first n odd numbers
int main() {
	int oddSum, i;
	oddSum = 0;
	
	std::cout << "The sum of:" << std::endl;
	for (i = 0; i != 10; i++) {
		std::cout << i << std::endl;
		oddSum += (2*i + 1);
	}
	
	std::cout << "is..." << std::endl;
	std::cout << oddSum;
	
	return 0;
}
*/


/*
//first series given
int main () {
	float term;
	int n = 20;
	
	
	// i terms have been printed so far
	term = 1;
	for (int i = 0; i !=n; i++ ) { 
		std::cout << term << std::endl;
		term = 1 + 1/term ;
	}
	return 0;
}
*/


//second series given
int main () {
	double term;
	int n = 100;
	
	
	// i terms have been printed so far
	term = 2;
	int T_0 = term;
	for (int i = 0; i != n; i++ ) { 
		printf("%.18g", term);
		std::cout << std::endl;
		term = T_0 + 1/term ;
	}
	return 0;
}


/*
//third series given
int main () {
	double term;
	int n = 20;
	
	
	// i terms have been printed so far
	term = 1;
	for (int i = 0; i != n; i++ ) { 
		printf("%.18g", term);
		std::cout << std::endl;
		term = sqrt(1 + term);
	}
	return 0;
}
*/
