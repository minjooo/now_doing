#include <GL/freeglut.h>
#include <math.h>
#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

int turn_y = 0;
int turn_x = 0;
int turn_z = 0;
int move_1 = 0;
int move_2 = 0;
int move_3 = 0;
int move_1_ = 0;
int move_2_ = 0;
int move_3_ = 0;
void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("1-17");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}
void TimerFunction(int value)
{
	move_1 += 1;
	move_2 += 3;
	move_3 += 2;
	move_1_ += 6;
	move_2_ += 8;
	move_3_ += 10;
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
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
	}
	glutPostRedisplay();
}
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


	glPushMatrix();

	gluLookAt(cos(PI/180*turn_y)*300+sin(PI/180*turn_z)*300, cos(PI / 180 * turn_x) * 300  + sin(PI / 180 * turn_z) * 300, cos(PI / 180 * turn_x) * 300 + sin(PI / 180 * turn_y) * 300, 0.0, 0.0, 0.0, 0, 1, 0);
	//glRotated(turn_y, 0.0f, 1.0f, 0.0f);
	//glRotated(turn_x, 1.0f, 0.0f, 0.0f);
	//glRotated(turn_z, 0.0f, 0.0f, 1.0f);//회전

	glColor4f(0.8f, 0.3f, 0.2f, 1.0f);
	glutSolidSphere(20, 20, 20);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRotated(90, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(cos(PI / 180 * i) * 120, sin(PI / 180 * i) * 120);
	}
	glEnd();
	glPushMatrix();
	glTranslated(cos(PI / 180 * move_1) * 120, sin(PI / 180 * move_1) * 120, 0.0);
	glColor4f(0.0f, 0.6f, 0.7f, 1.0f);
	glutSolidSphere(5, 20, 20);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(cos(PI / 180 * i) * 20, sin(PI / 180 * i) * 20);
	}
	glEnd();
	glPushMatrix();
	glTranslated(cos(PI / 180 * move_1_) * 20, sin(PI / 180 * move_1_) * 20, 0.0);
	glColor4f(0.5f, 0.4f, 1.0f, 1.0f);
	glutSolidSphere(2, 20, 20);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPopMatrix();
	glPopMatrix();

	glRotated(45, 0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(cos(PI / 180 * i) * 120, sin(PI / 180 * i) * 120);
	}
	glEnd();
	glPushMatrix();
	glTranslated(cos(PI / 180 * move_2) * 120, sin(PI / 180 * move_2) * 120, 0.0);
	glColor4f(0.9f, 0.7f, 0.6f, 1.0f);
	glutSolidSphere(5, 20, 20);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(cos(PI / 180 * i) * 20, sin(PI / 180 * i) * 20);
	}
	glEnd();
	glPushMatrix();
	glTranslated(cos(PI / 180 * move_2_) * 20, sin(PI / 180 * move_2_) * 20, 0.0);
	glColor4f(0.5f, 0.5f, 0.2f, 1.0f);
	glutSolidSphere(2, 20, 20);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPopMatrix();
	glPopMatrix();

	glRotated(-90, 0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(cos(PI / 180 * i) * 120, sin(PI / 180 * i) * 120);
	}
	glEnd();
	glPushMatrix();
	glTranslated(cos(PI / 180 * move_3) * 120, sin(PI / 180 * move_3) * 120, 0.0);
	glColor4f(0.4f, 0.9f, 0.6f, 1.0f);
	glutSolidSphere(5, 20, 20);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 360; ++i)
	{
		glVertex2f(cos(PI / 180 * i) * 20, sin(PI / 180 * i) * 20);
	}
	glEnd();
	glPushMatrix();
	glTranslated(cos(PI / 180 * move_3_) * 20, sin(PI / 180 * move_3_) * 20, 0.0);
	glColor4f(0.3f, 0.4f, 0.5f, 1.0f);
	glutSolidSphere(2, 20, 20);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPopMatrix();
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
	//glTranslatef(0.0, 0.0, -300.0); // 투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.

}