#include <GL/freeglut.h>
#include<stdlib.h>
#include<time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("1-14");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
	srand(time(NULL));
}
struct AM_1 {
	bool ON = false;
	int what = rand() % 4 + 1;
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	int size = rand() % 100 + 50;
	float scale = 1.0;
	int rotate = 0;
	int x = 0;
	int y = 0;
};
AM_1 SLEEP[20];
int count = 0;
bool can_count = true;
bool turn_opposite = false;
void TimerFunction(int value)
{
	for (int i = 0; i < 20; ++i)
	{
		if (SLEEP[i].ON == true)
		{
			if (turn_opposite == false)
			{
				SLEEP[i].rotate += 2;
			}
			else if (turn_opposite == true)
			{
				SLEEP[i].rotate -= 2;
			}
			SLEEP[i].scale -= 0.02;
			if (SLEEP[i].scale <= 0.0)
			{
				SLEEP[i].ON = false;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (can_count)
		{
			SLEEP[count].x = x - 400;
			SLEEP[count].y = 300 - y;
			SLEEP[count].ON = true;
			count += 1;
			if (count == 20)
			{
				can_count = false;
			}
		}
	}
	glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		if (turn_opposite == true)
		{
			turn_opposite = false;
		}
		else if (turn_opposite == false)
		{
			turn_opposite = true;
		}
		break;
	case 'q':
		PostQuitMessage(NULL);
		break;
	}
	glutPostRedisplay();
}
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glBegin(GL_LINES);
	glEnd();

	glPushMatrix();

	glTranslatef(400, 300, 0.0);//중점 가운데로
	//glTranslated(gox, goy, 0.0);//이동
	//glScaled(scale, 1.0, 1.0);//확대
	//glRotated(turnY, 0.0f, 1.0f, 0.0f);

	for (int i = 0; i < 20; ++i)
	{
		if (SLEEP[i].ON == true)
		{
			if (SLEEP[i].what == 1)
			{
				glPushMatrix();
				glTranslatef(SLEEP[i].x, SLEEP[i].y, 0.0);
				glRotated(SLEEP[i].rotate, 0.0f, 1.0f, 0.0f);
				glScaled(SLEEP[i].scale, SLEEP[i].scale, SLEEP[i].scale);
				glColor4f((float)SLEEP[i].r / 255, (float)SLEEP[i].g / 255, (float)SLEEP[i].b / 255, 1.0f);
				glutWireCone(SLEEP[i].size, SLEEP[i].size, 10, 10);
				glPopMatrix();
			}
			if (SLEEP[i].what == 2)
			{
				glPushMatrix();
				glTranslatef(SLEEP[i].x, SLEEP[i].y, 0.0);
				glRotated(SLEEP[i].rotate, 0.0f, 1.0f, 0.0f);
				glScaled(SLEEP[i].scale, SLEEP[i].scale, SLEEP[i].scale);
				glColor4f((float)SLEEP[i].r / 255, (float)SLEEP[i].g / 255, (float)SLEEP[i].b / 255, 1.0f);
				glutWireCube(SLEEP[i].size);
				glPopMatrix();
			}
			if (SLEEP[i].what == 3)
			{
				glPushMatrix();
				glTranslatef(SLEEP[i].x, SLEEP[i].y, 0.0);
				glRotated(SLEEP[i].rotate, 0.0f, 1.0f, 0.0f);
				glScaled(SLEEP[i].scale, SLEEP[i].scale, SLEEP[i].scale);
				glColor4f((float)SLEEP[i].r / 255, (float)SLEEP[i].g / 255, (float)SLEEP[i].b / 255, 1.0f);
				glutWireSphere(SLEEP[i].size, 10, 10);
				glPopMatrix();
			}
			if (SLEEP[i].what == 4)
			{
				glPushMatrix();
				glTranslatef(SLEEP[i].x, SLEEP[i].y, 0.0);
				glRotated(SLEEP[i].rotate, 0.0f, 1.0f, 0.0f);
				glScaled(SLEEP[i].scale, SLEEP[i].scale, SLEEP[i].scale);
				glColor4f((float)SLEEP[i].r / 255, (float)SLEEP[i].g / 255, (float)SLEEP[i].b / 255, 1.0f);
				glutWireTorus(SLEEP[i].size - 50, SLEEP[i].size, 10, 10);
				glPopMatrix();
			}
		}
	}

	glPopMatrix();
	glFlush();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -200.0, 200.0);
}