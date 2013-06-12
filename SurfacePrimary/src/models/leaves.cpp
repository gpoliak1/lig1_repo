#include "leaves.h"
#include "../utils/utils.h"

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <GL/glut.h>

#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#define NUM_OF_LEAVES		400
#define TREE_TRUNK_TEXTURE "texture/wood.png"

float leafBox_StartX = -5;
float leafBox_EndX = 5;
float leafBox_StartY = 9;
float leafBox_EndY = 15;
float leafBox_StartZ = -5;
float leafBox_EndZ = 5;

float xSpan = leafBox_EndX - leafBox_StartX;
float ySpan = leafBox_EndY - leafBox_StartY;
float zSpan = leafBox_EndZ - leafBox_StartZ;

struct leaf leaves[NUM_OF_LEAVES];

void genLeaves() {

	srand(5888);

	for (int i = 0; i < NUM_OF_LEAVES; i++) {

		float randFloat = genRand();
		leaves[i].transX = (xSpan * randFloat) + leafBox_StartX;

		randFloat = genRand();
		leaves[i].transY = (ySpan * randFloat) + leafBox_StartY;

		randFloat = genRand();
		leaves[i].transZ = (zSpan * randFloat) + leafBox_StartZ;

		printf("Gen X is: %f - Gen Y is: %f - Gen Z is: %f - \n", leaves[i].transX, leaves[i].transY,
				leaves[i].transZ);
	}
}
