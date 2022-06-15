#include <GL/glut.h>
#include <math.h>

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	float R = 1;
	float Pi = 3.1415926;
	glTranslatef(0.0f, 0.0f, -6.0f);
	for (float i = 0; i <= 2 * Pi; i += Pi / 100)
	{
		glBegin(GL_TRIANGLES);
		if (i <= 2 * Pi / 5)glColor3f(1.0f, 1.0f, 0.0f);//ÉÏÉ«
		else if (i <= 4 * Pi / 5)glColor3f(0.0f, 1.0f, 0.0f);
		else if (i <= 6 * Pi / 5)glColor3f(1.0f, 1.0f, 1.0f);
		else if (i <= 8 * Pi / 5)glColor3f(0.0f, 0.0f, 1.0f);
		else glColor3f(255, 0.0, 0.0);
		glVertex3f(0.0f, 0.0f, 0.0f);//»æÖÆÔ²
		glVertex3f(R*cos(i), R*sin(i), 0.0f);
		glVertex3f(R*cos(i+Pi/100), R*sin(i+Pi/100), 0.0f);
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