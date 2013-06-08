/*  bezcurve.c
 *  This program uses evaluators to draw a Bezier curve.
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int interpolate(double, double, double, double, double, double, double, double,
		double, double, double, double, double, double);

typedef struct tagVector3D {
	double x, y, z;
} Vector3D;

double prePoints[4][3];
GLfloat ctrlPoints[4][3];

void initOpenGL(void) {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlPoints[0][0]); //need to resolve
	glEnable(GL_MAP1_VERTEX_3);
}

void display(void) {

	int i;
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble) (w) / (GLdouble) (h), 0.1, 40.0);
	gluLookAt(2.0, 2.0, 15.0, 2.0, 2.0, 0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINE_STRIP);
	for (i = 0; i <= 30; i++) {
		glEvalCoord1f((GLfloat) i / 30.0);
	}
	glEnd();

	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);

	glBegin(GL_POINTS);
	for (i = 0; i < 4; i++) {
		glVertex3fv(&ctrlPoints[i][0]);
	}
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glEnd();

	glFlush();
}

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

int interpolate(double p0x, double p0y, double p0z, double u, double p1x,
		double p1y, double p1z, double v, double p2x, double p2y, double p2z,
		double p3x, double p3y, double p3z) {

	double a = 0.0, b = 0.0, c = 0.0, d = 0.0, det = 0.0;
	Vector3D q1, q2;
	u = u / 100;
	v = v / 100;

	if ((u <= 0.0) || (u >= 1.0) || (v <= 0.0) || (v >= 1.0) || (u >= v))
		return 0; /* failure */

	a = 3 * (1 - u) * (1 - u) * u;
	b = 3 * (1 - u) * u * u;
	c = 3 * (1 - v) * (1 - v) * v;
	d = 3 * (1 - v) * v * v;
	det = a * d - b * c;
	/* unnecessary, but just in case... */
	if (det == 0.0)
		return 0; /* failure */

	prePoints[0][0] = p0x;
	prePoints[0][1] = p0y;
	prePoints[0][2] = p0z;
	prePoints[3][0] = p3x;
	prePoints[3][1] = p3y;
	prePoints[3][2] = p3z;

	q1.x = p1x - ((1 - u) * (1 - u) * (1 - u) * p0x + u * u * u * p3x);
	q1.y = p1y - ((1 - u) * (1 - u) * (1 - u) * p0y + u * u * u * p3y);
	q1.z = p1z - ((1 - u) * (1 - u) * (1 - u) * p0z + u * u * u * p3z);

	q2.x = p2x - ((1 - v) * (1 - v) * (1 - v) * p0x + v * v * v * p3x);
	q2.y = p2y - ((1 - v) * (1 - v) * (1 - v) * p0y + v * v * v * p3y);
	q2.z = p2z - ((1 - v) * (1 - v) * (1 - v) * p0z + v * v * v * p3z);

	prePoints[1][0] = d * q1.x - b * q2.x;
	prePoints[1][1] = d * q1.y - b * q2.y;
	prePoints[1][2] = d * q1.z - b * q2.z;
	prePoints[1][0] /= det;
	prePoints[1][1] /= det;
	prePoints[1][2] /= det;

	prePoints[2][0] = (-c) * q1.x + a * q2.x;
	prePoints[2][1] = (-c) * q1.y + a * q2.y;
	prePoints[2][2] = (-c) * q1.z + a * q2.z;
	prePoints[2][0] /= det;
	prePoints[2][1] /= det;
	prePoints[2][2] /= det;

	return 1; /* success */
}

void ask(void) {
	int i, j, result;
	char response;
	double u, v;

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 3; ++j) {
			prePoints[i][j] = 0.0;
		}
	}

	printf(
			"Enter the points, three components at a time (x y z) with a space between them.");

	printf("\nEnter u (0 - 100): ");
	scanf("%lf", &u);
	printf("Enter v (0 = 100): ");
	scanf("%lf", &v);

	printf("Enter the first point : ");
	scanf("%lf", &(prePoints[0][0]));
	scanf("%lf", &(prePoints[0][1]));
	scanf("%lf", &(prePoints[0][2]));

	printf("Enter the second point : ");
	scanf("%lf", &(prePoints[1][0]));
	scanf("%lf", &(prePoints[1][1]));
	scanf("%lf", &(prePoints[1][2]));

	printf("Enter the third point : ");
	scanf("%lf", &(prePoints[2][0]));
	scanf("%lf", &(prePoints[2][1]));
	scanf("%lf", &(prePoints[2][2]));

	printf("Enter the fourth point : ");
	scanf("%lf", &(prePoints[3][0]));
	scanf("%lf", &(prePoints[3][1]));
	scanf("%lf", &(prePoints[3][2]));

	result = interpolate(prePoints[0][0], prePoints[0][1], prePoints[0][2], u,
			prePoints[1][0], prePoints[1][1], prePoints[1][2], v,
			prePoints[2][0], prePoints[2][1], prePoints[2][2], prePoints[3][0],
			prePoints[3][1], prePoints[3][2]);

	if (result == 1) {
		printf("\nThe calculated control points are:");
		for (i = 0; i < 4; i++) {
			printf("\nPoint %d (%4.5f   %4.5f   %4.5f)", i + 1, prePoints[i][0],
					prePoints[i][1], prePoints[i][2]);
		}
		printf("\n");

	} else {
		printf("\nUnable to calculate Bezier control points.");
	}

	//Perform the conversion
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			ctrlPoints[i][j] = (GLfloat) prePoints[i][j];
		}
	}

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	ask();
	initOpenGL();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
