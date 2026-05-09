//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <stdio.h>
#include <malloc.h>
#include "linedmodel.h"

namespace vidu6 {
// Ví dụ 6: Vẽ đa giác đều
// 	   
// Thực hành 1: Vẽ mô hình mặt trời với tâm là một hình tròn và
//		các tia nắng là các tam giác đều quay quanh
// Thực hành 2: Vẽ đồng hồ 
// Thực hành 3: Tham khảo lại ví dụ 3.3 để dùng chuột vẽ vài đa giác cơ bản 
//		(như trong MS Paint).

Vector3 trans;
LinedModel model;
int nPoints = 3;
double angle =0;
bool rotate = false;

void init() {
	trans.x = 0;
	trans.y = 0;
	trans.z = 0;

	nPoints = 6;
	angle = 0;

	//regularPolygon(&model, 0.5, nPoints);
	regularPolygon(&model, nPoints, 0.5, 0);

	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void render() {
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(trans.x, trans.y, trans.z);
	drawLinedModel(&model);
	glPopMatrix();
	
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	render();
	glFlush();
}
void idle() {
	if (rotate) {
		angle = angle + 0.0005;
	}
	regularPolygon1(&model, 0.5, nPoints, angle);

	glutPostRedisplay();
}
void processKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		trans.y += 0.1;
		break;
	case 's':
		trans.y -= 0.1;
		break;
	case 'a':
		trans.x -= 0.1;
		break;
	case 'd':
		trans.x += 0.1;
		break;
	case 'r':
		rotate = !rotate;
		break;
	case '>':
		nPoints++;
		break;
	case '<':
		nPoints--;
		if (nPoints<3) nPoints = 3;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("vidu6");

	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(processKeys);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}

};