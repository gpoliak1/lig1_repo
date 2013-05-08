#define DIRECTINPUT_VERSION 0x0700

#include "glbase.h"

mouse_t mse;
keyboard_t key;

LPDIRECTINPUT	    lpdi = NULL;
LPDIRECTINPUTDEVICE lpKeyboard = NULL;
LPDIRECTINPUTDEVICE lpMouse = NULL;

void I_DeviceInit (void)
{
	// init mouse
	mse.x = 0;
	mse.y = 0;
	mse.pinstate = 0;
	mse.pin = 0;

	for (int i=0; i<256; i++)
		key.state[i] = 0;
}

void I_Init (HWND hwnd, HINSTANCE instance)
{
	Log("; I_Init(); initialize DirectInput\n");

	I_DeviceInit();

	// create the direct input object

	if ((err = DirectInputCreate(instance, DIRECTINPUT_VERSION, &lpdi, NULL)) != DI_OK)
		LogErr(dierrCreate(err));

	// create keyboard

	if ((err = lpdi->CreateDevice(GUID_SysKeyboard, &lpKeyboard, NULL)) != DI_OK)
		LogErr(dierrCreateDevice(err));

	if ((err = lpKeyboard->SetCooperativeLevel(hwnd, DISCL_BACKGROUND|DISCL_NONEXCLUSIVE)) != DI_OK)
		LogErr(dierrCooperate(err));

	if ((err = lpKeyboard->SetDataFormat(&c_dfDIKeyboard)) != DI_OK)
		LogErr(dierrSetDataFormat(err));

	if ((err = lpKeyboard->Acquire()) != DI_OK)
		LogErr(dierrAcquire(err));

	// create mouse

	if ((err = lpdi->CreateDevice(GUID_SysMouse, &lpMouse, NULL)) != DI_OK)
		LogErr(dierrCreateDevice(err));

	if ((err = lpMouse->SetCooperativeLevel(hwnd, DISCL_BACKGROUND|DISCL_NONEXCLUSIVE)) != DI_OK)
		LogErr(dierrCooperate(err));

	if ((err = lpMouse->SetDataFormat(&c_dfDIMouse)) != DI_OK)
		LogErr(dierrSetDataFormat(err));

	if ((err = lpMouse->Acquire()) != DI_OK)
		LogErr(dierrAcquire(err)); 
}

void I_Shutdown (void)
{
	Log("; I_Shutdown(); destroy DirectInput interface\n");

	if (lpdi)
	{
		if (lpMouse) {
			lpMouse->Release();
			lpMouse = NULL;
		}
		
		if (lpKeyboard) {
			lpKeyboard->Release();
			lpKeyboard = NULL;
		}	
		
		lpdi->Release();
		lpdi = NULL;
	}
}

void I_Get (void)
{
	I_GetMouse();
	I_GetKeyboard();
}

void I_GetMouse (void)
{
	if ((err = lpMouse->GetDeviceState(sizeof(DIMOUSESTATE), (void*)&mse.state) != DI_OK))
		if ((err & DIERR_INPUTLOST) && (err & DIERR_NOTACQUIRED)) {
			// try to (re-)acquire the mouse interface
			I_ReacquireMouse();
		}
		else // ...some other error
			LogErr(dierrGetDeviceState(err));

	mse.x += mse.state.lX;
	mse.y += mse.state.lY;

	// to constrain mouse cursor position to the screen bounding box
	// uncomment the following lines and define screenWidth and screenHeight
	/*
	if (mse.x <= 0)
		mse.x = 0;
	if (mse.x > screenWidth)
		mse.x = screenwidth;
	if (mse.y <= 0)
		mse.y = 0;
	if (mse.y > screenHeight)
		mse.y = screenHeight; */

	mse.pin = 0;

	// has a single-click occured?
	if (mse.state.rgbButtons[0] && !mse.pinstate)
	{
		mse.pinstate = 1;
		mse.pin = 1;
	}

	// reset 'pin' state
	if (!mse.state.rgbButtons[0])
		mse.pinstate = 0;
}

void I_GetKeyboard (void)
{
	if ((err = lpKeyboard->GetDeviceState( ((sizeof(unsigned char)) << 8), (void*)key.state)) != DI_OK)
		if ((err & DIERR_INPUTLOST) && (err & DIERR_NOTACQUIRED))
		{
			// try to (re-)acquire the keyboard interface
			I_ReacquireKeyboard();
		} else // ...some other error
			LogErr(dierrGetDeviceState(err));
}

void I_ReacquireKeyboard (void)
{
	Log("reacquiring keyboard...");
	
	if ((err = lpKeyboard->Acquire()) != DI_OK)
		Log("di_ok\n");
	else
		LogErr(dierrAcquire(err));
}

void I_ReacquireMouse (void)
{
	Log("reacquiring mouse...");

	if ((err = lpMouse->Acquire()) != DI_OK)
		Log("di_ok\n");
	else
		LogErr(dierrAcquire(err));
}
