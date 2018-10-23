#include <GL/freeglut.h>
#include<stdlib.h>
#include<time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void TimerFunction1(int value);
void TimerFunction2(int value);
void Motion(int x, int y);
void DrawEmptyBoxes(int x, int y);//중앙 좌표 넘겨준다
void MovingTriangles();
void ShootingRectangle();
void IWillCut();
void CuttingNow(int startX, int startY, int endX, int endY, int squareY);
void CutLeftRight(int squareY);
void CutUpDown(int squareY);
void RainbowStar();

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 700);
	glutCreateWindow("저 별은 내 별이다");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(100, TimerFunction1, 1);
	glutTimerFunc(7000, TimerFunction2, 2);
	glutMainLoop();
	srand(time(NULL));
}
struct rainbowStar {
	int x;
	int y;
	int r = rand() % 100 + 100;
	int g = rand() % 100 + 100;
	int b = rand() % 100 + 100;
	float sizeAndColor = 0.0;
	int count = 0;
	bool goup = true;
	bool ON = false;
};
struct cuttingLine {
	int startX;
	int startY;
	int endX;
	int endY;
	bool cutting;
};
struct freeTriangles {
	int x;
	int y; //중점이 가운데 있을 때만 가능
	int rotate;
	bool match = false;
};
struct shootingRectangles {
	int leftTriangleX;
	int leftTriangleY;
	int rightTriangleX;
	int rightTriangleY;

	int rectangleY = -300;
	float fade = 1.0;
	
	bool canCut = true;
	bool seperate = false;
};
struct twoTriangle {
	int firstX;
	int firstY;
	int firstRotate = -(rand() % 10);

	int secondX;
	int secondY;
	int secondRotate = rand() % 10;

	bool ON = false;
};

freeTriangles triangles[11] = { {-548, 300,rand()%100},{-452,300,rand() % 100},{-352,300,rand() % 100},{-252,300,rand() % 100},{-152,300,rand() % 100},{-52,300,rand() % 100},{52,300,rand() % 100},{152,300,rand() % 100},{252,300,rand() % 100},{352,300,rand() % 100},{452,300,rand() % 100} };
shootingRectangles shoot;
cuttingLine cut;
rainbowStar star[16];//16개가 최대더라
twoTriangle tt;//암락티티
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(500, 350, 0.0);

	glBegin(GL_LINES);//맨 위 선
		glVertex3f(-500.0, 250.0, 0.0);
		glVertex3f(500.0, 250.0, 0.0);
		glVertex3f(-500.0, 300.0, 0.0);
		glVertex3f(500.0, 300.0, 0.0);
	glEnd();

	glPushMatrix();// 밑에 네모 박스
	glTranslatef(-300.0, -250.0, 0.0);
	DrawEmptyBoxes(0, 0);
	DrawEmptyBoxes(600, 0);
	glPopMatrix();
	
	glPushMatrix();
	MovingTriangles();
	glPopMatrix();

	if (shoot.seperate == false)
	{
		glPushMatrix();
		ShootingRectangle();
		glPopMatrix();
	}
	else if (shoot.seperate == true)
	{
		glPushMatrix();
		CutLeftRight(shoot.rectangleY);
		glPopMatrix();
	}

	IWillCut();

	glPopMatrix();
	glFlush();
}
void TimerFunction1(int value)
{
	for (int i = 0; i < 11; ++i)
	{
		if (triangles[i].x <= -550)
		{
			triangles[i].x = 550;
		}
		triangles[i].x -= 2;
		triangles[i].rotate += 3;
	}
	for (int i = 0; i < 16; ++i)
	{
		if (true == star[i].ON)
		{
			if (true == star[i].goup)
			{

			}
		}
	}
	shoot.rectangleY += 8;
	if (shoot.rectangleY >= 250)
	{
		shoot.canCut = false;
	}
	if (false == shoot.canCut)
	{

		shoot.fade -= 0.1;
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction1, 1);
}
void TimerFunction2(int value)
{
	shoot.rectangleY = -400;
	shoot.canCut = true;
	shoot.seperate = false;
	shoot.fade = 1.0;
	glutPostRedisplay();
	glutTimerFunc(10000, TimerFunction2, 2);
}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cut.cutting = true;
		cut.startX = x-500;
		cut.startY = -(y-350);
		cut.endX = x - 500;
		cut.endY = -(y - 350);
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		cut.cutting = false;
		cut.endX = x-500;
		cut.endY = -(y-350);
		CuttingNow(cut.startX, cut.startY, cut.endX, cut.endY, shoot.rectangleY);
	}
	glutPostRedisplay();
}
void Motion(int x, int y)
{
	if(true==cut.cutting)
	{
		cut.endX = x - 500;
		cut.endY = -(y - 350);
	}
	glutPostRedisplay();
}
void CutLeftRight(int squareY)
{
	tt.firstX = -40;
	tt.secondX = 40;
	tt.firstRotate = -45;
	tt.secondRotate = -45;
	tt.firstY = squareY + 5;
	tt.secondY = squareY + 5;

	glPushMatrix();
	glTranslatef(tt.firstX, tt.firstY, 0);
	glRotatef(tt.firstRotate, 0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.0);
	glVertex3f(50, 0, 0.0);
	glVertex3f(0, 50, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(tt.secondX, tt.secondY, 0);
	glRotatef(tt.secondRotate, 0, 0, 1);

	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0.0);
	glVertex3f(0, -50, 0.0);
	glVertex3f(-50, 0, 0.0);
	glEnd();
	glPopMatrix();
}
void CutUpDown(int squareY)
{

}
void ShootingRectangle()
{
	glColor4f(1.0, 1.0, 1.0, shoot.fade);
	glTranslatef(0, shoot.rectangleY, 0);
	glRotatef(45, 0, 0, 1);
	glBegin(GL_POLYGON);
		glVertex3f(0 - 25, +25, 0.0);
		glVertex3f(0 - 25, -25, 0.0);
		glVertex3f(0 + 25, -25, 0.0);
		glVertex3f(0 + 25, +25, 0.0);
	glEnd();
}
void MovingTriangles()
{
	for (int i = 0; i < 11; ++i)
	{
		if (false == triangles[i].match)
		{
			glPushMatrix();
			glTranslatef(triangles[i].x, 300, 0);
			glRotatef(triangles[i].rotate, 0, 0, 1);

			glBegin(GL_POLYGON);
				glVertex3f(0, 25, 0.0);
				glVertex3f(0 - 25, -25, 0.0);
				glVertex3f(0 + 25, -25, 0.0);
			glEnd();
			glPopMatrix();
		}
	}
}
void CuttingNow(int startX, int startY, int endX, int endY, int squareY)
{
	if ((abs(endX - startX) > abs(endY - startY))&&(abs(endY-startY)<20)&&abs((endY+startY)/2-squareY)<15)// -
	{
		shoot.canCut = false;
		shoot.seperate = true;
		CutUpDown(squareY);
	}
	else if ((abs(endX - startX) < abs(endY - startY)) && (abs(endX - startX) < 10) && abs((endX + startX) / 2 ) < 15)// |
	{
		shoot.canCut = false;
		shoot.seperate = true;
		CutLeftRight(squareY);
	}
}
void IWillCut()
{
	glColor4f(1.0, 0.0, 0.0, 1.0);

	if (true == cut.cutting)
	{
		glBegin(GL_LINES);
			glVertex3f(cut.startX, cut.startY, 0.0);
			glVertex3f(cut.endX, cut.endY, 0.0);
		glEnd();
	}
	glColor4f(1.0, 1.0, 1.0, 1.0);
}
void RainbowStar()
{
	for (int i = 0; i < 16; ++i)
	{
		if (true == star[i].ON)
		{
			glColor4f(star[i].r, star[i].g, star[i].b, 1.0);
			glPushMatrix();
				glTranslatef(star[i].x, star[i].y, 0.0);
				glBegin(GL_POLYGON);
					glVertex3f(0, 15, 0.0);
					glVertex3f(0 - 15, -15, 0.0);
					glVertex3f(0 + 15, -15, 0.0);
				glEnd();
				glBegin(GL_POLYGON);
					glVertex3f(0, -15, 0.0);
					glVertex3f(0 - 15, 15, 0.0);
					glVertex3f(0 + 15, 15, 0.0);
				glEnd();

			glPopMatrix();
			glColor4f(1.0, 1.0, 1.0, 1.0);
		}
	}

}
void DrawEmptyBoxes(int x, int y)
{
	glBegin(GL_LINES);
		glVertex3f(x - 200, y + 100, 0.0);
		glVertex3f(x + 200, y + 100, 0.0);
		glVertex3f(x - 200, y, 0.0);
		glVertex3f(x + 200, y, 0.0);
		glVertex3f(x - 200, y - 100, 0.0);
		glVertex3f(x + 200, y - 100, 0.0);
	glEnd();
	for (int i = -200; i <= 200; i += 100)
	{
		glBegin(GL_LINES);
			glVertex3f(x - i, y + 100, 0.0);
			glVertex3f(x - i, y - 100, 0.0);
		glEnd();
	}
	
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 1000.0, 0.0, 700.0, -1.0, 1.0);
}