/** The glut keyboard function. We use it here
* because we want our program to end when we press the escape key */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ESCKEY:  /** ESC: Quit */
        exit(0);
        break;
    }
}
