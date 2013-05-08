// openGL basecode defines
// www.falloutsoftware.com

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0300 // force direct input 3
#endif

#ifndef DINPUT_H_
#include <dinput.h>
#define DINPUT_H_
#endif

typedef bool bit;
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;
typedef LARGE_INTEGER int64;
typedef int fixed32;

typedef struct char2_s
{
	char *c1;
	char *c2;
} char2_t;
