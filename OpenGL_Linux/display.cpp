#include "display.h"

#define ROT_INC			0.1
#define factor 			1
#define PI				3.14159265
#define RADIUS			5
#define NUM_OF_ANGLES	10

void *font = GLUT_BITMAP_8_BY_13;
static GLfloat g_rotate = 0;
static GLfloat g_rotInc = ROT_INC;
static void (*drawPrimP)(void) = drawGrid;

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

void drawGrid(void);

void drawNumbers(const char *str1, const char *str2, const char *str3, float pos[3], float color[4], void *font);
static void (*drawPrimP)(void) = drawGrid;

using namespace std;
using namespace glm;

struct Vertex
{
    vec3 position;
    vec2 texcoord;
    vec3 normal;
};

struct VertRef
{
    VertRef( int v, int vt, int vn )
        : v(v), vt(vt), vn(vn)
    { }
    int v, vt, vn;
};


vector< Vertex > model;

void OglDisplay::doOglDisplay(float solidZ, GLuint sphereList, float transparentZ, GLuint cubeList) {

    printf("%s%g%s%g%s%g", "\nDISPLAY - Camera now positioned at ", eyeX, ",", eyeY, ",", eyeZ);
    printf("%s%g%s%g%s%g%s", "\nDISPLAY - Looking at ", lookatX, ",", lookatY, ",", lookatZ, "\n");

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective( 60.0, (GLdouble)w/(GLdouble)h, 0.1, 40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glScalef(1.0, 1.0, -1.0);
	glTranslatef(-1,-1,-1);

    gluLookAt(eyeX, eyeY, eyeZ,lookatX, lookatY, lookatZ,0.0, 1.0, 0.0);
    glColor3ub( 0, 0, 180 );
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), &model[0].position );
    glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &model[0].texcoord );
    glNormalPointer( GL_FLOAT, sizeof(Vertex), &model[0].normal );
    glDrawArrays( GL_TRIANGLES, 0, model.size() );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );
	(*drawPrimP)();
    glPopMatrix();

    glutSwapBuffers();
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

void drawGrid(void) {

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