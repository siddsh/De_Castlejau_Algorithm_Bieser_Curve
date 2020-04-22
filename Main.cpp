//#include"glut.h"
#include "GL/freeglut.h"
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
struct vertex
{
	int x, y;
};
vector<vertex> v;
vertex merge(vertex v1, vertex v2, float t) 
{
	vertex out;
	out.x = t * v1.x + (1 - t) * v2.x;
	out.y = t * v1.y + (1 - t) * v2.y;
	return out;
}
vector<vertex> findOneLess(vector<vertex> vert, float t)
{
	vector<vertex> f;
	for (int i = 0; i < vert.size() - 1; i++)
	{
		f.push_back(merge(vert[i], vert[i + 1], t));
	}
	return f;
}
vertex findFinalVert(float t)
{
	vector<vertex> vtr;
	vtr = findOneLess(v, t);
	while (vtr.size() != 1)
	{
		vtr = findOneLess(vtr, t);
	}
	return vtr[0];
}
void renderScene(void) {
	//Clear all pixels

	glLoadIdentity();
	glOrtho(0.0, 1000, 0.0, 1000, -1.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	vertex p1, p2, p3, p4;
	//Point 1
	p1.x = 100;
	p1.y = 200;
	v.push_back(p1);
	//Point 2
	p2.x = 300;
	p2.y = 800;
	v.push_back(p2);
	//Point 3
	p3.x = 500;
	p3.y = 200;
	v.push_back(p3);
	//Point 4
	p4.x = 700;
	p4.y = 800;
	v.push_back(p4);
	/*glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);/*
	glVertex2i(p3.x, p3.y);
	glVertex2i(p4.x, p4.y);*/
	for (float i = 0; i < 1; i+=0.001)
	{
		vertex finalvert;
		finalvert = findFinalVert(i);
		glVertex2i(finalvert.x, finalvert.y);
	}
	glEnd();

	glutSwapBuffers();
}
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
void init() {
	//select clearing (background) color
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//initialize viewing values 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1000, 0.0, 1000, -1.0, 1.0);
}

int main(int argc, char** argv) {

	//Initialise GLUT with command-line parameters. 
	glutInit(&argc, argv);
	
	//Set Display Mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	//Set the window size
	glutInitWindowSize(750, 750);

	//Set the window position
	glutInitWindowPosition(100, 100);

	//Create the window
	glutCreateWindow("Biezer Curve");

	//Call init (initialise GLUT
	init();

	//Call "display" function
	glutDisplayFunc(renderScene);

	//Enter the GLUT event loop
	glutMainLoop();

	return 0;
}

