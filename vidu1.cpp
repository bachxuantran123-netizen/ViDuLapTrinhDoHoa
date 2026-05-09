//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <math.h>

namespace vidu1 {
// Ví dụ 1: Vẽ các đoạn thẳng
// 	   
// Thực hành 1: Sửa đổi ví dụ để vẽ họ tên mình sử dụng các đoạn thẳng
// Thực hành 2: Vẽ ngôi sao năm cánh sử dụng các đoạn thẳng

void display() {
	// gán màu (r, g, b) => xanh lá cây
	glColor3f(0.0, 1.0, 0.0);
	// bắt đầu chế độ vẽ các đường thẳng
	glBegin(GL_LINES);	
	// T
	glVertex3f(-0.8, 0.3, 0.0);
	glVertex3f(-0.8, 0.7, 0.0);
	if (0) {
		glVertex3f(-0.9, 0.7, 0.0);
		glVertex3f(-0.7, 0.7, 0.0);

		// O
		glVertex3f(-0.6, 0.7, 0.0);
		glVertex3f(-0.4, 0.7, 0.0);

		glVertex3f(-0.4, 0.7, 0.0);
		glVertex3f(-0.4, 0.3, 0.0);

		glVertex3f(-0.4, 0.3, 0.0);
		glVertex3f(-0.6, 0.3, 0.0);

		glVertex3f(-0.6, 0.3, 0.0);
		glVertex3f(-0.6, 0.7, 0.0);

		// A
		glVertex3f(-0.3, 0.3, 0.0);
		glVertex3f(-0.2, 0.7, 0.0);

		glVertex3f(-0.2, 0.7, 0.0);
		glVertex3f(-0.1, 0.3, 0.0);

		glVertex3f(-0.25, 0.5, 0.0);
		glVertex3f(-0.15, 0.5, 0.0);

		// N
		glVertex3f(0.0, 0.3, 0.0);
		glVertex3f(0.0, 0.7, 0.0);

		glVertex3f(0.0, 0.7, 0.0);
		glVertex3f(0.2, 0.3, 0.0);

		glVertex3f(0.2, 0.3, 0.0);
		glVertex3f(0.2, 0.7, 0.0);

		// dau huyen
		glVertex3f(-0.25, 0.85, 0.0);
		glVertex3f(-0.15, 0.8, 0.0);
	}
	// Kết thúc chế độ vẽ
	glEnd(); // 
	// đẩy bộ nhớ vẽ ra
	glFlush();
}
int main(int argc, char** argv) {
	// Khởi tạo cửa sổ
	glutInitWindowSize(250, 250); // kích thước
	glutInitWindowPosition(50, 50); // vị trí trên destop
	glutCreateWindow("vidu1"); // caption 
	// 
	glutDisplayFunc(display); // đăng ký hàm callback hiển thị

	glutMainLoop(); // vòng lặp chính
	return 0;
}

}
