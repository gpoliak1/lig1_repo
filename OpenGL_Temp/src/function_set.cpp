#include "function_set.h"

void print() {
	printf("func1 %d\n", i);
}

void print2() {
	printf("func2 %d\n", i);
}

void print3() {
	printf("func3 %d\n", i);
}

void changeI() {
	// i is shared across the whole project
	i = 2000402;
}
