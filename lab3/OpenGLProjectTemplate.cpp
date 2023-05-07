#include <GL/glut.h>
#include <cmath>

/*void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t < 20 * 3.14159; t += 0.1) {
        float x = 20 * cos(t);
        float y = 20 * sin(t);
        float z = t / 2;
        glVertex3f(x, y, z);
    }
    glEnd();
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Helix");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
*/