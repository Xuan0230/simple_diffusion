#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

const int width = 300;      // 網格的寬度
const int height = 300;     // 網格的高度
float grid[width][height];  // 模擬濃度的網格
float diffusionRate = 0.27f; // 擴散速率

void initializeGrid() {
    // 初始化所有格子為 0
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            grid[x][y] = 0.0f;
        }
    }

    // 設定中間 5x5 區域的濃度為最大值 100
    int centerX = width / 2;
    int centerY = height / 2;
    for (int x = centerX - 2; x <= centerX + 2; ++x) {
        for (int y = centerY - 2; y <= centerY + 2; ++y) {
            grid[x][y] = 100.0f;
        }
    }
}

void updateDiffusion() {
    float newGrid[width][height];

    // 擴散計算
    for (int x = 1; x < width - 1; ++x) {
        for (int y = 1; y < height - 1; ++y) {
            newGrid[x][y] = grid[x][y] + diffusionRate * (
                grid[x - 1][y] + grid[x + 1][y] +
                grid[x][y - 1] + grid[x][y + 1] -
                4 * grid[x][y]
                );
            if (grid[x][y] < 0.0f) {
                grid[x][y] = 0.0f;  // 防止負數
            }
            if (grid[x][y] > 100.0f) {
                grid[x][y] = 100.0f;  // 防止負數
            }


        }

    }

    // 將新的網格數據複製回原始網格
    for (int x = 1; x < width - 1; ++x) {
        for (int y = 1; y < height - 1; ++y) {
            grid[x][y] = newGrid[x][y];
        }
    }

    // 確保中間的 5x5 區域保持最大濃度
    int centerX = width / 2;
    int centerY = height / 2;
    for (int x = centerX - 2; x <= centerX + 2; ++x) {
        for (int y = centerY - 2; y <= centerY + 2; ++y) {
            grid[x][y] = 99.0f;
        }
    }

    glutPostRedisplay();  // 通知 OpenGL 重新繪製視窗
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float value = grid[x][y] / 100.0f;
            // 強化顏色對比度
            glColor3f(value * value, value, 1.0f - value * value);
            glVertex2f((x / (float)width) * 2 - 1, (y / (float)height) * 2 - 1);
        }
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Center Diffusion Simulation");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);

    initializeGrid();
    glutDisplayFunc(display);
    glutIdleFunc(updateDiffusion);

    glutMainLoop();
    return 0;
}
