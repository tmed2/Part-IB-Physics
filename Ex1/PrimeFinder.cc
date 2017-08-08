//Prime Tester/Finder
/*
Primes are tested using a common "less than square root" factor method

Limited when input > 2^31 - 1; 2^31 - 1 will be returned
(seemingly) accurate for input < 2^31 - 1
Answer: the standard int type will only repesent intergers
>= 2^31 - 1, which also happens to be prime.
solution? use unsigned long type to extend the 
memory of the variables. Problem, compuation
time significant for larger numbers. Implementation 
for larger numbers left for another day; better
algorithm needed.
*/
#include <iostream>
#include <cmath>


int main () {
	int n, i, m;
	bool p;
	
	std::cout << "Give me a natural number. I'll give you the first prime greater than, or equal, to it" << std::endl;
	std::cin >> n;
	
	p = false;
	while (not p) {
		
		/*The 'if'/'else if' statements handle the special cases
		  which the 'for loop' can't detect*/
		  
		if (n <= 1) {
			n = 2 ;
			p = true;
		}
		else if  (n == 2 or n == 3) {
			p = true;
		} 
		else {
			
			/*m is an int type; the decimals will be truncated automatically
			m is updated every time the while-loop-block is excecuted*/
			m = sqrt(n);
			
			for (i = 2; i <= m; i++) {
				if (n % i == 0) {
					p = false;
					/*Increment n to try next highest number
					  when primality test fails*/
					n++;
					//to avoid further, unnecessary, work
					break;
				} else {
					p = true;
				}
			}
		}
	}
	
	std::cout << n << " is the first prime number after the input (inclusive)." << std::endl;
	
return 0;
}
