#!/bin/bash

gcc -lglut -lGL -lGLEW -lGLU -lpthread -lX11 -c displayListMain.c

gcc -lglut -lGL -lGLEW -lGLU -lpthread -lX11 -o final displayListMain.o

#(exec wmctrl -k on)

#cd JavaSocketClient/ && exec xterm cd JavaSocketClient/ | javac Form2.java && exec xterm cd /home/gil/Desktop/OpenGL_Linux/JavaSocketClient | java Form2 &)

#./final
