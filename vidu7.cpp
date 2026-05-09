//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "linedmodel.h"

namespace vidu7 {
// Ví dụ 7: Thay đổi thông tin camera
// 	   
// Thực hành 1: Dùng phím để thay đổi góc nhìn theo các trục x, y, z
// 	   với phép chiếu vuông góc tương tự góc nhìn bản vẽ kỹ thuật
// Thực hành 2: Dùng phím để thay đổi góc nhìn theo tọa độ cầu
// 	   (camera di chuyển trên 1 mặt cầu quanh vật thể với phép chiếu phối cảnh)
//
LinedModel model1;

float x = 0.0f, z = 15.0f;

void init() {
	model1.nVertices = 8;
	model1.vertices[0] = point3(-0.5, -0.5, -0.5);
	model1.vertices[1] = point3(0.5, -0.5, -0.5);
	model1.vertices[2] = point3(0.5, 0.5, -0.5);
	model1.vertices[3] = point3(-0.5, 0.5, -0.5);
	model1.vertices[4] = point3(-0.5, -0.5, 0.5);
	model1.vertices[5] = point3(0.5, -0.5, 0.5);
	model1.vertices[6] = point3(0.5, 0.5, 0.5);
	model1.vertices[7] = point3(-0.5, 0.5, 0.5);

	model1.nEdges = 12;
	model1.edges[0][0] = 0; model1.edges[0][1] = 1;
	model1.edges[1][0] = 1; model1.edges[1][1] = 2;
	model1.edges[2][0] = 2; model1.edges[2][1] = 3;
	model1.edges[3][0] = 3; model1.edges[3][1] = 0;
	model1.edges[4][0] = 4; model1.edges[4][1] = 5;
	model1.edges[5][0] = 5; model1.edges[5][1] = 6;
	model1.edges[6][0] = 6; model1.edges[6][1] = 7;
	model1.edges[7][0] = 7; model1.edges[7][1] = 4;
	model1.edges[8][0] = 0; model1.edges[8][1] = 4;
	model1.edges[9][0] = 1; model1.edges[9][1] = 5;
	model1.edges[10][0] = 2; model1.edges[10][1] = 6;
	model1.edges[11][0] = 3; model1.edges[11][1] = 7;

	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void render() {
	glColor3f(0.0, 0.0, 0.0);
	drawLinedModel(&model1);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x, 0.0f, z,
		0, 0.0f, 0,
		0.0f, 1.0f, 0.0f);

	render();

	glFlush();
}
void processKeys(unsigned char key, int xx, int yy) {
	switch (key) {
	case 'w':
		z += 0.5;
		break;
	case 's':
		z -= 0.5;
		break;
	case 'a':
		x -= 0.5;
		break;
	case 'd':
		x += 0.5;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void changeSize(int w, int h) {
	if (h == 0) h = 1;
	float ratio = w * 1.0 / h;
	// su dung ma tran phep chieu
	glMatrixMode(GL_PROJECTION);
	// Cap nhat ve ma tran don vi
	glLoadIdentity();
	// Thiet lap viewport
	glViewport(0, 0, w, h);
	// thiet lap phep chieu
	gluPerspective(10.0f, ratio, 0.1f, 100.0f);
	//glOrtho(-100.f, 100.f, -100.f, 100.f, -100.f, 100.f);
	// quay lai ma tran model view
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv) {
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("vidu7");

	init();
	glutReshapeFunc(changeSize);
	glutDisplayFunc(display);
	glutKeyboardFunc(processKeys);
	glutMainLoop();

	return 0;
}

};