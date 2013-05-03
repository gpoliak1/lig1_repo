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

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

namespace Keyboard 
{
void doKeyboard(unsigned char, int, int, float, float, float, float, float, float, float);
};

#endif