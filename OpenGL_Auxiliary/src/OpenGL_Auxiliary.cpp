/* texture.c
 * This program reads in a single image from a .rgb file, uses the
 * utility routine gluScaleImage() to scale the image, if
 * necessary, sets up the minification and magnification filter,
 * and then uses glTexImage2D() to load the image into texture
 * memory. It then applies the texture to a rectangular polygon
 * using explicit texture coordinates.
 *
 *     <a> key     - toggle animation on/off
 *     Escape Key      - exit program
 */

#include <GL/glut.h>    /* includes gl.h, glu.h */

#include <math.h>
#include <stdio.h>

#include "texture.h"   /* should be in ../../include */

/*  Function Prototypes  */

GLvoid initgfx(GLvoid);
GLvoid animate(GLvoid);
GLvoid visibility(GLint);
GLvoid drawScene(GLvoid);
GLvoid reshape(GLsizei, GLsizei);
GLvoid keyboard(GLubyte, GLint, GLint);

GLvoid initTexture(GLubyte *, GLsizei, GLsizei);

static GLuint nearestPower(GLuint);

void printHelp(char *progname);

/* Global Definitions */

#define KEY_ESC 27  /* ascii value for the escape key */

/* Global Variables */

static GLfloat swim = 1.0;

static GLboolean animateFlag = GL_TRUE;

void main(int argc, char *argv[]) {
	char *imageFileName = "fish.rgba";
	GLubyte *image;
	GLsizei width, height;
	GLsizei imageWidth, imageHeight, components;

	glutInit(&argc, argv);

	if (argc < 2) {
		fprintf(stderr, "usage: %s [imageFileName]\n", argv[0]);
	} else
		imageFileName = argv[1];

	fprintf(stdout, "using image %s\n\n", imageFileName);

	image = read_texture(imageFileName, &imageWidth, &imageHeight, &components);

	/* create a window that is 1/4 the size of the screen */

	width = glutGet(GLUT_SCREEN_WIDTH);
	height = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((width / 2) + 4, height / 4);
	glutInitWindowSize((width / 2) - 4, height / 2);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);

	initTexture(image, imageWidth, imageHeight);
	initgfx();

	glutKeyboardFunc(keyboard);
	glutIdleFunc(animate);
	glutVisibilityFunc(visibility);
	glutReshapeFunc(reshape);
	glutDisplayFunc(drawScene);

	printHelp(argv[0]);

	glutMainLoop();
}

GLvoid printHelp(char *progname) {
	fprintf(stdout, "\n%s - demonstrates basic texture mapping\n"
			"<a> key      - toggle animation on/off\n"
			"Escape key   - exit the program\n\n", progname);
}

GLvoid initgfx(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

/* Compute the nearest power of 2 number that is
 * less than or equal to the value passed in.
 */
static GLuint nearestPower(GLuint value) {
	int i = 1;

	if (value == 0)
		return -1; /* Error! */
	for (;;) {
		if (value == 1)
			return i;
		else if (value == 3)
			return i * 4;
		value >>= 1;
		i *= 2;
	}
}

GLvoid initTexture(GLubyte *image, GLsizei imageWidth, GLsizei imageHeight) {
	GLsizei sWidth, sHeight;
	GLubyte *sImage;

	/* Find the largest power of two dimensions that are
	 * less than or equal to the size of the image
	 */
	sWidth = nearestPower(imageWidth);
	sHeight = nearestPower(imageHeight);

	printf("input image size: %dx%d\n", imageWidth, imageHeight);
	printf("scaled image size: %dx%d\n", sWidth, sHeight);

	/* scale texture image to 2^m by 2^n if necessary */
	if (sWidth == imageWidth && sHeight == imageHeight) {
		sImage = (GLubyte *) image;
	} else {
		sImage = (GLubyte *) malloc(sHeight * sWidth * 4 * sizeof(GLubyte));
		gluScaleImage(GL_RGBA, imageWidth, imageHeight, GL_UNSIGNED_BYTE, image,
				sWidth, sHeight, GL_UNSIGNED_BYTE, sImage);
	}

	/* Setting the minification and magnification filters
	 * to nearest instead of linear, may run faster on some
	 * platforms, with possibly lower quality
	 */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	/* Set the minification filter to something other than
	 * the default (GL_NEAREST_MIPMAP_LINEAR)
	 */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/* load texture */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sWidth, sHeight, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, sImage);

	/* enable 2D texture mapping */
	glEnable(GL_TEXTURE_2D);
}

GLvoid keyboard(GLubyte key, GLint x, GLint y) {
	switch (key) {
	case 'a': /* toggle animation */
		animateFlag = !animateFlag;
		if (animateFlag)
			glutIdleFunc(animate);
		else
			glutIdleFunc(NULL);
		break;
	case KEY_ESC: /* Exit whenever the Escape key is pressed */
		exit(0);
	}
}

GLvoid animate(GLvoid) {
	swim = fmod(swim + 0.1, 35.0);

	/* Tell GLUT to redraw the scene */
	glutPostRedisplay();
}

GLvoid visibility(int state) {
	if (state == GLUT_VISIBLE && animateFlag) {
		glutIdleFunc(animate);
	} else {
		glutIdleFunc(NULL);
	}
}

GLvoid reshape(GLsizei width, GLsizei height) {
	GLdouble aspect;

	glViewport(0, 0, width, height);

	aspect = (GLdouble) width / (GLdouble) height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -12.0);
}

GLvoid drawScene(void) {
	static float v0[3] = { -1.5, -1.0, 0.0 };
	static float v1[3] = { 1.5, -1.0, 0.0 };
	static float v2[3] = { 1.5, 1.0, 0.0 };
	static float v3[3] = { -1.5, 1.0, 0.0 };

	static float t0[2] = { 0.0, 0.0 };
	static float t1[2] = { 1.0, 0.0 };
	static float t2[2] = { 1.0, 1.0 };
	static float t3[2] = { 0.0, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(-6.0 + swim, 0.2 * sin(swim * 3.0), -swim);

	glBegin(GL_QUADS);
	glTexCoord2fv(t0);
	glVertex3fv(v0);
	glTexCoord2fv(t1);
	glVertex3fv(v1);
	glTexCoord2fv(t2);
	glVertex3fv(v2);
	glTexCoord2fv(t3);
	glVertex3fv(v3);
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}
