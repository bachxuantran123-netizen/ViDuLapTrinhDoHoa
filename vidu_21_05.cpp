#include <glut.h>
#include <math.h>

namespace vidu1 {
    // Biến trạng thái để kiểm soát việc hiển thị từng chữ cái
    int step = 0;

    // Thiết lập môi trường vẽ
    void init() {
        glClearColor(0.0, 0.0, 0.0, 1.0); // Màu nền đen
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // Thiết lập hệ tọa độ 2D: x từ 0->50, y từ 0->40
        gluOrtho2D(0.0, 50.0, 0.0, 40.0);
    }

    // Vẽ chữ B
    void drawB() {
        glBegin(GL_LINE_STRIP);
        glVertex2f(5.0f, 10.0f);
        glVertex2f(5.0f, 30.0f);
        glVertex2f(10.0f, 30.0f);
        glVertex2f(10.0f, 20.0f);
        glVertex2f(5.0f, 20.0f);
        glVertex2f(10.0f, 20.0f);
        glVertex2f(10.0f, 10.0f);
        glVertex2f(5.0f, 10.0f);
        glEnd();
    }

    // Vẽ chữ A
    void drawA() {
        glBegin(GL_LINE_STRIP);
        glVertex2f(15.0f, 10.0f);
        glVertex2f(17.5f, 30.0f);
        glVertex2f(20.0f, 10.0f);
        glEnd();

        // Nét gạch ngang của chữ A
        glBegin(GL_LINES);
        glVertex2f(16.25f, 20.0f);
        glVertex2f(18.75f, 20.0f);
        glEnd();
    }

    // Vẽ chữ C
    void drawC() {
        glBegin(GL_LINE_STRIP);
        glVertex2f(30.0f, 30.0f);
        glVertex2f(25.0f, 30.0f);
        glVertex2f(25.0f, 10.0f);
        glVertex2f(30.0f, 10.0f);
        glEnd();
    }

    // Vẽ chữ H
    void drawH() {
        glBegin(GL_LINES);
        // 2 nét dọc
        glVertex2f(35.0f, 10.0f); glVertex2f(35.0f, 30.0f);
        glVertex2f(40.0f, 10.0f); glVertex2f(40.0f, 30.0f);
        // Nét ngang
        glVertex2f(35.0f, 20.0f); glVertex2f(40.0f, 20.0f);
        glEnd();
    }

    // Vẽ dấu sắc (trên đầu chữ A)
    void drawDauSac() {
        glBegin(GL_LINES);
        glVertex2f(18.0f, 32.0f);
        glVertex2f(19.5f, 35.0f);
        glEnd();
    }

    // Hàm hiển thị chính
    void display() {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 1.0, 0.0); // Chỉnh màu nét vẽ (0,1,0) là màu xanh lá giống code mẫu của thầy
        glLineWidth(3.0f);        // Chỉnh độ dày của nét vẽ

        // Kiểm tra biến step để hiện lần lượt
        if (step >= 1) drawB();
        if (step >= 2) drawA();
        if (step >= 3) drawC();
        if (step >= 4) drawH();
        if (step >= 5) drawDauSac();

        glFlush();
    }

    // Hàm xử lý sự kiện bàn phím
    void keyboard(unsigned char key, int x, int y) {
        // Nhấn phím Space hoặc Enter để hiện chữ tiếp theo
        if (key == ' ' || key == 13) {
            step++;
            if (step > 5) {
                step = 0; // Reset lại về màn hình trống
            }
            glutPostRedisplay();
        }
    }

    int main(int argc, char** argv) {
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(50, 50);
        glutCreateWindow("Ve chu BACH bang ban phim");

        init();

        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard);

        glutMainLoop();
        return 0;
    }
}