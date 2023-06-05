#include <iostream>
#include <GL/glut.h>
using namespace std;

int xa, ya, xb, yb; // Variables to store coordinates of the line
int lineType;       // Variable to store the type of line

void bresenham(int xa, int ya, int xb, int yb, int lineType)
{
    int dx = abs(xb - xa);
    int dy = abs(yb - ya);
    // int slope_x = (xa < xb) ? 1 : -1;
    // int slope_y = (ya < yb) ? 1 : -1;

    int slope_x, slope_y;
    if (xa < xb)
    {
        slope_x = 1;
    }
    else
    {
        slope_x = -1;
    }

    if (ya < yb)
    {
        slope_y = 1;
    }
    else
    {
        slope_y = -1;
    }

    int error = dx - dy;

    glBegin(GL_POINTS);

    while (true)
    {
        switch (lineType)
        {
        case 1: // Simple Line
            glVertex2d(xa, ya);
            break;
        case 2: // Dotted Line
            if ((xa + ya) % 5 == 0)
            {
                glVertex2d(xa, ya);
            }
            break;
        case 3: // Dashed Line
            if ((xa + ya) %4 != 0)
            {
                glVertex2d(xa, ya);
            }
            break;
        case 4: // Solid Line
           
            glPointSize(6.0);
            glBegin(GL_POINTS);
            glVertex2d(xa, ya);
            glEnd();
            glFlush();
            break;
        }
        if (xa == xb && ya == yb)
        {
            break;
        }

        int e2 = 2 * error;
        if (e2 > -dy)
        {
            error -= dy;
            xa += slope_x;
        }
        if (e2 < dx)
        {
            error += dx;
            ya += slope_y;
        }
    }

    glEnd();
    glFlush();
}

void mouse1(int button, int state, int x, int y)
{
    y = 440 - y; // Adjust the y-coordinate to match the window's coordinate system
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xa = x - 320; // Calculate the initial x-coordinate relative to the center of the window
        ya = y - 240; // Calculate the initial y-coordinate relative to the center of the window
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        xb = x - 320;                        // Calculate the final x-coordinate relative to the center of the window
        yb = y - 240;                        // Calculate the final y-coordinate relative to the center of the window
        glColor3f(1.0, 0.0, 0.0);            // Set color to red
        bresenham(xa, ya, xb, yb, lineType); // Call the bresenham function to draw the line
    }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
    glColor3f(0.0, 1.0, 0.0);      // Set color to green
    bresenham(-320, 0, 320, 0, 1); // Draw x-axis using DDA algorithm
    bresenham(0, -240, 0, 240, 1); // Draw y-axis using DDA algorithm
}

int main(int argc, char **argv)
{
    cout << "Enter \n";
    cout << "1. Simple Line \n";
    cout << "2. Dotted Line \n";
    cout << "3. Dashed Line \n";
    cout << "4. Solid Line \n";
    cin >> lineType; // Read the line type from user input

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Line Drawing");
    gluOrtho2D(-320, 320, -240, 240); // Set the orthographic projection
    glutDisplayFunc(draw);            // Register the draw function to be called when the window needs to be redrawn
    glutMouseFunc(mouse1);            // Register the mouse function to handle mouse events
    glutMainLoop();                   // Start the main loop

    return 0;
}
