#include "keyboard.h"

void mouseClick(int button);
void animate(void);

float _solidZ;
float _transparentZ; 
float _MAXZ;
float _MINZ;
float _ZINC;

void animate(void)
{printf("In Animate!");
	if (_solidZ <= _MINZ || _transparentZ >= _MAXZ) {
		glutIdleFunc(NULL); std::cout << "*** 1 ***" << "_solidZ: " << _solidZ << "_transparentZ: " << _transparentZ << "_MAXZ: " << _MAXZ;
	} else {
		_solidZ -= _ZINC;
		_transparentZ += _ZINC;
		glutPostRedisplay(); std::cout << "*** 2 ***" << "_solidZ: " << _solidZ << "_transparentZ: " << _transparentZ << "_MAXZ: " << _MAXZ;
	}
}

void Keyboard::doKeyboard(unsigned char key, int x, int y, float solidZ, float transparentZ, float MAXZ, float MINZ, float ZINC, float WINPOSX, float WINPOSY) {

	_solidZ = solidZ;
	_transparentZ = transparentZ; 
	_MAXZ = MAXZ;
	_MINZ = MINZ;
	_ZINC = ZINC;



	switch (key) {
	case 'a':
	case 'A':
		solidZ = MAXZ;
		transparentZ = MINZ;
		glutIdleFunc(animate);
		break;
	case 'r':
	case 'R':
		solidZ = MAXZ;
		transparentZ = MINZ;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}

		std::cout << "_solidZ: " << _solidZ << "_transparentZ: " << _transparentZ << "_MAXZ: " << _MAXZ;

	Display *display = XOpenDisplay(0);
	Window root = DefaultRootWindow(display);

	XWarpPointer(display, None, root, 0, 0, 0, 0, WINPOSX+30, WINPOSY+30);

	mouseClick(Button1);

	XFlush(display);
	XCloseDisplay(display);
}

void mouseClick(int button)
{
	Display *display = XOpenDisplay(NULL);

	XEvent event;

	if(display == NULL)
	{
		fprintf(stderr, "Errore nell'apertura del Display !!!\n");
		exit(EXIT_FAILURE);
	}

	memset(&event, 0x00, sizeof(event));

	event.type = ButtonPress;
	event.xbutton.button = button;
	event.xbutton.same_screen = True;

	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

	event.xbutton.subwindow = event.xbutton.window;

	while(event.xbutton.subwindow)
	{
		event.xbutton.window = event.xbutton.subwindow;

		XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	}

	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

	XFlush(display);

	usleep(100000);

	event.type = ButtonRelease;
	event.xbutton.state = 0x100;

	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

	XFlush(display);

	XCloseDisplay(display);
}