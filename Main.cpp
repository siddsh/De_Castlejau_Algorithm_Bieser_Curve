#include "GL/freeglut.h"
#include <iostream>
#include <math.h>
#include <vector>
#include "vertex.cpp"
using namespace std;
 
// Global variables
// Window/viewport
const int startwinsize = 600; // Starting window width & height, in pixels
int winw, winh;               // Window width & height, in pixels, saved by reshape
 
// Mouse
bool mouseleftdown = false;   // True if mouse LEFT button is down.//glutMotionFunc(motion);
    // Do something
    
                              // Saved by mouse.
int mousex, mousey;           // Mouse x,y coords, in GLUT format (pixels from upper-left corner).
                              // Only guaranteed to be valid if a mouse button is down.
                              // Saved by mouse, motion.
 
// Keyboard
const int ESCKEY = 27;        // ASCII value of escape character
 
// Other
const double pointsize = 40;  // Size of point
/*Instance of our class here. We called the object here
and will use its functions accordingly. This is global as
it has been used across many functions*/
vertex obj;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0.0, 0.6, 0.6); //Setting the colour aqua
    glPointSize(4.0);
    glBegin(GL_POINTS);
    /*Drawing all the points that are in our vector array of type vertex*/
    for (int i = 0; i < obj.v.size(); i++)
    {
        glVertex2f(obj.v[i].x, obj.v[i].y);
    }
    glPointSize(2.0);
    /* Drawing the curve */
    for (double i = 0; i < 1; i += 0.001)
    {
        vertex final;
        final = obj.findFinalVert(i);
        glVertex2d(final.x, final.y);
        
    }
    glEnd();
    glColor3d(1.0, 1.0, 1.0);  // White text
    obj.printbitmap("Bezier Curve", 0.05, 0.95);
    obj.printbitmap("Press Left Mouse Button to add point", 0.05, 0.9);
    obj.printbitmap("Press Middle(Scroll) Mouse Button to drag the nearest point to a new location", 0.05, 0.85);
    obj.printbitmap("Press Right Mouse Button to Remove the nearest point", 0.05, 0.80);
    glutSwapBuffers();
}

// mouse
// The GLUT mouse function
int nearVtx;
void mouse(int button, int state, int x, int y)
{
    /* When left button of our mouse is pressed , we want to add a new point
    and change our bezier curve accordingly */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mousex = x;
        mousey = y;
        /* Getting the x-y position of the cursor 
        when the left button is clicked*/
        double oglx = double(mousex) / winw;
        double ogly = 1 - double(mousey) / winh;
        /* We print out the co-ordinates to see that the axes 
        and glutOrtho function is working correctly*/
        cout << "X: " << oglx;
        cout << "\tY: " << ogly << endl;
        vertex vert;
        vert.x = oglx;
        vert.y = ogly;
        /*Adding this to our original array of all the points as any point where the left click is pressed
        should be drawn and the bezier curve should be changed accordingly*/
        obj.v.push_back(vert);
        //glutPostRedisplay();  // Left button has changed; redisplay!
    }
    /*When our right button of the mouse is pressed , we want to 
    delete that point from our set of points to draw the bezier curve and hence
    the curve should be changed accordingly*/
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if (obj.v.size() == 0)
        {
            cout << "No Points To Remove" << endl;
            return;
        }
        mousex = x;
        mousey = y;
        /* Getting the x-y position of the cursor 
        when the right button is clicked*/
        double oglx = double(mousex) / winw;
        double ogly = 1 - double(mousey) / winh;
        cout << "X: " << oglx;
        cout << "Y: " << ogly << endl;
        int nearestVertexIndex;
        /*We find the nearest point which is used to draw our bezier curve
        and remove that point. This is done because we cant always have pin point 
        precision in removing a point.*/
        nearestVertexIndex = obj.findNearestVertex(oglx, ogly);
        cout << "NEAREST :" << nearestVertexIndex << endl;
        /*Removing the point from our original vertex containing the points used to
        draw the bezier curve. After removing , we must update our bezier curve*/
        obj.v.erase(obj.v.begin() + nearestVertexIndex);
    }
    /*Now we want to drag a point from the point where we click our middle
    button of our mouse and then draw it at the point where we release 
    the middle button of our mouse*/
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        nearVtx = -1;
        mousex = x;
        mousey = y;
        /* Getting the x-y position of the cursor 
        when the middle button is clicked*/
        double oglx = double(mousex) / winw;
        double ogly = 1 - double(mousey) / winh;
        cout << "X: " << oglx;
        cout << "\tY: " << ogly << endl;
        /*We find the nearest point which is used to draw our bezier curve
        and select that point. This is done because we cant always have pin point 
        precision in selecting a point.*/
        nearVtx = obj.findNearestVertex(oglx, ogly);
        cout << "NEAR VERTEX: " << nearVtx << endl;
        cout << "X: " << obj.v[nearVtx].x;
        cout << "\tY: " << obj.v[nearVtx].y << endl;
    }
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
    {
        cout << "UP" << endl;
        mouseleftdown = (state == GLUT_DOWN);
        mousex = x;
        mousey = y;
        /* Getting the x-y position of the cursor 
        when the middle button is released*/
        double oglx = double(mousex) / winw;
        double ogly = 1 - double(mousey) / winh;
        cout << "X: " << oglx;
        cout << "Y: " << ogly << endl;
        /*Now we change the point where our middle button was released in
         the original vertex vector and update the bezier curve accordingly*/
        obj.v[nearVtx].x = oglx;
        obj.v[nearVtx].y = ogly;
        nearVtx = -1;
    }
    // Save the mouse position
    
}
/*The glut keyboard function. We use it here
because we want our program to end when we press the escape key */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ESCKEY:  // ESC: Quit
        exit(0);
        break;
    }
}


/*reshape function. This is to ensure that the aspect ratio is 
maintained even when we change the window size */
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

/* Initializes GL states
 Called by main after window creation*/
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
    /* The glut display function to render our scene to the 
    window we made */
    glutDisplayFunc(display);
    /* Glut idle function is defines what happens when our screen
    is idle,i.e, we arent interacting with it */ 
    glutIdleFunc(display);
    // to implement our keyboard strokes and allow our keyboard to interact with the window
    glutKeyboardFunc(keyboard);
    //to maintain the aspect ratio on changing the size of our window
    glutReshapeFunc(reshape);
    //to allow our mouse interacting with the window
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
