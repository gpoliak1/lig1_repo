#include <GL/gl.h>

#ifndef UTILS_H_
#define UTILS_H_

/************* POLYGON ****************/
extern int NumUs;
extern int NumVs;
extern GLenum shadeModel; // Toggles between GL_FLAT and GL_SMOOTH
extern GLenum polygonMode; // Toggles between GL_LINE and GL_FILL

/************* ANIMATION ****************/
extern GLenum runMode;
extern float RotX; // Rotational position around x-axis
extern float RotY; // Rotational position around y-axis
extern float RotZ; // Rotational position around z-axis
extern float RotIncrementX; // Rotational increment, x-axis
extern float RotIncrementY; // Rotational increment, y-axis
extern float RotIncrementZ; // Rotational increment, z-axis
extern const float RotIncFactor; // Factor change in rot rate per key stroke

extern float genRand();

extern void updateOrientation();
extern void ResetAnimation();
extern void ZeroRotation();
extern void ShadeModelToggle();
extern void FillModeToggle();
extern void MoreUs();
extern void LessUs();
extern void MoreVs();
extern void LessVs();


#endif /* UTILS_H_ */