#include <GL/glut.h>
#include <cmath>

#define RADIAN (M_PI / 180)

int windowWidth = 800;
int windowHeight = 800;
int iterations = 4;
bool mousePressedBefore = false;
int x, y;

void drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void drawKochLine(double x1, double y1, double x2, double y2, int n) {
    if (n <= 1) {
        drawLine(x1, y1, x2, y2);
        return;
    }

    double x3 = (x2 + 2 * x1) / 3.0;
    double y3 = (y2 + 2 * y1) / 3.0;
    double x4 = (2 * x2 + x1) / 3.0;
    double y4 = (2 * y2 + y1) / 3.0;
    double xh = x4 + ((x3 - x4) * cos(60 * RADIAN)) + ((y3 - y4) * sin(60 * RADIAN));
    double yh = y4 - ((x3 - x4) * sin(60 * RADIAN)) + ((y3 - y4) * cos(60 * RADIAN));

    drawKochLine(x1, y1, x3, y3, n - 1);
    drawKochLine(x3, y3, xh, yh, n - 1);
    drawKochLine(xh, yh, x4, y4, n - 1);
    drawKochLine(x4, y4, x2, y2, n - 1);
}

void myMouse(int button, int action, int xMouse, int yMouse) {
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
        if (!mousePressedBefore) {
            x = xMouse;
            y = yMouse;
            mousePressedBefore = true;
        } else {
            drawKochLine(x, windowHeight - y, xMouse, windowHeight - yMouse, iterations);
            mousePressedBefore = false;
        }
    }
    glFlush();
}

void Init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Assignment7");
    Init();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}
