#include "util.h"

#define PI				3.14159265
#define RADIUS			5

using namespace std;
using namespace glm;

float Grid::trigSinVals[40];
float Grid::trigCosVals[40];

void Util::loadTrigValsIntoArr(void) {
	Grid::trigCosVals[0] = (RADIUS * cos(360 * PI / 180));
	Grid::trigSinVals[0] = (RADIUS * sin(360 * PI / 180));
	Grid::trigCosVals[1] = (RADIUS * cos(9 * PI / 180));
	Grid::trigSinVals[1] = (RADIUS * sin(9 * PI / 180));
	Grid::trigCosVals[2] = (RADIUS * cos(18 * PI / 180));
	Grid::trigSinVals[2] = (RADIUS * sin(18 * PI / 180));
	Grid::trigCosVals[3] = (RADIUS * cos(27 * PI / 180));
	Grid::trigSinVals[3] = (RADIUS * sin(27 * PI / 180));
	Grid::trigCosVals[4] = (RADIUS * cos(36 * PI / 180));
	Grid::trigSinVals[4] = (RADIUS * sin(36 * PI / 180));
	Grid::trigCosVals[5] = (RADIUS * cos(45 * PI / 180));
	Grid::trigSinVals[5] = (RADIUS * sin(45 * PI / 180));
	Grid::trigCosVals[6] = (RADIUS * cos(54 * PI / 180));
	Grid::trigSinVals[6] = (RADIUS * sin(54 * PI / 180));
	Grid::trigCosVals[7] = (RADIUS * cos(63 * PI / 180));
	Grid::trigSinVals[7] = (RADIUS * sin(63 * PI / 180));
	Grid::trigCosVals[8] = (RADIUS * cos(72 * PI / 180));
	Grid::trigSinVals[8] = (RADIUS * sin(72 * PI / 180));
	Grid::trigCosVals[9] = (RADIUS * cos(81 * PI / 180));
	Grid::trigSinVals[9] = (RADIUS * sin(81 * PI / 180));
	Grid::trigCosVals[10] = (RADIUS * cos(90 * PI / 180));
	Grid::trigSinVals[10] = (RADIUS * sin(90 * PI / 180));
	Grid::trigCosVals[11] = (RADIUS * cos(99 * PI / 180));
	Grid::trigSinVals[11] = (RADIUS * sin(99 * PI / 180));
	Grid::trigCosVals[12] = (RADIUS * cos(108 * PI / 180));
	Grid::trigSinVals[12] = (RADIUS * sin(108 * PI / 180));
	Grid::trigCosVals[13] = (RADIUS * cos(117 * PI / 180));
	Grid::trigSinVals[13] = (RADIUS * sin(117 * PI / 180));
	Grid::trigCosVals[14] = (RADIUS * cos(126 * PI / 180));
	Grid::trigSinVals[14] = (RADIUS * sin(126 * PI / 180));
	Grid::trigCosVals[15] = (RADIUS * cos(135 * PI / 180));
	Grid::trigSinVals[15] = (RADIUS * sin(135 * PI / 180));
	Grid::trigCosVals[16] = (RADIUS * cos(144 * PI / 180));
	Grid::trigSinVals[16] = (RADIUS * sin(144 * PI / 180));
	Grid::trigCosVals[17] = (RADIUS * cos(153 * PI / 180));
	Grid::trigSinVals[17] = (RADIUS * sin(153 * PI / 180));
	Grid::trigCosVals[18] = (RADIUS * cos(162 * PI / 180));
	Grid::trigSinVals[18] = (RADIUS * sin(162 * PI / 180));
	Grid::trigCosVals[19] = (RADIUS * cos(171 * PI / 180));
	Grid::trigSinVals[19] = (RADIUS * sin(171 * PI / 180));
	Grid::trigCosVals[20] = (RADIUS * cos(180 * PI / 180));
	Grid::trigSinVals[20] = (RADIUS * sin(180 * PI / 180));
	Grid::trigCosVals[21] = (RADIUS * cos(189 * PI / 180));
	Grid::trigSinVals[21] = (RADIUS * sin(189 * PI / 180));
	Grid::trigCosVals[22] = (RADIUS * cos(198 * PI / 180));
	Grid::trigSinVals[22] = (RADIUS * sin(198 * PI / 180));
	Grid::trigCosVals[23] = (RADIUS * cos(207 * PI / 180));
	Grid::trigSinVals[23] = (RADIUS * sin(207 * PI / 180));
	Grid::trigCosVals[24] = (RADIUS * cos(216 * PI / 180));
	Grid::trigSinVals[24] = (RADIUS * sin(216 * PI / 180));
	Grid::trigCosVals[25] = (RADIUS * cos(225 * PI / 180));
	Grid::trigSinVals[25] = (RADIUS * sin(225 * PI / 180));
	Grid::trigCosVals[26] = (RADIUS * cos(234 * PI / 180));
	Grid::trigSinVals[26] = (RADIUS * sin(234 * PI / 180));
	Grid::trigCosVals[27] = (RADIUS * cos(243 * PI / 180));
	Grid::trigSinVals[27] = (RADIUS * sin(243 * PI / 180));
	Grid::trigCosVals[28] = (RADIUS * cos(252 * PI / 180));
	Grid::trigSinVals[28] = (RADIUS * sin(252 * PI / 180));
	Grid::trigCosVals[29] = (RADIUS * cos(261 * PI / 180));
	Grid::trigSinVals[29] = (RADIUS * sin(261 * PI / 180));
	Grid::trigCosVals[30] = (RADIUS * cos(270 * PI / 180));
	Grid::trigSinVals[30] = (RADIUS * sin(270 * PI / 180));
	Grid::trigCosVals[31] = (RADIUS * cos(279 * PI / 180));
	Grid::trigSinVals[31] = (RADIUS * sin(279 * PI / 180));
	Grid::trigCosVals[32] = (RADIUS * cos(288 * PI / 180));
	Grid::trigSinVals[32] = (RADIUS * sin(288 * PI / 180));
	Grid::trigCosVals[33] = (RADIUS * cos(297 * PI / 180));
	Grid::trigSinVals[33] = (RADIUS * sin(297 * PI / 180));
	Grid::trigCosVals[34] = (RADIUS * cos(306 * PI / 180));
	Grid::trigSinVals[34] = (RADIUS * sin(306 * PI / 180));
	Grid::trigCosVals[35] = (RADIUS * cos(315 * PI / 180));
	Grid::trigSinVals[35] = (RADIUS * sin(315 * PI / 180));
	Grid::trigCosVals[36] = (RADIUS * cos(324 * PI / 180));
	Grid::trigSinVals[36] = (RADIUS * sin(324 * PI / 180));
	Grid::trigCosVals[37] = (RADIUS * cos(333 * PI / 180));
	Grid::trigSinVals[37] = (RADIUS * sin(333 * PI / 180));
	Grid::trigCosVals[38] = (RADIUS * cos(342 * PI / 180));
	Grid::trigSinVals[38] = (RADIUS * sin(342 * PI / 180));
	Grid::trigCosVals[39] = (RADIUS * cos(351 * PI / 180));
	Grid::trigSinVals[39] = (RADIUS * sin(351 * PI / 180));
	int i;
	for (i = 0; i < numOfAngles; i++) {
		printf("\nCos: %f", Grid::trigCosVals[i]);
		printf("\nSin: %f", Grid::trigSinVals[i]);
	}
}
