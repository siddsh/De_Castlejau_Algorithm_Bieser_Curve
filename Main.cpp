//#include"glut.h"
#include "GL/freeglut.h"
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

// simplemouse.cpp
// by Glenn G. Chappell
// September 2003
//
// For CS 381
// Simple Mouse Demo
//
// Draws a red box at the mouse position
// whenever the left mouse button is down.


// Global variables
// Window/viewport
const int startwinsize = 400; // Starting window width & height, in pixels
int winw, winh;               // Window width & height, in pixels, saved by reshape

// Mouse
bool mouseleftdown = false;   // True if mouse LEFT button is down.
                              // Saved by mouse.
int mousex, mousey;           // Mouse x,y coords, in GLUT format (pixels from upper-left corner).
                              // Only guaranteed to be valid if a mouse button is down.
                              // Saved by mouse, motion.

// Keyboard
const int ESCKEY = 27;        // ASCII value of escape character

// Other
const double pointsize = 40;  // Size of point
struct vertex
{
    double x, y;
};
vector<vertex> v;
vertex merge(vertex v1, vertex v2, double t)
{
    vertex out;
    out.x = t * v1.x + (1 - t) * v2.x;
    out.y = t * v1.y + (1 - t) * v2.y;
    return out;
}
vector<vertex> findOneLess(vector<vertex> vert, double t)
{
    if (vert.size() != 1)
    {
        vector<vertex> f;
        for (int i = 0; i < vert.size() - 1; i++)
        {
            f.push_back(merge(vert[i], vert[i + 1], t));
        }
        return f;
    }
}
vertex findFinalVert(double t)
{
    if (v.size() < 2)
    {
        vertex vecto{};
        vecto.x = NULL;
        vecto.y = NULL;
        return vecto;
    }

    vector<vertex> vtr;
    vtr = findOneLess(v, t);
    while (vtr.size() != 1)
    {
        vtr = findOneLess(vtr, t);
    }
    return vtr[0];
}

// printbitmap
// Prints the given string at the given raster position
//  using GLUT bitmap fonts.
// You probably don't want any rotations in the model/view
//  transformation when calling this function.
void printbitmap(const string msg, double x, double y)
{
    glRasterPos2d(x, y);
    for (string::const_iterator ii = msg.begin();
        ii != msg.end();
        ++ii)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *ii);
    }
}


// display
// The GLUT display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Make a small box at the mouse position, if the LEFT button is down
    // Draw the box
    glColor3d(0.0, 0.6, 0.6);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < v.size(); i++)
    {
        glVertex2f(v[i].x, v[i].y);
    }
    for (double i = 0; i < 1; i += 0.001)
    {
        vertex final;
        final = findFinalVert(i);
        glVertex2d(final.x, final.y);
    }
    glEnd();
    // Documentation
    glColor3d(1.0, 1.0, 1.0);  // White text
    printbitmap("Bezier Curve", 0.05, 0.95);
    printbitmap("Press Left mouse button to add point", 0.05, 0.9);
    printbitmap("Press Middle Button to drag the nearest point", 0.05, 0.85);
    printbitmap("Press Right Button to Remove the nearest point", 0.05, 0.80);
    glutSwapBuffers();
}


// mouse
// The GLUT mouse function
void mouse(int button, int state, int x, int y)
{
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseleftdown = (state == GLUT_DOWN);
        mousex = x;
        mousey = y;
        double oglx = double(mousex) / winw;
        double ogly = 1 - double(mousey) / winh;
        cout << "X: " << oglx;
        cout << "Y: " << ogly << endl;
        vertex vert;
        vert.x = oglx;
        vert.y = ogly;
        v.push_back(vert);
        //glutPostRedisplay();  // Left button has changed; redisplay!
    }

    // Save the mouse position
    
}


// motion
// The GLUT motion function
void motion(int x, int y)
{
    // We only do anything if the left button is down
    if (mouseleftdown)
        //glutPostRedisplay();

    // Save the mouse position
    mousex = x;
    mousey = y;
}


// idle
// The GLUT idle function
void idle()
{
    // Print OpenGL errors, if there are any (for debugging)
    if (GLenum err = glGetError())
    {
        cerr << "OpenGL ERROR: " << gluErrorString(err) << endl;
    }
}


// keyboard
// The GLUT keyboard function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ESCKEY:  // ESC: Quit
        exit(0);
        break;
    }
}


// reshape
// The GLUT reshape function
void reshape(int w, int h)
{
    // Set the viewport to be the entire drawing area of the window
    glViewport(0, 0, w, h);

    // Save the window size
    winw = w;
    winh = h;

    // Set up the projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);  // Always go back to model/view mode
}


// init
// Initializes GL states
// Called by main after window creation
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}


int main(int argc, char** argv)
{
    // Initialize OpenGL/GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Make a window
    glutInitWindowSize(startwinsize, startwinsize);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bezier Curves");
   
    // Initialize GL states & register callbacks
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    // Do something
    glutMainLoop();

    return 0;
}