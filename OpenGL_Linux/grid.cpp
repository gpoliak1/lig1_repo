#include "grid.h"
#include "reshape.h"
#include "readParse.h"
#include "display.h"
using namespace std;

float MAXZ;
float MINZ;
float ZINC;
float WINPOSX;
float WINPOSY;

#define CONFIG		"test.cfg"

static float solidZ = MAXZ;
static float transparentZ = MINZ;
static GLuint sphereList, cubeList;

static map<string,float> map1;
static void start();
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void animate(void);
void mouseClick(int button);
void startThreadListener(char **);
void *print_message_function( void *ptr );

static void load(void)
{
	map1 = Readparse::doReadParse(CONFIG);

	std::map<std::string, float>::iterator iter;
	std::string strToReturn; //This is no longer on the heap

	MAXZ = map1["MAXZ"];
	MINZ = map1["MINZ"];
	ZINC = map1["ZINC"];
	WINPOSX = map1["WINPOSX"];
	WINPOSY = map1["WINPOSY"];
}

static void init(void)
{
	//LIGHT0
	GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat white_light[] = {0.0, 1.0, 1.0, 1.0};
	GLfloat lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0};
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	//glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	//LIGHT1
	GLfloat mat_specular1[] = {1.0,1.0,1.0,1.0};
	GLfloat mat_shininess1[] = {50.0};
	GLfloat light_position1[] = {-1.0, 1.0, 1.0, 0.0};
	GLfloat white_light1[] = {1.0, 1.0, 0.0, 1.0};
	GLfloat lmodel_ambient1[] = {0.1, 0.1, 0.1, 1.0};
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light1);
	//glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

		//LIGHT2
	GLfloat mat_specular2[] = {1.0,1.0,1.0,1.0};
	GLfloat mat_shininess2[] = {50.0};
	GLfloat light_position2[] = {1.0, -1.0, 1.0, 0.0};
	GLfloat white_light2[] = {1.0, 0.0, 1.0, 1.0};
	GLfloat lmodel_ambient2[] = {0.1, 0.1, 0.1, 1.0};
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);

	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white_light2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, white_light2);
	//glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); //if didnt exist - black, if exists but undefined, default - white
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key, int x, int y)
{
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

	Display *display = XOpenDisplay(0);
	Window root = DefaultRootWindow(display);

	XWarpPointer(display, None, root, 0, 0, 0, 0, WINPOSX+30, WINPOSY+30);

	mouseClick(Button1);

	XFlush(display);
	XCloseDisplay(display);
}

static void start(int argc, char ** argv) {
	load();
	startThreadListener(argv);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

/*************** START UTIL *******************/

void display(void)
{	
	OglDisplay::doOglDisplay(solidZ, sphereList, transparentZ, cubeList);
}

void reshape(int w, int h)
{
	Reshape::doReshape(w, h);
}

void startThreadListener(char** argv) 
{
	pthread_t thread1, thread2;
	char *message1 = "Thread 1";
	int  iret1, iret2;

	std::string word(argv[0]);

	iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
}

void animate(void)
{
	if (solidZ <= MINZ || transparentZ >= MAXZ)
		glutIdleFunc(NULL);
	else {
		solidZ -= ZINC;
		transparentZ += ZINC;
		glutPostRedisplay();
	}
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

void performSwitch(char c) {

	int x = glutGet(GLUT_WINDOW_X);
	int y = glutGet(GLUT_WINDOW_Y);

	keyboard(c, x, y);
}

void* SocketHandler(void* lp) {
	int *csock = (int*)lp;

	char buffer[1024];
	int buffer_len = 1024;
	int bytecount;

	const char yChar = 'y';
	while ((bytecount = recv(*csock, buffer, buffer_len, 0)) > 0) {

		performSwitch(*buffer);

		printf("Rec bytes %c\n", *buffer);
	}


FINISH:
	free(csock);
	return 0;
}

void *print_message_function( void *ptr )
{
	int host_port= 6789;

	struct sockaddr_in my_addr;

	int hsock;
	int * p_int ;
	int err;

	socklen_t addr_size = 0;
	int* csock;
	sockaddr_in sadr;
	pthread_t thread_id=0;


	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if(hsock == -1) {
		printf("Error initializing socket %d\n", errno);
		goto FINISH;
	}

	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;

	if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ) {
			printf("Error setting options %d\n", errno);
			free(p_int);
			goto FINISH;
	}
	free(p_int);

	my_addr.sin_family = AF_INET ;
	my_addr.sin_port = htons(host_port);

	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = INADDR_ANY ;

	if( bind( hsock, (sockaddr*)&my_addr, sizeof(my_addr)) == -1 ) {
		fprintf(stderr,"Error binding to socket, make sure nothing else is listening on this port %d\n",errno);
		goto FINISH;
	}
	if(listen( hsock, 10) == -1 ) {
		fprintf(stderr, "Error listening %d\n",errno);
		goto FINISH;
	}

	//Now lets do the server stuff

	addr_size = sizeof(sockaddr_in);

	while(true) {
		printf("waiting for a connection\n");
		csock = (int*)malloc(sizeof(int));
		if((*csock = accept( hsock, (sockaddr*)&sadr, &addr_size))!= -1) {
			printf("---------------------\nReceived connection from %s\n",inet_ntoa(sadr.sin_addr));
			pthread_create(&thread_id,0,&SocketHandler, (void*)csock );
			pthread_detach(thread_id);
		}
		else {
			fprintf(stderr, "Error accepting %d\n", errno);
		}
	}

FINISH:
	;
}

/*************** END UTIL *******************/

int main(int argc, char *argv[])
{
	start(argc, argv);
}

