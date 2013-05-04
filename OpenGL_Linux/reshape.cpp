#include <iostream>
#include <stdio.h>
#include <string.h>
#include "reshape.h"

#define MAX_LINE_LEN 256

using namespace std;
using namespace glm;

	float Grid::eyeX;
	float Grid::eyeY;
	float Grid::eyeZ;
	float Grid::lookatX;
	float Grid::lookatY;
	float Grid::lookatZ;
	int Grid::multiplierXZ;
	int Grid::multiplierYZ;
	float Grid::trigSinVals[10];
	float Grid::trigCosVals[10];

void Reshape::doReshape(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); /* init projection matrix */
    gluPerspective( 60.0, (GLdouble)w/(GLdouble)h, 0.1, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glScalef(1.0, 1.0, -1.0);
    gluLookAt(Grid::eyeX, Grid::eyeY, Grid::eyeZ,
              Grid::lookatX, Grid::lookatY, Grid::lookatZ,
              0.0, 1.0, 0.0);

	printf("%s","\nreshape");
    
}