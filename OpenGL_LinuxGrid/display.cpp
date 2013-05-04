#include "display.h"

using namespace std;

#define ROT_INC			0.1
#define factor 			1
#define PI				3.14159265
#define RADIUS			5
#define NUM_OF_ANGLES	10

void *font = GLUT_BITMAP_8_BY_13;

void OglDisplay::doOglDisplay(float solidZ, GLuint sphereList, float transparentZ, GLuint cubeList) {


}

void OglDisplay::drawGrid(void) {
	float color[4] = {0.0, 0.0, 1.0, 0.0};

	int a, b, c;
	for (a=0; a<10; a++) {
		for (b=0; b<10; b++) {
			for (c=0; c<10; c++) {

				float pos[3];
				pos[0] = (float)a;
				pos[1] = (float)b;
				pos[2] = (float)c;

				char buffer1 [5];
				char buffer3 [5];
				char buffer5 [5];
				char final [50];

				int n;
				n = sprintf(buffer1, "%d", a);
				n = sprintf(buffer3, "%d", b);
				n = sprintf(buffer5, "%d", c);

				int d;
				for(d=0; d<2; d++)
					final[d] = buffer1[d];

				for(d=0; d<2; d++)
					final[d+2] = buffer3[d];

				for(d=0; d<2; d++)
					final[d+4] = buffer5[d];

				final[d+6] = (char)'\0';

				for(d=0; d<5; d++)
					//printf("%c", final[d]);

					//printf("%s", " ");
					if (((a % factor) == 0) && ((b % factor) == 0) && ((c % factor) == 0)) {
						drawNumbers(buffer1, buffer3, buffer5, pos, color, font);
					}
			}
		}
	}

	glBegin(GL_LINES);
	int i;

	for(i=0; i<=10; i++) {
		if ((i % factor) == 0) {
			int j;
			for (j=0; j<=10; j++) {
				if ((j % factor) == 0) {
					glVertex3f(i,0,j);
					glVertex3f(i,10,j);

					glVertex3f(0,i,j);
					glVertex3f(10,i,j);
				}
			}

			int k;
			for (k=0; k<=10; k++) {
				if ((k % factor) == 0) {
					glVertex3f(i,k,0);
					glVertex3f(i,k,10);

					glVertex3f(0,k,i);
					glVertex3f(10,k,i);
				}
			}
		}
	}
	glEnd();

}

void OglDisplay::drawNumbers(const char *str1, const char *str2, const char *str3, float pos[3], float color[4], void *font)
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

