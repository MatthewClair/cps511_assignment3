#include <cstdlib>
#include <cstring>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "global.h"
#include "modules/Light/Light.h"

#include "modules/Enemy/Enemy.h"

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

	glClearColor(1.0,1.0,1.0,1.0);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	float light_ambient[] = {.2, .2, .2, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_3D);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);

	animationHandler(0);
}

void display()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, (float)window_width/(float)window_height, 1, 5000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//temp--->
	gluLookAt(500, 200, 200,
			0, 0, 0,
			0, 1, 0);

	Vector3D o(2000, 500, 0);
	Vector3D a(0, 0, 0);
	float d[] = {0.5, 0.5, 0.5, 1.0};
	Light light(o, a, GL_LIGHT0, d);
	light.Draw();

	glColor3ub(109, 192, 247);

	Vector3D o2(50.0, 0.0, 0.0);
	Vector3D a2(0.0, 90.0, 0.0);

	Enemy enemy(o2, a2);
	enemy.Draw();

	//<---temp

	glutSwapBuffers();
}

void animationHandler(int param)
{
	glutPostRedisplay();
	glutTimerFunc(10, animationHandler, 0);
}
