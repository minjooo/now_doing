#include <GL/freeglut.h>
#include<math.h>

#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

int choose = 0;
int gox = 0;
int goy = 0;
float scale = 1.0;
bool animation = false;
bool countup = true;
void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("1-11");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}
void TimerFunction(int value)
{
	if (countup)
	{
		gox += 1;
		if (gox == 100)
		{
			countup = false;
		}
	}
	else
	{
		gox -= 1;
		if (gox == -100)
		{
			countup = true;
		}
	}
	glutPostRedisplay();
	if (animation)
	{
		glutTimerFunc(100, TimerFunction, 1);
	}
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		choose = 1;
		break;
	case '2':
		choose = 2;
		break;
	case '3':
		choose = 3;
		break;
	case '4':
		choose = 4;
		break;
	case 'x':
		gox += 1;
		break;
	case 'X':
		gox -= 1;
		break;
	case 'y':
		goy += 1;
		break;
	case 'Y':
		goy -= 1;
		break;
	case 's':
		scale += 0.1;
		break;
	case 'S':
		scale -= 0.1;
		break;
	case 'a':
		animation = true;
		glutTimerFunc(100, TimerFunction, 1);
		break;
	case 't':
		animation = false;
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

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPushMatrix();

	glTranslatef(400, 300, 0.0);//중점 가운데로

	glBegin(GL_LINES);
		glVertex3f(-400.0, 0.0, 0.0);
		glVertex3f(400.0, 0.0, 0.0);
		glVertex3f(0.0, -300.0, 0.0);
		glVertex3f(0.0, 300.0, 0.0);
	glEnd();//가로선 세로선

	glTranslated(gox, goy, 0.0);//이동
	glScaled(scale, 1.0, 1.0);//확대

	switch (choose)
	{
	case 1:
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 100; ++i)
		{
			glVertex2f(i * 6 - 300, sin(PI / 10 * i) * 25);
		}
		glEnd();
		break;
	case 2:
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 200; ++i)
		{
			glVertex2f(cos(PI / 10 * i)*15 - 300+i*2.5, sin(PI / 10 * i) * 35);
		}
		glEnd();
		break;
	case 3:
		glBegin(GL_LINE_LOOP);
			glVertex2f(-200, 100);
			glVertex2f(200, -100);
			glVertex2f(200, 100);
			glVertex2f(-200, -100);
		glEnd();
		break;
	case 4:
		glBegin(GL_LINE_LOOP);
		glVertex2f(-200, 100);
		glVertex2f(200, 100);
		glVertex2f(200, -100);
		glVertex2f(-200, -100);
		glEnd();
		break;
	}
	
	glPopMatrix();

	glFlush();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -200.0, 200.0);
}