//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <stdio.h>
namespace vidu3_1 {
// Ví dụ 3.1: Sử dụng sự kiện chuột và bàn phím: đổi màu và di chuyển
// 
// Thực hành 1: Xây dựng việc di chuyển trong 1 bản đồ, 
//   màn hình chỉ hiển thị 1 phần bản đồ.
// 

const int N_LINES = 4;
double model[N_LINES][2][3] = {
	{ { -0.2, 0.2, 0 },	{ -0.2, -0.2, 0 } },
	{ { -0.2, -0.2, 0 }, { 0.2, -0.2, 0 } },
	{ { 0.2, -0.2, 0 },	{ 0.2, 0.2, 0 } },
	{ { 0.2, 0.2, 0 },	{ -0.2, 0.2, 0 } } };

const int N_LINES1 = 13;
double model1[N_LINES1][2][3] = {
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
const int N_COLORS = 7;
double colors[N_COLORS][3] = {
	{0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0},
	{1.0, 0.0, 0.0},
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 0.0, 1.0 },
	{ 0.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0 }
};

int colorIdx = 0; // index màu
double tx = 0, ty = 0; // thay đổi tọa độ x, y sẽ vẽ

void render() {
	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_LINES);
	for (int i = 0; i < N_LINES1; i++) {
		glVertex3f(model1[i][0][0], model1[i][0][1], model1[i][0][2]);
		glVertex3f(model1[i][1][0], model1[i][1][1], model1[i][1][2]);
	}
	glEnd();

	glColor3f(colors[colorIdx][0],
		colors[colorIdx][1],
		colors[colorIdx][2]);
	glBegin(GL_LINES);
	for (int i = 0; i < N_LINES; i++) {
		glVertex3f(model[i][0][0] + tx, model[i][0][1] + ty, model[i][0][2]);
		glVertex3f(model[i][1][0] + tx, model[i][1][1] + ty, model[i][1][2]);
	}
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	render();
	glFlush();
}

void processKeys(unsigned char key, int x, int y) {
	switch (key) { // kiểm tra mã phím
	case 'a': //xử lý với từng trường hợp
		tx -= 0.1;
		break;
	case 'd':
		tx += 0.1;
		break;
	case 'w': //xử lý với từng trường hợp
		ty += 0.1;
		break;
	case 's':
		ty -= 0.1;
		break;
	default:
		break;
	}
	glutPostRedisplay(); // vẽ lại
}
// colorIdx cần phải trong phạm vi [0,1,..., N_COLORS-1]
void processMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		colorIdx = (colorIdx + 1) % N_COLORS;
		glutPostRedisplay();
	}
}
int main(int argc, char** argv) {
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("vidu3.1");

	glutDisplayFunc(display);
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouse);

	glutMainLoop();
	return 0;
}

}