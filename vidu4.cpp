//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <stdio.h>
namespace vidu4 {
// Ví dụ 4: Animation mô hình chuyển động qua lại trái phải
// 	   
// Thực hành 1: Mô hình di chuyển theo các cạnh hình chữ nhật
// Thực hành 2: Mô hình di chuyển theo hình tròn
// Thực hành 3: Mô hình di chuyển theo quỹ đạo bất kỳ

const int N_LINES = 13;
double model[N_LINES][2][3] = {
	{ { -0.8, 0.3, 0 },	{ -0.8, 0.7, 0 } },
	{ { -0.9, 0.7, 0 },	{ -0.7, 0.7, 0 } },
	{ { -0.6, 0.7, 0 },	{ -0.4, 0.7, 0 } },
	{ { -0.4, 0.7, 0 },	{ -0.4, 0.3, 0 } },
	{ { -0.4, 0.3, 0 },	{ -0.6, 0.3, 0 } },
	{ { -0.6, 0.3, 0 },	{ -0.6, 0.7, 0 } },
	{ { -0.3, 0.3, 0 },	{ -0.2, 0.7, 0 } },
	{ { -0.2, 0.7, 0 },	{ -0.1, 0.3, 0 } },
	{ { -0.25, 0.5, 0 }, { -0.15, 0.5, 0 } },
	{ { 0.0, 0.3, 0 },	{ 0.0, 0.7, 0 } },
	{ { 0.0, 0.7, 0 },	{ 0.2, 0.3, 0 } },
	{ { 0.2, 0.3, 0 },	{ 0.2, 0.7, 0 } },
	{ { -0.25, 0.85, 0 }, { -0.15, 0.8, 0.0 } }
};
double tx=0;	
bool bAuto = false;
int state= 0;


void render() {
	glColor3f(1.f, 1.f, 1.f);

	glPushMatrix();
	glTranslatef(tx, 0, 0);
	glBegin(GL_LINES);
	for (int i = 0; i < N_LINES; i++) {
		glVertex3f(model[i][0][0], model[i][0][1], model[i][0][2]);
		glVertex3f(model[i][1][0], model[i][1][1], model[i][1][2]);
	}
	glEnd();
	glPopMatrix();
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	render();
	glFlush();
}
void idle() {		
	if (bAuto) {
		double s=0.0003;
		// duong thang song song truc Ox
		if (state==0) {
			tx += s;
			if (tx>0.5) {
				state=1;
			}
		} else {
			tx -= s;
			if (tx<-0.5) {
				state=0;
			}
		}
	}

	glutPostRedisplay();
}
void processKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 'p':
		bAuto = !bAuto;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("vidu4");

	//	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(processKeys);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

};