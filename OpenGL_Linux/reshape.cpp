#include <iostream>
#include <stdio.h>
#include <string.h>
#include "reshape.h"

#define MAX_LINE_LEN 256

float eyeX = 0.0;
float eyeY = 0.0;
float eyeZ = -10.0;
float lookatX = 0.0;
float lookatY = 0.0;
float lookatZ = -15.0;

int multiplierXZ = 0;
int multiplierYZ = 0;
float trigSinVals[10];
float trigCosVals[10];

using namespace std;
using namespace glm;

void Reshape::doReshape(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); /* init projection matrix */
    gluPerspective( 60.0, (GLdouble)w/(GLdouble)h, 0.1, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glScalef(1.0, 1.0, -1.0);
    gluLookAt(eyeX, eyeY, eyeZ,
              lookatX, lookatY, lookatZ,
              0.0, 1.0, 0.0);

	printf("%s","\nreshape");
    
}