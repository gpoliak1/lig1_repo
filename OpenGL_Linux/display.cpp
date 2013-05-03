#include "display.h"

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