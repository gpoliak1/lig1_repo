/*
 LodePNG Examples

 Copyright (c) 2005-2012 Lode Vandevenne

 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:

 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.

 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.

 3. This notice may not be removed or altered from any source
 distribution.
 */

//Compile command for Linux:
//g++ lodepng.cpp example_opengl.cpp -lSDL -lGL -O3
/*
 LodePNG OpenGL example. Decodes a PNG and shows it in OpenGL. PNG filename
 should be given as a command line parameter.

 It's written for the most basic old OpenGL version, and a correction for non
 power of two textures had to be added.

 Only very few lines on the sample are about loading the PNG. Most of the
 sample lines show a way to render a texture in 2D in OpenGL.

 No fancy 3D graphics are shown, it only shows the image statically. The sample
 shows LodePNG can be used to load PNG images as textures in OpenGL.
 */

#include "lodepng.h"

#include <iostream>
//#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glut.h>

size_t u2 = 1;
size_t v2 = 1;
double u3;
double v3;
std::vector<unsigned char> image;
unsigned width, height;

//General values
float eyeX = 4.0;
float eyeY = 4.0;
float eyeZ = 2.0;
float lookatX = 0.0;
float lookatY = 0.0;
float lookatZ = -15.0;

void init() {
	const char* filename = "bricks.png"; //argv[1];

	// Load file and decode image.
	lodepng::decode(image, width, height, filename);

	// Here the PNG is loaded in "image". All the rest of the code is SDL and OpenGL stuff.
	int screenw = width;
	if (screenw > 1024)
		screenw = 1024;
	int screenh = height;
	if (screenh > 768)
		screenw = 768;

	// The official code for "Setting Your Raster Position to a Pixel Location" (i.e. set up a camera for 2D screen)
	glViewport(0, 0, screenw, screenh);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Make some OpenGL properties better for 2D and enable alpha channel.
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

	// Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
	size_t u2 = 1;
	while (u2 < width)
		u2 *= 2;
	size_t v2 = 1;
	while (v2 < height)
		v2 *= 2;
	// Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
	u3 = (double) width / u2;
	v3 = (double) height / v2;

	// Make power of two version of the image.
	std::vector<unsigned char> image2(u2 * v2 * 4);
	for (size_t y = 0; y < height; y++)
		for (size_t x = 0; x < width; x++)
			for (size_t c = 0; c < 4; c++) {
				image2[4 * u2 * y + 4 * x + c] =
						image[4 * width * y + 4 * x + c];
			}

	// Enable the texture for OpenGL.
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			&image2[0]);

}

void display(void) {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble) w / (GLdouble) h, 0.1, 40.0);
	gluLookAt(eyeX, eyeY, eyeZ, lookatX, lookatY, lookatZ, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	glTranslatef(-2.0, -2.0, -4.6);
	glScalef(7.0, 7.0, 7.0);

	glBegin(GL_QUADS);

	glTexCoord2d(0, 0);
	glVertex2f(0, 0);

	glTexCoord2d(1, 0);
	glVertex2f(1, 0);

	glTexCoord2d(1, 1);
	glVertex2f(1, 1);

	glTexCoord2d(0, 1);
	glVertex2f(0, 1);

	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 30.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glTranslatef(-2.0, -2.0, -4.6);
//	glScalef(7.0, 7.0, 7.0);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
//	   glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

