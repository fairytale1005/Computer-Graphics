#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif

void display(void)

{
	/* clear window */

	glClear(GL_COLOR_BUFFER_BIT);//���֡������


	/* draw unit square polygon */

	glBegin(GL_POLYGON);//ͼԪ���� GL_POINTS GL_LINES GL_POLYGON

	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);


	glEnd();//������������

	/* flush GL buffers */

	glFlush();//ǿ��ִ��OpenGL����

}


void init()
{

	/* set clear color to black */

	glClearColor(0.0, 0.5, 0.5, 0.5);
	/* set fill  color to white */

	glColor3f(0.1, 0.2, 0.4);

	/* set up standard orthogonal view with clipping */
	/* box as cube of side 2 centered at origin */
	/* This is default view and these statement could be removed */
	glShadeModel(GL_SMOOTH); //GL_FLAT�������һ���������ɫʹ�õ�һ��ɫ GL_SMOOTH�����ֵ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{

	/* Initialize mode and open a window in upper left corner of screen */
	/* Window title is name of program (arg[0]) */

	glutInit(&argc, argv);
	//��ʼ��GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);//��������
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");//�������� ����Ϊ"simple"

	glutDisplayFunc(display);//���ûص�������������Ҫ�ػ�ʱ����func

	init();//���ó�ʼ״̬
	glutMainLoop();//������Ϣѭ����main���һ�����

}