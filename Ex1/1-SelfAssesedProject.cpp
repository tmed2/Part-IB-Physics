//Prime Tester/Finder
#include <iostream>
#include <cmath>


int main () {
	int n, i, m;
	bool p;
	
	std::cout << "Give me a number, and see if it's a prime" << std::endl;
	std::cin >> n;
	
	// m is an int type; the decimals will be truncated automatically
	m = sqrt(n);
	
	/*The 'if' statement handles the special cases
	  which the 'for loop' can't detect*/
	  
	if (n == 2 or n == 3) {
		p = true;
	} else {
		for (i = 2; i <= m; i++) {
			if (n % i == 0) {
				p = false;
				//to avoid further, unnecessary, work
				break;
			} else {
				p = true;
			}
		}
	}
	
	if (p) {
		std::cout << n << " is a prime number." << std::endl;
	} else {
		std::cout << n << " is not a prime number. It is composite." << std::endl;
	}
	
return 0;
}
