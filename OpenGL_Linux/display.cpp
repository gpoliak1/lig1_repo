#include "display.h"

void OglDisplay::doOglDisplay(float solidZ, GLuint sphereList, float transparentZ, GLuint cubeList) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidSphere(1.0, 20, 16);
	glFlush();
}

void drawNumbers(const char *str1, const char *str2, const char *str3, float pos[3], float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);// need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);

    glColor4fv(color);
    glRasterPos3fv(pos);

    glutBitmapCharacter(font, *str1);
    glutBitmapCharacter(font, ',');
    glutBitmapCharacter(font, *str2);
    glutBitmapCharacter(font, ',');
    glutBitmapCharacter(font, *str3);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}