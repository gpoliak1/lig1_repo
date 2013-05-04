#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <pthread.h>
#include <glm/glm.hpp>
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <map>

#ifndef _GRID_H
#define _GRID_H

using namespace std;

extern map<string,string> doReadParse();

class Grid {

public:
	static map<string,float> map1;
	static void init(void);
	void display(void);
	void reshape(int w, int h);

	void keyboard(unsigned char key, int x, int y);

	void performSwitch(char c);
	void* print_message_function( void *ptr );
	void* SocketHandler(void*);


	void animate(void);

	void mouseClick(int button);

	static float eyeX;
	static float eyeY;
	static float eyeZ;
	static float lookatX;
	static float lookatY;
	static float lookatZ;
	static int multiplierXZ;
	static int multiplierYZ;
	static float trigSinVals[10];
	static float trigCosVals[10];
private:



};

#endif