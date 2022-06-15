#include <GL/glut.h>
#include <math.h>

void init()
{
	glClearColor(0.0, 0.0, 255, 0.0);
	glShadeModel(GL_FLAT);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	float R = 1.2, r = 1;
	float Pi = 3.1415926;
	glTranslatef(0.0, 0.0, -10.0f);

	glTranslatef(-2.75, 0.5, 0.0);//绘制五个圆环
	glColor3f(0.0, 0.42, 0.69);
	for (float i = 0; i < 2 * Pi; i += Pi / 100)
	{
		glBegin(GL_POLYGON);
		glVertex3f(r * cos(i), r * sin(i), 0.0);
		glVertex3f(r * cos(i + 2 * Pi / 100), r * sin(i + 2 * Pi / 100), 0.0);
		glVertex3f(R * cos(i), R * sin(i), 0.0);
		glVertex3f(R * cos(i + 2 * Pi / 100), R * sin(i + 2 * Pi / 100), 0.0);
		glEnd();
	}

	glTranslatef(2.75, 0.0, 0.0);
	glColor3f(0.114, 0.094, 0.0824);
	for (float i = 0; i < 2 * Pi; i += Pi / 100)
	{
		glBegin(GL_POLYGON);
		glVertex3f(r * cos(i), r * sin(i), 0.0);
		glVertex3f(r * cos(i + 2 * Pi / 100), r * sin(i + 2 * Pi / 100), 0.0);
		glVertex3f(R * cos(i), R * sin(i), 0.0);
		glVertex3f(R * cos(i + 2 * Pi / 100), R * sin(i + 2 * Pi / 100), 0.0);
		glEnd();
	}

	glTranslatef(2.75, 0.0, 0.0);
	glColor3f(0.863, 0.184, 0.122);
	for (float i = 0; i < 2 * Pi; i += Pi / 100)
	{
		glBegin(GL_POLYGON);
		glVertex3f(r * cos(i), r * sin(i), 0.0);
		glVertex3f(r * cos(i + 2 * Pi / 100), r * sin(i + 2 * Pi / 100), 0.0);
		glVertex3f(R * cos(i), R * sin(i), 0.0);
		glVertex3f(R * cos(i + 2 * Pi / 100), R * sin(i + 2 * Pi / 100), 0.0);
		glEnd();
	}

	glTranslatef(-4.125, -1, 0.0);
	glColor3f(0.937, 0.663, 0.051);
	for (float i = 0; i < 2 * Pi; i += Pi / 100)
	{
		glBegin(GL_POLYGON);
		glVertex3f(r * cos(i), r * sin(i), 0.0);
		glVertex3f(r * cos(i + 2 * Pi / 100), r * sin(i + 2 * Pi / 100), 0.0);
		glVertex3f(R * cos(i), R * sin(i), 0.0);
		glVertex3f(R * cos(i + 2 * Pi / 100), R * sin(i + 2 * Pi / 100), 0.0);
		glEnd();
	}

	glTranslatef(2.75, 0.0, 0.0);
	glColor3f(0.0196, 0.576, 0.255);
	for (float i = 0; i < 2 * Pi; i += Pi / 100)
	{
		glBegin(GL_POLYGON);
		glVertex3f(r * cos(i), r * sin(i), 0.0);
		glVertex3f(r * cos(i + 2 * Pi / 100), r * sin(i + 2 * Pi / 100), 0.0);
		glVertex3f(R * cos(i), R * sin(i), 0.0);
		glVertex3f(R * cos(i + 2 * Pi / 100), R * sin(i + 2 * Pi / 100), 0.0);
		glEnd();
	}

	glTranslatef(-4.125, 1, 0.0);
	glColor3f(0.0, 0.42, 0.69);//重新绘制重叠部分
	for (float i = 14 * Pi / 8; i < 2 * Pi + Pi / 4; i += Pi / 100)
	{
		glBegin(GL_POLYGON);
		glVertex3f(r * cos(i), r * sin(i), 0.0);
		glVertex3f(r * cos(i + 2 * Pi / 100), r * sin(i + 2 * Pi / 100), 0.0);
		glVertex3f(R * cos(i), R * sin(i), 0.0);
		glVertex3f(R * cos(i + 2 * Pi / 100), R * sin(i + 2 * Pi / 100), 0.0);
		glEnd();
	}

	glTranslatef(2.75, 0.0, 0.0);
	glColor3f(0.114, 0.094, 0.0824);
	for (float i = 14 * Pi / 8; i < 2 * Pi + Pi / 4; i += Pi / 100)
	{
		glBegin(GL_POLYGON);
		glVertex3f(r * cos(i), r * sin(i), 0.0);
		glVertex3f(r * cos(i + 2 * Pi / 100), r * sin(i + 2 * Pi / 100), 0.0);
		glVertex3f(R * cos(i), R * sin(i), 0.0);
		glVertex3f(R * cos(i + 2 * Pi / 100), R * sin(i + 2 * Pi / 100), 0.0);
		glEnd();
	}
	for (float i = 10 * Pi / 8; i < 12 * Pi / 8; i += Pi / 100)
	{
		glBegin(GL_POLYGON);
		glVertex3f(r * cos(i), r * sin(i), 0.0);
		glVertex3f(r * cos(i + 2 * Pi / 100), r * sin(i + 2 * Pi / 100), 0.0);
		glVertex3f(R * cos(i), R * sin(i), 0.0);
		glVertex3f(R * cos(i + 2 * Pi / 100), R * sin(i + 2 * Pi / 100), 0.0);
		glEnd();
	}

	glTranslatef(2.75, 0.0, 0.0);
	glColor3f(0.863, 0.184, 0.122);
	for (float i = 10 * Pi / 8; i < 12 * Pi / 8; i += Pi / 100)
	{
		glBegin(GL_POLYGON);
		glVertex3f(r * cos(i), r * sin(i), 0.0);
		glVertex3f(r * cos(i + 2 * Pi / 100), r * sin(i + 2 * Pi / 100), 0.0);
		glVertex3f(R * cos(i), R * sin(i), 0.0);
		glVertex3f(R * cos(i + 2 * Pi / 100), R * sin(i + 2 * Pi / 100), 0.0);
		glEnd();
	}

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}