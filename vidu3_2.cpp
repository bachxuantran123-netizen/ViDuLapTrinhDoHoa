//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <stdio.h>
namespace vidu3_2 {
// Ví dụ 3.2: Sử dụng sự kiện chuột: thay đổi mô hình bằng thêm, bớt từng cạnh
// 
// Thực hành 1: Xây dựng 1 ví dụ gõ text đơn giản với một số ký tự cơ bản 
// 

const int N_LINES = 13;
double model[N_LINES][2][3] ={
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
int pos = 0;

void render() {
	glBegin(GL_LINES);
	for (int i = 0; i <= pos; i++) {
		glVertex3f(model[i][0][0], model[i][0][1], model[i][0][2]);
		glVertex3f(model[i][1][0], model[i][1][1], model[i][1][2]);
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
		pos -= 1;
		if (pos < 0) pos = 0;
		break;
	case 'd':
		pos += 1;
		if (pos >= N_LINES) pos = N_LINES-1;

		break;
	default:
		break;
	}
	glutPostRedisplay(); // vẽ lại
}
int main(int argc, char** argv) {
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("vidu3.2");

	glutDisplayFunc(display);
	glutKeyboardFunc(processKeys);

	glutMainLoop();
	return 0;
}

}
