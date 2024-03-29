/* gasket.c   */

/* E. Angel, Interactive Computer Graphics */
/* A Top-Down Approach with OpenGL, Third Edition */
/* Addison-Wesley Longman, 2003 */

/* Two-Dimensional Sierpinski Gasket          */
/* Generated Using Randomly Selected Vertices */
/* And Bisection                              */
/* gasket2.c   */

/* E. Angel, Interactive Computer Graphics */
/* A Top-Down Approach with OpenGL, Third Edition */
/* Addison-Wesley Longman, 2003 */

/* Recursive subdivision of triangle to form Sierpinski gasket */

// #include <GL/glut.h>
#include "glut.h"

typedef float point2[2];

/* initial triangle */

point2 v[]={{-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15}};

int n;

void triangle( point2 a, point2 b, point2 c)

/* display one triangle  */
{
    glBegin(GL_TRIANGLES);
       glVertex2fv(a);
       glVertex2fv(b);
       glVertex2fv(c);
    glEnd();
}

void divide_triangle(point2 a, point2 b, point2 c, int m)
{

/* triangle subdivision using vertex numbers */

    point2 v0, v1, v2;
    int j;
    if(m>0) 
    {
        for(j=0; j<2; j++) v0[j]=(a[j]+b[j])/2;
        for(j=0; j<2; j++) v1[j]=(a[j]+c[j])/2;
        for(j=0; j<2; j++) v2[j]=(b[j]+c[j])/2;
        divide_triangle(a, v0, v1, m-1);
        divide_triangle(c, v1, v2, m-1);
        divide_triangle(b, v2, v0, m-1);
    }
    else(triangle(a,b,c)); /* draw triangle at end of recursion */
}


void display(void)
{


    glClear(GL_COLOR_BUFFER_BIT);
	divide_triangle(v[0], v[1], v[2], n);
    glFlush();
}

void myinit()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0,0.0,0.0);
}

void
main(int argc, char **argv)
{
    n=4;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Gasket");
    glutDisplayFunc(display);
	myinit();
    glutMainLoop();
}

