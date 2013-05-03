#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <map>
#include <utility>
#include <stdio.h>
#include <string.h>
#include "readParse.h"

#define ROT_INC			0.1
#define factor 			1
#define PI				3.14159265
#define RADIUS			5
#define NUM_OF_ANGLES	10
void drawGrid(void);
void setCamera(void);
void drawNumbers(const char *str1, const char *str2, const char *str3, float pos[3], float color[4], void *font);
static void (*drawPrimP)(void) = drawGrid;
void *font = GLUT_BITMAP_8_BY_13;
static GLfloat g_rotate = 0;
static GLfloat g_rotInc = ROT_INC;
float eyeX = 0.0;
float eyeY = 0.0;
float eyeZ = -10.0;
float lookatX = 0.0;
float lookatY = 0.0;
float lookatZ = -15.0;
int multiplierXZ = 0;
int multiplierYZ = 0;
float trigSinVals[10];
float trigCosVals[10];

#define MAX_LINE_LEN 256

using namespace std;

int stringToInt(string str);
float stringToFloat(string str);
string extract(char *input);

int stringToInt(string str) {

	int result;
	stringstream(str) >> result;

	return result;
}

float stringToFloat(string str) {

	float result;
	stringstream(str) >> result;

	return result;
}

string extract(char *input) {

	int i; i=0;
	while (isalnum(input[i]) || input[i] == '.' || input[i] == '_') i++;

	input[i] = 0;

	return input;
}

map<string,float> Readparse::doReadParse(string config) {

	map<string, float> vals;

	FILE* config_fp ;
	char line[MAX_LINE_LEN + 1] ;
	char* token ;

	config_fp = fopen(config.c_str(), "r" ) ;

	while( fgets( line, MAX_LINE_LEN, config_fp ) != NULL )
	{
		token = strtok( line, "\t =\n\r" ) ;
		if( token != NULL && token[0] != '#' )
		{
			string key = extract(token);

			token = strtok( NULL, "\t =\n\r" ) ;

			string value = extract(token);
			float floatValue = stringToFloat(value);
			vals[key] = floatValue;
		}
	}

	return vals;
}

