#include <GL/freeglut.h>
#include<stdlib.h>
#include<time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void draw_rectangle(int x, int y, int z);
void draw_full_rectangle(int x, int y, int z);
void draw_empty8();
void draw_number(int num);

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1400, 600);
	glutCreateWindow("1-15");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(1000, TimerFunction, 1);
	glutMainLoop();
	srand(time(NULL));
}
int turn_Y = -30;
int turn_X = -30;
int h_10, h_1, m_10, m_1, s_10, s_1;

bool fliker = true;
void TimerFunction(int value)
{
	if (fliker == true)
	{
		fliker = false;
	}
	else if (fliker == false)
	{
		fliker = true;
	}
	time_t now = time(0);
	struct tm curr_time;
	localtime_s(&curr_time, &now);

	h_10 = curr_time.tm_hour / 10, h_1 = curr_time.tm_hour % 10;
	m_10 = curr_time.tm_min / 10, m_1 = curr_time.tm_min % 10;
	s_10 = curr_time.tm_sec / 10, s_1 = curr_time.tm_sec % 10;
	glutPostRedisplay();
	glutTimerFunc(1000, TimerFunction, 1);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
		turn_Y += 3;
		break;
	case 'a':
		turn_Y -= 3;
		break;
	case 'w':
		turn_X += 3;
		break;
	case 's':
		turn_X -= 3;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glPushMatrix();

	glTranslatef(700, 300, 0.0);//중점 가운데로
	glRotated(turn_Y, 0.0f, 1.0f, 0.0f);
	glRotated(turn_X, 1.0f, 0.0f, 0.0f);
	//glTranslated(gox, goy, 0.0);//이동
	//glScaled(scale, 1.0, 1.0);//확대
	//glRotated(turnY, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glTranslatef(-550, 0.0, 0.0);
	draw_empty8();
	draw_number(h_10);
	glPopMatrix();//시간 10

	glPushMatrix();
	glTranslatef(-350, 0.0, 0.0);
	draw_empty8();
	draw_number(h_1);
	glPopMatrix();//시간 1

	glPushMatrix();
	glTranslatef(-100, 0.0, 0.0);
	draw_empty8();
	draw_number(m_10);
	glPopMatrix();//분 10

	glPushMatrix();
	glTranslatef(100, 0.0, 0.0);
	draw_empty8();
	draw_number(m_1);
	glPopMatrix();//분 1

	glPushMatrix();
	glTranslatef(350, 0.0, 0.0);
	draw_empty8();
	draw_number(s_10);
	glPopMatrix();//초 10

	glPushMatrix();
	glTranslatef(550, 0.0, 0.0);
	draw_empty8();
	draw_number(s_1);
	glPopMatrix();//초 1

	//점찍자
	glPushMatrix();
	glTranslatef(-220, 50.0, 0.0);
	if (fliker == true)
	{
		glutSolidCube(30);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glutWireCube(30);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else {
		glutWireCube(30);
	}
	glTranslatef(0, -100.0, 0.0);
	if (fliker == true)
	{
		glutSolidCube(30);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glutWireCube(30);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else {
		glutWireCube(30);
	}
	glTranslatef(450, 0.0, 0.0);
	if (fliker == true)
	{
		glutSolidCube(30);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glutWireCube(30);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else {
		glutWireCube(30);
	}
	glTranslatef(0, 100.0, 0.0);
	if (fliker == true)
	{
		glutSolidCube(30);
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glutWireCube(30);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else {
		glutWireCube(30);
	}
	glPopMatrix();//초 1



	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glFlush();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 1400.0, 0.0, 600.0, -800.0, 800.0);
}
void draw_number(int num)
{
	if (num == 1)
	{
		glPushMatrix();
		glTranslated(60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//오
	}
	else if (num == 2)
	{
		glPushMatrix();
		glTranslated(-60, 50, 0);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//왼	
		glPushMatrix();
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, 100, 0);
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, -200, 0);
		draw_full_rectangle(80, 40, 50);
		glPopMatrix();//위
		glPushMatrix();
		glTranslated(60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//오
	}
	else if (num == 3)
	{
		glPushMatrix();
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, 100, 0);
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, -200, 0);
		draw_full_rectangle(80, 40, 50);
		glPopMatrix();//위
		glPushMatrix();
		glTranslated(60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//오
	}
	else if (num == 4)
	{
		glPushMatrix();
		glTranslated(-60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//왼	
		glPushMatrix();
		draw_full_rectangle(80, 40, 50);
		glPopMatrix();//위
		glPushMatrix();
		glTranslated(60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//오
	}
	else if (num == 5)
	{
		glPushMatrix();
		glTranslated(-60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//왼	
		glPushMatrix();
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, 100, 0);
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, -200, 0);
		draw_full_rectangle(80, 40, 50);
		glPopMatrix();//위
		glPushMatrix();
		glTranslated(60, 50, 0);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//오
	}
	else if (num == 6)
	{
		glPushMatrix();
		glTranslated(-60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//왼
		glPushMatrix();
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, 100, 0);
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, -200, 0);
		draw_full_rectangle(80, 40, 50);
		glPopMatrix();//위
		glPushMatrix();
		glTranslated(60, 50, 0);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//오
	}
	else if (num == 7)
	{
		glPushMatrix();
		glTranslated(-60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//왼	
		glPushMatrix();
		glTranslated(0, 100, 0);
		draw_full_rectangle(80, 40, 50);
		glPopMatrix();//위
		glPushMatrix();
		glTranslated(60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//오
	}
	else if (num == 8)
	{
		glPushMatrix();
		glTranslated(-60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//왼	
		glPushMatrix();
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, 100, 0);
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, -200, 0);
		draw_full_rectangle(80, 40, 50);
		glPopMatrix();//위
		glPushMatrix();
		glTranslated(60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//오
	}
	else if (num == 9)
	{
		glPushMatrix();
		glTranslated(-60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//왼	
		glPushMatrix();
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, 100, 0);
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, -200, 0);
		draw_full_rectangle(80, 40, 50);
		glPopMatrix();//위
		glPushMatrix();
		glTranslated(60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//오
	}
	else if (num == 0)
	{
		glPushMatrix();
		glTranslated(-60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//왼	
		glPushMatrix();
		glTranslated(0, 100, 0);
		draw_full_rectangle(80, 40, 50);
		glTranslated(0, -200, 0);
		draw_full_rectangle(80, 40, 50);
		glPopMatrix();//위
		glPushMatrix();
		glTranslated(60, 50, 0);
		draw_full_rectangle(40, 80, 50);
		glTranslated(0, -100, 0);
		draw_full_rectangle(40, 80, 50);
		glPopMatrix();//오
	}
}
void draw_empty8()
{
	glPushMatrix();
	draw_rectangle(80, 40, 50);
	glTranslated(0, 100, 0);
	draw_rectangle(80, 40, 50);
	glTranslated(0, -200, 0);
	draw_rectangle(80, 40, 50);
	glPopMatrix();//위
	glPushMatrix();
	glTranslated(-60, 50, 0);
	draw_rectangle(40, 80, 50);
	glTranslated(0, -100, 0);
	draw_rectangle(40, 80, 50);
	glPopMatrix();//왼	
	glPushMatrix();
	glTranslated(60, 50, 0);
	draw_rectangle(40, 80, 50);
	glTranslated(0, -100, 0);
	draw_rectangle(40, 80, 50);
	glPopMatrix();//오
}
void draw_full_rectangle(int x, int y, int z)
{
	float scale_x;
	float scale_y;
	float scale_z;
	scale_x = x / 10;
	scale_y = y / 10;
	scale_z = z / 10;

	glColor4f(0.0f, 0.4f, 0.5f, 1.0f);
	glPushMatrix();
	glScaled(scale_x, scale_y, scale_z);
	glutSolidCube(10);
	glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
	glutWireCube(10);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPopMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
void draw_rectangle(int x, int y, int z)
{
	float scale_x;
	float scale_y;
	float scale_z;
	scale_x = x / 10;
	scale_y = y / 10;
	scale_z = z / 10;

	glPushMatrix();
	glScaled(scale_x, scale_y, scale_z);
	glutWireCube(10);
	glPopMatrix();
}