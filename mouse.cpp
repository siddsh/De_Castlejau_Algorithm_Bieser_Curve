int nearVtx;
/** mouse
* The GLUT mouse function
*/

void mouse(int button, int state, int x, int y)
{
    /** When left button of our mouse is pressed , we want to add a new point
    * and change our bezier curve accordingly */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mousex = x;
        mousey = y;
        /** Getting the x-y position of the cursor 
        * when the left button is clicked*/
        double oglx = double(mousex) / winw;
        double ogly = 1 - double(mousey) / winh;
        /** We print out the co-ordinates to see that the axes 
        * and glutOrtho function is working correctly*/
        cout << "X: " << oglx;
        cout << "\tY: " << ogly << endl;
        vertex vert;
        vert.x = oglx;
        vert.y = ogly;
        /** Adding this to our original array of all the points as any point where the left click is pressed
        * should be drawn and the bezier curve should be changed accordingly*/
        obj.v.push_back(vert);
    }
    /** When our right button of the mouse is pressed , we want to 
    * delete that point from our set of points to draw the bezier curve and hence
    * the curve should be changed accordingly*/
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if (obj.v.size() == 0)
        {
            cout << "No Points To Remove" << endl;
            return;
        }
        mousex = x;
        mousey = y;
        /** Getting the x-y position of the cursor 
        * when the right button is clicked*/
        double oglx = double(mousex) / winw;
        double ogly = 1 - double(mousey) / winh;
        cout << "X: " << oglx;
        cout << "Y: " << ogly << endl;
        int nearestVertexIndex;
        /** We find the nearest point which is used to draw our bezier curve
        * and remove that point. This is done because we cant always have pin point 
        * precision in removing a point.*/
        nearestVertexIndex = obj.findNearestVertex(oglx, ogly);
        cout << "NEAREST :" << nearestVertexIndex << endl;
        /** Removing the point from our original vertex containing the points used to
        * draw the bezier curve. After removing , we must update our bezier curve*/
        obj.v.erase(obj.v.begin() + nearestVertexIndex);
    }
    /** Now we want to drag a point from the point where we click our middle
    * button of our mouse and then draw it at the point where we release 
    * the middle button of our mouse*/
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        nearVtx = -1;
        mousex = x;
        mousey = y;
        /** Getting the x-y position of the cursor 
        * when the middle button is clicked*/
        double oglx = double(mousex) / winw;
        double ogly = 1 - double(mousey) / winh;
        cout << "X: " << oglx;
        cout << "\tY: " << ogly << endl;
        /** We find the nearest point which is used to draw our bezier curve
        * and select that point. This is done because we cant always have pin point 
        * precision in selecting a point.*/
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
        /** Getting the x-y position of the cursor 
        * when the middle button is released*/
        double oglx = double(mousex) / winw;
        double ogly = 1 - double(mousey) / winh;
        cout << "X: " << oglx;
        cout << "Y: " << ogly << endl;
        /** Now we change the point where our middle button was released in
        * the original vertex vector and update the bezier curve accordingly*/
        obj.v[nearVtx].x = oglx;
        obj.v[nearVtx].y = ogly;
        nearVtx = -1;
    }
    /** Save the mouse position */
    
}