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

