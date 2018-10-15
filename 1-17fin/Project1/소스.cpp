#include <GL/freeglut.h>
#include <math.h>
#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);

int rotationY = 90;
int rotationX = 0;
int rotationZ = 0;
int camPosX = 0;
int camPosY = 0;
int camPosZ = 150;
int move_1 = 0;
int move_2 = 0;
int move_3 = 0;
int move_1_ = 0;
int move_2_ = 0;
int move_3_ = 0;
bool wire = true;
void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("1-17");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	

	int menu, submenu;
	submenu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Wire", 2);
	glutAddMenuEntry("Solid", 1);

	menu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("type", submenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}
void MenuFunc(int button)
{
	switch (button)
	{
	case 1:
		wire = false;
		break;
	case 2:
		wire = true;
		break;
	case 3:
		break;
	}
	glutPostRedisplay();
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
	switch (key)//여기가 그 음 음 넣는데...?
	{
	case 'x':
		rotationX += 3;
		break;
	case 'y':
		rotationY += 3;
		break;
	case 'z':
		rotationZ += 3;
		break;
	case 'X':
		rotationX -= 3;
		break;
	case 'Y':
		rotationY -= 3;
		break;
	case 'Z':
		rotationZ -= 3;
		break;
	case 'w':
		camPosY -= 2;
		break;
	case 'a':
		camPosX += 2;
		break;
	case 's':
		camPosY += 2;
		break;
	case 'd':
		camPosX -= 2;
		break;
	case '+':
		camPosZ -= 2;
		break;
	case '-':
		camPosZ += 2;
		break;
	case 'i':
		rotationY = 90;
		rotationX = 0;
		rotationZ = 0;
		camPosX = 0;
		camPosY = 0;
		camPosZ = 150;
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
	glMatrixMode(GL_MODELVIEW);

	//camPosY += sin(PI / 180 * turn_x) * 150 +sin(PI / 180 * turn_x)*camPosY;
	//camPosZ += cos(PI / 180 * turn_x) * 150 -sin(PI / 180 * turn_x)*camPosZ;
	//
	//camPosX = cos(PI / 180 * turn_y) * 150 - sin(PI / 180 * turn_y)*camPosZ;
	//camPosZ = sin(PI / 180 * turn_y) * 150 + cos(PI / 180 * turn_y)*camPosZ;
	//
	//camPosX = cos(PI / 180 * turn_z) * 150 - sin(PI / 180 * turn_z)*camPosY;
	//camPosY = sin(PI / 180 * turn_z) * 150 + cos(PI / 180 * turn_z)*camPosY;
	float atX = camPosX + cosf(rotationY*PI / 180);
	float atY = camPosY + sinf(rotationX*PI / 180);
	float atZ = camPosZ - sinf(rotationY*PI / 180) - cosf(rotationX*PI / 180);

	gluLookAt(camPosX, camPosY, camPosZ, atX, atY, atZ, 0, 1, 0);//여기가 룻엣읷고

	//glRotated(turn_y, 0.0f, 1.0f, 0.0f);
	//glRotated(turn_x, 1.0f, 0.0f, 0.0f);
	//glRotated(turn_z, 0.0f, 0.0f, 1.0f);//회전

	glPushMatrix();

		glColor4f(0.8f, 0.3f, 0.2f, 1.0f);
		if (wire)
		{
			glutWireSphere(20, 20, 20);
		}
		else
		{
			glutSolidSphere(20, 20, 20);
		}
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
			if (wire)
			{
				glutWireSphere(5, 20, 20);
			}
			else
			{
				glutSolidSphere(5, 20, 20);
			}
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
				if (wire)
				{
					glutWireSphere(2, 20, 20);
				}
				else
				{
					glutSolidSphere(2, 20, 20);
				}
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
			if (wire)
			{
				glutWireSphere(5, 20, 20);
			}
			else
			{
				glutSolidSphere(5, 20, 20);
			}
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
				if (wire)
				{
					glutWireSphere(2, 20, 20);
				}
				else
				{
					glutSolidSphere(2, 20, 20);
				}
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
			if (wire)
			{
				glutWireSphere(5, 20, 20);
			}
			else
			{
				glutSolidSphere(5, 20, 20);
			}
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
				if (wire)
				{
					glutWireSphere(2, 20, 20);
				}
				else
				{
					glutSolidSphere(2, 20, 20);
				}
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glPopMatrix();
		glPopMatrix();

		glPopMatrix();


	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
	//glFlush();?????
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -400.0, 400.0);
	// 투영 행렬 스택 재설정
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);//투영행렬을 만든것임
	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	
	glTranslatef(0.0, 0.0, 0.0); // 투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.흠 무쓸ㄹ모
}