//
// Ky thuat do hoa
// Ha Manh Toan lhttuy@gmail.com
//
#include <glut.h>
#include <stdio.h>
namespace vidu3_3 {
// Ví dụ 3.3: Sử dụng chuột để vẽ đoạn thẳng
// 
// Thực hành 1: Vẽ hình chữ nhật
// Thực hành 2: Vẽ nhiều đoạn thẳng và lưu lại thành 1 file mô hình 
//   (tham khảo thực hành ví dụ 2). 
//   Sử dụng các kết quả để cập nhật thực hành ví dụ 3.1
// 

bool isDrawing = false;    // Trạng thái đang vẽ: ấn chuột => vẽ, nhả => không
float startX, startY;      // Điểm bắt đầu
float currentX, currentY;  // Điểm hiện tại 

int WINDOW_HEIGHT = 600, WINDOW_WIDTH = 800;
float convertX(int x) {
    return (2.0f * x / WINDOW_WIDTH) - 1.0f;
}
float convertY(int y) {
    return 1.0f - (2.0f * y / WINDOW_HEIGHT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (isDrawing) {
        glColor3f(0.0f, 1.0f, 0.0f); 
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex3f(startX, startY, 0);
        glVertex3f(currentX, currentY, 0);
        glEnd();
    }

    glFlush();
}

// Xử lý sự kiện chuột: thay đổi trạng thái vẽ
void processMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            // Bắt đầu vẽ
            isDrawing = true;
            startX = convertX(x);
            startY = convertY(y);
            currentX = startX;
            currentY = startY;
        }
        else if (state == GLUT_UP && isDrawing) {
            // Thôi vẽ
            isDrawing = false;

            glutPostRedisplay();
        }
    }
}

// Xử lý kéo chuột: hiển thị line hiện thời
void processMotion(int x, int y) {
    if (isDrawing) {
        currentX = convertX(x);
        currentY = convertY(y);
        glutPostRedisplay(); 
    }
}

int main(int argc, char** argv) {
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("vidu3.3");

    glutDisplayFunc(display);
    glutMouseFunc(processMouse);
    glutMotionFunc(processMotion);

    glutMainLoop();
    return 0;
}

}
