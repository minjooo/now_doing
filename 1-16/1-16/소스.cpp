#include <GL/freeglut.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

int turn_y = 0;
int turn_x = 0;
int turn_z = 0;
int choose = 0;
int turn_left = 0;
int turn_right = 0;
bool change = false;
void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("1-16");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}
void TimerFunction(int value)
{
	glutPostRedisplay();
	//glutTimerFunc(100, TimerFunction, 1);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		turn_x += 5;
		break;
	case 'y':
		turn_y += 5;
		break;
	case 'z':
		turn_z += 5;
		break;
	case 'q':
		PostQuitMessage(NULL);
		break;
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
	case 'c':
		if (change)
		{
			change = false;
		}
		else
		{
			change = true;
		}
		break;
	case 'l':
		turn_left += 3;
		break;
	case 'r':
		turn_right += 3;
		break;
	case 'o':
		turn_left += 3;
		turn_right += 3;
	}
	glutPostRedisplay();
}
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPushMatrix();

	//glTranslatef(400, 300, 0.0);//중점 가운데로
	//glRotated(20, 1.0f, 0.0f, 0.0f);
	glRotated(turn_y, 0.0f, 1.0f, 0.0f);
	glRotated(turn_x, 1.0f, 0.0f, 0.0f);
	glRotated(turn_z, 0.0f, 0.0f, 1.0f);//회전

	glBegin(GL_LINES);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(-40.0, 0.0, 0.0);
	glVertex3f(40.0, 0.0, 0.0);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex3f(0.0, -30.0, 0.0);
	glVertex3f(0.0, 30.0, 0.0);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0, 0.0, -30.0);
	glVertex3f(0.0, 0.0, 30.0);
	glEnd();//가로선 세로선

	//glTranslated(gox, goy, 0.0);//이동
	//glScaled(scale, 1.0, 1.0);//확대

	glPushMatrix();
	glRotated(270, 1.0f, 0.0f, 0.0f);
	glTranslated(0.0, 0.0, -50.0);
	glColor4f(0.3f, 0.4f, 0.2f, 1.0f);
	glRectd(-200, -200, 200, 200);
	glPopMatrix();//바닥 판 그리기

	//glRotated(270, 1.0f, 0.0f, 0.0f);
	glColor4f(0.5f, 0.6f, 0.7f, 1.0f);
	glPushMatrix();
	glRotated(270, 1.0f, 0.0f, 0.0f);
	if (choose == 1)
	{
		glTranslated(-80.0, 0.0, 0.0);
		glPushMatrix();
		glRotated(turn_left, 0.0, 0.0, 1.0);
		if (change)
		{
			glutWireCube(90);
		}
		else
		{
			glutSolidCube(90);
		}
		glPopMatrix();
		glTranslated(160.0, 0.0, 0.0);
		glPushMatrix();
		glRotated(turn_right, 0.0, 0.0, 1.0);
		if (change)
		{
			glutSolidCube(90);
		}
		else
		{
			glutWireCube(90);
		}
		glPopMatrix();
	}
	else if (choose == 2)
	{
		glTranslated(-80.0, 0.0, 0.0);
		glPushMatrix();
		glRotated(turn_left, 0.0, 0.0, 1.0);
		if (change)
		{
			glutWireSphere(45, 10, 10);
		}
		else
		{
			glutSolidSphere(45, 10, 10);
		}
		glPopMatrix();
		glTranslated(160.0, 0.0, 0.0);
		glPushMatrix();
		glRotated(turn_right, 0.0, 0.0, 1.0);
		if (change)
		{
			glutSolidSphere(45, 10, 10);
		}
		else
		{
			glutWireSphere(45, 10, 10);
		}
		glPopMatrix();
	}
	else if (choose == 3)
	{
		glTranslated(-80.0, -40.0, -40.0);
		glPushMatrix();
		glRotated(turn_left, 0.0, 0.0, 1.0);
		if (change)
		{
			glutWireCone(40.0, 80.0, 10, 10);
		}
		else
		{
			glutSolidCone(40.0, 80.0, 10, 10);
		}
		glPopMatrix();
		glTranslated(160.0, 0.0, 0.0);
		glPushMatrix();
		glRotated(turn_right, 0.0, 0.0, 1.0);
		if (change)
		{
			glutSolidCone(40.0, 80.0, 10, 10);
		}
		else
		{
			glutWireCone(40.0, 80.0, 10, 10);
		}
		glPopMatrix();
	}
	else if (choose == 4)
	{
		glTranslated(-80.0, 0.0, 0.0);
		glRotated(90, 1.0f, 0.0f, 0.0f);
		glPushMatrix();
		glRotated(turn_left, 0.0, 1.0, 0.0);
		if (change)
		{
			glutWireTeapot(50);
		}
		else
		{
			glutSolidTeapot(50);
		}
		glPopMatrix();
		glTranslated(160.0, 0.0, 0.0);
		glPushMatrix();
		glRotated(turn_right, 0.0, 1.0, 0.0);
		if (change)
		{
			glutSolidTeapot(50);
		}
		else
		{
			glutWireTeapot(50);
		}
		glPopMatrix();
	}
	glPopMatrix();
	

	
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glFlush();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -400.0, 400.0);
	// 투영 행렬 스택 재설정
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -600.0); // 투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
}