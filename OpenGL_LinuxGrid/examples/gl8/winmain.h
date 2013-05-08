// winmain.h

// from:  www.falloutsoftware.com
// by:    Greg Damon (gregd@falloutsoftware.com)
// ---------------------------------------------

#define WINDOWED		0					// predefined flags for initialization
#define FULLSCREEN		1

#define SCRWIDTH		640					// width of the window
#define SCRHEIGHT		480					// height of the window
#define SCRDEPTH		16					// bit depth

#define WNDCLASSNAME	"GLClass"			// window class name
#define WNDNAME			"OpenGL base code"	// string that will appear in the title bar

extern HDC hdc;								// device context handle
extern HGLRC hglrc;							// OpenGL rendering context
extern HWND hwnd;							// window handle

extern int screenw;							// when window is resized, the new dimensions...
extern int screenh;							// ...are stored in these variables
extern int screenmode;						// FULLSCREEN or WINDOWED?

extern bool quit;							// indicates the state of application

extern indexPixelFormat;					// number of available pixel formats
