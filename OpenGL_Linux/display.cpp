#include "display.h"

void OglDisplay::doOglDisplay(float solidZ, GLuint sphereList, float transparentZ, GLuint cubeList) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidSphere(1.0, 20, 16);
	glFlush();
}