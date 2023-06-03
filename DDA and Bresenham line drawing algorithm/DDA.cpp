/*
2. Implement DDA and line drawing algorithm to draw: 
i) Simple Line 
ii) Dotted Line
iii) Dashed Line
iv) Solid line 
using mouse interface Divide the screen in four quadrants with
center as (0, 0). The line should work for all the slopes positive as well as negative.
*/
#include <iostream>
#include <GL/glut.h>
using namespace std;
int xa, ya, xb, yb;
int lineType;

int Round(float a)
{
    return (int)(a + 0.5);
}

void ddaline(int xa, int ya, int xb, int yb, int lineType)
{
    int dx, dy, steps;
    dx = xb - xa;
    dy = yb - ya;

    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    float xincrement, yincrement;
    xincrement = dx / (float)(steps);
    yincrement = dy / (float)(steps);

    float x, y;
    x = xa;
    y = ya;

    glBegin(GL_POINTS);
    glVertex2d(Round(x), Round(y));

    int k;
    for (k = 0; k < steps; k++)
    {
        if (lineType == 4)
        {
            glPointSize(3.0);
            x = x + xincrement;
            y = y + yincrement;
            glVertex2d(Round(x), Round(y));
        }
        if (lineType == 3)
        {
            if (k % 4 != 0)
            {
                glVertex2d(Round(x), Round(y));
            }
            x = x + xincrement;
            y = y + yincrement;
        }
        else if (lineType == 2)
        {
            if (k % 4 == 0)
            {
                glVertex2d(Round(x), Round(y));
            }
            x = x + xincrement;
            y = y + yincrement;
        }
        else
        {
            x = x + xincrement;
            y = y + yincrement;
            glVertex2d(Round(x), Round(y));
        }
    }

    glEnd();
    glFlush();
}

void mouse1(int button, int state, int x, int y)
{
    y = 480 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xa = x - 320; // Shifting x-coordinate to center (0,0)
        ya = y - 240; // Shifting y-coordinate to center (0,0)
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        xb = x - 320; // Shifting x-coordinate to center (0,0)
        yb = y - 240; // Shifting y-coordinate to center (0,0)
        glColor3f(1.0, 0.0, 0.0);
        ddaline(xa, ya, xb, yb, lineType);
    }
}
void Init()
{
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    gluOrtho2D(-320, 320, -240, 240); // Set the coordinate system
}
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    ddaline(-320, 0, 320, 0, 1); // X-axis
    ddaline(0, -240, 0, 240, 1); // Y-axis
}

int main(int argc, char **argv)
{
    cout << "Enter what type of line to draw \n1. Simple \n2. Dotted \n3. Dashed \n4. Solid :-  ";
    cin >> lineType;

    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA Line");
    Init();
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse1);

    glutMainLoop();
    return 0;
}
