#include <glut.h>
#include <stdio.h>
#include <math.h> // Thêm thư viện math để tính sin, cos cho quỹ đạo tròn

namespace vidu4 {
	// Ví dụ 4: Animation mô hình chuyển động qua lại trái phải
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

	double tx = 0;
	double ty = 0;    // Thêm biến ty cho trục Y
	double angle = 0; // Biến góc để chạy quỹ đạo tròn/bất kỳ
	bool bAuto = false;
	int state = 0;
	int mode = 1;     // 0: Trái-Phải, 1: Chữ nhật, 2: Tròn, 3: Quỹ đạo số 8

	void render() {
		glColor3f(1.f, 1.f, 1.f);

		glPushMatrix();
		glTranslatef(tx, ty, 0); // Đưa biến ty vào để mô hình dịch chuyển được theo cả trục X và Y
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
			double s = 0.0003;

			if (mode == 0) {
				// Ví dụ ban đầu: Chuyển động qua lại trái phải trên trục Ox
				if (state == 0) {
					tx += s; if (tx > 0.5) state = 1;
				}
				else {
					tx -= s; if (tx < -0.5) state = 0;
				}
			}
			else if (mode == 1) {
				// THỰC HÀNH 1: Di chuyển theo các cạnh hình chữ nhật
				if (state == 0) {        // Đi sang phải
					tx += s; if (tx > 0.5) { tx = 0.5; state = 1; }
				}
				else if (state == 1) { // Đi lên trên
					ty += s; if (ty > 0.5) { ty = 0.5; state = 2; }
				}
				else if (state == 2) { // Đi sang trái
					tx -= s; if (tx < -0.5) { tx = -0.5; state = 3; }
				}
				else if (state == 3) { // Đi xuống dưới
					ty -= s; if (ty < -0.5) { ty = -0.5; state = 0; }
				}
			}
			else if (mode == 2) {
				// THỰC HÀNH 2: Di chuyển theo hình tròn
				double speed = s * 5; // Tính vận tốc góc
				angle += speed;
				if (angle > 2 * 3.14159) angle -= 2 * 3.14159;
				// Tính x, y trên đường tròn bán kính 0.5
				tx = 0.5 * cos(angle);
				ty = 0.5 * sin(angle);
			}
			else if (mode == 3) {
				// THỰC HÀNH 3: Di chuyển theo quỹ đạo bất kỳ (Quỹ đạo hình số 8 vô cực)
				double speed = s * 5;
				angle += speed;
				if (angle > 2 * 3.14159) angle -= 2 * 3.14159;
				tx = 0.5 * sin(angle);
				ty = 0.3 * sin(angle * 2); // Hệ số * 2 tạo ra hình số 8
			}
		}

		glutPostRedisplay();
	}

	void processKeys(unsigned char key, int x, int y) {
		switch (key) {
		case 'p':
		case 'P':
			bAuto = !bAuto;
			break;
		case '0':
			mode = 0; tx = 0; ty = 0; state = 0;
			break;
		case '1':
			mode = 1; tx = -0.5; ty = -0.5; state = 0;
			break;
		case '2':
			mode = 2; angle = 0;
			break;
		case '3':
			mode = 3; angle = 0;
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}

	int main(int argc, char** argv) {
		glutInitWindowSize(600, 600); // Tăng kích thước cửa sổ để dễ quan sát quỹ đạo
		glutInitWindowPosition(50, 50);
		glutCreateWindow("Thuc Hanh Animation - Vidu 4");

		glutDisplayFunc(display);
		glutKeyboardFunc(processKeys);
		glutIdleFunc(idle); // Đăng ký hàm idle để vẽ chuyển động liên tục
		glutMainLoop();
		return 0;
	}

};