#pragma once
using namespace std;
class vertex {
    public:
        /** a function to find the point of our bezier curve between any  2 points. We use the parametric equation of line
        * and loop t from 0 to 1 to cover all the points that may come between our two points. */
        vertex merge(vertex v1, vertex v2, double t) ;
        /** We use this function to find the joining coordinates that will arise for our bezier curves
        * using the vertices that have been given . The function merge is used here to calculate the coordinates and
        * then they are stored in a vertex f which is returned as final output*/
        vector<vertex> findOneLess(vector<vertex> vert, double t);
        /**This function is used to find the points at an interval of 0.01 factors to draw our bezier curve from
        * the given input vector of type vertex class*/
        vertex findFinalVert(double t);
        /** A function to calculate the distance between any 2 given points. We use this function
        * to find the nearest point as we can't accurately point on any given pixel when deleting or
        * scrolling through a function*/
        double distance(vertex v1, vertex v2);
        /** This function is used to find the nearest vertex from a given point where we clicked.
        * The distance is calculated between the point where we clicked and the vertex of the bezier curve*/
        int findNearestVertex(double x, double y);
        /** printbitmap
        * Prints the given string at the given raster position using GLUT bitmap fonts.
        */
        void printbitmap(const string msg, double x, double y);

        vector<vertex> v; /** we defined a vector of type vertex here. this will be used to store all the vertices that we use for drawing our bezier curve*/ 
        double x, y;

    private:
        
                      
};