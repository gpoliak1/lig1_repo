// log.h

#include <stdio.h>
#include <string.h>

#define LOGFILE	"gl.log"

extern bool LogCreated;

void Log (char *message);
void LogErr (char *message);
