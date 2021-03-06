#define NDEBUG
#include <GL/glut.h>

GLfloat r = 1.0f, g = 0.0f, b = 1.0f;
GLfloat random = 1.0f;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
}

void display(void)

{
	/* A triangle */
	GLfloat vertices[3][2] = { {-1.0,-1.0},{1.0,-1.0},{0.0,1.0} };

	int j, k;
	GLfloat p[2] = { 0.0,0.0 };  /* an arbitrary initial point inside
							  traingle */
	glClear(GL_COLOR_BUFFER_BIT);  /* clear the window */
	glBegin(GL_POINTS);
	/* compute and plots 5000 new points */
	for (k = 0; k < 5000; k++)
	{
		j = rand() % 3; /* pick a vertex at random */
		/* Compute point halfway between selected vertex and old point */
		p[0] = (p[0] + vertices[j][0]) / 2.0;
		p[1] = (p[1] + vertices[j][1]) / 2.0;

		/* plot new point */
		glVertex2fv(p);
	}
	glEnd();
	glFlush(); /* clear buffers */
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void idlefunc()
{
	//改变动画参数
	r = rand() % 100 / 100.0;
	g = rand() % 100 / 100.0;
	b = rand() % 100 / 100.0;//获得100内随机数
	glColor3f(r, g, b);
	glRotated(60, 0, 0, 1);
	random = rand() % 10 / 10.0;
	if (rand() % 10 % 2 == 0) random = -random;
	glScaled( 1 + random, 1 + random, 1);
	Sleep(1000);
	glutPostRedisplay();
	

}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
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
	glutIdleFunc(idlefunc);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}