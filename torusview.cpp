#include <stdlib.h>
#include <math.h>
#include "glut.h"
#include<iostream>

using namespace std;

double deg2rad(double a)
{
	return 	a*3.1415926/180.0;
}

static GLfloat theta = 0.0;
static GLfloat phi = 0.0;
static GLdouble viewer[3];

/*****************************************************************/
void draw_torus(int which)
{
	glPushMatrix();

	
	
	if(which == 1)
	{
		glColor3f(1.0,1.0,1.0);
		glRotatef(90.0f,0.0f,1.0f,0.0f);
	}
	else
		glColor3f(0.0,0.0,1.0);

	//move, then rotate the Torus to be on the x,y axis
	glutSolidTorus(0.5f,4.5f,25,10);

	glPopMatrix();
}

//function to draw the 10 cylindars along the x axis
void draw_x_cylindar()
{
	int times;

	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);

	for(times = 0; times < 10; times++)
	{
		if(times % 2 == 0)
            glColor3f(1.0f, 0.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);

		glPushMatrix();
		glTranslatef(times, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

		gluCylinder(myCylinder, 0.1, 0.1, 1.0, 16, 16);
		glPopMatrix();
	}

	gluDeleteQuadric(myCylinder); 
}
/*****************************************************************/
//function to draw the 10 cylindars along the y axis
void draw_y_cylindar()
{
	int times;

	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);

	for(times = 0; times < 10; times++)
	{
		if(times % 2 == 0)
            glColor3f(1.0f, 1.0f, 1.0f);
		else
			glColor3f(0.0f, 1.0f, 0.0f);

		glPushMatrix();
		glTranslatef(0.0f, times, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		
		gluCylinder(myCylinder, 0.1, 0.1, 1.0, 16, 16);
		
		glPopMatrix();
	}

	gluDeleteQuadric(myCylinder); 
}
/*****************************************************************/
//function to draw the 10 cylindars along the z axis
void draw_z_cylindar()
{
	int times;

	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);

	for(times = 0; times < 10; times++)
	{
		if(times % 2 == 0)
            glColor3f(0.0f, 0.0f, 1.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);
		
		glPushMatrix();
		glTranslatef(0.0, 0.0f, times);
		
		gluCylinder(myCylinder, 0.1, 0.1, 1.0, 16, 16);
		
		glPopMatrix();
	}
}
/*****************************************************************/
// draw the coordinate system, added by Zhang
void draw_axes()
{
	// red X
	draw_x_cylindar();

	// green y
	draw_y_cylindar();

	// blue Z
	draw_z_cylindar();
}
/*****************************************************************/
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Update viewer position in modelview matrix */

	glLoadIdentity();

	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	draw_torus(0);
	draw_torus(1);

	draw_axes();

	glFlush();
	glutSwapBuffers();

}
/*****************************************************************/
void specKeys(int key, int x, int y)
{
	float delta = 10.0;

	if(key == GLUT_KEY_UP)
	{
		phi -= delta;
	}
	if(key == GLUT_KEY_DOWN)
	{
		phi += delta;
	}
	if(key == GLUT_KEY_LEFT)
	{
		theta -= delta;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		theta += delta;
	}
	if(theta == 90){
		cout<<"Testing"<<endl;
	}
	int asd = viewer[2];
	viewer[0] = 10.0 * sin(deg2rad(theta)) * sin(deg2rad(phi));
	//viewer[1] = 10.0 * sin(deg2rad(theta)) * cos(deg2rad(phi));
	viewer[2] = 10.0 * cos(deg2rad(theta));

	glutPostRedisplay();
}
/*****************************************************************/
void myReshape(int w, int h)
{
 glViewport(0, 0, w, h);

/* Use a perspective view */

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-10.0, 10.0, -10.0, 10.0, 0.0, 20.0);
 glMatrixMode(GL_MODELVIEW);
}
/*****************************************************************/
void main(int argc, char **argv)
{
	viewer[0] = 10.0 * sin(deg2rad(theta)) * sin(deg2rad(phi));
	int x = viewer[0];
	viewer[1] = 10.0 * sin(deg2rad(theta)) * cos(deg2rad(phi));
	int y = viewer[1];
	viewer[2] = 10.0 * cos(deg2rad(theta)); /* initial viewer location */
	int z = viewer[2];
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Tori Turn");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutSpecialFunc(specKeys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
