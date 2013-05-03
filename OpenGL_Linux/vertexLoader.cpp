#include "vertexLoader.h"

#define ROT_INC			0.1
#define factor 			1
#define PI				3.14159265
#define RADIUS			5
#define NUM_OF_ANGLES	10
void drawGrid(void);
void setCamera(void);
void drawNumbers(const char *str1, const char *str2, const char *str3, float pos[3], float color[4], void *font);
static void (*drawPrimP)(void) = drawGrid;
void *font = GLUT_BITMAP_8_BY_13;
static GLfloat g_rotate = 0;
static GLfloat g_rotInc = ROT_INC;
float eyeX = 0.0;
float eyeY = 0.0;
float eyeZ = -10.0;
float lookatX = 0.0;
float lookatY = 0.0;
float lookatZ = -15.0;
int multiplierXZ = 0;
int multiplierYZ = 0;
float trigSinVals[10];
float trigCosVals[10];

using namespace std;
using namespace glm;

struct Vertex
{
    vec3 position;
    vec2 texcoord;
    vec3 normal;
};

struct VertRef
{
    VertRef( int v, int vt, int vn )
        : v(v), vt(vt), vn(vn)
    { }
    int v, vt, vn;
};

vector< Vertex >  VertexLoader::doObjLoad(void)
{	
	vector< Vertex > verts;



	return verts;
}