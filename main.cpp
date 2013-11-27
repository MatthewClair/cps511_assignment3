#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <list>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "global.h"
#include "modules/Light/Light.h"
#include "modules/Projectile/Projectile.h"
#include "modules/Colour/Colour.h"
#include "modules/Enemy/Enemy.h"

void initDisplay(int *argc, const char *argv[]);
void display();
void timerTick(int param);

void keyDownHandler(unsigned char key, int x, int y);
void keyUpHandler(unsigned char key, int x, int y);
void keyHandler();
bool* keyStates = new bool[256];

int tick;

std::list<Projectile> projectiles;
std::list<Enemy> enemies;
int numEnemies;

float plDiffuse[] = {0.8, 0.8, 0.8, 1.0};
Vector3D plAngles(0, 0, 0);
Light playerLight(ThePlayer.getOrigin(), plAngles, GL_LIGHT0, plDiffuse);

int main(int argc, const char *argv[])
{
	initDisplay(&argc, argv);
	glutKeyboardFunc(keyDownHandler);
	glutKeyboardUpFunc(keyUpHandler);
	tick = 0;

	numEnemies = 10;
	for (int i = 0; i < numEnemies; i++) {
		for (int j = 0; j < numEnemies; j++) {
			Vector3D origin(200*i-(numEnemies-1)*100, 200*j-(numEnemies-1)*100, -TheWorld.getRadius()/2);
			Vector3D angles(0, -90, 0);
			Enemy e(origin, angles);
			enemies.push_back(e);
		}
	}

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
	float light_ambient[] = {.5, .5, .5, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_3D);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);

	timerTick(0);
}

void display()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, (float)window_width/(float)window_height, 1, TheWorld.getRadius());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ThePlayer.draw();

	playerLight.draw();

	TheWorld.draw();

	std::list<Projectile>::iterator p;
	for (p = projectiles.begin(); p != projectiles.end(); p++) {
		p->draw();
	}

	std::list<Enemy>::iterator e;
	for (e = enemies.begin(); e != enemies.end(); e++) {
		e->draw();
	}

	glutSwapBuffers();
	tick++;
}

void timerTick(int param)
{
	keyHandler();
	ThePlayer.update();
	playerLight.setOrigin(ThePlayer.getOrigin());

	std::list<Projectile>::iterator p;
	for (p = projectiles.begin(); p != projectiles.end(); p++) {
		p->update();

		if (p->noLongerExists) {
			p = projectiles.erase(p);
		}
	}

	std::list<Enemy>::iterator e;
	for (e = enemies.begin(); e != enemies.end(); e++) {
		e->update();
	}

	glutPostRedisplay();
	glutTimerFunc(10, timerTick, 0);
}

void keyDownHandler(unsigned char key, int x, int y)
{
	keyStates[key]= true;
}

void keyUpHandler(unsigned char key, int x, int y)
{
	keyStates[key] = false;
}

void keyHandler()
{
	//player movement
	if (keyStates['a'] || keyStates['A'])
	{
		if (ThePlayer.getOrigin().x > -TheWorld.getRadius()/2)
		{
			ThePlayer.accelerate(Player::LEFT);
		}
		else
		{
			ThePlayer.brake();
		}
	}

	if (keyStates['d'] || keyStates['D'])
	{
		if (ThePlayer.getOrigin().x < TheWorld.getRadius()/2)
		{
			ThePlayer.accelerate(Player::RIGHT);
		}
		else
		{
			ThePlayer.brake();
		}
	}

	if (keyStates['w'] || keyStates['W'])
	{
		if (ThePlayer.getOrigin().y < TheWorld.getRadius()/2)
		{
			ThePlayer.accelerate(Player::UP);
		}
		else
		{
			ThePlayer.brake();
		}
	}

	if (keyStates['s'] || keyStates['W'])
	{
		if (ThePlayer.getOrigin().y > -TheWorld.getRadius()/2)
		{
			ThePlayer.accelerate(Player::DOWN);
		}
		else
		{
			ThePlayer.brake();
		}
	}

	//breaking if no movement keys are being pressed
	if(!keyStates['a'] && !keyStates['d'] && !keyStates['w'] && !keyStates['s'] &&
		!keyStates['A'] && !keyStates['D'] && !keyStates['W'] && !keyStates['S'])
	{
		ThePlayer.brake();
	}

	//firing a projectile
	if (keyStates[' '])
	{
		ThePlayer.fireProjectiles(&projectiles);
	}

}
