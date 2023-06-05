/*
1. Implement DDA line drawing algorithm to draw: 
i) Simple Line
ii) Dotted Line
iii) Dashed Line 
iv) Solid line 
using mouse interface. Divide the screen in four quadrants with center as (0, 0). The line should work for all the slopes positive as well as negative.
*/
#include <iostream>
#include <GL/glut.h>
using namespace std;

int xa, ya, xb, yb;  // Variables to store coordinates of the line
int lineType;        // Variable to store the type of line
int Round(float num) // Function to round off a floating-point number to the nearest integer
{
    return (int)(num + 0.5);
}

void dda(int xa, int ya, int xb, int yb, int lineType)
{
    int dx, dy;
    dx = xb - xa;
    dy = yb - ya;

    int step;
    if (abs(dx) > abs(dy))
    {
        step = abs(dx);
    }
    else
    {
        step = abs(dy);
    }

    float xIncrement, yIncrement;

    xIncrement = dx / float(step);
    yIncrement = dy / float(step);

    float x, y;
    x = xa;
    y = ya;

    glBegin(GL_POINTS);

    int k;

    for (k = 0; k < step; k++)
    {
        switch (lineType)
        {
        case 1: // Simple Line
            x = x + xIncrement;
            y = y + yIncrement;
            glVertex2d(Round(x), Round(y));
            break;
        case 2: // Dotted Line
            if (k % 4 == 0)
            {
                glVertex2d(Round(x), Round(y));
            }
            x = x + xIncrement;
            y = y + yIncrement;
            break;
        case 3: // Dashed Line
            if (k % 8 != 0)
            {
                glVertex2d(Round(x), Round(y));
            }
            x = x + xIncrement;
            y = y + yIncrement;
            break;
        case 4: // Solid Line
            glPointSize(3.0);
            glBegin(GL_POINTS);
            x = x + xIncrement;
            y = y + yIncrement;
            glVertex2d(Round(x), Round(y));
            glEnd();
            glFlush();
            break;
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
        xb = x - 320;                  // Calculate the final x-coordinate relative to the center of the window
        yb = y - 240;                  // Calculate the final y-coordinate relative to the center of the window
        glColor3f(1.0, 0.0, 0.0);      // Set color to red
        dda(xa, ya, xb, yb, lineType); // Call the DDA function to draw the line
    }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glColor3f(0.0, 1.0, 0.0);     // Set color to green
    dda(-320, 0, 320, 0, 1);      // Draw x-axis using DDA algorithm
    dda(0, -240, 0, 240, 1);      // Draw y-axis using DDA algorithm
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
    glutCreateWindow("1st Assignment");
    gluOrtho2D(-320, 320, -240, 240); // Set the orthographic projection
    glutDisplayFunc(draw);            // Register the draw function to be called when the window needs to be redrawn
    glutMouseFunc(mouse1);            // Register the mouse function to handle mouse events
    glutMainLoop();                   // Start the main loop

    return 0;
}

//dharmendra@pandit:~$ g++ test.cpp -lGL -lGLU -lglut
//dharmendra@pandit:~$ ./a.out


//dharmendra@pandit:~$ g++ test.cpp -lGL -lGLU -lglut
//dharmendra@pandit:~$ ./a.out
