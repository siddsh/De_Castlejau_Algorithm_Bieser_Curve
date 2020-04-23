#include "GL/freeglut.h"
#include <iostream>
#include <math.h>
#include <vector>
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
struct vertex                   // a structure to store the x and y coordinates of each point
{
    double x, y;
};
vector<vertex> v;               //we defined a vector of type vertex here. this will be used to store all the vertices that we use for drawing our bezier curve
 
/* a function to find the point of our bezier curve between any  2 points. We use the parametric equation of line
and loop t from 0 to 1 to cover all the points that may come between our two points. */
vertex merge(vertex v1, vertex v2, double t)    
{
    vertex out;
    out.x = t * v1.x + (1 - t) * v2.x;
    out.y = t * v1.y + (1 - t) * v2.y;
    return out;
}
/*We use this function to find the joining coordinates that will arise for our bezier curves
using the vertices that have been given . The function merge is used here to calculate the coordinates and
then they are stored in a vertex f which is returned as final output*/
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
/**/
vertex findFinalVert(double t)
{
    /*We put this if condition to ensure that we have atleast 2 points, which is the
    minimum requirement for drawing a bezier curve.*/
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
/*A function to calculate the distance between any 2 given points. We use this function
to find the nearest point as we can't accurately point on any given pixel when deleting or
scrolling through a function*/
double distance(vertex v1, vertex v2)
{
    return ((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y));
}
/*This function is used to find the nearest vertex from a given point where we clicked.
The distance is calculated between the point where we clicked and the vertex of the bezier curve*/
int findNearestVertex(double x, double y)
{
    double minDistance;
    /*To calculate distance, we need a minimum of two points. Hence the condition checking here*/
    if (v.size() < 2)
    {
        vertex vecto{};
        vecto.x = NULL;
        vecto.y = NULL;
   
        return NULL;
    }
    vertex vtx;
    vtx.x = x;
    vtx.y = y;
    int index = 0;
    minDistance = distance(vtx, v[0]);
    for (int i = 1; i < v.size() ; i++)
    {
        if (minDistance > distance(vtx, v[i]))
        {
             minDistance = distance(vtx, v[i]);
            index = i;
        }
   
    }
    return index;
}
/* printbitmap
 Prints the given string at the given raster position using GLUT bitmap fonts.
*/
void printbitmap(const string msg, double x, double y)
{
    glRasterPos2d(x, y);
    for (string::const_iterator ii = msg.begin();
        ii != msg.end();
        ++ii)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *ii);
    }
   
}/* This is our rendering function to display our scene*/
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0.0, 0.6, 0.6); //Setting the colour aqua
    glPointSize(4.0);
    glBegin(GL_POINTS);
    /*Drawing all the points that are in our vector array of type vertex*/
    for (int i = 0; i < v.size(); i++)
    {
        glVertex2f(v[i].x, v[i].y);
    }
    glPointSize(2.0);
    /* Drawing the updated points , after the clicks */
    for (double i = 0; i < 1; i += 0.001)
    {
        vertex final;
        final = findFinalVert(i);
        glVertex2d(final.x, final.y);
    }
    glEnd();
    glColor3d(1.0, 1.0, 1.0);  // White text
    printbitmap("Bezier Curve", 0.05, 0.95);
    printbitmap("Press Left Mouse Button to add point", 0.05, 0.9);
    printbitmap("Press Middle(Scroll) Mouse Button to drag the nearest point to a new location", 0.05, 0.85);
    printbitmap("Press Right Mouse Button to Remove the nearest point", 0.05, 0.80);
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
        v.push_back(vert);
        //glutPostRedisplay();  // Left button has changed; redisplay!
    }
    /*When our right button of the mouse is pressed , we want to 
    delete that point from our set of points to draw the bezier curve and hence
    the curve should be changed accordingly*/
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if (v.size() == 0)
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
        nearestVertexIndex = findNearestVertex(oglx, ogly);
        cout << "NEAREST :" << nearestVertexIndex << endl;
        /*Removing the point from our original vertex containing the points used to
        draw the bezier curve. After removing , we must update our bezier curve*/
        v.erase(v.begin() + nearestVertexIndex);
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
        nearVtx = findNearestVertex(oglx, ogly);
        cout << "NEAR VERTEX: " << nearVtx << endl;
        cout << "X: " << v[nearVtx].x;
        cout << "\tY: " << v[nearVtx].y << endl;
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
        v[nearVtx].x = oglx;
        v[nearVtx].y = ogly;
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
