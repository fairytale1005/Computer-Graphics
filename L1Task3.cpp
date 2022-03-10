#include <GL/glut.h>
#include <math.h>
const GLfloat R = 0.25f;//圆环宽0.05f
const GLfloat r = 0.2f;
const GLfloat Pi = 3.1415926536f;
const int n = 3600;

void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//白色背景色

	glShadeModel(GL_FLAT); 
}




void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//清空帧缓存区
	glLoadIdentity();

	glTranslatef(0.0f, 0.25f, 0.0f);

		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);//黑色
		for (int i = 0; i <= n; i ++)
		{
			glVertex2f(r * sin(2 * Pi / n * i), r * cos(2 * Pi / n * i));
			glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));
			
		}
		glEnd();
	
	glTranslatef(0.55f, 0.0f, 0.0f);
		
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);//红色
		for (int i = 0; i <= n; i++)
		{
			glVertex2f(r * sin(2 * Pi / n * i), r * cos(2 * Pi / n * i));
			glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));

		}
		glEnd();

	glTranslatef(-1.1f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.5f, 0.8f);//蓝色
		for (int i = 0; i <= n; i++)
		{
			glVertex2f(r * sin(2 * Pi / n * i), r * cos(2 * Pi / n * i));
			glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));

		}
		glEnd();
	
	glTranslatef(0.275f, -0.25f, 0.0f);
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.8f, 0.0f);//黄色
		for (int i = 0; i <= n; i++)
		{
			glVertex2f(r * sin(2 * Pi / n * i), r * cos(2 * Pi / n * i));
			glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));

		}
		glEnd();

	glTranslatef(0.55f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glColor3f(0.1f, 0.6f, 0.0f);//绿色
		for (int i = 0; i <= n; i++)
		{
			glVertex2f(r * sin(2 * Pi / n * i), r * cos(2 * Pi / n * i));
			glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));

		}
		glEnd();
	
	glTranslatef(-0.275f, 0.25f, 0.0f);//填补黑色
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);//黑色
		for (int i = 900; i <= 1300; i++)
		{
			glVertex2f(r * sin(2 * Pi / n  * i), r * cos(2 * Pi / n * i));
			glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));

		}
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);//黑色
		for (int i = 1800; i <= 2200; i++)
		{
			glVertex2f(r * sin(2 * Pi / n * i), r * cos(2 * Pi / n * i));
			glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));

		}
		glEnd();

	glTranslatef(0.55f, 0.0f, 0.0f);

		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);//填补红色
		for (int i = 1800; i <= 2200; i++)
		{
			glVertex2f(r * sin(2 * Pi / n * i), r * cos(2 * Pi / n * i));
			glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));

		}
		glEnd();

	glTranslatef(-1.1f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.5f, 0.8f);//填补蓝色
		for (int i = 900; i <= 1300; i++)
		{
			glVertex2f(r * sin(2 * Pi / n * i), r * cos(2 * Pi / n * i));
			glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));

		}
		glEnd();


	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Task3");

	glutDisplayFunc(display);
	init();

	glutMainLoop();

}