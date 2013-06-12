#!/bin/bash

g++ -lGL -lGLU -lGLEW -lglut -c utils/lodepng.cpp utils/utils.cpp utils/textureUtils.cpp controlPoints/controlPointArrs.cpp controlPoints/controlPointLoader.cpp models/leaves.cpp models/treetrunk.cpp config.cpp displayMain.cpp

rm -rf final

g++ -lGL -lGLU -lGLEW -lglut -o final lodepng.o utils.o textureUtils.o controlPointArrs.o controlPointLoader.o leaves.o treetrunk.o config.o displayMain.o

rm -rf *.o && rm *.*~

./final
