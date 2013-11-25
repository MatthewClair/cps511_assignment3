#include <cstdlib>
#include <cstring>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "global.h"

void initDisplay(int *argc, const char *argv[]);
void display();
void animationHandler(int param);

int main(int argc, const char *argv[])
{
	initDisplay(&argc, argv);

	glutMainLoop();
	return 0;
}

void initDisplay(int *argc, const char *argv[])
{
	glutInit(argc, (char **)argv);

	for (int i = 0; i < *argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
				case 'w':
					switch (argv[i][2])
					{
						case '\0':
							window_width = std::atoi(argv[i+1]);
							i++;
							break;
						case '=':
							window_width = std::atoi(&argv[i][3]);
							break;
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
							window_width = std::atoi(&argv[i][2]);
							break;
					}
					break;
				case 'h':
					switch (argv[i][2])
					{
						case '\0':
							window_height = std::atoi(argv[i+1]);
							i++;
							break;
						case '=':
							window_height = std::atoi(&argv[i][3]);
							break;
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
							window_height = std::atoi(&argv[i][2]);
							break;
					}
					break;
			}
		}
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-window_width)/2, (glutGet(GLUT_SCREEN_HEIGHT)-window_height)/2); 
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("CPS511 - Assignment 3 - Matthew Clair, Brandon Cardoso");

	glutDisplayFunc(display);
	
	animationHandler(0);
}

void display()
{
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(106, (float)window_width/(float)window_height, 1, 5000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); 

	//temp--->
	gluLookAt(100, 100, 100,
			0, 0, 0,
			0, 1, 0);

	glColor3ub(109, 192, 247);
	//<---temp

	glutSwapBuffers();
}

void animationHandler(int param)
{
	glutPostRedisplay();
	glutTimerFunc(10, animationHandler, 0);
}
