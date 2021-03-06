#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
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
#include "modules/Player/Player.h"

void init();
void initDisplay(int *argc, const char *argv[]);
void display();
void timerTick(int param);

void keyDownHandler(unsigned char key, int x, int y);
void keyUpHandler(unsigned char key, int x, int y);
void keyHandler();
bool keyStates[256];

void checkWin();
bool playerWins;

std::list<Projectile> projectiles;
std::list<Projectile> enemyProjectiles;
std::list<Enemy> enemies;

float plDiffuse[] = {0.5, 0.5, 0.5, 1.0};
Light playerLight(ThePlayer.origin, GL_LIGHT0, plDiffuse);

Vector3D sunOrigin(3750, 700, -1000);
float sunDiffuse[] = {1, 1, 0.5, 1};
Light sun(sunOrigin, GL_LIGHT1, sunDiffuse);

int attackingEnemy;

void *font = GLUT_STROKE_ROMAN;

char playerWinsString[] = "YOU WIN";
char gameOverString[] = "GAME OVER";
char playAgainString[] = "Press 'c' to play again";

int main(int argc, const char *argv[])
{
	std::srand(std::time(0));
	initDisplay(&argc, argv);
	glutKeyboardFunc(keyDownHandler);
	glutKeyboardUpFunc(keyUpHandler);

	init();

	glutMainLoop();
	return 0;
}

void init()
{
	projectiles.clear();
	enemyProjectiles.clear();
	enemies.clear();

	ThePlayer.isAlive = true;
	playerWins = false;

	int n = 6;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Vector3D origin(400*i-(n-1)*200, 200*j-(n-1)*100, -2000);
			Enemy e(origin);
			enemies.push_back(e);
		}
	}
	attackingEnemy = std::rand() % enemies.size();
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

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, .1f);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, .04f);

	glutDisplayFunc(display);

	timerTick(0);
}

void display()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, (float)window_width/(float)window_height, 1, 10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ThePlayer.draw();

	playerLight.draw();
	sun.draw();

	glDisable(GL_LIGHTING);
	glPushMatrix();
		glColor3ub(255, 255, 0);
		glTranslated(sunOrigin.x, sunOrigin.y, sunOrigin.z);
		glutSolidSphere(1000, 32, 16);
	glPopMatrix();
	glEnable(GL_LIGHTING);

	TheWorld.draw();

	std::list<Projectile>::iterator p;
	for (p = projectiles.begin(); p != projectiles.end(); p++) {
		p->draw();
	}
	for (p = enemyProjectiles.begin(); p != enemyProjectiles.end(); p++) {
		p->draw();
	}

	std::list<Enemy>::iterator e;
	for (e = enemies.begin(); e != enemies.end(); e++) {
		e->draw();
	}

	if (!ThePlayer.isAlive || playerWins)
	{
		glPushMatrix();
			glViewport(0, 0, window_width, window_height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0, window_width, 0, window_height);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glDisable(GL_LIGHTING);
			glColor3ub(255, 255, 255);
			glLineWidth(3);

			if(!ThePlayer.isAlive)
			{
				int len = (int) strlen(gameOverString);
				for (int i = 0; i < len; i++) {
					glPushMatrix();
						glTranslatef(window_width/2 + i*90 - (len+1)/2 *90, window_height/2 + 40, 0);
						glutStrokeCharacter(font, gameOverString[i]);
					glPopMatrix();
				}
			}
			else if (playerWins)
			{
				int len = (int) strlen(playerWinsString);
				for (int i = 0; i < len; i++) {
					glPushMatrix();
						glTranslatef(window_width/2 + i*90 - (len+1)/2 *90, window_height/2 + 40, 0);
						glutStrokeCharacter(font, playerWinsString[i]);
					glPopMatrix();
				}
			}

			int len = (int) strlen(playAgainString);
			for (int i = 0; i < len; i++) {
				glPushMatrix();
					glTranslatef(window_width/2 + i*30 - (len+1)/2 *30, window_height/2 - 20, 0);
					glScalef(0.3, 0.3, 0);
					glutStrokeCharacter(font, playAgainString[i]);
				glPopMatrix();
			}
		glPopMatrix();
	}

	glutSwapBuffers();
}

void timerTick(int param)
{
	tick++;
	keyHandler();

	if (ThePlayer.isAlive) {
		ThePlayer.update();
		playerLight.setOrigin(ThePlayer.origin);

		std::list<Projectile>::iterator p;
		std::list<Enemy>::iterator e;

		int counter = 0;
		for (e = enemies.begin(); e != enemies.end(); e++)
		{
			bool attackFlag = false;
			if (counter == attackingEnemy)
			{
				e->attacking = true;
				attackFlag = true;
			}

			e->update(&enemyProjectiles);
			if (e->isColliding(ThePlayer))
			{
				ThePlayer.isAlive = false;
			}

			if(attackFlag && !e->attacking)
			{
				if(enemies.size() > 0)
				{
					attackingEnemy = std::rand() % enemies.size();
				}
			}

			if (!e->isAlive)
			{
				if (e->attacking)
				{
					if(enemies.size() > 0)
					{
						attackingEnemy = std::rand() % enemies.size();
					}
				}

				e = enemies.erase(e);
			}
			counter++;
		}

		for (p = projectiles.begin(); p != projectiles.end(); p++)
		{
			p->update();

			if (p->noLongerExists)
			{
				p = projectiles.erase(p);
			}
			else
			{
				for (e = enemies.begin(); e != enemies.end(); e++)
				{
					if (e->isColliding(*p))
					{
						e->isAlive = false;
					}
				}
			}
		}

		for (p = enemyProjectiles.begin(); p != enemyProjectiles.end(); p++) {
			p->update();

			if (p->noLongerExists)
			{
				p = enemyProjectiles.erase(p);
			}
			else if (ThePlayer.isColliding(*p))
			{
				ThePlayer.isAlive = false;
			}
		}

		checkWin();
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
	if ((keyStates['c'] || keyStates['C']) && (!ThePlayer.isAlive || playerWins))
	{
		init();
	}
	//player movement
	if (keyStates['a'] || keyStates['A'])
	{
		if (ThePlayer.origin.x > -1500)
		{
			ThePlayer.accelerate(Ship::LEFT);
		}
		else
		{
			ThePlayer.brake();
		}
	}

	if (keyStates['d'] || keyStates['D'])
	{
		if (ThePlayer.origin.x < 1500)
		{
			ThePlayer.accelerate(Ship::RIGHT);
		}
		else
		{
			ThePlayer.brake();
		}
	}

	if (keyStates['w'] || keyStates['W'])
	{
		if (ThePlayer.origin.y < 1000)
		{
			ThePlayer.accelerate(Ship::UP);
		}
		else
		{
			ThePlayer.brake();
		}
	}

	if (keyStates['s'] || keyStates['S'])
	{
		if (ThePlayer.origin.y > -1000)
		{
			ThePlayer.accelerate(Ship::DOWN);
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
		ThePlayer.fire(&projectiles);
	}

}

void checkWin()
{
	playerWins = true;
	std::list<Enemy>::iterator e;
	for (e = enemies.begin(); e != enemies.end(); e++) {
		if (e->isAlive)
		{
			playerWins = false;
			break;
		}
	}
}
