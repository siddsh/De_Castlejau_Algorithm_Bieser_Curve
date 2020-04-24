#include "vertex.h"
using namespace std;
vertex vertex::merge(vertex v1, vertex v2, double t){
    vertex out;
    out.x = t * v1.x + (1 - t) * v2.x;
    out.y = t * v1.y + (1 - t) * v2.y;
    return out;
}
vector<vertex> vertex::findOneLess(vector<vertex> vert, double t){
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
vertex vertex::findFinalPt(double t, vector<vertex> ver)
{
    if (ver.size() < 1)
        return vertex();

    if (ver.size() == 1)
    {
        return ver[0];
    }
    ver = findOneLess(ver, t);
    return findFinalPt(t, ver);    
}
double vertex::distance(vertex v1, vertex v2){
    return ((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y));
}
int vertex::findNearestVertex(double x, double y){
    double minDistance;
    /** To calculate distance, we need a minimum of two points. Hence the condition checking here*/
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
void vertex::printbitmap(const string msg, double x, double y){
    glRasterPos2d(x, y);
    for (string::const_iterator ii = msg.begin();
        ii != msg.end();
        ++ii)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *ii);
    }
}