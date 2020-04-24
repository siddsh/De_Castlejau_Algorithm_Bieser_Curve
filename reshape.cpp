/** reshape function. This is to ensure that the aspect ratio is 
* maintained even when we change the window size */
void reshape(int w, int h)
{
    /** Set the viewport to be the entire drawing area of the window */
    glViewport(0, 0, w, h);

    /** Save the window size */
    winw = w;
    winh = h;

    /** Set up the projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);  /** Always go back to model/view mode */
}
