#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

const int width = 300;      // ���檺�e��
const int height = 300;     // ���檺����
float grid[width][height];  // �����@�ת�����
float diffusionRate = 0.27f; // �X���t�v

void initializeGrid() {
    // ��l�ƩҦ���l�� 0
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            grid[x][y] = 0.0f;
        }
    }

    // �]�w���� 5x5 �ϰ쪺�@�׬��̤j�� 100
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

    // �X���p��
    for (int x = 1; x < width - 1; ++x) {
        for (int y = 1; y < height - 1; ++y) {
            newGrid[x][y] = grid[x][y] + diffusionRate * (
                grid[x - 1][y] + grid[x + 1][y] +
                grid[x][y - 1] + grid[x][y + 1] -
                4 * grid[x][y]
                );
            if (grid[x][y] < 0.0f) {
                grid[x][y] = 0.0f;  // ����t��
            }
            if (grid[x][y] > 100.0f) {
                grid[x][y] = 100.0f;  // ����t��
            }


        }

    }

    // �N�s������ƾڽƻs�^��l����
    for (int x = 1; x < width - 1; ++x) {
        for (int y = 1; y < height - 1; ++y) {
            grid[x][y] = newGrid[x][y];
        }
    }

    // �T�O������ 5x5 �ϰ�O���̤j�@��
    int centerX = width / 2;
    int centerY = height / 2;
    for (int x = centerX - 2; x <= centerX + 2; ++x) {
        for (int y = centerY - 2; y <= centerY + 2; ++y) {
            grid[x][y] = 99.0f;
        }
    }

    glutPostRedisplay();  // �q�� OpenGL ���sø�s����
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float value = grid[x][y] / 100.0f;
            // �j���C�����
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
