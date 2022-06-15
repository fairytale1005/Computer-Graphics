#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif

void display(void)

{
	/* clear window */

	glClear(GL_COLOR_BUFFER_BIT);//清空帧缓存区


	/* draw unit square polygon */

	glBegin(GL_POLYGON);//图元定义 GL_POINTS GL_LINES GL_POLYGON

	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);


	glEnd();//结束顶点序列

	/* flush GL buffers */

	glFlush();//强制执行OpenGL命令

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
	glShadeModel(GL_SMOOTH); //GL_FLAT根据最后一个顶点的颜色使用单一颜色 GL_SMOOTH顶点差值
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{

	/* Initialize mode and open a window in upper left corner of screen */
	/* Window title is name of program (arg[0]) */

	glutInit(&argc, argv);
	//初始化GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);//窗口属性
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");//创建窗口 标题为"simple"

	glutDisplayFunc(display);//设置回调函数，窗口需要重绘时调用func

	init();//设置初始状态
	glutMainLoop();//进入消息循环，main最后一条语句

}