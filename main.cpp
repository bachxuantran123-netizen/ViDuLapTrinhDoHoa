#include "main.h"
#include <glut.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <time.h> 

#ifndef PI
#define PI 3.141592653589f
#endif

#pragma warning(disable : 4996) 

// =========================================================
// 1. BIẾN TOÀN CỤC MÔ PHỎNG ĐỒ HỌA
// =========================================================
GLuint texRoom, texDecal, texCarpet, texMetal, texFloor;

// Biến đổi không gian của Cẩu trục
float craneX = 0.0f, craneZ = 0.0f, dropY = 0.0f, clawAngle = 0.0f;
bool isClawOpen = true;

// Thông số Camera
float camAngleX = 0.0f, camAngleY = 20.0f, camDistance = 15.0f;
int lastMouseX = -1, lastMouseY = -1;
bool isDragging = false;

// Kỹ thuật Rendering
bool isDrawingShadow = false;

#define NUM_BEARS 12

struct Plushie {
    float x, y, z;
    float r, g, b;
    bool isGrabbed;
};

Plushie toys[NUM_BEARS];

void drawClawMachine();
void drawPlushies();
void drawMachineBase();
void drawShadows();
void drawGlassCabinet();

// Khởi tạo quần thể đối tượng 3D ngẫu nhiên 
void spawnBears() {
    for (int i = 0; i < NUM_BEARS; i++) {
        float rx, rz;
        bool inHole;
        do {
            rx = -2.0f + (rand() % 400) / 100.0f;
            rz = -2.0f + (rand() % 400) / 100.0f;
            inHole = (rx < -0.6f && rz > 0.6f);
        } while (inHole);

        toys[i].x = rx;
        toys[i].y = -0.49f;
        toys[i].z = rz;

        toys[i].r = 0.3f + (rand() % 70) / 100.0f;
        toys[i].g = 0.3f + (rand() % 70) / 100.0f;
        toys[i].b = 0.3f + (rand() % 70) / 100.0f;
        toys[i].isGrabbed = false;
    }
}

void useTexture(GLuint tex) {
    if (tex == 0) {
        glDisable(GL_TEXTURE_2D);
    }
    else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex);
    }
}

// =========================================================
// 2. TEXTURE MAPPING & XÂY DỰNG KHỐI LẬP PHƯƠNG CÓ UV
// =========================================================
void drawTexturedBox(float sx, float sy, float sz) {
    float hx = sx / 2.0f, hy = sy / 2.0f, hz = sz / 2.0f;
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, -hy, hz); glTexCoord2f(1.0f, 0.0f); glVertex3f(hx, -hy, hz); glTexCoord2f(1.0f, 1.0f); glVertex3f(hx, hy, hz); glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, hy, hz);
    glNormal3f(0.0f, 0.0f, -1.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(hx, -hy, -hz); glTexCoord2f(1.0f, 0.0f); glVertex3f(-hx, -hy, -hz); glTexCoord2f(1.0f, 1.0f); glVertex3f(-hx, hy, -hz); glTexCoord2f(0.0f, 1.0f); glVertex3f(hx, hy, -hz);
    glNormal3f(0.0f, 1.0f, 0.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, hy, hz); glTexCoord2f(1.0f, 0.0f); glVertex3f(hx, hy, hz); glTexCoord2f(1.0f, 1.0f); glVertex3f(hx, hy, -hz); glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, hy, -hz);
    glNormal3f(0.0f, -1.0f, 0.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, -hy, -hz); glTexCoord2f(1.0f, 0.0f); glVertex3f(hx, -hy, -hz); glTexCoord2f(1.0f, 1.0f); glVertex3f(hx, -hy, hz); glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, -hy, hz);
    glNormal3f(1.0f, 0.0f, 0.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(hx, -hy, hz); glTexCoord2f(1.0f, 0.0f); glVertex3f(hx, -hy, -hz); glTexCoord2f(1.0f, 1.0f); glVertex3f(hx, hy, -hz); glTexCoord2f(0.0f, 1.0f); glVertex3f(hx, hy, hz);
    glNormal3f(-1.0f, 0.0f, 0.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(-hx, -hy, -hz); glTexCoord2f(1.0f, 0.0f); glVertex3f(-hx, -hy, hz); glTexCoord2f(1.0f, 1.0f); glVertex3f(-hx, hy, hz); glTexCoord2f(0.0f, 1.0f); glVertex3f(-hx, hy, -hz);
    glEnd();
}

// C++ Thuần: Đọc file BMP 24-bit vào RAM và đẩy lên VRAM của GPU
GLuint loadBMPTexture(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return 0;
    unsigned char header[54];
    if (fread(header, 1, 54, file) != 54 || header[0] != 'B' || header[1] != 'M') { fclose(file); return 0; }
    unsigned int dataPos = *(int*)&(header[0x0A]);
    unsigned int width = *(int*)&(header[0x12]);
    unsigned int height = *(int*)&(header[0x16]);
    if (dataPos == 0) dataPos = 54;
    unsigned int imageSize = width * height * 3;
    unsigned char* data = new unsigned char[imageSize]();
    fseek(file, dataPos, SEEK_SET);
    int rowPadding = (4 - (width * 3) % 4) % 4;
    for (unsigned int y = 0; y < height; y++) {
        fread(&data[y * width * 3], 1, width * 3, file);
        if (rowPadding > 0) fseek(file, rowPadding, SEEK_CUR);
    }
    fclose(file);
    for (unsigned int i = 0; i < imageSize; i += 3) {
        unsigned char tmp = data[i]; data[i] = data[i + 2]; data[i + 2] = tmp;
    }
    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    delete[] data;
    return texId;
}

// =========================================================
// 3. MÔ HÌNH PHÂN CẤP
// =========================================================
// Vẽ căn phòng với kỹ thuật lặp ảnh
void drawRoom() {
    glDisable(GL_LIGHTING);
    float s = 40.0f, h = 30.0f;

    useTexture(texFloor);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-s, -2.5f, s);
    glTexCoord2f(10.0f, 0.0f);  glVertex3f(s, -2.5f, s);
    glTexCoord2f(10.0f, 10.0f); glVertex3f(s, -2.5f, -s);
    glTexCoord2f(0.0f, 10.0f);  glVertex3f(-s, -2.5f, -s);
    glEnd();

    useTexture(texRoom);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-s, -2.5f, -s); glTexCoord2f(1, 0); glVertex3f(s, -2.5f, -s); glTexCoord2f(1, 1); glVertex3f(s, h, -s); glTexCoord2f(0, 1); glVertex3f(-s, h, -s);
    glTexCoord2f(0, 0); glVertex3f(-s, -2.5f, s); glTexCoord2f(1, 0); glVertex3f(-s, -2.5f, -s); glTexCoord2f(1, 1); glVertex3f(-s, h, -s); glTexCoord2f(0, 1); glVertex3f(-s, h, s);
    glTexCoord2f(0, 0); glVertex3f(s, -2.5f, -s); glTexCoord2f(1, 0); glVertex3f(s, -2.5f, s); glTexCoord2f(1, 1); glVertex3f(s, h, s); glTexCoord2f(0, 1); glVertex3f(s, h, -s);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Vẽ 1 ngón tay của ngàm gắp (Sử dụng 2 khớp quay)
void drawFinger(float openAngle) {
    glPushMatrix();
    glTranslatef(0.5f, -0.25f, 0.0f); glRotatef(openAngle, 0.0f, 0.0f, 1.0f); glTranslatef(0.0f, -0.5f, 0.0f);
    glPushMatrix(); glScalef(0.15f, 1.0f, 0.15f); glutSolidCube(1.0f); glPopMatrix();

    glTranslatef(0.0f, -0.5f, 0.0f); glRotatef(45.0f, 0.0f, 0.0f, 1.0f); glTranslatef(0.0f, -0.3f, 0.0f);
    glPushMatrix(); glScalef(0.1f, 0.6f, 0.1f); glutSolidCube(1.0f); glPopMatrix();
    glPopMatrix();
}

// Vẽ toàn bộ Cụm Cẩu trục
void drawClawMachine() {
    glPushMatrix();
    if (!isDrawingShadow) {
        useTexture(texMetal); glColor3f(0.8f, 0.8f, 0.8f);
        glPushMatrix(); glTranslatef(0.0f, 6.0f, 0.0f); drawTexturedBox(5.0f, 0.2f, 5.0f); glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }

    // Tịnh tiến toàn bộ cụm theo trục X và Z (Người dùng điều khiển)
    glTranslatef(craneX, 0.0f, craneZ);

    if (!isDrawingShadow) {
        useTexture(texMetal); glColor3f(0.8f, 0.8f, 0.8f);
        glPushMatrix(); glTranslatef(0.0f, 5.8f, 0.0f); drawTexturedBox(0.8f, 0.4f, 0.8f); glPopMatrix();
        glDisable(GL_TEXTURE_2D); glColor3f(0.2f, 0.2f, 0.2f);
    }
    else {
        glPushMatrix(); glTranslatef(0.0f, 5.8f, 0.0f); glScalef(0.8f, 0.4f, 0.8f); glutSolidCube(1.0f); glPopMatrix();
    }

    // Dây cáp nối (Dài ra khi DropY âm)
    if (!isDrawingShadow) glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(2.0f);
    glBegin(GL_LINES); glVertex3f(0.0f, 5.8f, 0.0f); glVertex3f(0.0f, 4.0f + dropY, 0.0f); glEnd();

    glTranslatef(0.0f, 4.0f + dropY, 0.0f);
    if (!isDrawingShadow) glColor3f(0.9f, 0.1f, 0.1f);
    glPushMatrix(); glScalef(1.0f, 0.5f, 1.0f); glutSolidCube(1.0f); glPopMatrix();

    // Vẽ 3 ngón tay phân bố đều 120 độ
    if (!isDrawingShadow) glColor3f(0.8f, 0.8f, 0.8f);
    for (int i = 0; i < 3; i++) {
        glPushMatrix(); glRotatef(i * 120.0f, 0.0f, 1.0f, 0.0f); drawFinger(clawAngle); glPopMatrix();
    }
    glPopMatrix();
}

void drawMachineBase() {
    useTexture(texDecal); glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix(); glTranslatef(0.0f, -1.5f, 0.0f); drawTexturedBox(5.0f, 2.0f, 5.0f); glPopMatrix();

    // Sàn và lồng hố quà
    useTexture(texCarpet);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, -0.49f, 0.8f); glTexCoord2f(3.0f, 0.0f); glVertex3f(2.5f, -0.49f, 0.8f); glTexCoord2f(3.0f, 2.0f); glVertex3f(2.5f, -0.49f, -2.5f); glTexCoord2f(0.0f, 2.0f); glVertex3f(-2.5f, -0.49f, -2.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.8f, -0.49f, 2.5f); glTexCoord2f(2.0f, 0.0f); glVertex3f(2.5f, -0.49f, 2.5f); glTexCoord2f(2.0f, 1.0f); glVertex3f(2.5f, -0.49f, 0.8f); glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.8f, -0.49f, 0.8f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, -0.49f, 2.5f); glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.8f, -0.49f, 2.5f); glTexCoord2f(1.0f, 0.5f); glVertex3f(-0.8f, -0.49f, 2.2f); glTexCoord2f(0.0f, 0.5f); glVertex3f(-2.5f, -0.49f, 2.2f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, -0.49f, 2.2f); glTexCoord2f(0.5f, 0.0f); glVertex3f(-2.2f, -0.49f, 2.2f); glTexCoord2f(0.5f, 1.0f); glVertex3f(-2.2f, -0.49f, 0.8f); glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f, -0.49f, 0.8f);
    glEnd();

    useTexture(texMetal);
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.8f, -2.5f, 2.2f); glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.8f, -2.5f, 0.8f); glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.8f, -0.49f, 0.8f); glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.8f, -0.49f, 2.2f);
    glNormal3f(1.0f, 0.0f, 0.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.2f, -2.5f, 0.8f); glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.2f, -2.5f, 2.2f); glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.2f, -0.49f, 2.2f); glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.2f, -0.49f, 0.8f);
    glNormal3f(0.0f, 0.0f, 1.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.8f, -2.5f, 0.8f); glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.2f, -2.5f, 0.8f); glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.2f, -0.49f, 0.8f); glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.8f, -0.49f, 0.8f);
    glNormal3f(0.0f, 0.0f, -1.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.2f, -2.5f, 2.2f); glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.8f, -2.5f, 2.2f); glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.8f, -0.49f, 2.2f); glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.2f, -0.49f, 2.2f);
    glNormal3f(0.0f, 1.0f, 0.0f); glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.2f, -2.49f, 2.2f); glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.8f, -2.49f, 2.2f); glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.8f, -2.49f, 0.8f); glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.2f, -2.49f, 0.8f);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glPushMatrix();
    glTranslatef(-1.5f, -0.46f, 1.5f);
    glPushMatrix(); glTranslatef(-0.75f, 0.0f, 0.0f); drawTexturedBox(0.1f, 0.1f, 1.6f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.75f, 0.0f, 0.0f); drawTexturedBox(0.1f, 0.1f, 1.6f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 0.0f, -0.75f); drawTexturedBox(1.6f, 0.1f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 0.0f, 0.75f); drawTexturedBox(1.6f, 0.1f, 0.1f); glPopMatrix();
    glPopMatrix();

    // Bảng điều khiển (Dùng các ma trận quay và tịnh tiến lồng nhau)
    useTexture(texMetal); glColor3f(0.8f, 0.8f, 0.8f);
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 2.8f); glRotatef(-20.0f, 1.0f, 0.0f, 0.0f); drawTexturedBox(3.0f, 0.5f, 1.5f);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.0f, -0.2f, 2.8f); glColor3f(0.2f, 0.2f, 0.2f); glutSolidSphere(0.2f, 15, 15);
    glRotatef(craneZ * 15.0f, 1.0f, 0.0f, 0.0f); glRotatef(craneX * -15.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix(); glScalef(0.05f, 0.6f, 0.05f); glTranslatef(0.0f, 0.5f, 0.0f); glutSolidCube(1.0f); glPopMatrix();
    glColor3f(0.9f, 0.1f, 0.1f); glTranslatef(0.0f, 0.6f, 0.0f); glutSolidSphere(0.15f, 15, 15);
    glPopMatrix();
}

// Thuật toán Đổ bóng Dẹt (Planar Shadow Mapping)
void drawShadows() {
    isDrawingShadow = true;
    glDisable(GL_LIGHTING);

    // Dùng Blending để tạo bóng trong suốt (Alpha = 0.65)
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.65f);

    glPushMatrix();
    // Ép dẹt không gian theo trục Y xuống còn 0.001
    glTranslatef(0.0f, -0.485f, 0.0f);
    glScalef(1.0f, 0.001f, 1.0f);
    glTranslatef(0.0f, 0.485f, 0.0f);

    // Khóa ghi chiều sâu để bóng không bị nhấp nháy Z-Fighting
    glDepthMask(GL_FALSE);
    drawClawMachine();
    drawPlushies();
    glDepthMask(GL_TRUE);
    glPopMatrix();

    glDisable(GL_BLEND); glEnable(GL_LIGHTING);
    isDrawingShadow = false;
}

// Xử lý vật liệu trong suốt (Alpha Blending)
void drawGlassCabinet() {
    glPushMatrix();
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.6f, 0.8f, 1.0f, 0.25f); // Kính xanh nhạt, trong suốt 75%

    glTranslatef(0.0f, 2.5f, 0.0f);
    glPushMatrix(); glScalef(4.8f, 6.8f, 4.8f); glutSolidCube(1.0f); glPopMatrix();
    glDisable(GL_BLEND);

    useTexture(texMetal); glColor3f(0.8f, 0.8f, 0.8f);
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix(); glTranslatef(i * 2.45f, 0.0f, j * 2.45f); drawTexturedBox(0.2f, 6.8f, 0.2f); glPopMatrix();
        }
    }

    glPushMatrix(); glTranslatef(0.0f, 3.6f, 0.0f); drawTexturedBox(5.1f, 0.2f, 5.1f); glPopMatrix();
    glDisable(GL_TEXTURE_2D); glPopMatrix();
}

void drawBear(float r, float g, float b) {
    if (!isDrawingShadow) glColor3f(r, g, b);
    glPushMatrix(); glTranslatef(0.0f, 0.3f, 0.0f); glutSolidSphere(0.3f, 20, 20); glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.7f, 0.0f); glutSolidSphere(0.25f, 20, 20);
    glPushMatrix(); glTranslatef(-0.15f, 0.15f, 0.0f); glutSolidSphere(0.08f, 10, 10); glPopMatrix();
    glPushMatrix(); glTranslatef(0.15f, 0.15f, 0.0f); glutSolidSphere(0.08f, 10, 10); glPopMatrix();
    glPopMatrix();
}

void drawPlushies() {
    for (int i = 0; i < NUM_BEARS; i++) {
        if (isDrawingShadow && toys[i].y < -1.0f) continue;
        glPushMatrix();
        if (toys[i].isGrabbed) {
            // Ràng buộc tọa độ gấu theo tọa độ cẩu trục
            glTranslatef(craneX, 4.0f + dropY - 0.8f, craneZ);
        }
        else {
            glTranslatef(toys[i].x, toys[i].y, toys[i].z);
        }
        drawBear(toys[i].r, toys[i].g, toys[i].b);
        glPopMatrix();
    }
}

// =========================================================
// 4. XỬ LÝ SỰ KIỆN TƯƠNG TÁC (USER INTERACTION)
// =========================================================
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0); // Nhấn ESC để thoát chương trình

    switch (key) {
    case 'w': case 'W': craneZ -= 0.2f; break;
    case 's': case 'S': craneZ += 0.2f; break;
    case 'a': case 'A': craneX -= 0.2f; break;
    case 'd': case 'D': craneX += 0.2f; break;
    case ' ': {
        isClawOpen = !isClawOpen;
        clawAngle = isClawOpen ? 0.0f : -30.0f;

        if (!isClawOpen) {
            // Thuật toán kiểm tra va chạm bằng khoảng cách (Distance Collision Detection)
            float clawRealY = 4.0f + dropY - 0.5f;
            for (int i = 0; i < NUM_BEARS; i++) {
                if (!toys[i].isGrabbed) {
                    float dx = craneX - toys[i].x; float dy = clawRealY - (toys[i].y + 0.5f); float dz = craneZ - toys[i].z;
                    if (sqrt(dx * dx + dy * dy + dz * dz) < 0.8f) { toys[i].isGrabbed = true; break; }
                }
            }
        }
        else {
            for (int i = 0; i < NUM_BEARS; i++) {
                if (toys[i].isGrabbed) {
                    toys[i].isGrabbed = false; toys[i].x = craneX; toys[i].z = craneZ;

                    // Vật lý rớt xuống hố
                    if (craneX > -2.2f && craneX < -0.8f && craneZ > 0.8f && craneZ < 2.2f) {
                        toys[i].y = -2.2f;
                    }
                    else {
                        toys[i].y = -0.49f;
                    }
                }
            }
        }
        break;
    }
    }

    // Giới hạn biên (Clamping)
    if (craneX > 2.0f) craneX = 2.0f; if (craneX < -2.0f) craneX = -2.0f;
    if (craneZ > 2.0f) craneZ = 2.0f; if (craneZ < -2.0f) craneZ = -2.0f;
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:   dropY += 0.2f; break;
    case GLUT_KEY_DOWN: dropY -= 0.2f; break;
    }
    if (dropY > 0.0f) dropY = 0.0f; if (dropY < -3.5f) dropY = -3.5f;
    glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) { isDragging = (state == GLUT_DOWN); lastMouseX = x; lastMouseY = y; }
}

void mouseMotion(int x, int y) {
    if (isDragging) {
        camAngleX += (x - lastMouseX) * 0.5f; camAngleY += (y - lastMouseY) * 0.5f;
        if (camAngleY > 89.0f) camAngleY = 89.0f; if (camAngleY < -10.0f) camAngleY = -10.0f;
        lastMouseX = x; lastMouseY = y; glutPostRedisplay();
    }
}

// =========================================================
// 5. CƠ CHẾ RENDER CORE
// =========================================================
void resize(int width, int height) {
    if (height == 0) height = 1;
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);

    // Khởi tạo Ma trận Phép chiếu Tiên cảnh (Perspective Projection)
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0f, ar, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();

    // Hệ tọa độ Cầu của Camera (Spherical Camera System)
    float camX = camDistance * sin(camAngleX * PI / 180.0f) * cos(camAngleY * PI / 180.0f);
    float camY = 3.0f + camDistance * sin(camAngleY * PI / 180.0f);
    float camZ = camDistance * cos(camAngleX * PI / 180.0f) * cos(camAngleY * PI / 180.0f);
    gluLookAt(camX, camY, camZ, 0.0, 2.0, 0.0, 0.0, 1.0, 0.0);

    drawRoom();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat lightPos[] = { 10.0f, 15.0f, 10.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    drawMachineBase();
    drawShadows();
    drawClawMachine();
    drawPlushies();
    drawGlassCabinet();

    glutSwapBuffers(); glFlush();
}

// Cấu hình Nguồn sáng và Vật liệu Phản quang (Lighting & Material Parameters)
void setupLighting() {
    glEnable(GL_LIGHT0);
    GLfloat lightPos[] = { 10.0f, 15.0f, 10.0f, 1.0f };
    GLfloat ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f }; // Ánh sáng môi trường
    GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Ánh sáng khuếch tán

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    // Tinh chỉnh phản quang Kim loại (Specular Highlights)
    GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat shininess[] = { 30.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    setupLighting();

    srand((unsigned)time(NULL));
    spawnBears();

    texRoom = loadBMPTexture("data/room.bmp"); texDecal = loadBMPTexture("data/decal.bmp");
    texCarpet = loadBMPTexture("data/carpet.bmp"); texMetal = loadBMPTexture("data/metal.bmp");
    texFloor = loadBMPTexture("data/floor.bmp");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(50, 50); glutInitWindowSize(800, 600);
    glutCreateWindow("Computer Graphics - 3D Claw Machine Simulation");
    init();
    glutReshapeFunc(resize); glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboard); glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseClick); glutMotionFunc(mouseMotion);
    glutMainLoop(); return 0;
}