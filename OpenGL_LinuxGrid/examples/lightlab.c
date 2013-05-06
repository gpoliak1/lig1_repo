#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <GL/glut.h>

enum {
  RED_PLASTIC
} MaterialType;
enum {
  TORUS_MATERIAL = 1
} MaterialDisplayList;
enum {
  LIGHT_RED, LIGHT_GREEN
} LightValues;

GLfloat red_light[] = {1.0, 0.0, 0.0, 1.0}; 
GLfloat green_light[] = {0.0, 1.0, 0.0, 1.0};
GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
GLfloat left_light_position[] = {-1.0, 0.0, 1.0, 0.0};
GLfloat right_light_position[] = {1.0, 0.0, 1.0, 0.0};
GLfloat red_plastic_ambient[] = {0.0, 0.0, 0.0}; 
GLfloat red_plastic_diffuse[] = {0.5, 0.0, 0.0};
GLfloat red_plastic_specular[] = {0.7, 0.6, 0.6};
GLfloat red_plastic_shininess = 32.0;

int shade_model = GL_SMOOTH;

void 
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();
  	glScalef(1.3, 1.3, 1.3);
  	glRotatef(20.0, 1.0, 0.0, 0.0);
  	glPushMatrix();
  		glTranslatef(-0.65, 0.7, 0.0);
  		glRotatef(90.0, 1.0, 0.0, 0.0);
  		glCallList(TORUS_MATERIAL);
  		glutSolidTorus(0.275, 0.85, 10, 15);
  	glPopMatrix();
  glPopMatrix();

  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);

  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, 3000, 0, 3000);
  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();
  	glLoadIdentity();
  	glPopMatrix();
  	glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glPopAttrib();

  glutSwapBuffers();
}



int 
main(int argc, char **argv)
{
  glutInitWindowSize(400, 400);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Lighting Laboratory");
  glutDisplayFunc(display);

  glLightfv(GL_LIGHT0, GL_POSITION, left_light_position);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
  glLightfv(GL_LIGHT1, GL_POSITION, right_light_position);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);

  glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light);
  //glutPostRedisplay();

  glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, green_light);
  //glutPostRedisplay();

  glNewList(TORUS_MATERIAL, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT, red_plastic_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red_plastic_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, red_plastic_specular);
  glMaterialf(GL_FRONT, GL_SHININESS, red_plastic_shininess);
  glEndList();

  //glutPostRedisplay();

  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  //glLineWidth(1.0);
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* degrees field of view */ 50.0,
    /* aspect ratio */ 1.0, /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.);
  glTranslatef(0.0, 0.0, -1.0);

  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
