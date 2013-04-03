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

typedef float point2[25];


/* initial triangle */

point2 v[]={{0.0, 0.0}, {-5.0, -10.0}, {5.0,-10.0},
			{0.0, 0.0}, {5.0,-10.0}, {10.0, -5.0},
			{0.0, 0.0}, {10.0, 5.0}, {10.0, -5.0},
			{0.0, 0.0}, {10.0, 5.0}, {5.0, 10.0},
			{0.0, 0.0}, {5.0, 10.0}, {-5.0, 10.0},
			{0.0, 0.0}, {-5.0, 10.0}, {-10.0, 5.0},
			{0.0, 0.0}, {-10.0, 5.0}, {-10.0, -5.0},
			{0.0, 0.0}, {-10.0, -5.0}, {-5.0, -10.0},
			//wall starts here
			{0.0, 0.0}, {0.0, 15.0}, {10.0, 0.0},
			{10.0, 0.0}, {10.0, 15.0}, {0.0, 15.0},};

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

void wall()
{
	glPushMatrix();
	glTranslatef(-5.0,-10.0,0);
	//glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	divide_triangle(v[24], v[25], v[26], n);
	divide_triangle(v[27], v[28], v[29], n);
	glPopMatrix();
}

void display(void)
{


    glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	divide_triangle(v[0], v[1], v[2], n);
	divide_triangle(v[3], v[4], v[5], n);
	divide_triangle(v[6], v[7], v[8], n);
	divide_triangle(v[9], v[10], v[11], n);
	divide_triangle(v[12], v[13], v[14], n);
	divide_triangle(v[15], v[16], v[17], n);
	divide_triangle(v[18], v[19], v[20], n);
	divide_triangle(v[21], v[22], v[23], n);
	glPopMatrix();
	int degr=0;
	for(int i=0;i<8;i++)
	{
	glPushMatrix();
	glRotatef(degr, 0.0f, 0.0f, 1.0f);
	degr+=45;
	wall();
	glPopMatrix();
	}
    glFlush();
}

void myinit()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20.0, 20.0, -20.0, 20.0);
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
