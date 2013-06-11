#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <stdio.h>
using namespace std;

int main() {

	srand(time(0));

	float h = 0;

	for (int nCount = 0; nCount < 10000; ++nCount) {

		float f = rand();//(float) (rand() % 32767) / (float) 32767;
		cout << f << "\t";
		h += f;

		if ((nCount + 1) % 5 == 0)
			cout << endl;
	}

	h = h / 10000;

	printf("AVG IS: %f", h);
}
