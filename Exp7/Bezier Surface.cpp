#include "GL/glut.h"
#include <math.h>
#include <iostream>
#define POINT_MAX 6
#define TIMESLEEP 10
#define POINT_SIZE 10
#define LINE_WIDTH  5

static bool down = false;					// 鼠标状态
static GLdouble	t = 0;
static GLint selectI = -1, selectJ = -1;

struct Point
{
	GLdouble x, y, z;
	Point();
	Point(GLdouble, GLdouble);
	Point(GLdouble, GLdouble, GLdouble);
};
static void		setPoint(Point);				// 画出一个点
static void		setLine(Point, Point);			// 画出两点间的线

class Bezier
{
public:
	Bezier();
	Point		bezierpoint(GLdouble, GLint);	// 计算Bezier点
	Point		bezierpoint(GLdouble, Point*);	// 计算Bezier点
	void		create(GLdouble);				// 绘画Bezier曲面
	void		setXY(GLint, GLint);			// 根据鼠标位置更新控制点坐标
	bool		hit(GLfloat, GLfloat);			// 鼠标和点的碰撞检测
	void		myAdd();						// 增加一组控制点
	void		myDelete();						// 删除一组控制点
private:
	GLint		cnt;							// 控制点的数量
	Point		points[POINT_MAX][POINT_MAX];	// 存储控制点
	GLdouble	param[POINT_MAX];				// 存储Bezier计算参数
};
static Bezier bezier = Bezier();

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0);
	glPointSize(POINT_SIZE);
	glLineWidth(LINE_WIDTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
	glClear(GL_COLOR_BUFFER_BIT);
}

void display(void)
{
	bezier.create(t);
	Sleep(TIMESLEEP);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
}

void mouseFuc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			down = true;
			if (bezier.hit(x, glutGet(GLUT_WINDOW_HEIGHT) - y))
				return;
			selectI = -1, selectJ = -1;
		}
		else if (state == GLUT_UP)
			down = false;
	}
}

void mouseMov(int x, int y)
{
	if (down && selectI != -1 && selectJ != -1)
	{
		bezier.setXY(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
		t = 0;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		bezier.myAdd();
		break;
	case 'd':
		bezier.myDelete();
		break;
	}
	glutPostRedisplay();
}

void idleFuc()
{
	t += 0.005;
	if (t >= 1.0) t = 0.0;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(600, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bezier Surface");
	init();
	glutMouseFunc(&mouseFuc);
	glutMotionFunc(&mouseMov);
	glutKeyboardFunc(&keyboard);
	glutDisplayFunc(&display);
	glutIdleFunc(&idleFuc);
	glutMainLoop();
	return 0;
}
Point::Point()
{
	x = 0, y = 0, z = 0;
}
Point::Point(GLdouble xx, GLdouble yy)
{
	x = xx, y = yy, z = 0;
}
Point::Point(GLdouble xx, GLdouble yy, GLdouble zz)
{
	x = xx, y = yy, z = zz;
}
static void setPoint(Point p)
{
	glBegin(GL_POINTS);
	glVertex3f(p.x, p.y, p.z);
	glEnd();
}
static void setLine(Point p1, Point p2)
{
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
}
GLint calculate(int first, int last)
{
	GLint cnt = 1;
	for (int i = 1; i <= first; ++i)
	{
		cnt = cnt * (last + 1 - i) / i;
	}
	return cnt;
}
Bezier::Bezier()
{
	memset(param, 0, sizeof param);
	cnt = 5, t = 0;
	for (int i = 0; i < cnt; ++i)
	{
		for (int j = 0; j < cnt; ++j)
		{
			bezier.points[i][j] = Point((i + 1) * 680 / (cnt + 1) - (j * 111) % 127, (j + 1) * 480 / (cnt + 1));
		}
	}
}
Point Bezier::bezierpoint(GLdouble t, GLint index)
{
	Point p(0, 0);
	for (int i = 0; i < cnt; ++i)
	{
		param[i] = pow((1 - t), cnt - i - 1)
			* pow(t, i)
			* calculate(i, cnt - 1);
	}
	for (int i = 0; i < cnt; ++i)
	{
		p.x += param[i] * points[index][i].x;
		p.y += param[i] * points[index][i].y;
	}
	return p;
}
Point Bezier::bezierpoint(GLdouble t, Point* points)
{
	Point p(0, 0);
	for (int i = 0; i < cnt; ++i)
	{
		param[i] = pow((1 - t), cnt - i - 1)
			* pow(t, i)
			* calculate(i, cnt - 1);
	}
	for (int i = 0; i < cnt; ++i)
	{
		p.x += param[i] * points[i].x;
		p.y += param[i] * points[i].y;
	}
	return p;
}
bool Bezier::hit(GLfloat point_x, GLfloat point_y)
{
	for (int i = 0; i < cnt; ++i)
	{
		for (int j = 0; j < cnt; ++j)
		{
			if (abs(point_x - points[i][j].x) <= POINT_SIZE / 2 + 3 && abs(point_y - points[i][j].y) <= POINT_SIZE / 2 + 3)
			{
				selectI = i, selectJ = j;
				return true;
			}
		}
	}
	return false;
}
void Bezier::setXY(GLint point_x, GLint point_y)
{
	points[selectI][selectJ].x = point_x;
	points[selectI][selectJ].y = point_y;
}
void Bezier::create(GLdouble temp)
{
	// 画出所有点和折线
	for (int i = 0; i < cnt; ++i){
		for (int j = 0; j < cnt - 1; ++j){
			glColor3ub(149, 219, 125);
			setLine(points[i][j], points[i][j + 1]);
			glColor3f(0.7f, 0.7f, 0.7f);
			setPoint(points[i][j]);
			setPoint(points[i][j + 1]);
		}
	}
	// 绘制贝塞尔曲线
	for (int i = 0; i < cnt; ++i){
		Point pLast = points[i][0];
		for (GLdouble j = 0.0; j <= 1.05; j += 0.05)
		{
			Point pNow = bezierpoint(j, i);
			glColor3ub(133, 192, 206);
			setLine(pLast, pNow);
			pLast = pNow;
		}
	}
	// 贝赛尔曲面绘制
	for (double f = 0.0; f <= temp; f += 0.003){
		Point ptemps[POINT_MAX];
		for (int i = 0; i < cnt; ++i)
		{
			ptemps[i] = bezierpoint(f, i);
		}
		Point pLast = ptemps[0];
		for (GLdouble j = 0.0; j <= 1.05; j += 0.05)
		{
			glLineWidth(3);
			Point pNow = bezierpoint(j, ptemps);
			glColor4ub(255, 214, 100, 0.2f);
			setLine(pLast, pNow);
			pLast = pNow;
		}
	}
	glFlush();
}
void Bezier::myAdd()
{
	if (cnt < POINT_MAX) ++cnt;
}
void Bezier::myDelete()
{
	if (cnt > 2) --cnt;
}