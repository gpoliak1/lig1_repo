#include "texture/lodepng.h"
#include "Utils.h"
#include "config.h"
#include "controlPoints/controlPointLoader.h"
#include "controlPoints/externVarDeclaration.h"
#include "models/leaves.h"
#include "models/treetrunk.h"

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#include <stdlib.h>
#include "SimpleNurbs.h"
#include <math.h>
#include <limits.h>
#include <GL/glut.h>

#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

/************* UTILS ****************/

void myKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
			runMode = !runMode;
			break;
		case 's':
			runMode = GL_TRUE;
			updateScene();
			runMode = GL_FALSE;
			break;
		case 27: // Escape key
			exit(1);
		case 'r': // Reset the animation (resets everything)
			ResetAnimation();
			break;
		case '0': // Zero the rotation rates
			ZeroRotation();
			break;
		case 'f': // Shade mode toggles from flat to smooth
			ShadeModelToggle();
			break;
		case 'p': // Polygon mode toggles between fill and line
			FillModeToggle();
			break;
		case 'u': // Decrement number of U's
			LessUs();
			break;
		case 'U': // Increment number of U's
			MoreUs();
			break;
		case 'v': // Decrement number of V's
			LessVs();
			break;
		case 'V': // Increment number of V's
			MoreVs();
			break;

		case 'i':
			eyeY += 1;
			targetY += 1;
			break;
		case 'k':
			eyeY -= 1;
			targetY -= 1;
			break;
		case 'j':
			eyeX -= 1;
			targetX -= 1;
			break;
		case 'l':
			eyeX += 1;
			targetX += 1;
			break;
		case 'x':
			eyeZ -= 1;
			targetZ -= 1;
			break;
		case 'z':
			eyeZ += 1;
			targetZ += 1;
			break;
		case 'n':
			eyeX = 0;
			eyeY = 0;
			eyeZ = 0;
			targetX = 0;
			targetY = 0;
			targetZ = -100;
			break;
		case 'b':
			eyeZ *= -1;
			targetZ = 0;
			break;
	}

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	float aspectRatio;
	glViewport(0, 0, w, h); // View port uses whole window
	h = (w == 0) ? 1 : h;
	aspectRatio = (float) w / (float) h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspectRatio, 1.0, 30.0);
	gluLookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

void mySpecialKeyFunc(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
			RotIncrementX = -0.5;
			break;
		case GLUT_KEY_UP:
			RotIncrementY = 0.5;
			break;
		case GLUT_KEY_RIGHT:
			RotIncrementZ = 0.5;
			break;
		case GLUT_KEY_DOWN:
			RotIncrementX = 0.0;
			RotIncrementY = 0.0;
			RotIncrementZ = 0.0;
			break;
	}
}

/************* TEXTURE FUNCS ****************/

void texDimenPowerOfTwo() {
	// Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
	while (u2 < width)
		u2 *= 2;
	while (v2 < height)
		v2 *= 2;
}

void loadTexture(const std::string& filename) {
	preArr.erase(preArr.begin(), preArr.end());
	lodepng::decode(preArr, width, height, filename);
	texDimenPowerOfTwo();
}

void buildTexImg2D(std::vector<unsigned char> fullArr, int texArrPos) {
	glBindTexture(GL_TEXTURE_2D, texName[texArrPos]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &fullArr[0]);
}

std::vector<unsigned char> makePowerOfTwo(size_t& u2, size_t& v2, std::vector<unsigned char>& incArr,
		std::vector<unsigned char>& outArr) {

	//for cropping, the top is lowered for height, right border moves left for width
	for (size_t y = 0; y < height; y++)
		for (size_t x = 0; x < width; x++)
			for (size_t c = 0; c < 4; c++) {
				outArr[4 * u2 * y + 4 * x + c] = incArr[4 * width * y + 4 * x + c];
			}

	return outArr;
}

void initTexture(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D); //made it change color
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(NUM_OF_TEXTURES, texName);

	loadTexture(TREE_TRUNK_TEXTURE);
	std::vector<unsigned char> brickArr(u2 * v2 * 4);
	brickArr = makePowerOfTwo(u2, v2, preArr, brickArr);
	buildTexImg2D(brickArr, 0);
}

/************* DISPLAY UTILS ****************/
void drawLines() {
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1, -100, 0);
	glVertex3f(-1, 100, 0);
	//
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	//
	glVertex3f(1, -100, 0);
	glVertex3f(1, 100, 0);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, -100);
	glVertex3f(0, 0, 100);

	glEnd();
	glEnable(GL_LIGHTING);
}

/************* DISPLAY ****************/
void updateScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float texel[2][2][2] =
		{
			{
				{0.0, 0.0},
				{1.0, 0.0}},
			{
				{0.0, 1.0},
				{1.0, 1.0}}};

	glPushMatrix();
	/********** UPDATE ORIENTATION **********/ //needs to be in a matrix
	updateOrientation();
	glRotatef(RotX, 1.0, 0.0, 0.0);
	glRotatef(RotY, 0.0, 1.0, 0.0);
	glRotatef(RotZ, 0.0, 0.0, 1.0);

	glScalef(0.5, 1.0, 0.5);
	glRotatef(-90, 1.0, 0.0, 0.0);

	for (int i = 0; i < NUM_PARTS; i++) {
		glPushMatrix();

		//glRotatef(-90, 1.0, 0.0, 0.0);
		glTranslatef(ctrlPtPartsArr[i].transX, ctrlPtPartsArr[i].transY, ctrlPtPartsArr[i].transZ);
		glScalef(ctrlPtPartsArr[i].scaleX, ctrlPtPartsArr[i].scaleY, ctrlPtPartsArr[i].scaleZ);
//		glRotatef(-90, 1.0, 0.0, 0.0);

		/********** POLYGON **********/
		glShadeModel(shadeModel);
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

		/********** MATERIAL **********/
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Matnonspec);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Matspec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Matshiny);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);

		/********** DRAW BEZIER AND TEXTURIZE **********/
		glEnable(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, texName[0]);

		glMap2f(GL_MAP2_VERTEX_4, 0, 1, 4, 4, 0, 1, 16, 4, ctrlPtPartsArr[i].points);
		glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texel[0][0][0]);
		glMapGrid2f(NumUs, 0, 1, NumVs, 0, 1);
		glEvalMesh2(GL_FILL, 0, NumUs, 0, NumVs);
		glDisable(GL_TEXTURE);
		glPopMatrix();
	}
//	glPopMatrix();

	//leaves
	for (int i = 0; i < NUM_OF_LEAVES; i++) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);

		glTranslatef(leaves[i].transX, leaves[i].transZ, leaves[i].transY); //leaves[i].transZ);

//		std::cout << "***X is: " << leaves[i].transX << " - Y is: " << leaves[i].transY << "\n";

		glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0.5, 0, 0.5);
		glVertex3f(0, 0, 0.5);
		glEnd();

//		std::cout << "\n\n";
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	glPopMatrix();

	////////////////////////////////////////////////////////
//	glPushMatrix();
//	glTranslatef(1, 0, 0);
//	/********** POLYGON **********/
//	glShadeModel(shadeModel);
//	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
//
//	/********** MATERIAL **********/
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Matnonspec);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Matspec);
//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Matshiny);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);
//
//	/********** UPDATE ORIENTATION **********/
//	updateOrientation();
//
//	glRotatef(RotX, 1.0, 0.0, 0.0);
//	glRotatef(RotY, 0.0, 1.0, 0.0);
//
//	/********** DRAW BEZIER AND TEXTURIZE **********/
//	glEnable(GL_TEXTURE);
//	glBindTexture(GL_TEXTURE_2D, texName[0]);
//	glMap2f(GL_MAP2_VERTEX_4, 0, 1, 4, 4, 0, 1, 16, 4, &ctrlpoints_D[0][0][0]);
//	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2,
//			&texel[0][0][0]);
//	glMapGrid2f(NumUs, 0, 1, NumVs, 0, 1);
//	glEvalMesh2(GL_FILL, 0, NumUs, 0, NumVs);
//	glDisable(GL_TEXTURE);
//	glPopMatrix();
	////////////////////////////////////////////////////////

	/********** DRAW LINES **********/
	glPushMatrix();
	drawLines();
	glPopMatrix();

	/********** DRAW LIGHT BOXES **********/
	glPushMatrix();
	glDisable(GL_LIGHTING);

	glLoadIdentity();
	glTranslatef(1.0, 0.0, 1.0);
	glColor3f(1, 1, 1);
	glutWireCube(0.75);

	glLoadIdentity();
	glTranslatef(0.0, 1.0, 1.0);
	glColor3f(1, 1, 1);
	glutWireCube(0.75);

	glEnable(GL_LIGHTING);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();

}

/************* INIT ****************/
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_MAP2_VERTEX_4);

	glEnable(GL_LIGHTING); // Enable lighting calculations
	glEnable(GL_LIGHT0); // Turn on lights (unnecessary here, since also in Animate()
	glEnable(GL_LIGHT1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight); // Ambient light
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Phong light backsides

	// Next line is suspicious, perhaps compensating for OpenGL bug
	glFrontFace(GL_CW); // Is needed for Bezier Patches (OpenGL bug??)

	// Light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, Lt0amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Lt0spec);
	glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

	// Light 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, Lt1amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Lt1diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Lt1spec);
	glLightfv(GL_LIGHT1, GL_POSITION, Lt1pos);
}

void resizeWindow(int w, int h) {
	float aspectRatio;
	glViewport(0, 0, w, h); // View port uses whole window
	h = (w == 0) ? 1 : h;
	aspectRatio = (float) w / (float) h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspectRatio, 1.0, 30.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glTranslatef(0.0, 0.0, -10.0);
//	glRotatef(15.0, 1.0, 0.0, 0.0);
}



/************* MAIN ****************/
int main(int argc, char** argv) {

	loadMasterArr();
	genLeaves();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(10, 60);
	glutInitWindowSize(620, 160);
	glutCreateWindow("Nurbs demo");

	initRendering();
	initTexture();
	resizeWindow(620, 160);

	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyFunc);
	glutReshapeFunc(resizeWindow);
	glutIdleFunc(updateScene);
	glutDisplayFunc(updateScene);
	glutMainLoop();

	return 0;
}
