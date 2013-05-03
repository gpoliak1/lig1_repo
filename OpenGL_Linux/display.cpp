#include "display.h"

void OglDisplay::doOglDisplay(float solidZ, GLuint sphereList, float transparentZ, GLuint cubeList) {

	GLfloat mat_solid[] = {0.75, 0.75, 0.0, 1.0};
	GLfloat mat_zero[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat mat_transparent[] = {0.0, 0.8, 0.8, 0.6};
	GLfloat mat_emission[] = {0.0, 0.3, 0.3, 0.6};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(-0.15, -0.15, solidZ);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
	glCallList(sphereList);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.15, 0.15, transparentZ);
	glRotatef(15.0, 1.0, 1.0, 0.0);
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glCallList(cubeList);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPopMatrix();

	glutSwapBuffers();
}