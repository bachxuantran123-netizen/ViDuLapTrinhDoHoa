//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <stdio.h>
#include <malloc.h>
#include "linedmodel.h"

namespace vidu5 {
// Ví dụ 5: Tạo animation biến đổi giữa 2 mô hình
//     (sử dụng cấu trúc mô hình dạng cạnh)
//
// Thực hành 1: Cập nhật cho thực hành ví dụ 3.1

LinedModel model1, model2, model;

double alpha = 0;
double step = 0.0002;
void init() {
	model1.nVertices = 4;
	model1.vertices[0] = point3(-0.5, -0.5, 0);
	model1.vertices[1] = point3(-0.5, 0, 0);
	model1.vertices[2] = point3(-0.5, 0.5, 0);
	model1.vertices[3] = point3(0.5, -0.5, 0);

	model1.nEdges = 4;
	model1.edges[0][0] = 0;
	model1.edges[0][1] = 1;
	model1.edges[1][0] = 1;
	model1.edges[1][1] = 2;
	model1.edges[2][0] = 2;
	model1.edges[2][1] = 3;
	model1.edges[3][0] = 3;
	model1.edges[3][1] = 0;

	model2.nVertices = 4;
	model2.vertices[0] = point3(-0.5, -0.5, 0);
	model2.vertices[1] = point3(-0.5, 0.5, 0);
	model2.vertices[2] = point3(0.5, 0.5, 0);
	model2.vertices[3] = point3(0.5, -0.5, 0);
	model2.nEdges = 4;
	model2.edges[0][0] = 0;
	model2.edges[0][1] = 1;
	model2.edges[1][0] = 1;
	model2.edges[1][1] = 2;
	model2.edges[2][0] = 2;
	model2.edges[2][1] = 3;
	model2.edges[3][0] = 3;
	model2.edges[3][1] = 0;

	model.nVertices = 4;
	model.vertices[0] = point3(-0.5, -0.5, 0);
	model.vertices[1] = point3(-0.5, 0.5, 0);
	model.vertices[2] = point3(0.5, 0.5, 0);
	model.vertices[3] = point3(0.5, -0.5, 0);
	model.nEdges = 4;
	model.edges[0][0] = 0;
	model.edges[0][1] = 1;
	model.edges[1][0] = 1;
	model.edges[1][1] = 2;
	model.edges[2][0] = 2;
	model.edges[2][1] = 3;
	model.edges[3][0] = 3;
	model.edges[3][1] = 0;
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void render() {
	glColor3f(0.0, 0.0, 0.0);
	drawLinedModel(&model);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	render();

	glFlush();
}
void idle() {
	for (int i=0; i<model.nVertices; i++) {
		model.vertices[i].x = alpha*model1.vertices[i].x+(1-alpha)*model2.vertices[i].x;
		model.vertices[i].y = alpha*model1.vertices[i].y+(1-alpha)*model2.vertices[i].y;
		model.vertices[i].z = alpha*model1.vertices[i].z+(1-alpha)*model2.vertices[i].z;
	}
	alpha += step;
	if (alpha>1) {
		alpha = 1;
		step = -step;
	} else if (alpha<0){
		alpha=0;
		step=-step;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("vidu5");

	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}

};