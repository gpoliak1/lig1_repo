// system.h

// from:  www.falloutsoftware.com
// by:    Greg Damon (gregd@falloutsoftware.com)
// ---------------------------------------------

extern char sysBuffer[128];

void SysShutdown (void);			// SysShutdown: shutdowns the application and releases memory
void SysShutdownMSG (char *sMSG);	// SysShutdownMSG: destroys the application and outputs an error string within a Message Box
void SysSetDisplayMode (int width, int height, int depth); // SysSetDisplayMode: sets display mode
void SysRecoverDisplayMode (void);	// SysRecoverDisplayMode: switch back to default resolution
