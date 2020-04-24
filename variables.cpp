#pragma once
#include "vertex.cpp"

vertex obj;


/** Global variables */
/** Window/viewport */
const int startwinsize = 600; /** Starting window width & height, in pixels */
int winw, winh;               /** Window width & height, in pixels, saved by reshape */
 
/** Mouse */
bool mouseleftdown = false;   /** True if mouse LEFT button is down./**glutMotionFunc(motion); */
    /** Do something */
    
                              /** Saved by mouse. */
int mousex, mousey;           /** Mouse x,y coords, in GLUT format (pixels from upper-left corner). */
                              /** Only guaranteed to be valid if a mouse button is down. */
                              /** Saved by mouse, motion. */
 
/** Keyboard */
const int ESCKEY = 27;        /** ASCII value of escape character */
 
/** Other */
const double pointsize = 40;  /** Size of point */
/** Instance of our class here. We called the object here
* and will use its functions accordingly. This is global as
* it has been used across many functions*/
