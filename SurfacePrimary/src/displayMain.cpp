#include "displayMain.h"
#include "utils/lodepng.h"
#include "utils/utils.h"
#include "utils/textureUtils.h"
#include "config.h"
#include "controlPoints/controlPointLoader.h"
#include "controlPoints/controlPointArrs.h"
#include "models/leaves.h"
#include "models/treetrunk.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <GL/gl.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

void declareLights() {
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

//Init
void initRendering() {

	genLeaves();
	declareLights();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_MAP2_VERTEX_4);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	// Next line is suspicious, perhaps compensating for OpenGL bug
	glFrontFace(GL_CW);
	// Light 0
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

//Config-specific display util
void displayLightBoxes() {
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
}

void displayLeaves(int i) {
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
}

void display(void) {

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

		displayLeaves(i);

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

	//Display extras
	glPushMatrix();
	drawLines();
	glPopMatrix();

	glPushMatrix();
	displayLightBoxes();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h) {
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

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(10, 60);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Primary OpenGL");

	loadControlPointsArr();
	initRendering();
	initTexture();
	reshape(windowWidth, windowHeight);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}