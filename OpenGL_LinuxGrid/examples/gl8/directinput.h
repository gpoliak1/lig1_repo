#define MOUSEL	0
#define MOUSER	1
#define MOUSEM	2

typedef struct tagMouse
{
	int x, y,
		pinstate,	// pin-click
		pin;		// pin is a single click, it occurs when this value is 1 (only once per frame)
	DIMOUSESTATE state;
} mouse_t;

typedef struct tagKeyboard
{
	byte state[256];
} keyboard_t;

extern mouse_t mse;
extern keyboard_t key;

extern LPDIRECTINPUT	   lpdi;
extern LPDIRECTINPUTDEVICE lpKeyboard;
extern LPDIRECTINPUTDEVICE lpMouse;

void I_Init (HWND hwnd, HINSTANCE instance);
void I_Shutdown (void);
void I_DeviceInit (void);
void I_Get (void);
void I_GetMouse (void);
void I_GetKeyboard (void);
void I_ReacquireKeyboard (void);
void I_ReacquireMouse (void);
