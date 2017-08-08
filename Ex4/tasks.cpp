//Estimates the square root of some number using interval bisection

#include <iostream>
#include <cmath>

float MySquareRoot(float v);
float Quad(float x, float c);


int main() {
	float Root = MySquareRoot(2);
	std::cout << Root << std::endl;
	return 0;	
}


//Here begin the function definitions
float Quad(float x, float c) {
	float quad = c - x*x;
	return quad;
}

float MySquareRoot(float square) {
	int i;
	float a = 0.1, b = 10.1, mid, lower, p;
	
	for (i = 0; i != 100; i++) {
		p = (a + b)/2;
		mid = Quad(p, square);
		lower = Quad(a, square);
		
		if (lower*mid < 0) {
			b = p;
		} else {
			a = p;
		}
	}
	return p;
}
