#include "GL/freeglut.h"
#include <iostream>
#include <math.h>
#include <vector>
#include "variables.cpp"
#include "mouse.cpp"
#include "keyboard.cpp"
#include "reshape.cpp"
using namespace std;

 void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0.0, 0.6, 0.6); /**Setting the colour aqua */
    glPointSize(4.0);
    glBegin(GL_POINTS);
    /** Drawing all the points that are in our vector array of type vertex*/
    for (int i = 0; i < obj.v.size(); i++)
    {
        glVertex2f(obj.v[i].x, obj.v[i].y);
    }
    glPointSize(2.0);
    /** Drawing the curve */
    for (double i = 0; i < 1; i += 0.001)
    {
        vertex final;
        final = obj.findFinalVert(i);
        glVertex2d(final.x, final.y);
        
    }
    glEnd();
    glColor3d(1.0, 1.0, 1.0);  /** White text */
    obj.printbitmap("Bezier Curve", 0.05, 0.95);
    obj.printbitmap("Press Left Mouse Button to add point", 0.05, 0.9);
    obj.printbitmap("Press Middle(Scroll) Mouse Button to drag the nearest point to a new location", 0.05, 0.85);
    obj.printbitmap("Press Right Mouse Button to Remove the nearest point", 0.05, 0.80);
    glutSwapBuffers();
}

/** Initializes GL states
* Called by main after window creation*/
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}


int main(int argc, char** argv)
{
    /** Initialize OpenGL/GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    /** Make a window */
    glutInitWindowSize(startwinsize, startwinsize);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bezier Curves");
    /** Initialize GL states & register callbacks */
    init();
    /** The glut display function to render our scene to the 
    * window we made */
    glutDisplayFunc(display);
    /** Glut idle function is defines what happens when our screen
    * is idle,i.e, we arent interacting with it */ 
    glutIdleFunc(display);
    /** to implement our keyboard strokes and allow our keyboard to interact with the window */
    glutKeyboardFunc(keyboard);
    /**to maintain the aspect ratio on changing the size of our window */
    glutReshapeFunc(reshape);
    /**to allow our mouse interacting with the window */
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
