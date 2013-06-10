#!/bin/bash

g++ -lGL -lGLU -lGLEW -lglut -c lodepng.cpp OpenGL_Auxiliary.cpp

g++ -lGL -lGLU -lGLEW -lglut -o final lodepng.o OpenGL_Auxiliary.o

#(exec wmctrl -k on)

#cd JavaSocketClient/ && exec xterm cd JavaSocketClient/ | javac Form2.java && exec xterm cd /home/gil/Desktop/OpenGL_Linux/JavaSocketClient | java Form2 &)

./final
