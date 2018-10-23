#include <GL/freeglut.h>
#include <math.h>
#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *qobj;
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void draw_rectangle(int x, int y, int z);
void crane();

int rotationY = 90;
int rotationX = 0;
int rotationZ = 0;
int camPosX = 0;
int camPosY = 300;
int camPosZ = 150;
int move_1 = 0;
int move_2 = 0;
int move_3 = 0;
int move_1_ = 0;
int move_2_ = 0;
int move_3_ = 0;
int level1Rotate = 0;
int level2Rotate = 0;
int level1Front = 0;
int level1Left = 0;
int level2Tilt = 0;
int level3Tilt = 0;
int level3Tilt2 = 0;
int angle = 0;
int animation = 0;
bool Animation = true;
void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("1-20");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);

	glutMainLoop();
}
void TimerFunction(int value)
{
	if (Animation)
	{
		animation += 2;
		if (animation == 450)
		{
			Animation = false;
		}
	}
	else
	{
		animation -= 2;
		if (animation == -450)
		{
			Animation = true;
		}
	}
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
		angle += 3;
		break;
	case 'X':
		rotationX -= 3;
		angle -= 3;
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
	case '5':
		level1Front -= 3;
		break;
	case '1':
		level1Left -= 3;
		break;
	case '2':
		level1Front += 3;
		break;
	case '3':
		level1Left += 3;
		break;
	case '4':
		level1Rotate += 3;
		break;
	case '6':
		level1Rotate -= 3;
		break;
	case 'l':
		level2Rotate -= 3;
		break;
	case ',':
		if (level2Tilt <= 90)
		{
			level2Tilt += 3;
		}
		break;
	case '.':
		if (level2Tilt >= -90)
		{
			level2Tilt -= 3;
		}
		break;
	case'n':
		if (level3Tilt <= 90)
		{
			level3Tilt += 3;
		}
		break;
	case 'm':
		if (level3Tilt >= -90)
		{
			level3Tilt -= 3;
		}
		break;
	case 'j':
		if (level3Tilt2 >= -90)
		{
			level3Tilt2 -= 3;
		}
		break;
	case 'k':
		if (level3Tilt2 <= 90)
		{
			level3Tilt2 += 3;
		}
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
	glLoadIdentity();
	float atX = camPosX + cosf(rotationY*PI / 180);
	float atY = camPosY + sinf(rotationX*PI / 180);
	float atZ = camPosZ - sinf(rotationY*PI / 180) - cosf(rotationX*PI / 180);

	gluLookAt(camPosX, camPosY, camPosZ, atX, atY, atZ, 0, 1, 0);//여기가 룻엣읷고

	glPushMatrix();

	glRotated(90, 1.0, 0.0, 0.0);
	glColor4f(0.2f, 0.6f, 0.3f, 1.0f);
	glRectf(-500, -500, 500, 500);
	glRotatef(-90, 1.0, 0.0, 0.0);

	glPushMatrix();

	glTranslatef(animation, 50, 0);
	crane();
	glPopMatrix();


	glPopMatrix();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}
void crane()
{
	glColor4f(0.5f, 0.5f, 0.1f, 1.0f);
	glPushMatrix();
		glTranslatef(level1Left, 0, level1Front);
		glRotatef(level1Rotate, 0, 1, 0);
		draw_rectangle(100, 70, 100);
		glPushMatrix();
			glColor4f(0.6f, 0.6f, 0.2f, 1.0f);
			glTranslatef(0, 35, 0);
			glRotatef(level2Rotate, 0, 1, 0);
			glRotatef(level2Tilt, 0, 0, 1);
			glTranslatef(0, 50, 0);
			draw_rectangle(20, 100, 20);
			glPushMatrix();
				glColor4f(0.8f, 0.8f, 0.2f, 1.0f);
				glTranslatef(0, 50, 0);
				glRotatef(level3Tilt2, 1, 0, 0);
				glRotatef(level3Tilt, 0, 0, 1);
				glTranslatef(0, 40, 0);
				draw_rectangle(15, 80, 15);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

}
void draw_rectangle(int x, int y, int z)
{
	float scale_x;
	float scale_y;
	float scale_z;
	scale_x = x / 10.0;
	scale_y = y / 10.0;
	scale_z = z / 10.0;

	glPushMatrix();
	glScaled((float)scale_x, (float)scale_y, (float)scale_z);
	glutSolidCube(10);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glutWireCube(10);
	glPopMatrix();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -400.0, 400.0);
	// 투영 행렬 스택 재설정
	//glMatrixMode(GL_PROJECTION);


	glMatrixMode(GL_PROJECTION);//투영행렬을 만든것임
	glLoadIdentity();
	gluPerspective(60.0f, w / h, 1.0, -1000.0);
	glTranslatef(0.0, 0.0, -1000);
	//glTranslatef(-300, 00, -200);
}