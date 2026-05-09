//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
//#include <stdlib.h>
#include <glut.h>
#include "imageloader.h"
#include "texturemodel.h"
#include "linedmodel.h"
#include <math.h>

namespace vidu11 {
// Ví dụ 11: Minh họa vẽ cảnh đơn giản có texture và thao tác di chuyển của người

LinedModel name;
GLuint _textureBrick, _textureDoor, _textureGrass, _textureRoof, _textureWindow, _textureSky, _textureSkyTop;
TextureModel sky, skyTop, grass, wall, roof, door, window, wallside;
Vector3 sky_t, skyTop_t, grass_t, wall_t1, wall_t2, roof_t, door_t,
	wallside_t1, wallside_t2, window_t1, window_t2, window_t3, window_t4;
float lx = 0.0f, lz = 0.0f;
float x = 0.0f, z = 0.0f;
float angle = -1.5f;
float speed = 0.1f;
float heightAngle = 0;
float height_view = -1;

void draw(TextureModel* m, Vector3 t) {
	glPushMatrix();
	glTranslatef(t.x, t.y, t.z);
	m->draw();
	glPopMatrix();
}
void makeSky() {
	sky.clear();
	sky.setTextureFromBMP("data/sky.bmp");
	sky.addVertex(point3(-100, -100, -100));//0
	sky.addVertex(point3(100, -100, -100));//1
	sky.addVertex(point3(-100, 100, -100));//2
	sky.addVertex(point3(100, 100, -100));//3
	sky.addVertex(point3(-100, -100, 100));//4
	sky.addVertex(point3(100, -100, 100));//5
	sky.addVertex(point3(-100, 100, 100));//6
	sky.addVertex(point3(100, 100, 100));//7
	sky.addQuad(quadIndex(2, 3, 1, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
	sky.addQuad(quadIndex(6, 7, 5, 4, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
	sky.addQuad(quadIndex(2, 6, 4, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
	sky.addQuad(quadIndex(3, 7, 5, 1, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

	sky_t = point3(0, 0, 0);
}
void makeSkyTop() {
	skyTop.clear();
	skyTop.setTextureFromBMP("data/skytop.bmp");
	skyTop.addVertex(point3(-100, 100, -100));
	skyTop.addVertex(point3(100, 100, -100));
	skyTop.addVertex(point3(100, 100, 100));
	skyTop.addVertex(point3(-100, 100, 100));
	skyTop.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

	skyTop_t = point3(0, 0, 0);
}
void makeGrass() {
	grass.clear();
	grass.setTextureFromBMP("data/grass.bmp");
	grass.addVertex(point3(-10, -1.5, 10));
	grass.addVertex(point3(-10, -1.5, -10));
	grass.addVertex(point3(10, -1.5, -10));
	grass.addVertex(point3(10, -1.5, 10));
	grass.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 100), texCoord2(100, 100), texCoord2(100, 0), texCoord2(0, 0)));

	grass_t = point3(0, 0, 0);
}
void makeWall() {
	wall.clear();
	wall.setTextureFromBMP("data/bricks.bmp");
	wall.addVertex(point3(-2, 0, 1));
	wall.addVertex(point3(2, 0, 1));
	wall.addVertex(point3(2, -1.5, 1));
	wall.addVertex(point3(-2, -1.5, 1));
	wall.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 2), texCoord2(4, 2), texCoord2(4, 0), texCoord2(0, 0)));

	wall_t1 = point3(0, 0, -6);
	wall_t2 = point3(0, 0, -8);
}
void makeName() {
	name.nVertices = 26;
	name.vertices[0] = point3(-0.8, 0.3, 0);
	name.vertices[1] = point3(-0.8, 0.7, 0);
	name.vertices[2] = point3(-0.9, 0.7, 0);
	name.vertices[3] = point3(-0.7, 0.7, 0);
	name.vertices[4] = point3(-0.6, 0.7, 0);
	name.vertices[5] = point3(-0.4, 0.7, 0);
	name.vertices[6] = point3(-0.4, 0.7, 0);
	name.vertices[7] = point3(-0.4, 0.3, 0);
	name.vertices[8] = point3(-0.4, 0.3, 0);
	name.vertices[9] = point3(-0.6, 0.3, 0);
	name.vertices[10] = point3(-0.6, 0.3, 0);
	name.vertices[11] = point3(-0.6, 0.7, 0);
	name.vertices[12] = point3(-0.3, 0.3, 0);
	name.vertices[13] = point3(-0.2, 0.7, 0);
	name.vertices[14] = point3(-0.2, 0.7, 0);
	name.vertices[15] = point3(-0.1, 0.3, 0);
	name.vertices[16] = point3(-0.25, 0.5, 0);
	name.vertices[17] = point3(-0.15, 0.5, 0);
	name.vertices[18] = point3(0.0, 0.3, 0);
	name.vertices[19] = point3(0.0, 0.7, 0);
	name.vertices[20] = point3(0.0, 0.7, 0);
	name.vertices[21] = point3(0.2, 0.3, 0);
	name.vertices[22] = point3(0.2, 0.3, 0);
	name.vertices[23] = point3(0.2, 0.7, 0);
	name.vertices[24] = point3(-0.25, 0.85, 0);
	name.vertices[25] = point3(-0.15, 0.8, 0);
	name.nEdges = 25;
	for (int i = 0; i < 25; i++) {
		name.edges[i][0] = i * 2;
		name.edges[i][1] = i * 2 + 1;
	}
}
void makeRoof() {
	roof.clear();
	roof.setTextureFromBMP("data/roof.bmp");
	roof.addVertex(point3(-2.2, 0.5, 0));
	roof.addVertex(point3(2.2, 0.5, 0));
	roof.addVertex(point3(2.2, -0.1, 1.25));
	roof.addVertex(point3(-2.2, -0.1, 1.25));
	roof.addVertex(point3(2.2, -0.1, -1.25));
	roof.addVertex(point3(-2.2, -0.1, -1.25));
	roof.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 2), texCoord2(4, 2), texCoord2(4, 0), texCoord2(0, 0)));
	roof.addQuad(quadIndex(0, 1, 4, 5, texCoord2(0, 2), texCoord2(4, 2), texCoord2(4, 0), texCoord2(0, 0)));

	roof_t = point3(0, 0, -6);
}
void makeDoor() {
	door.clear();
	door.setTextureFromBMP("data/door.bmp");
	door.addVertex(point3(-0.3, -0.4, 1.0001));
	door.addVertex(point3(0.3, -0.4, 1.0001));
	door.addVertex(point3(0.3, -1.5, 1.0001));
	door.addVertex(point3(-0.3, -1.5, 1.0001));
	door.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

	door_t = point3(0, 0, -6);
}
void makeWindow() {
	window.clear();
	window.setTextureFromBMP("data/window.bmp");
	window.addVertex(point3(-1.5, -0.3, 1.0001));
	window.addVertex(point3(-0.75, -0.3, 1.0001));
	window.addVertex(point3(-0.75, -0.8, 1.0001));
	window.addVertex(point3(-1.5, -0.8, 1.0001));
	window.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

	window_t1 = point3(0, 0, -6);
	window_t2 = point3(2.25, 0, -6);
	window_t3 = point3(0, 0, -8.002);
	window_t4 = point3(2.25, 0, -8.002);
}
void makeWallside() {
	wallside.clear();
	wallside.setTextureFromBMP("data/bricks.bmp");
	wallside.addVertex(point3(2, 0, 1));
	wallside.addVertex(point3(2, 0, -1));
	wallside.addVertex(point3(2, -1.5, -1));
	wallside.addVertex(point3(2, -1.5, 1));
	wallside.addVertex(point3(2, 0.5, 0));
	wallside.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 2), texCoord2(2, 2), texCoord2(2, 0), texCoord2(0, 0)));
	wallside.addTriangle(triangleIndex(4, 0, 1, texCoord2(0, 1), texCoord2(1, 0), texCoord2(-1, 0)));

	wallside_t1 = point3(0, 0, -6);
	wallside_t2 = point3(-4, 0, -6);
}
void drawName() {
	glPushMatrix();
	glLineWidth(4.0f);
	glColor3f(0.6, 0.17, 0.71);
	glScalef(10, 10, 10);
	glTranslatef(0, 9, -9.f);
	drawLinedModel(&name);
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);
}
void resize(int width, int height) {
	if (height == 0) height = 1;
	const float ar = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluPerspective(45.0f, ar, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(x, -1.0f, z,
		x + lx, height_view, z + lz,
		0.0f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);

	draw(&sky, sky_t);
	draw(&skyTop, skyTop_t);
	for (int x1 = -5; x1 < 5; x1++) {
		for (int z1 = -5; z1 < 5; z1++) {
			Vector3 grass_t1;
			grass_t1.x = x1;
			grass_t1.z = z1;
			grass_t1.y = 0;

			draw(&grass, grass_t1);
		}
	}
	draw(&wall, wall_t1);
	draw(&roof, roof_t);
	draw(&door, door_t);
	draw(&window, window_t1);
	draw(&window, window_t2);
	draw(&wall, wall_t2);
	draw(&window, window_t3);
	draw(&window, window_t4);
	draw(&wallside, wallside_t1);
	draw(&wallside, wallside_t2);
	drawName();
	glutSwapBuffers();
	glFlush();
}
void processKeys(unsigned char key, int xx, int yy) {
	switch (key) {
	case '>':
		speed += 0.1;
		break;
	case '<':
		speed -= 0.1;
		break;
	case 'w':
		if (heightAngle < PI / 2) {
			heightAngle += 0.1;
			height_view = sin(heightAngle) - 1;
		}
		break;
	case 's':
		if (heightAngle > (-PI / 2)) {
			heightAngle -= 0.1;
			height_view = sin(heightAngle) - 1;
		}
		break;
	case 'a':
		angle -= 0.02f;
		lx = cos(angle);
		lz = sin(angle);
		break;
	case 'd':
		angle += 0.02f;
		lx = cos(angle);
		lz = sin(angle);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void processSpecialKeys(int key, int xx, int yy) {

	float fraction = speed;

	switch (key) {
	case GLUT_KEY_LEFT:
		x += lz * fraction;
		z -= lx * fraction;
		break;
	case GLUT_KEY_RIGHT:
		x -= lz * fraction;
		z += lx * fraction;
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}glutPostRedisplay();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	lx = cos(angle);
	lz = sin(angle);

	makeSky();
	makeSkyTop();
	makeGrass();
	makeWall();
	makeRoof();
	makeDoor();
	makeWindow();
	makeWallside();
	makeName();
}
int main(int argc, char** argv) {
	glutInitDisplayMode(/*GLUT_DOUBLE | GLUT_RGBA | */GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("vidu11");
	glEnable(GL_DEPTH_TEST);

	glutReshapeFunc(resize);
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc(renderScene);
	init();

	glutMainLoop();
	return 0;
}

}