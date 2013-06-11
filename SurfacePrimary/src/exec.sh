#!/bin/bash

g++ -lGL -lGLU -lGLEW -lglut -c texture/lodepng.cpp Utils.cpp controlPoints/externVarDefinition.cpp controlPoints/controlPointLoader.cpp models/leaves.cpp models/treetrunk.cpp config.cpp OpenGL_Auxiliary.cpp

g++ -lGL -lGLU -lGLEW -lglut -o final lodepng.o Utils.o externVarDefinition.o controlPointLoader.o leaves.o treetrunk.o config.o OpenGL_Auxiliary.o

rm -rf *.o && rm *.*~

./final
