#include <GL/freeglut.h>
#include <math.h>
#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *qobj;
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void draw_rectangle(int x, int y, int z);
void wreckingBall();

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
int angle = 0;
int moveFront = 0;
int moveLeft = 0;
int rotateFront = 0;
int rotateLeft = 0;
void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("1-19");
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
		move_1 = 0;
		move_2 = 0;
		move_3 = 0;
		move_1_ = 0;
		move_2_ = 0;
		move_3_ = 0;
		angle = 0;
		moveFront = 0;
		moveLeft = 0;
		rotateFront = 0;
		rotateLeft = 0;
		break;
	case '5':
		if (moveFront >= -500)
		{
			moveFront -= 3;
		}
		rotateFront -= 3;
		break;
	case '1':
		if (moveLeft >= -500)
		{
			moveLeft -= 3;
		}
		rotateLeft -= 3;
		break;
	case '2':
		if (moveFront <= 500)
		{
			moveFront += 3;
		}
		rotateFront += 3;
		break;
	case '3':
		if (moveLeft <= 500)
		{
			moveLeft += 3;
		}
		rotateLeft += 3;
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

	glTranslatef(0, 100, 0);
	wreckingBall();
	glPopMatrix();


	glPopMatrix();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}
void wreckingBall() 
{
	glTranslatef(0, 0, moveFront);
	glTranslatef(moveLeft, 0, 0);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPushMatrix();
	glRotatef(rotateFront, 1, 0, 0);
	glRotatef(rotateLeft, 0,0, 1);

	glutWireSphere(100, 20, 20);
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