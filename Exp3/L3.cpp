#define NDEBUG
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Model {
public:
	//���ڼ�¼ģ�͵���������
	float center_x;
	float center_y;
	float center_z;
private:
	int vertices, faces;
	vector<float *> ver;//����λ��
	vector<int *> face;//��
	vector<float*> nor;//������
public :
	Model() {
		vertices = 37702;
		faces = 75404;
		center_x = 0;
		center_y = 0;
		center_z = 0;
	}

 
	void fileIO(const char* filename) {
		string line;
		vector<string> lines;

		ifstream in(filename);
		if (!in.is_open()) {
			printf_s("Cannot load model %s\n", filename);
			return;
		}
		for (int i = 0; i < 13; i++) {//����ǰ13��
			getline(in, line);
		}//����ͷ��

		while (!in.eof()) {
			getline(in, line);
			lines.push_back(line);
		}

		int a, b, c;
		float x, y, z, nx, ny, nz;
		for (string& line : lines) {
			if (line[0] == '3' && line[1] == ' ') { //�������������ж�(һ����������)
				sscanf_s(line.c_str(), "3 %d %d %d", &a, &b, &c);
				face.push_back(new int[3]{ a, b, c });
			}
			else
			{
				sscanf_s(line.c_str(), "%f %f %f %f %f %f", & x, & y, & z, & nx, & ny, & nz);
				nor.push_back(new float[3]{ nx, ny, nz });
				ver.push_back(new float[3]{ x, y, z });
				center_x += x;
				center_y += y;
				center_z += z;
			}
			
		}
		center_x /= vertices;
		center_y /= vertices;
		center_z /= vertices;
		in.close();
	}
	void draw() {

		glBegin(GL_TRIANGLES);
			for (int i = 0; i < faces; i++) {
				glNormal3fv(nor[face[i][0]]);
				glNormal3fv(nor[face[i][1]]);
				glNormal3fv(nor[face[i][2]]);
				glVertex3fv(ver[face[i][0]]);
				glVertex3fv(ver[face[i][1]]);
				glVertex3fv(ver[face[i][2]]);		
			}	
		glEnd();
	}
	
};

Model model;

void init(void)
{
	model.fileIO("lizhenxiout.ply");
	glShadeModel(GL_FLAT);

	//���ù��ռ���
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//������Ȼ�����
	glEnable(GL_DEPTH_TEST);
	//��������
	glEnable(GL_NORMALIZE);

	//��������������ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1500, 1500, -1500, 1500, -1500, 1500);

	//�����������������������Է�λ
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(100, -300, 100, model.center_x, model.center_y, model.center_z, 0.0, 1.0, 0.0);
	GLfloat light_pos[] = { 50.0, -10.0, 20.0 , 0};

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

}

void display(void)

{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  /* clear the window */
	glLoadIdentity();
	model.draw();
	glEnd();
	glutSwapBuffers(); /* clear buffers */
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}


void idlefunc()
{
	glRotated(60, 0, 0, 1);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Task1");
	init();
	glutDisplayFunc(display);
	/*glutReshapeFunc(reshape);*/
	glutIdleFunc(idlefunc);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
