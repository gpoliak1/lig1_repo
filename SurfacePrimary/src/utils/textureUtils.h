#include <GL/gl.h>
#include <vector>
#include <string>

#ifndef TEXTUREUTILS_H_
#define TEXTUREUTILS_H_

extern void texDimenPowerOfTwo();
extern void loadTexture(const std::string& filename);
extern void buildTexImg2D(std::vector<unsigned char> fullArr, int texArrPos);
extern std::vector<unsigned char> makePowerOfTwo(size_t& u2, size_t& v2, std::vector<unsigned char>& incArr,
		std::vector<unsigned char>& outArr);

#endif /* TEXTUREUTILS_H_ */
