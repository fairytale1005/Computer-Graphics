#include <GL/glut.h>
#include <math.h>

const GLfloat Pi = 3.1415926536f;
const GLfloat R = 0.5f;
const int n = 70;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);//背景色
	glShadeModel(GL_FLAT); //GL_FLAT根据最后一个顶点的颜色使用单一颜色 GL_SMOOTH顶点差值

	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//清空帧缓存区
	
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0, 0);
	for (int i = 0; i < 10; i++)
		glVertex2f(R * sin(2 * Pi / n * i),R * cos(2 * Pi / n * i) );
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0, 0);
	for (int i = 9; i < 20; i++)
		glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0, 0);
	for (int i = 19; i < 30; i++)
		glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.8);
	glVertex2f(0, 0);
	for (int i = 29; i < 40; i++)
		glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 1);
	glVertex2f(0, 0);
	for (int i = 39; i < 50; i++)
		glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0.8, 0);
	glVertex2f(0, 0);
	for (int i = 49; i < 60; i++)
		glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,1.0, 1);
	glVertex2f(0, 0);
	for (int i = 59; i <= 70; i++)
		glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));
	glEnd();
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//初始化GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//窗口显示模式
	glutInitWindowSize(500, 500);//窗口属性
	glutInitWindowPosition(0, 0);//0,0是屏幕左上角的位置
	glutCreateWindow("Task2");//创建窗口


	init();
	glutDisplayFunc(display);//显示回调函数
	

	glutMainLoop();	//调用此函数之前窗口不会显示
}