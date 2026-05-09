//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <stdio.h>
namespace vidu2 {
// Ví dụ 2: 
// - Chỉnh sửa ví dụ 1 để tách thao tác vẽ với dữ liệu mô hình
// 	 Sử dụng mảng để lưu mô hình là các cạnh cần vẽ
// 	 Thứ tự các chiều model[số cạnh][số đỉnh 1 cạnh][số tọa độ 1 đỉnh]
//	 => model[số cạnh][2][3]
// 
// Thực hành 1: Đọc dữ liệu mô hình từ 1 file text, ví dụ như sau:
// 	   Dòng 1: Số cạnh, ví dụ N
// 	   N dòng tiếp theo, mỗi dòng là x1 y1 z1 x2 y2 z2
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
void render() {
	glBegin(GL_LINES);
	for (int i = 0; i < N_LINES; i++) {
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
int main(int argc, char** argv) {
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("vidu2");

	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}

}