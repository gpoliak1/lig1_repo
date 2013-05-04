#include "util.h"

#define PI				3.14159265
#define RADIUS			5
#define NUM_OF_ANGLES	10

using namespace std;
using namespace glm;

float Grid::trigSinVals[10];
float Grid::trigCosVals[10];

void Util::loadTrigValsIntoArr(void) {
	Grid::trigCosVals[0] = (RADIUS * cos(360*PI/180));
	Grid::trigSinVals[0] = (RADIUS * sin(360*PI/180));
	Grid::trigCosVals[1] = (RADIUS * cos(36*PI/180));
	Grid::trigSinVals[1] = (RADIUS * sin(36*PI/180));
	Grid::trigCosVals[2] = (RADIUS * cos(72*PI/180));
	Grid::trigSinVals[2] = (RADIUS * sin(72*PI/180));
	Grid::trigCosVals[3] = (RADIUS * cos(108*PI/180));
	Grid::trigSinVals[3] = (RADIUS * sin(108*PI/180));
	Grid::trigCosVals[4] = (RADIUS * cos(144*PI/180));
	Grid::trigSinVals[4] = (RADIUS * sin(144*PI/180));
	Grid::trigCosVals[5] = (RADIUS * cos(180*PI/180));
	Grid::trigSinVals[5] = (RADIUS * sin(180*PI/180));
	Grid::trigCosVals[6] = (RADIUS * cos(216*PI/180));
	Grid::trigSinVals[6] = (RADIUS * sin(216*PI/180));
	Grid::trigCosVals[7] = (RADIUS * cos(252*PI/180));
	Grid::trigSinVals[7] = (RADIUS * sin(252*PI/180));
	Grid::trigCosVals[8] = (RADIUS * cos(288*PI/180));
	Grid::trigSinVals[8] = (RADIUS * sin(288*PI/180));
	Grid::trigCosVals[9] = (RADIUS * cos(324*PI/180));
	Grid::trigSinVals[9] = (RADIUS * sin(324*PI/180));
	int i;
	for (i=0; i<NUM_OF_ANGLES; i++) {
		printf("\nCos: %f", Grid::trigCosVals[i]);
		printf("\nSin: %f", Grid::trigSinVals[i]);
	}
}