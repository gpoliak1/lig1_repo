#include <iostream>
#include <stdio.h>
#include <string.h>
#include "reshape.h"

#define MAX_LINE_LEN 256

using namespace std;

void Reshape::doReshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w, 1.5*(GLfloat)w/(GLfloat)h, -10.0, 10.0);
	} else {
		glOrtho(-1.5*(GLfloat)h/(GLfloat)w, 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
        
    
}