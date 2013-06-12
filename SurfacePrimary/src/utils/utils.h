#include <GL/gl.h>

#ifndef UTILS_H_
#define UTILS_H_

extern float genRand();
extern void drawLines();

extern void updateOrientation();
extern void ResetAnimation();
extern void ZeroRotation();
extern void ShadeModelToggle();
extern void FillModeToggle();
extern void MoreUs();
extern void LessUs();
extern void MoreVs();
extern void LessVs();

extern void keyboard(unsigned char key, int x, int y);
extern void specialKeyboard(int key, int x, int y);

#endif /* UTILS_H_ */
