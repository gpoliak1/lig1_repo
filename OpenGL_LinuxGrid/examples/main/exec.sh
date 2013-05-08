#!/bin/bash

g++ -lglut -lGL -lGLEW -lGLU -lpthread -lX11 -lm -c starWarsScroller.cpp

g++ -lglut -lGL -lGLEW -lGLU -lpthread -lX11 -lm -o starWarsScroller starWarsScroller.o

#(exec wmctrl -k on)

#cd JavaSocketClient/ && exec xterm cd JavaSocketClient/ | javac Form2.java && exec xterm cd /home/gil/Desktop/OpenGL_Linux/JavaSocketClient | java Form2 &)

#./final
