#include "grid.h"

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
#include <glm/glm.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <map>

#ifndef _OGLDISPLAY_H
#define _OGLDISPLAY_H

namespace OglDisplay 
{
void doOglDisplay(float, GLuint, float, GLuint);
};

#endif

//void display(void)
//{	
//	OglDisplay::doOglDisplay(solidZ, sphereList, transparentZ, cubeList);
//}