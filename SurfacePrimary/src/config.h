#include <GL/gl.h>
#include <vector>

#define NUM_OF_TEXTURES		2

#ifndef CONFIG_H_
#define CONFIG_H_

extern int windowWidth;
extern int windowHeight;

/************* LIGHTING ****************/
extern float ambientLight[4];
extern float Lt0amb[4];
extern float Lt0diff[4];
extern float Lt0spec[4];
extern float Lt0pos[4];

extern float Lt1amb[4];
extern float Lt1diff[4];
extern float Lt1spec[4];
extern float Lt1pos[4];

/************* MATERIAL ****************/
extern float Noemit[4];
extern float Matspec[4];
extern float Matnonspec[4];
extern float Matshiny;

/************* TEXTURE ****************/
extern GLuint texName[NUM_OF_TEXTURES];
extern size_t u2;
extern size_t v2;
extern double u3, v3;
extern unsigned width, height;
extern std::vector<unsigned char> preArr;

/************* CAMERA ****************/
extern float eyeX;
extern float eyeY;
extern float eyeZ;
extern float targetX;
extern float targetY;
extern float targetZ;

/************* POLYGON ****************/
extern int NumUs;
extern int NumVs;
extern GLenum shadeModel; // Toggles between GL_FLAT and GL_SMOOTH
extern GLenum polygonMode; // Toggles between GL_LINE and GL_FILL

/************* ANIMATION ****************/
extern GLenum runMode;
extern float RotX;
extern float RotY;
extern float RotZ;
extern float RotIncrementX;
extern float RotIncrementY;
extern float RotIncrementZ;
extern float RotIncFactor;

#endif /* CONFIG_H_ */
