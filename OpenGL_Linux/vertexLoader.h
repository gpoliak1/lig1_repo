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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <sstream>

#ifndef _VERTEXLOADER_H
#define _VERTEXLOADER_H

namespace VertexLoader 
{
	struct Vertex;
	struct VertRef;
	extern std::vector<Vertex> doObjLoad(void);
};

#endif

//void doObjLoad(void)
//{	
//	Vertex::doObjLoad();
//}