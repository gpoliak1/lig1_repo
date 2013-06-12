#include "Utils.h"

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

/************* POLYGON ****************/
int NumUs = 4;
int NumVs = 4;
GLenum shadeModel = GL_FLAT; // Toggles between GL_FLAT and GL_SMOOTH
GLenum polygonMode = GL_LINE; // Toggles between GL_LINE and GL_FILL

/************* ANIMATION ****************/
GLenum runMode = GL_TRUE;
float RotX = 0.0f; // Rotational position around x-axis
float RotY = 0.0f; // Rotational position around y-axis
float RotZ = 0.0f; // Rotational position around z-axis
float RotIncrementX = 0.0; // Rotational increment, x-axis
float RotIncrementY = 0.0; // Rotational increment, y-axis
float RotIncrementZ = 0.0; // Rotational increment, z-axis
const float RotIncFactor = 1.5; // Factor change in rot rate per key stroke

float genRand() {

	float f = (float) (rand() % 32767) / (float) 32767;

	return f;
}

void updateOrientation() {
	// Update the orientation, if the animation is running.
	if (runMode) {
		RotX += RotIncrementX;
		if (fabs(RotX) > 360.0) {
			RotX -= 360.0 * ((int) (((RotX / 360.0))));
		}
		RotY += RotIncrementY;
		if (fabs(RotY) > 360.0) {
			RotY -= 360.0 * ((int) (((RotY / 360.0))));
		}
		RotZ += RotIncrementZ;
		if (fabs(RotZ) > 360.0) {
			RotZ -= 360.0 * ((int) (((RotZ / 360.0))));
		}
	}

}

void ResetAnimation() {
	RotX = RotY = RotZ = RotIncrementX = RotIncrementY = RotIncrementZ = 0.0;
}

void ZeroRotation() {
	RotIncrementX = RotIncrementY = RotIncrementZ = 0.0;
}

void ShadeModelToggle() {
	if (shadeModel == GL_FLAT) {
		shadeModel = GL_SMOOTH;
	} else {
		shadeModel = GL_FLAT;
	}
}

void FillModeToggle() {
	if (polygonMode == GL_LINE) {
		polygonMode = GL_FILL;
	} else {
		polygonMode = GL_LINE;
	}
}

void MoreUs() {
	NumUs++;
}

void LessUs() {
	if (NumUs > 4) {
		NumUs--;
	}
}

void MoreVs() {
	NumVs++;
}

void LessVs() {
	if (NumVs > 4) {
		NumVs--;
	}
}


