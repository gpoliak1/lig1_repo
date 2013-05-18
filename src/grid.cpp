#include "display.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
using namespace glm;

//General values
float eyeX = 0.0;
float eyeY = 0.0;
float eyeZ = 15.0;
float lookatX = 0.0;
float lookatY = 0.0;
float lookatZ = -15.0;
int multiplierXZ = 20;
int multiplierYZ = 20;

//Basic Config
#define STEPINCR		0.5
#define ROT_INC			0.1
#define FACTOR 			1
bool gridOn = false;

struct Vertex {
	vec3 position;
	vec2 texcoord;
	vec3 normal;
};

struct VertRef {
	VertRef(int v, int vt, int vn) :
			v(v), vt(vt), vn(vn) {
	}
	int v, vt, vn;
};

vector<Vertex> models[2];

vector<Vertex> LoadOBJ(istream& in) {
	vector<Vertex> verts;

	vector<vec4> positions(1, vec4(0, 0, 0, 0));
	vector<vec3> texcoords(1, vec3(0, 0, 0));
	vector<vec3> normals(1, vec3(0, 0, 0));
	string lineStr;
	while (getline(in, lineStr)) {
		istringstream lineSS(lineStr);
		string lineType;
		lineSS >> lineType;

		// vertex
		if (lineType == "v") {
			float x = 0, y = 0, z = 0, w = 1;
			lineSS >> x >> y >> z >> w;
			positions.push_back(vec4(x, y, z, w));
		}

		// texture
		if (lineType == "vt") {
			float u = 0, v = 0, w = 0;
			lineSS >> u >> v >> w;
			texcoords.push_back(vec3(u, v, w));
		}

		// normal
		if (lineType == "vn") {
			float i = 0, j = 0, k = 0;
			lineSS >> i >> j >> k;
			normals.push_back(normalize(vec3(i, j, k)));
		}

		// polygon
		if (lineType == "f") {
			vector<VertRef> refs;
			string refStr;
			while (lineSS >> refStr) {
				istringstream ref(refStr);
				string vStr, vtStr, vnStr;
				getline(ref, vStr, '/');
				getline(ref, vtStr, '/');
				getline(ref, vnStr, '/');
				int v = atoi(vStr.c_str());
				int vt = atoi(vtStr.c_str());
				int vn = atoi(vnStr.c_str());
				v = (v >= 0 ? v : positions.size() + v);
				vt = (vt >= 0 ? vt : texcoords.size() + vt);
				vn = (vn >= 0 ? vn : normals.size() + vn);
				refs.push_back(VertRef(v, vt, vn));
			}

			if (refs.size() < 3) {
				// error, skip
				continue;
			}

			// triangulate, assuming n>3-gons are convex and coplanar
			VertRef* p[3] = { &refs[0], NULL, NULL };
			for (size_t i = 1; i + 1 < refs.size(); ++i) {
				p[1] = &refs[i + 0];
				p[2] = &refs[i + 1];

				vec3 U(positions[p[1]->v] - positions[p[0]->v]);
				vec3 V(positions[p[2]->v] - positions[p[0]->v]);
				vec3 faceNormal = normalize(cross(U, V));

				for (size_t j = 0; j < 3; ++j) {
					Vertex vert;
					vert.position = vec3(positions[p[j]->v]);
					vert.texcoord = vec2(texcoords[p[j]->vt]);
					vert.normal = (
							p[j]->vn != 0 ? normals[p[j]->vn] : faceNormal);
					verts.push_back(vert);
				}
			}
		}
	}

	return verts;
}

void moveForward() {
	if ((lookatX - eyeX) > 0) {
		eyeX += STEPINCR;
		lookatX += STEPINCR;
	} else if ((lookatX - eyeX) < 0) {
		eyeX -= STEPINCR;
		lookatX -= STEPINCR;
	}

	if ((lookatY - eyeY) > 0) {
		eyeY += STEPINCR;
		lookatY += STEPINCR;
	} else if ((lookatY - eyeY) < 0) {
		eyeY -= STEPINCR;
		lookatY -= STEPINCR;
	}

	if ((lookatZ - eyeZ) > 0) {
		eyeZ += STEPINCR;
		lookatZ += STEPINCR;
	} else if ((lookatZ - eyeZ) < 0) {
		eyeZ -= STEPINCR;
		lookatZ -= STEPINCR;
	}
}

void moveBackward() {
	if ((lookatX - eyeX) > 0) {
		eyeX -= STEPINCR;
		lookatX -= STEPINCR;
	} else if ((lookatX - eyeX) < 0) {
		eyeX += STEPINCR;
		lookatX += STEPINCR;
	}

	if ((lookatY - eyeY) > 0) {
		eyeY -= STEPINCR;
		lookatY -= STEPINCR;
	} else if ((lookatY - eyeY) < 0) {
		eyeY += STEPINCR;
		lookatY += STEPINCR;
	}

	if ((lookatZ - eyeZ) > 0) {
		eyeZ -= STEPINCR;
		lookatZ -= STEPINCR;
	} else if ((lookatZ - eyeZ) < 0) {
		eyeZ += STEPINCR;
		lookatZ += STEPINCR;
	}
}

void keyboard(unsigned char k, int x, int y) {

	switch (k) {
	case 'q':
	case 'Q':
		exit(0);
		break;

	case 'f':

		moveForward();
		glutPostRedisplay();
		break;

	case 'b':

		moveBackward();
		glutPostRedisplay();
		break;

	default:
		printf("Unknown keyboard command \'%c\'.\n", k);
		break;
	}
}

void lookLeft() {
	if (multiplierXZ != 0) {
		multiplierXZ--;
	} else {
		multiplierXZ = Util::numOfAngles - 1;
	}
	lookatX = Grid::trigSinVals[multiplierXZ] + eyeX;
	lookatZ = Grid::trigCosVals[multiplierXZ] + eyeZ;

	printf("@@@ %f lookatX is: ", lookatX);
	printf("@@@ %f lookatZ is: ", lookatZ);
}

void lookRight() {
	if (multiplierXZ != (Util::numOfAngles - 1)) {
		multiplierXZ++;
	} else {
		multiplierXZ = 0;
	}
	lookatX = Grid::trigSinVals[multiplierXZ] + eyeX;
	lookatZ = Grid::trigCosVals[multiplierXZ] + eyeZ;
	printf("\nAngle XZ: %d", multiplierYZ * 36);
}

void lookUp() {
	if (multiplierYZ != 0) {
		multiplierYZ--;
	} else {
		multiplierYZ = Util::numOfAngles - 1;
	}
	lookatY = Grid::trigSinVals[multiplierYZ] + eyeY;
	lookatZ = Grid::trigCosVals[multiplierYZ] + eyeZ;
	printf("\nAngle YZ: %d", multiplierYZ * 36);
}

void lookDown() {
	if (multiplierYZ != Util::numOfAngles - 1) {
		multiplierYZ++;
	} else {
		multiplierYZ = 0;
	}
	lookatY = Grid::trigSinVals[multiplierYZ] + eyeY;
	lookatZ = Grid::trigCosVals[multiplierYZ] + eyeZ;
}

void processSpecialKeys(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:

		lookLeft();
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:

		lookRight();
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:

		lookUp();
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:

		lookDown();
		glutPostRedisplay();
		break;
	}

}

void display(void) {
	printf("%s%g%s%g%s%g", "\nDISPLAY - Camera now positioned at ", eyeX, ",",
			eyeY, ",", eyeZ);
	printf("%s%g%s%g%s%g%s", "\nDISPLAY - Looking at ", lookatX, ",", lookatY,
			",", lookatZ, "\n");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	// set up "headlamp"-like light
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat position[] = { 0, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble) w / (GLdouble) h, 0.1, 40.0);

	gluLookAt(eyeX, eyeY, eyeZ, lookatX, lookatY, lookatZ, 0.0, 1.0, 0.0);

	/** grid */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(1.0, 1.0, 1.0);
	glTranslatef(-1, -1, -1);
	glColor3ub(0, 0, 180);

	if (gridOn) {
		OglDisplay::drawGrid();
	}

	/** stone */
	int j;
	for (j = 0; j < 1; j++) {
		glColor3ub(180, 0, 0);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &models[j][0].position);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &models[j][0].texcoord);
		glNormalPointer(GL_FLOAT, sizeof(Vertex), &models[j][0].normal);
		glDrawArrays(GL_TRIANGLES, 0, models[j].size());
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}

	/** stone 2 */
	/*glColor3ub( 0, 180, 0 );
	 glTranslatef(-5, -1, -1);

	 glEnableClientState( GL_VERTEX_ARRAY );
	 glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	 glEnableClientState( GL_NORMAL_ARRAY );
	 glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), &models[j][0].position );
	 glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &models[j][0].texcoord );
	 glNormalPointer( GL_FLOAT, sizeof(Vertex), &models[j][0].normal );
	 glDrawArrays( GL_TRIANGLES, 0, models[j].size() );
	 glDisableClientState( GL_VERTEX_ARRAY );
	 glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	 glDisableClientState( GL_NORMAL_ARRAY );*/

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); /* init projection matrix */
	gluPerspective(60.0, (GLdouble) w / (GLdouble) h, 0.1, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(1.0, 1.0, -1.0);
	gluLookAt(eyeX, eyeY, eyeZ, lookatX, lookatY, lookatZ, 0.0, 1.0, 0.0);

	printf("%s", "\nreshape");
}

void mouse(int btn, int state, int x, int y) {

}

void idle(void) {

}

int main(int argc, char **argv) {
	//from objloader
	ifstream stone("test.obj");
	ifstream stone2("test.obj");
	ifstream stone3("test.obj");
	ifstream stone4("test.obj");
	ifstream stone5("test.obj");
	models[0] = LoadOBJ(stone);
	models[1] = LoadOBJ(stone2);
	models[2] = LoadOBJ(stone3);
	models[3] = LoadOBJ(stone4);
	models[4] = LoadOBJ(stone5);

	glutInit(&argc, argv);
	Util::loadTrigValsIntoArr();
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutReshapeFunc(reshape);
	glutCreateWindow("3D GRID");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(mouse);

	/*glEnable( GL_DEPTH_TEST );

	 // set up "headlamp"-like light
	 glShadeModel( GL_SMOOTH );
	 glEnable( GL_COLOR_MATERIAL );
	 glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
	 glEnable( GL_LIGHTING );
	 glEnable( GL_LIGHT0 );*/

	//glMatrixMode(GL_PROJECTION);
	//gluLookAt(-10, 0, 5, 0, 0, 5, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(1.0, 1.0, -1.0);
	glTranslatef(-1, -1, -1);

	/*GLfloat position[] = { 0, 0, 1, 0 };
	 glLightfv( GL_LIGHT0, GL_POSITION, position );*/

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	lookLeft();

	glutMainLoop();

	return 0;
}

