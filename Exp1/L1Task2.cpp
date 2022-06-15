#include <GL/glut.h>
#include <math.h>

const GLfloat Pi = 3.1415926536f;
const GLfloat R = 0.5f;
const int n = 70;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);//����ɫ
	glShadeModel(GL_FLAT); //GL_FLAT�������һ���������ɫʹ�õ�һ��ɫ GL_SMOOTH�����ֵ

	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//���֡������
	
	
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
	//��ʼ��GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//������ʾģʽ
	glutInitWindowSize(500, 500);//��������
	glutInitWindowPosition(0, 0);//0,0����Ļ���Ͻǵ�λ��
	glutCreateWindow("Task2");//��������


	init();
	glutDisplayFunc(display);//��ʾ�ص�����
	

	glutMainLoop();	//���ô˺���֮ǰ���ڲ�����ʾ
}