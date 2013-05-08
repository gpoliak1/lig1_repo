// OpenGL  base code
// updated: april 2004

// system.cpp - system code; shutdown,
// release memory, system misc.

// from:  www.falloutsoftware.com
// by:    Greg Damon (gregd@falloutsoftware.com)
// ---------------------------------------------

#include "glbase.h"

char sysBuffer[128];

void SysShutdown (void)
{
	wglMakeCurrent(hdc, NULL);		// release device context in use by rc
	wglDeleteContext(hglrc);		// delete rendering context

	PostQuitMessage(0);				// make sure the window will be destroyed

	if (screenmode == FULLSCREEN)	// if FULLSCREEN, change back to original resolution
		SysRecoverDisplayMode();
}

void SysShutdownMSG (char *sMSG)
{
	MessageBox(hwnd, sMSG, "ShutdownMSG", MB_OK);
	SysShutdown();
}

void SysSetDisplayMode (int width, int height, int depth)
{	
	DEVMODE dmode;
	
	memset(&dmode, 0, sizeof(DEVMODE));
	dmode.dmSize=sizeof(DEVMODE);
	dmode.dmPelsWidth = width;
	dmode.dmPelsHeight = height;
	dmode.dmBitsPerPel = depth;
	dmode.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;
	
	// change resolution, if possible
	if (ChangeDisplaySettings(&dmode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		// if not... failed to change resolution

		// this prevents SysShutdown from changing resolution back
		screenmode = 0;

		MessageBox(NULL, "Your system doesn't support this screen resolution", "Display Error", MB_OK);
		SysShutdown();
	}
}

void SysRecoverDisplayMode (void)
{
	ChangeDisplaySettings(NULL, 0);
}
