#include <GL/glut.h>
#include <stdio.h>
#define ERRORTHRESHOLD 0.000001

int verticescount = 0;
int windowwidth = 800, windowheight = 800;
bool objectdrawn = false;

class Color {
public:
    float r, g, b;
};

Color bcolor, fcolor, icolor;

class Point {
public:
    float x, y;
};

class PolygonFiller {
public:
    Point points[20];
    static PolygonFiller* instance;

    float mouseytowindowy(float y) {
        return windowheight - y;
    }

    bool arevaluesequal(float x, float y) {
        return abs(x - y) < ERRORTHRESHOLD;
    }

    bool arecolorsequal(Color c1, Color c2) {
        return arevaluesequal(c1.r, c2.r) && arevaluesequal(c1.g, c2.g) && arevaluesequal(c1.b, c2.b);
    }

    void drawPolygon() {
        glColor3f(bcolor.r, bcolor.g, bcolor.b);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < verticescount; i++) {
            glVertex2i(points[i].x, points[i].y);
        }
        glEnd();
        glFlush();
    }

    void myInit() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0, windowwidth, 0, windowheight);
    }

    void drawcoloredpoint(float x, float y, Color color) {
        glBegin(GL_POINTS);
        glColor3f(color.r, color.g, color.b);
        glVertex2f(x, y);
        glEnd();
        glFlush();
    }

    void initcolors() {
        bcolor.r = 0.0f;
        bcolor.g = 0.0f;
        bcolor.b = 0.0f;

        fcolor.r = 1.0f;
        fcolor.g = 0.0f;
        fcolor.b = 0.0f;

        icolor.r = 1.0f;
        icolor.g = 1.0f;
        icolor.b = 1.0f;
    }

    void bf(int x, int y) {
        Color pixelcolor;
        glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, &pixelcolor);

        if (!arecolorsequal(pixelcolor, bcolor) && !arecolorsequal(pixelcolor, fcolor)) {
            drawcoloredpoint(x, y, fcolor);

            bf(x - 1, y);
            bf(x + 1, y);
            bf(x, y - 1);
            bf(x, y + 1);
        }
        glFlush();
    }

    void ff(int x, int y) {
        Color pixelcolor;
        glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, &pixelcolor);

        if (arecolorsequal(pixelcolor, icolor)) {
            drawcoloredpoint(x, y, fcolor);

            ff(x - 1, y);
            ff(x + 1, y);
            ff(x, y - 1);
            ff(x, y + 1);
        }
        glFlush();
    }

    static void staticMouseFunc(int button, int state, int mx, int my) {
        instance->myMouse(button, state, mx, my);
    }

    static void staticKeyboardFunc(unsigned char key, int mousex, int mousey) {
        instance->myKeyboard(key, mousex, mousey);
    }

    void myMouse(int button, int state, int mx, int my) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            if (objectdrawn) {
                objectdrawn = false;
                verticescount = 0;
            } else {
                points[verticescount].x = mx;
                points[verticescount].y = mouseytowindowy(my);
                verticescount++;
            }
        } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
            objectdrawn = true;

            drawPolygon();
        }
    }

    void myKeyboard(unsigned char key, int mousex, int mousey) {
        if (key == 'b') {
            bf(mousex, mouseytowindowy(mousey));
        }
        if (key == 'f') {
            ff(mousex, mouseytowindowy(mousey));
        }
    }

    void display() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glColor3f(0.0, 0.0, 0.0);
    }
};

PolygonFiller* PolygonFiller::instance = new PolygonFiller();

void displayWrapper() {
    PolygonFiller::instance->display();
}

int main(int argc, char** argv) {
    PolygonFiller::instance->initcolors();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowwidth, windowheight);
    glutCreateWindow("Color filling");
    PolygonFiller::instance->myInit();
    glutDisplayFunc(displayWrapper);
    glutMouseFunc(PolygonFiller::staticMouseFunc);
    glutKeyboardFunc(PolygonFiller::staticKeyboardFunc);
    glutMainLoop();

    return 0;
}
