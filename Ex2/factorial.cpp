#include <iostream>


int main () {
	int fact, i, n;
	fact = 1;
	n = 10;
	for (i = 0; i !=n; i++) {
		fact *= (i + 1);
	}
	std::cout << fact << std::endl;
	return 0;
}
