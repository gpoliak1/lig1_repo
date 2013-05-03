#include <iostream>
#include <stdio.h>
#include <string.h>
#include "reshape.h"

#define MAX_LINE_LEN 256

using namespace std;

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