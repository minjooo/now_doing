#include <GL/freeglut.h>
#include<math.h>

#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

int turnY = 0;
float scale = 1.0;
int move = 0;
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
	move += 1;
	if (move == 300)
	{
		move = 0;
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		scale += 0.1;
		break;
	case 'S':
		scale -= 0.1;
		break;
	case 'y':
		turnY += 3;
		break;
	case 'Y':
		turnY -= 3;
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
	glScaled(scale, scale, scale);//확대
	
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 300; ++i)
	{
		if (i >= 0 && i < 100)
		{
			glVertex3f(i * 2, 150 - 3 * i, 0.0);
		}
		else if (i >= 100 && i < 200)
		{
			glVertex3f(200-(4*(i-100)), -150, 0.0);
		}
		else if (i >= 200 && i < 300)
		{
			glVertex3f((i - 200) * 2 - 200, 3 * (i - 200) - 150, 0.0);
		}
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 300; ++i)
	{
		if (i >= 0 && i < 100)
		{
			glVertex3f(0.0, 150 - 3 * i, i * 2);
		}
		else if (i >= 100 && i < 200)
		{
			glVertex3f(0.0, -150, 200 - (4 * (i - 100)));
		}
		else if (i >= 200 && i < 300)
		{
			glVertex3f(0.0, 3 * (i - 200) - 150, (i - 200) * 2 - 200);
		}
	}
	glEnd();
	
	glPushMatrix();
	if (move >= 0 && move < 100)
	{
		glTranslated(move * 2, 150 - 3 * move, 0.0);
	}
	else if (move >= 100 && move < 200)
	{
		glTranslated(200 - (4 * (move - 100)), -150, 0.0);
	}
	else if (move >= 200 && move < 300)
	{
		glTranslated((move - 200) * 2 - 200, 3 * (move - 200) - 150, 0.0);
	}
	glBegin(GL_POLYGON);
		glVertex2f(0, 15);
		glVertex2f(10, -10);
		glVertex2f(-10, -10);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	if (move >= 0 && move < 100)
	{
		glTranslated(0.0, 150 - 3 * move, move * 2);
	}
	else if (move >= 100 && move < 200)
	{
		glTranslated(0.0, -150, 200 - (4 * (move - 100)));
	}
	else if (move >= 200 && move < 300)
	{
		glTranslated(0.0, 3 * (move - 200) - 150, (move - 200) * 2 - 200);
	}
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 15,0);
	glVertex3f(0.0, -10,10);
	glVertex3f(0.0,-10,-10);
	glEnd();
	glPopMatrix();
	
	glPopMatrix();
	glFlush();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -200.0, 200.0);
}