#include "glbase.h"

char dierr_msg[128];
dword err = 0;

// direct input errors:

char *dierrCreate (dword err)
{
	memset(dierr_msg, 0, 128);

	if (err == DIERR_BETADIRECTINPUTVERSION)
		strcpy(dierr_msg, "dierrCreate() Beta Direct Input version");
	else
	if (err == DIERR_INVALIDPARAM)
		strcpy(dierr_msg, "dierrCreate() Invalid param");
	else
	if (err == DIERR_OLDDIRECTINPUTVERSION)
		strcpy(dierr_msg, "dierrCreate() Old Direct Input version");
	else
	if (err == DIERR_OUTOFMEMORY)
		strcpy(dierr_msg, "dierrCreate() Out of memory");
	else
		strcpy(dierr_msg, "dierrCreate() Unidentified error");

	strcat(dierr_msg, "\n");

	return (char*)&dierr_msg;
}

char *dierrCreateDevice (dword err)
{
	if (err == DIERR_DEVICENOTREG)
		strcpy(dierr_msg, "dierrCreateDevice() Device is not registered");
	else
	if (err == DIERR_INVALIDPARAM)
		strcpy(dierr_msg, "dierrCreateDevice() Invalid param");
	else
	if (err == DIERR_NOINTERFACE)
		strcpy(dierr_msg, "dierrCreateDevice() No interface");
	else
	if (err == DIERR_NOTINITIALIZED)
		strcpy(dierr_msg, "dierrCreateDevice() Not initialized");
	else
	if (err == DIERR_OUTOFMEMORY)
		strcpy(dierr_msg, "dierrCreateDevice() Out of memory");
	else
		strcpy(dierr_msg, "dierrCreateDevice() Unidentified error");

	strcat(dierr_msg, "\n");

	return (char*)&dierr_msg;
}

char *dierrCooperate (dword err)
{
	if (err == DIERR_NOTINITIALIZED)
		strcpy(dierr_msg, "dierrCooperate() Not initialized");
	else
	if (err == DIERR_INVALIDPARAM)
		strcpy(dierr_msg, "dierrCooperate() Invalid param");
	else
		strcpy(dierr_msg, "dierrCooperate() Unidentified error");

	strcat(dierr_msg, "\n");

	return (char*)&dierr_msg;
}

char *dierrSetDataFormat (dword err)
{
	if (err == DIERR_ACQUIRED)
		strcpy(dierr_msg, "dierrSetDataFormat() Acquired");
	else
	if (err == DIERR_INVALIDPARAM)
		strcpy(dierr_msg, "dierrSetDataFormat() Invalid param");
	else
	if (err == DIERR_NOTINITIALIZED)
		strcpy(dierr_msg, "dierrSetDataFormat() Not initialized");
	else
		strcpy(dierr_msg, "dierrSetDataFormat() Unidentified error");

	strcat(dierr_msg, "\n");

	return (char*)&dierr_msg;
}

char *dierrAcquire (dword err)
{
	if (err == DIERR_INVALIDPARAM)
		strcpy(dierr_msg, "dierrAcquire() Invalid param");
	else
	if (err == DIERR_NOTINITIALIZED)
		strcpy(dierr_msg, "dierrAcquire() Not initialized");
	else
	if (err == DIERR_OTHERAPPHASPRIO)
		strcpy(dierr_msg, "dierrAcquire() Other app has priority");
	else
		strcpy(dierr_msg, "dierrAcquire() Unidentified error");

	strcat(dierr_msg, "\n");

	return (char*)&dierr_msg;
}

char *dierrGetDeviceState (dword err)
{
	if (err == DIERR_INPUTLOST)
		strcpy(dierr_msg, "dierrGetDeviceState() Input is lost");
	else
	if (err == DIERR_INVALIDPARAM)
		strcpy(dierr_msg, "dierrGetDeviceState() Invalid param");
	else
	if (err == DIERR_NOTACQUIRED)
		strcpy(dierr_msg, "dierrGetDeviceState() Not aquired");
	else
	if (err == DIERR_NOTINITIALIZED)
		strcpy(dierr_msg, "dierrGetDeviceState() Not initialized");
	else
	if (err == E_PENDING)
		strcpy(dierr_msg, "dierrGetDeviceState() Data is not yet available");
	else
		strcpy(dierr_msg, "dierrGetDeviceState() Unidentified error");

	strcat(dierr_msg, "\n");

	return (char*)&dierr_msg;
}
