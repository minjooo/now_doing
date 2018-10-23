#include <GL/freeglut.h>
#include <math.h>
#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *qobj;
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void drawAirplane();
void drawRunning();
void draw_rectangle(int x, int y, int z);
void bumpingTree();
void benchPress();
void bar();

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
int ppRotate = 0;
int aaa = 0;
int move = 0;
int roundandround = 0;
int treeSize = 0;
bool goup = true;
float apPup = 0;
bool airplaneCW = true;
bool wire = true;
bool jick_gack = false;
void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("1-22");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);

	glutMainLoop();
}
void TimerFunction(int value)
{
	ppRotate += 20;
	apPup += 5.0;
	if (airplaneCW)
	{
		move -= 5;
	}
	else
	{
		move += 5;
	}
	roundandround -= 3;
	if (true == goup)
	{
		treeSize += 1;
		if (treeSize == 8)
		{
			goup = false;
		}
	}
	else
	{
		treeSize -= 1;
		if (treeSize == 0)
		{
			goup = true;
		}
	}
	if (apPup == 50)
	{
		apPup = 0.0;
	}
	glutPostRedisplay();
	glutTimerFunc(1000 / 20, TimerFunction, 1);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)//여기가 그 음 음 넣는데...?
	{
	case 'p':
		airplaneCW != airplaneCW;
		break;
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
	case 'j'://직각투영으로 바꾸자
		jick_gack = !jick_gack;

		glMatrixMode(GL_PROJECTION);//투영행렬을 만든것임
		glLoadIdentity();
		if (jick_gack == false)
		{
			gluPerspective(60.0f, 8.0f / 6, 1.0, 1000.0);
			glTranslatef(0.0, 0.0, -200.0);
		}
		else
		{
			glOrtho(-300.0, 300.0, -200.0, 200.0, -100.0, 800.0);
		}
		glMatrixMode(GL_MODELVIEW);
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
	glTranslatef(0, 500, 0);
	glRotated(-90, 1.0, 0.0, 0.0);
	if (airplaneCW == false)
	{
		glRotatef(180, 0.0, 1.0, 0.0);
	}
	glScalef(0.5, 0.5, 0.5);
	glTranslated(cos(PI / 180 * move) * 500, sin(PI / 180 * move) * 500, 0.0);
	glRotated(move, 0.0, 0.0, 1.0);
	drawAirplane();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.3, 0.3, 0.3);
	glTranslatef(-1000, 25, -1000);
	drawRunning();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(-350, -350, 35);
	bumpingTree();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(350, 55, -350);
	benchPress();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.4, 0.4, 0.4);
	glTranslatef(0, 120, 0);
	glTranslatef(780, 0, 800);
	bar();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
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
void bar()
{
	glColor4f(0.8f, 0.6f, 0.8f, 1.0f);
	draw_rectangle(10, 250, 10);
	glTranslatef(150, 0, 0);
	draw_rectangle(10, 250, 10);
	glTranslatef(-75, 110, 0);
	draw_rectangle(150, 10, 10);
	glPushMatrix();
	glRotatef(roundandround * 2, 1, 0, 0);
	glPushMatrix();
	glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
	glTranslatef(0, -90, 0);
	draw_rectangle(40, 70, 20);
	glTranslatef(0, 50, 0);
	glutSolidSphere(20, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-30, -35, 0);
	glRotatef(20, 0, 0, 1);
	draw_rectangle(10, 60, 10);
	glPopMatrix();//왼팔
	glPushMatrix();
	glTranslatef(30, -35, 0);
	glRotatef(-20, 0, 0, 1);
	draw_rectangle(10, 60, 10);
	glPopMatrix();//오른팔
	glPushMatrix();
	glTranslatef(13, -150, 0);
	draw_rectangle(15, 60, 15);
	glTranslatef(-26, 0, 0);
	draw_rectangle(15, 60, 15);
	glPopMatrix();
	glPopMatrix();
}
void benchPress()
{
	glColor4f(0.5f, 0.3f, 0.3f, 1.0f);
	draw_rectangle(150, 10, 60);
	glPushMatrix();
	glColor4f(0.3f, 0.4f, 0.5f, 1.0f);
	glTranslatef(-50, -50, 0);
	draw_rectangle(10, 10, 60);
	glTranslatef(0, 25, 0);
	draw_rectangle(10, 45, 10);
	glTranslatef(100, 0, 0);
	draw_rectangle(10, 45, 10);
	glTranslatef(0, -25, 0);
	draw_rectangle(10, 10, 60);
	glPopMatrix();//다리완성
	glPushMatrix();
	glTranslatef(60, 25, 0);
	glTranslatef(0, 0, -30);
	draw_rectangle(10, 60, 10);
	glRotatef(45, 0, 0, 1);
	glTranslatef(0, 20, 0);
	draw_rectangle(10, 25, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(60, 25, 0);
	glTranslatef(0, 0, 30);
	draw_rectangle(10, 60, 10);
	glRotatef(45, 0, 0, 1);
	glTranslatef(0, 20, 0);
	draw_rectangle(10, 25, 10);
	glPopMatrix();
	glPushMatrix();
	glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
	glTranslatef(53, 35 + treeSize * 3, 0);
	draw_rectangle(10, 10, 170);
	glColor4f(1.0f, 0.5f, 0.5f, 1.0f);
	glTranslatef(0, 0, -75);
	glutSolidTorus(20, 25, 10, 10);
	glTranslatef(0, 0, 150);
	glutSolidTorus(20, 25, 10, 10);
	glPopMatrix();//아령
	glPushMatrix();
	glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
	glTranslatef(0, 10, 0);
	draw_rectangle(70, 20, 30);
	glTranslatef(50, 8, 0);
	glutSolidSphere(13, 20, 20);
	glTranslatef(-100, -8, 12);
	draw_rectangle(50, 10, 10);
	glTranslatef(0, 0, -24);
	draw_rectangle(50, 10, 10);
	glPopMatrix();//몸 얼굴 다리
	glPushMatrix();
	glTranslatef(40, 10 + treeSize, 40);
	glRotatef(treeSize*-3, 1, 0, 0);
	draw_rectangle(10, 10, 40);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(35, 25 + treeSize * 2, 45);
	draw_rectangle(8, 35, 8);
	glPopMatrix();//오른팔
	glPushMatrix();
	glTranslatef(40, 10 + treeSize, -40);
	glRotatef(treeSize * 3, 1, 0, 0);
	draw_rectangle(10, 10, 40);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(35, 25 + treeSize * 2, -45);
	draw_rectangle(8, 35, 8);
	glPopMatrix();//왼팔
}
void bumpingTree()
{
	glColor4f(0.5f, 0.5f, 0.3f, 1.0f);
	glutSolidCylinder(20, 20, 20, 20);
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor4f(0.2f, 0.2f, 0.1f, 1.0f);
	glTranslatef(0, 60, 0);
	draw_rectangle(5, 100, 5);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor4f(0.0f, 0.3f, 0.1f, 1.0f);
	glTranslatef(0, 110, 0);
	glRotatef(30, 0, 0, 1);
	glScaled(20 + treeSize, 20 + treeSize, 20 + treeSize);
	glutSolidDodecahedron();
	glPopMatrix();
}
void drawRunning()
{
	glPushMatrix();
	glScaled(4.0, 0.5, 10);
	glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
	glutSolidTorus(15, 45, 20, 10);
	glPushMatrix();
	glRotatef(roundandround, 0.0, 0.0, 1.0);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
	glutWireTorus(15, 45, 20, 10);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glColor4f(0.5f, 0.4f, 0.8f, 1.0f);
	glTranslatef(-160, 160.0, 100.0);
	draw_rectangle(20, 300, 20);
	glTranslatef(0, 0, -200.0);
	draw_rectangle(20, 300, 20);
	glTranslatef(-20, 150, 105.0);
	glRotatef(60, 0.0, 0.0, 1.0);
	draw_rectangle(20, 100, 240);
	glPopMatrix();
	glPushMatrix();
	glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
	glTranslatef(20, 230.0, 100.0);
	draw_rectangle(40, 170, 80);
	glTranslatef(0, 130, 0);
	glutSolidSphere(30, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(20, 230.0, 100.0);
	glRotatef((treeSize - 4) * 2, 0, 0, 1);
	glTranslatef(0, -140, 30);
	draw_rectangle(20, 90, 20);
	glPopMatrix();//왼쪽 다리
	glPushMatrix();
	glTranslatef(20, 230.0, 100.0);
	glRotatef((treeSize - 4) * -2, 0, 0, 1);
	glTranslatef(0, -140, -30);
	draw_rectangle(20, 90, 20);
	glPopMatrix();//오른쪽 다리
}
void drawAirplane()
{
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor4f(0.9f, 0.3f, 0.2f, 1.0f);
	draw_rectangle(200, 5, 40);
	glTranslatef(0.0, 50.0, 0.0);
	draw_rectangle(200, 5, 40);//날개끝
	glPushMatrix();
	glTranslatef(50.0, -25.0, 14.0);
	draw_rectangle(5.0, 50, 5);
	glTranslatef(48.0, 0.0, 0.0);
	draw_rectangle(5.0, 50, 5);
	glTranslatef(0.0, 0.0, -30);
	draw_rectangle(5.0, 50, 5);
	glTranslatef(-48, 0, 0);
	draw_rectangle(5.0, 50, 5);

	glTranslatef(-196, 0, 18);
	glTranslatef(50.0, 0, 14.0);
	draw_rectangle(5.0, 50, 5);
	glTranslatef(48.0, 0.0, 0.0);
	draw_rectangle(5.0, 50, 5);
	glTranslatef(0.0, 0.0, -30);
	draw_rectangle(5.0, 50, 5);
	glTranslatef(-48, 0, 0);
	draw_rectangle(5.0, 50, 5);
	glPopMatrix();//날개다리 끝
	glPushMatrix();
	glTranslatef(0, -28, 15);
	glColor4f(0.8f, 0.8f, 0.4f, 1.0f);
	draw_rectangle(40, 40, 70);
	glTranslatef(0, -2, -50);
	draw_rectangle(30, 30, 140);
	glTranslatef(0, 0, -70);
	draw_rectangle(100, 30, 5);
	glTranslatef(0, 20, -8);
	draw_rectangle(5, 60, 20);
	glPopMatrix();//몸통 끝
	glTranslatef(0, -28, 53);
	glutSolidSphere(20, 20, 20);//앞에 동그란거
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(0, 0, 22);
	glRotated(ppRotate, 0.0, 0.0, 1.0);
	draw_rectangle(50, 8, 4);
	draw_rectangle(8, 50, 4);
	glPopMatrix();//프로펠러
	glPushMatrix();
	glTranslatef(0, 0, -150);
	glTranslatef(0, 0, -apPup * 2);
	glutSolidSphere(apPup / 5, 20, 20);
	glTranslatef(0, 0, -(-10 + apPup * 2));
	glutSolidSphere(apPup / 4, 20, 20);
	glTranslatef(0, 0, -(-20 + apPup * 2));
	glutSolidSphere(apPup / 2, 20, 20);

	glPopMatrix();//비행기 방구
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