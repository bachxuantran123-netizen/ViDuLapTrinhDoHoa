//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <stdio.h>
#include "imageloader.h"

#include <time.h>
namespace vidu9 {
// Ví dụ 9: Vẽ bề mặt với texture
//
// Thực hành 1: Sử dụng texture tự chụp

float rx=0, ry=0, rz=1, angle=0; 
GLuint texture=0;

void init() {
	texture = textureFromBMP("data/c.bmp");
}
void release() {
	glDeleteTextures(1, &texture);
}

void render() {
	glBindTexture(GL_TEXTURE_2D, texture);
		
	glPushMatrix();
	glRotatef(angle, rx, ry, rz);
	glBegin(GL_TRIANGLES);
#if 1
	glTexCoord2f(0.0, 1.0);  glVertex3f(0, 0, 2);
	glTexCoord2f(1.0, 1.0);  glVertex3f(-1, -1, 0);
	glTexCoord2f(1.0, 0.0);  glVertex3f(-1, 1, 0);

	glTexCoord2f(0.0, 1.0);  glVertex3f(0, 0, 2);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-1, 1, 0);
	glTexCoord2f(1.0, 0.0);  glVertex3f(1, 1, 0);

	glTexCoord2f(0.0, 1.0);  glVertex3f(0, 0, 2);
	glTexCoord2f(1.0, 1.0);  glVertex3f(1, 1, 0);
	glTexCoord2f(1.0, 0.0);  glVertex3f(1, -1, 0);

	glTexCoord2f(0.0, 1.0);  glVertex3f(0, 0, 2);
	glTexCoord2f(0.0, 0.0);  glVertex3f(1, -1, 0);
	glTexCoord2f(1.0, 0.0);  glVertex3f(-1, -1, 0);
#else

	glColor3f(0.0, 1.0, 0.0);  glVertex3f(0, 0, 2);
	glColor3f(1.0, 0.0, 0.0);  glVertex3f(-1, -1, 0);
	glColor3f(0.0, 0.0, 1.0);  glVertex3f(-1, 1, 0);

	glColor3f(1.0, 0.0, 0.0);  glVertex3f(0, 0, 2);
	glColor3f(0.0, 1.0, 0.0);  glVertex3f(-1, 1, 0);
	glColor3f(1.0, 1.0, 1.0);  glVertex3f(1, 1, 0);

	glColor3f(0.0, 1.0, 1.0);  glVertex3f(0, 0, 2);
	glColor3f(1.0, 0.0, 1.0);  glVertex3f(1, 1, 0);
	glColor3f(1.0, 1.0, 0.0);  glVertex3f(1, -1, 0);

	glColor3f(0.5, 1.0, 0.0);  glVertex3f(0, 0, 2);
	glColor3f(0.5, 0.0, 5.0);  glVertex3f(1, -1, 0);
	glColor3f(0.0, 1.0, 5.0);  glVertex3f(-1, -1, 0);
#endif
	glEnd();

	glBegin(GL_QUADS);
#if 1
	glTexCoord2f(0.0, 1.0);  glVertex3f(-1, 1, 0);
	glTexCoord2f(1.0, 1.0);  glVertex3f(-1, -1, 0);
	glTexCoord2f(1.0, 0.0);  glVertex3f(1, -1, 0);
	glTexCoord2f(0.0, 0.0);  glVertex3f(1, 1, 0);
#else
	glColor3f(0.5, 1.0, 0.0);  glVertex3f(-1, 1, 0);
	glColor3f(0.5, 1.0, 0.0);  glVertex3f(-1, -1, 0);
	glColor3f(0.5, 1.0, 0.0);  glVertex3f(1, -1, 0);
	glColor3f(0.5, 1.0, 0.0);  glVertex3f(1, 1, 0);
#endif
	glEnd();
		
	glPopMatrix();
}

void resize(int width, int height) {
	if (height== 0) height = 1;
	const float ar = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluPerspective(45.0f, ar, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 5, 0, 0, 1, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	render();
		
	glFlush();
}
void idle() {
	angle += 0.01;

	glutPostRedisplay();
}
void processKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		rx += 0.1;
		break;
	case 's':
		rx -= 0.1;
		break;
	case 'a':
		ry -= 0.1;
		break;
	case 'd':
		ry += 0.1;
		break;
	case 'q':
		rz -= 0.1;
		break;
	case 'e':
		rz += 0.1;
		break;
	default:
		break;
	}
}
int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("vidu9");
	glEnable(GL_DEPTH_TEST);

	init();
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(processKeys);
	glutIdleFunc(idle);
	glutMainLoop();
	release();
	return 0;
}


};