#include <GL/gl.h>
#include <vector>

#define NUM_OF_TEXTURES		2

#ifndef CONFIG_H_
#define CONFIG_H_

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

#endif /* CONFIG_H_ */
