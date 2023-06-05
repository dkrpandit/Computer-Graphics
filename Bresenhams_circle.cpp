double mouseXToWindowX(double x) {
   return x - windowWidth/2;
}

double mouseYToWindowY(double y) {
   return windowHeight/2 - y;
}

double distBetween2Points(double x1, double y1, double x2, double y2) {
   return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void mouseFunc(int button, int action, int xMouse, int yMouse) {
   if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
       if (mousePressedBefore == false) {
           x = xMouse;
           y = yMouse;
           mousePressedBefore = true;
       }
       else {
           double radius = distBetween2Points(xMouse, yMouse, x , y);
           BresenhamCircleDrawingAlgo(mouseXToWindowX(x), mouseYToWindowY(y), radius);
           mousePressedBefore = false;
       }
       glFlush();
   }
}

int main(int argc, char** argv) {
   windowWidth = 800;
   windowHeight = 800;

   glutInit(&argc, argv);
   glutInitWindowPosition(0, 0);
   glutInitWindowSize(windowWidth, windowHeight);
   glutCreateWindow("Assignment3");

   Init();
   glutDisplayFunc(myDisplay);
   glutMouseFunc(mouseFunc);

   glutMainLoop();

  return 0;
}
