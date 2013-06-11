#include <stdio.h>

#include "externVarDeclaration.h"
#include "function_set.h"

int main() {
	printf("The extern'd var is %d\n", i);

	i = 20;
	print();

	i = 333;
	print2();

	changeI();

	printf("My oh my!  the extern'd var has changed to %d\n", i);

	for (int j = 0; j < 4; j++) {
		int a = arr[j];
	}
}
