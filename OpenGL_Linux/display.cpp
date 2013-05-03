#include "display.h"

#define ROT_INC			0.1
#define factor 			1
#define PI				3.14159265
#define RADIUS			5
#define NUM_OF_ANGLES	10
void drawGrid(void);
void setCamera(void);
void drawNumbers(const char *str1, const char *str2, const char *str3, float pos[3], float color[4], void *font);
static void (*drawPrimP)(void) = drawGrid;
void *font = GLUT_BITMAP_8_BY_13;
static GLfloat g_rotate = 0;
static GLfloat g_rotInc = ROT_INC;
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