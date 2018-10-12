#include <GL/freeglut.h>
#include<math.h>

#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);

struct Points {
	int x=0;
	int y=0;
};
int choose = 0;
int turnY = 0;
float scale = 1.0;
int move = 0;
int big = 0;
bool rectangle = false;//처음에는 삼각형
bool is_circle = true;
bool rotate = false;
bool sizeup = true;
bool finish_point = false;
Points points[5];
int count = 0;
int gox = 0;
int goy = 0;
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
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}
void TimerFunction(int value)
{
	move += 1;
	if (sizeup)
	{
		big += 1;
		if (big == 5)
		{
			sizeup = false;
		}
	}
	else
	{
		big -= 1;
		if (big == 0)
		{
			sizeup = true;
		}
	}
	if (is_circle == false)
	{
		if (move == 100)
		{
			move = 0;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}
void Mouse(int button, int state, int x, int y)
{
	if (choose == 4)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)		{
			points[count].x = x - 400;
			points[count].y = 300 - y;
			count += 1;
			if (count == 5)
			{
				finish_point = true;
			}
		}
	}
	glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '0':
		choose = 0;
		is_circle = true;
		move = 0;
		break;
	case '1':
		choose = 1;
		is_circle = false;
		move = 0;
		break;
	case '2':
		choose = 2;
		is_circle = false;
		move = 0;
		break;
	case '3':
		choose = 3;
		is_circle = false;
		move = 0;
		break;
	case '4':
		choose = 4;
		count = 0;
		is_circle = false;
		move = 0;
		finish_point = false;
		break;
	case 'y':
		turnY += 3;
		break;
	case 'Y':
		turnY -= 3;
		break;
	case 's'://삼각현 사각형 전환
		if (rectangle)
		{
			rectangle = false;
		}
		else
		{
			rectangle = true;
		}
		break;
	case 'r':
		if (is_circle)
		{
			if (rotate == false)
			{
				rotate = true;
			}
			else
			{
				rotate = false;
			}
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

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPushMatrix();

	glTranslatef(400, 300, 0.0);//중점 가운데로

	glBegin(GL_LINES);
	glVertex3f(-400.0, 0.0, 0.0);
	glVertex3f(400.0, 0.0, 0.0);
	glVertex3f(0.0, -300.0, 0.0);
	glVertex3f(0.0, 300.0, 0.0);
	glEnd();//가로선 세로선

	//glTranslated(gox, goy, 0.0);//이동
	//glScaled(scale, 1.0, 1.0);//확대
	glRotated(turnY, 0.0f, 1.0f, 0.0f);
	switch (choose)
	{
	case 0:
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 360; ++i)
		{
			glVertex2f(cos(PI / 180 * i) * 150, sin(PI / 180 * i) * 150);
		}
		glEnd();
		glPushMatrix();
			glTranslated(cos(PI / 180 * move) * 150, sin(PI / 180 * move) * 150, 0.0);
			if (rotate)
			{
				glRotated(move, 0.0, 0.0, 1.0);
			}
			if (rectangle == true)
			{
				glBegin(GL_POLYGON);
				glVertex2f(10, 10 + big);
				glVertex2f(10, -10);
				glVertex2f(-10, -10);
				glVertex2f(-10, 10 + big);
				glEnd();
			}
			else
			{
				glBegin(GL_POLYGON);
				glVertex2f(0, 10 + big);
				glVertex2f(10, -10);
				glVertex2f(-10, -10);
				glEnd();
			}
		glPopMatrix();
		break;
	case 1:
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 100; ++i)
		{
			glVertex2f(i * 6 - 300, sin(PI / 10 * i) * 25);
		}
		glEnd();
		glPushMatrix();
		glTranslated(move * 6 - 300, sin(PI / 10 * move) * 25, 0.0);
		if (rectangle == true)
		{
			glBegin(GL_POLYGON);
			glVertex2f(10, 10 + big);
			glVertex2f(10, -10);
			glVertex2f(-10, -10);
			glVertex2f(-10, 10 + big);
			glEnd();
		}
		else
		{
			glBegin(GL_POLYGON);
			glVertex2f(0, 10 + big);
			glVertex2f(10, -10);
			glVertex2f(-10, -10);
			glEnd();
		}
		glPopMatrix();
		break;
	case 2:
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 100; ++i)
		{
			glVertex2f(cos(PI / 10 * i) * (150 - i), sin(PI / 10 * i) * (150 - i));
		}
		glEnd();
		glPushMatrix();
		glTranslated(cos(PI / 10 * move) * (150 - move), sin(PI / 10 * move) * (150 - move), 0.0);
		if (rectangle == true)
		{
			glBegin(GL_POLYGON);
			glVertex2f(10, 10 + big);
			glVertex2f(10, -10);
			glVertex2f(-10, -10);
			glVertex2f(-10, 10 + big);
			glEnd();
		}
		else
		{
			glBegin(GL_POLYGON);
			glVertex2f(0, 10 + big);
			glVertex2f(10, -10);
			glVertex2f(-10, -10);
			glEnd();
		}
		glPopMatrix();
		break;
	case 3:
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 100; ++i)
		{
			if (i >= 0 && i < 20)
			{
				glVertex2f(6 * i - 300, 150 - 15 * i);
			}
			else if (i >= 20 && i < 40)
			{
				glVertex2f(6 * i - 300, 15 * (i - 20) - 150);
			}
			else if (i >= 40 && i < 60)
			{
				glVertex2f(6 * i - 300, 150 - 15 * (i - 40));
			}
			else if (i >= 60 && i < 80)
			{
				glVertex2f(6 * i - 300, 15 * (i - 60) - 150);
			}
			else
			{
				glVertex2f(6 * i - 300, 150 - 15 * (i - 80));
			}
		}
		glEnd();
		glPushMatrix();
		if (move >= 0 && move < 20)
		{
			glTranslated(6 * move - 300, 150 - 15 * move,0.0);
		}
		else if (move >= 20 && move < 40)
		{
			glTranslated(6 * move - 300, 15 * (move - 20) - 150,0.0);
		}
		else if (move >= 40 && move < 60)
		{
			glTranslated(6 * move - 300, 150 - 15 * (move - 40),0.0);
		}
		else if (move >= 60 && move < 80)
		{
			glTranslated(6 * move - 300, 15 * (move - 60) - 150,0.0);
		}
		else
		{
			glTranslated(6 * move - 300, 150 - 15 * (move - 80),0.0);
		}
		if (rectangle == true)
		{
			glBegin(GL_POLYGON);
			glVertex2f(10, 10 + big);
			glVertex2f(10, -10);
			glVertex2f(-10, -10);
			glVertex2f(-10, 10 + big);
			glEnd();
		}
		else
		{
			glBegin(GL_POLYGON);
			glVertex2f(0, 10 + big);
			glVertex2f(10, -10);
			glVertex2f(-10, -10);
			glEnd();
		}
		glPopMatrix();
		break;
	case 4:
		if (finish_point)
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 100; ++i)
			{
				if (i > 0 && i <= 25)
				{
					gox = (points[1].x - points[0].x) / 25;
					goy = (points[1].y - points[0].y) / 25;
					glVertex2f(points[0].x + i * gox, points[0].y + i * goy);
				}
				else if (i > 25 && i <= 50)
				{
					gox = (points[2].x - points[1].x) / 25;
					goy = (points[2].y - points[1].y) / 25;
					glVertex2f(points[1].x + (i-25) * gox, points[1].y + (i-25) * goy);
				}
				else if (i > 50 && i <= 75)
				{
					gox = (points[3].x - points[2].x) / 25;
					goy = (points[3].y - points[2].y) / 25;
					glVertex2f(points[2].x + (i-50) * gox, points[2].y + (i-50) * goy);
				}
				else if (i > 75 && i <= 100)
				{
					gox = (points[4].x - points[3].x) / 25;
					goy = (points[4].y - points[3].y) / 25;
					glVertex2f(points[3].x + (i - 75) * gox, points[3].y + (i - 75) * goy);
				}
			}
			glEnd();
			glPushMatrix();
			if (move > 0 && move <= 25)
			{
				gox = (points[1].x - points[0].x) / 25;
				goy = (points[1].y - points[0].y) / 25;
				glTranslated(points[0].x + move * gox, points[0].y + move * goy,0.0);
			}
			else if (move > 25 && move <= 50)
			{
				gox = (points[2].x - points[1].x) / 25;
				goy = (points[2].y - points[1].y) / 25;
				glTranslated(points[1].x + (move-25) * gox, points[1].y + (move-25) * goy,0.0);
			}
			else if (move > 50 && move <= 75)
			{
				gox = (points[3].x - points[2].x) / 25;
				goy = (points[3].y - points[2].y) / 25;
				glTranslated(points[2].x + (move-50) * gox, points[2].y + (move-50) * goy,0.0);
			}
			else
			{
				gox = (points[4].x - points[3].x) / 25;
				goy = (points[4].y - points[3].y) / 25;
				glTranslated(points[3].x + (move-75) * gox, points[3].y + (move-75) * goy,0.0);
			}
			if (rectangle == true)
			{
				glBegin(GL_POLYGON);
				glVertex2f(10, 10 + big);
				glVertex2f(10, -10);
				glVertex2f(-10, -10);
				glVertex2f(-10, 10 + big);
				glEnd();
			}
			else
			{
				glBegin(GL_POLYGON);
				glVertex2f(0, 10 + big);
				glVertex2f(10, -10);
				glVertex2f(-10, -10);
				glEnd();
			}
			glPopMatrix();
		}
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