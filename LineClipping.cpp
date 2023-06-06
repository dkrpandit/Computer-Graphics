#include <iostream>
#include <cmath>
#include <GL/glut.h>

int xmin, xmax, ymin, ymax;
int code[4];

class LineClipping {
public:
    float x, y;
    int binary[4];

    void check() {
        binary[3] = x < xmin ? 1 : 0;
        binary[2] = x > xmax ? 1 : 0;
        binary[1] = y < ymin ? 1 : 0;
        binary[0] = y > ymax ? 1 : 0;
    }
};

LineClipping p1, p2;

void LineDDA(int xa, int ya, int xb, int yb) {
    int dx = xb - xa;
    int dy = yb - ya;
    int steps = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);
    float xInc = dx / static_cast<float>(steps);
    float yInc = dy / static_cast<float>(steps);
    float x = xa;
    float y = ya;

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    for (int k = 0; k < steps; k++) {
        x += xInc;
        y += yInc;
        glVertex2i(std::floor(x + 0.5), std::floor(y + 0.5));
    }

    glEnd();
    glFlush();
}

void calculate(LineClipping* p) {
    int flag = 0;
    float x, y;

    for (int i = 0; i < 4; i++) {
        if (p->binary[i] == 0) {
            flag = 0;
        } else {
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        std::cout << "\nNo intersection";
    } else {
        if (p->binary[3] == 1)
            x = xmin;
        if (p->binary[2] == 1)
            x = xmax;
        if (p->binary[1] == 1)
            y = ymin;
        if (p->binary[0] == 1)
            y = ymax;

        if (p->binary[3] == 1 || p->binary[2] == 1) {
            float m = (p2.y - p1.y) / static_cast<float>(p2.x - p1.x);
            y = p->y + m * (x - p->x);
        } else {
            float m = (p2.y - p1.y) / static_cast<float>(p2.x - p1.x);
            x = p->x + (y - p->y) / m;
        }

        p->x = x;
        p->y = y;
    }
}

void find() {
    calculate(&p1);
    std::cout << "\n" << p1.x << "\t" << p1.y;
    calculate(&p2);
    std::cout << "\n" << p2.x << "\t" << p2.y;
    p1.check();
    p2.check();

    for (int i = 0; i < 4; i++) {
        std::cout << "\np1:" << p1.binary[i];
    }

    for (int i = 0; i < 4; i++) {
        std::cout << "\np2:" << p2.binary[i];
    }
}

void test() {
    int flag = 0;
    int flag1 = 0;

    for (int i = 0; i < 4; i++) {
        if (p1.binary[i] == 0 && p2.binary[i] == 0) {
            flag = 0;
        } else {
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        std::cout << "\nAccepted:";
    } else {
        for (int i = 0; i < 4; i++) {
            code[i] = p1.binary[i] && p2.binary[i];
        }

        for (int i = 0; i < 4; i++) {
            if (code[i] == 1) {
                flag1 = 0;
                break;
            } else {
                flag1 = 1;
            }
        }

        if (flag1 == 0) {
            std::cout << "\nRejected:";
        } else {
            std::cout << "\nPartially accepted:";
            find();
        }
    }
}

void Init() {
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);

    LineDDA(p1.x, p1.y, p2.x, p2.y);

    LineDDA(xmin, ymin, xmax, ymin);
    LineDDA(xmax, ymin, xmax, ymax);
    LineDDA(xmax, ymax, xmin, ymax);
    LineDDA(xmin, ymax, xmin, ymin);

    p1.check();
    p2.check();
    test();

    glColor3f(1.0, 0.0, 0.0);
    LineDDA(p1.x, p1.y, p2.x, p2.y);
}

int main(int argc, char** argv) {
    std::cout << "\nEnter the xmin and ymin value of a rectangle:";
    std::cin >> xmin >> ymin;
    std::cout << "\nEnter the xmax and ymax value of a rectangle:";
    std::cin >> xmax >> ymax;
    std::cout << "\nEnter the x and y value of point p1:";
    std::cin >> p1.x >> p1.y;
    std::cout << "\nEnter the x and y value of point p2:";
    std::cin >> p2.x >> p2.y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Line Clipping");
    Init();
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}
