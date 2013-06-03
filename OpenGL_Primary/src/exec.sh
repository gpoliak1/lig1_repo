#!/bin/bash

g++ -lGL -lSDL -c example_opengl.cpp lodepng.cpp

g++ -lGL -lSDL -o final example_opengl.o lodepng.o

#(exec wmctrl -k on)

#cd JavaSocketClient/ && exec xterm cd JavaSocketClient/ | javac Form2.java && exec xterm cd /home/gil/Desktop/OpenGL_Linux/JavaSocketClient | java Form2 &)

./final
