//RandDemo.cc
// 	usage:
//		./RandDemo [<N> [<seed>]]
//	example:
//		./RandDemo 
//		./RandDemo 30 9237832
//	* uses random() to get random integer
//	* gets parameters from the command line

#include <iostream>
#include <cstdlib>
#include <cstdio>

#define randf() \
	((double)rand()/(RAND_MAX))
	
int main (int argc, char* argv[]) {
	int outcome, N = 30, count_in = 0, seed = 123;
	double fraction_in;
	
	if (argc > 1) {
		sscanf( argv[1], "%d", &N);
	}
	if (argc > 2) {
		sscanf( argv[2], "%d", &seed);
	}
	
	std::cout << "# " << argv[0] << " N = " << N << " Seed = " << seed << std::endl;
	
	for(int n = 1; n <= N; n++) {
		double x = randf();
		double y = randf();
		outcome = (x*x + y*y < 1.0) ? 1 : 0;
		count_in += outcome;
		fraction_in = static_cast<double>(count_in)/n;
		std::cout << "Location " << outcome << "\t" << x << "\t" << y << "\t"
		<< count_in << "\t" << n << "\t" << 4.0 * fraction_in << std::endl;
	}
} 
