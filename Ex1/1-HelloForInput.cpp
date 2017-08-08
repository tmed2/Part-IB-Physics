#include <iostream>
using namespace std;


int main()
{
	int lucky, loopn;
	cout << "What is your favorite number?" << endl;
	cin >> lucky;
	cout << "What is your second favorite number?" << endl;
	cin >> loopn;
		
	for (int i = 1; i <= loopn; i++) {
		cout << i << "Hello word" << endl;
		if (i == lucky) {
			cout << "That was Lucky!" << endl;
		} else {
			cout << endl ;
		}
	}
	return 0;
}
