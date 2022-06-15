#include "GL/glut.h"
#include <math.h>
#include <iostream>
#define POINT_MAX 10
#define TIMESLEEP 30
struct Point
{
	GLdouble x, y, z;
	Point();
	Point(GLdouble, GLdouble);
	Point(GLdouble, GLdouble, GLdouble);
};

static void		setPoint(Point);			// 画出一个点
static void		setLine(Point, Point);		// 画出两点间的线

static GLdouble	t = 0;
class Bezier								// Bezier类，封装Bezier曲线的所需函数
{
public:
	Bezier();
	Point		bezierpoint(GLdouble);		// 计算Bezier点
	bool		addPoint(Point);			// 增加一个控制点
	void		deletPoint();				// 删除上一个控制点
	void		create(GLdouble);				// 画出Bezier曲线
	Point		lastpoint(void);			// 返回上一个控制点（用于显示）
private:
	Point		points[POINT_MAX];			// 存储控制点
	GLdouble	param[POINT_MAX];			// 存储Bezier计算参数
	GLint		cnt;						// 控制点的数量
};

static Bezier bezier = Bezier();

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0);
	glPointSize(10.0);
	glLineWidth(6.0);
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		if (bezier.addPoint(Point(x, glutGet(GLUT_WINDOW_HEIGHT) - y))) t = 0;
		glColor3b(242, 82, 20);
		setPoint(bezier.lastpoint());
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		t = 0;
		bezier.deletPoint();
		glColor3f(0.25f, 0.70f, 0.94f);
		setPoint(bezier.lastpoint());
	}
}

void idleFuc()
{
	t += 0.03;
	if (t > 1.003) t = 0.0;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(600, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bezier Curve");
	init();
	glutMouseFunc(mouseFuc);
	glutDisplayFunc(display);
	glutIdleFunc(idleFuc);
	glutMainLoop();
	return 0;
}
Point::Point()
{
	x = 0, y = 0, z = 0;
}
Point::Point(GLdouble x0, GLdouble y0)
{
	x = x0, y = y0, z = 0;
}
Point::Point(GLdouble x0, GLdouble y0, GLdouble z0)
{
	x = x0, y = y0, z = z0;
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
	//glFlush();
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
	cnt = 0, t = 0;
}
Point Bezier::bezierpoint(GLdouble t)
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
bool Bezier::addPoint(Point p)
{
	if (cnt >= POINT_MAX) return false;
	points[cnt++] = p;
	return true;
}
void Bezier::create(GLdouble temp)
{
	if (cnt == 1)
	{
		glColor3f(0.25f, 0.70f, 0.94f);
		setPoint(points[0]);
	}
	for (int i = 0; i < cnt - 1; ++i)
	{
		glColor3f(0.8, 0.8, 0.8);
		setLine(points[i], points[i + 1]);
		glColor3f(0.25f, 0.70f, 0.94f);
		setPoint(points[i]);
		setPoint(points[i + 1]);
	}
	glFlush();
	// 绘制贝塞尔曲线
	if (cnt < 2) return;
	Point pTemp[POINT_MAX][POINT_MAX];
	for (int i = 0; i < cnt - 2; ++i)
	{
		pTemp[0][i].x = points[i].x * (1 - temp) + points[i + 1].x * temp;
		pTemp[0][i].y = points[i].y * (1 - temp) + points[i + 1].y * temp;
		pTemp[0][i + 1].x = points[i + 1].x * (1 - temp) + points[i + 2].x * temp;
		pTemp[0][i + 1].y = points[i + 1].y * (1 - temp) + points[i + 2].y * temp;
		glColor3f(0.4f, 0.85f, 0.7f);
		setLine(pTemp[0][i], pTemp[0][i + 1]);
		glColor3f(0.1f, 0.8f, 0.4f);
		setPoint(pTemp[0][i]); setPoint(pTemp[0][i + 1]);
	}
	for (int idx = 1; idx < cnt - 1; ++idx)
	{
		for (int i = 0; i < cnt - 2 - idx; ++i)
		{
			pTemp[idx][i].x = pTemp[idx - 1][i].x * (1 - temp) + pTemp[idx - 1][i + 1].x * temp;
			pTemp[idx][i].y = pTemp[idx - 1][i].y * (1 - temp) + pTemp[idx - 1][i + 1].y * temp;
			pTemp[idx][i + 1].x = pTemp[idx - 1][i + 1].x * (1 - temp) + pTemp[idx - 1][i + 2].x * temp;
			pTemp[idx][i + 1].y = pTemp[idx - 1][i + 1].y * (1 - temp) + pTemp[idx - 1][i + 2].y * temp;
			glColor3f((idx * 245 % 255 / 255.f), (idx * 165 % 255 / 255.f), (idx * 105 % 255 / 255.f));
			setLine(pTemp[idx][i], pTemp[idx][i + 1]);
			glColor3f(0.1f, 0.8f, 0.4f);
			setPoint(pTemp[idx][i]); setPoint(pTemp[idx][i + 1]);
		}
	}
	Point pLast = points[0];
	for (GLdouble j = 0.0; j <= temp; j += 0.05)
	{
		Point pNow = bezierpoint(j);
		glColor3f(1.0f, 0.0f, 0.0f);
		setLine(pLast, pNow);
		pLast = pNow;
	}
	glFlush();
}
Point Bezier::lastpoint(void)
{
	return points[cnt - 1];
}
void Bezier::deletPoint(void)
{
	if (cnt <= 0) return;
	--cnt;
	points[cnt].x = 0, points[cnt].y = 0;
}