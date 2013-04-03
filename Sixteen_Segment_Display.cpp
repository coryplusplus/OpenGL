#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "glut.h"
using namespace std;


double deg2rad(double a)
{
	return 	a*3.1415926/180.0;
}

int letter = 48;

static GLfloat theta = 0.0;
static GLfloat phi = 0.0;
static GLdouble viewer[3];

void setletter(char x)
{
	letter = (int) x;
}

void draw_seg1()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(0.1f, 0.7f, 0.4f);
	glPushMatrix();
	glTranslatef(-3.5, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg2()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(2.0f, 0.4f, 0.9f);
	glPushMatrix();
	glTranslatef(-3.5, 2.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg3()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 3.0f, 1.0f);
	glPushMatrix();
	glTranslatef(-3.5, 2.5f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg4()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(0.0f, 1.0f, 4.0f);
	glPushMatrix();
	glTranslatef(-1.75, 2.5f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg5()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(4.0f, 4.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, 2.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg6()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(0.2f, 0.5f, 0.9f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg7()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.2f, 1.0f);
	glPushMatrix();
	glTranslatef(-1.75, -2.5f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg8()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.4f, 0.1f);
	glPushMatrix();
	glTranslatef(-3.5, -2.5f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg9()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(0.1f, 0.1f, 0.8f);
	glPushMatrix();
	glTranslatef(-3.5f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg10()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(0.8f, 0.1f, 0.3f);
	glPushMatrix();
	glTranslatef(-1.75, 2.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg11()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(0.6f, 0.6f, 0.1f);
	glPushMatrix();
	glTranslatef(-1.75, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg12()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(0.23f, 0.45f, 0.65f);
	glPushMatrix();
	glTranslatef(-1.75, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg13()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(0.34f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75f, 0.0f, 0.0f);
	glRotatef(-90.0f, 1.5f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 3.0, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg14()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.2f, 0.5f);
	glPushMatrix();
	glTranslatef(-1.75, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(145.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 3.0, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_seg15()
{
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-35.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 3.0, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}
}

void draw_seg16()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glTranslatef(-1.75f, 0.0f, 0.0f);
	glRotatef(90.0f, 1.5f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 3.0, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	
		//A = 1,2,3,4,5,6,9,11
		if(letter == 'A')
		{
		glTranslatef(-8.0f,8.0f,0.0f);
		glScalef(0.5f,0.5f,0.5f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();
		}

		//B = 3,4,5,6,7,8,10,11,12
		if(letter == 'B')
		{
		glTranslatef(-7.0f,8.0f,0.0f);
		glScalef(0.5f,0.5f,0.5f);
		draw_seg3();draw_seg4();draw_seg5();draw_seg6();
		draw_seg7();draw_seg8();draw_seg10();draw_seg11();draw_seg12();
		}

		//C = 1,2,3,4,7,8
		if(letter == 'C')
		{
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg7();draw_seg8();
		}

		//D = 3,4,5,6,7,8,10,12
		if(letter == 'D')
		{
		draw_seg3();draw_seg4();draw_seg5();draw_seg6();
		draw_seg7();draw_seg8();draw_seg10();draw_seg12();
		}

		//E = 1,2,3,4,7,8,9,11
		if(letter == 'E')
		{
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();
		}

		//F = 1,2,3,4,9,11
		if(letter == 'F')
		{
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg9();draw_seg11();
		}

		//G = 1,2,3,4,6,7,8,11
		if(letter == 'G')
		{
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg6();draw_seg7();draw_seg8();draw_seg11();
		}

		//H = 1,2,5,6,9,11
		if(letter == 'H')
		{
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg9();draw_seg11();
		}

		//I = 3,4,7,8,10,12
		if(letter == 'I')
		{
			draw_seg3();draw_seg4();draw_seg7();draw_seg8();
			draw_seg10();draw_seg12();
		}

		//J = 1,5,6,7,8
		if(letter == 'J')
		{
			draw_seg1();draw_seg5();draw_seg6();draw_seg7();draw_seg8();

		}

		//K = 1,2,9,14,16
		if(letter == 'K')
		{
			draw_seg1();draw_seg2();draw_seg9();draw_seg14();draw_seg16();
		}

		//L = 1,2,7,8
		if(letter == 'L')
		{
			draw_seg1();draw_seg2();draw_seg7();draw_seg8();
		}

		//M = 1,2,5,6,13,14
		if(letter == 'M')
		{
			draw_seg1();draw_seg2();draw_seg5();draw_seg6();
			draw_seg13();draw_seg14();
		}

		//N = 1,2,5,6,13,16
		if(letter == 'N')
		{
			draw_seg1();draw_seg2();draw_seg5();draw_seg6();
			draw_seg13();draw_seg16();
		}

		//O = 1,2,3,4,5,6,7,8
		if(letter == 'O')
		{
			draw_seg1();draw_seg2();draw_seg3();draw_seg4();
			draw_seg5();draw_seg6();draw_seg7();draw_seg8();
		}

		//P = 1,2,3,4,5,9,11
		if(letter == 'P')
		{
			draw_seg1();draw_seg2();draw_seg3();draw_seg4();
			draw_seg5();draw_seg9();draw_seg11();
		}

		//Q = 1,2,3,4,5,6,7,8,16
		if(letter == 'Q')
		{
			draw_seg1();draw_seg2();draw_seg3();draw_seg4();
			draw_seg5();draw_seg6();draw_seg7();draw_seg8();draw_seg16();
		}

		//R = 1,2,3,4,5,9,11,16
		if(letter == 'R')
		{
			draw_seg1();draw_seg2();draw_seg3();draw_seg4();
			draw_seg5();draw_seg9();draw_seg11();draw_seg16();
		}

		//S = 2,3,4,6,7,8,9,11
		if(letter == 'S')
		{
			draw_seg2();draw_seg3();draw_seg4();draw_seg6();
			draw_seg7();draw_seg8();draw_seg9();draw_seg11();
		}

		//T = 3,4,10,12
		if(letter == 'T')
		{
			draw_seg3();draw_seg4();draw_seg10();draw_seg12();
			
		}

		//U = 1,2,5,6,7,8
		if(letter == 'U')
		{
			draw_seg1();draw_seg2();draw_seg5();
			draw_seg6();draw_seg7();draw_seg8();			
		}

		//V = 1,2,14,15
		if(letter == 'V')
		{
			draw_seg1();draw_seg2();draw_seg14();draw_seg15();
		}


		//W = 1,2,5,6,15,16
		if(letter == 'W')
		{
			draw_seg1();draw_seg2();draw_seg5();
			draw_seg6();draw_seg15();draw_seg16();
		}


		//X = 13,14,15,16
		if(letter == 'X')
		{
			draw_seg13();draw_seg14();draw_seg15();draw_seg16();
		}

		//Y = 2,5,9,11,12
		if(letter == 'Y')
		{
			draw_seg2();draw_seg5();draw_seg9();
			draw_seg11();draw_seg12();	
		}


		//Z = 3,4,7,8,14,15
		if(letter == 'Z')
		{
			draw_seg3();draw_seg4();draw_seg7();draw_seg8();
			draw_seg14();draw_seg15();
		}

		//////////////////NUMBERS/////////////////////////
		//0 = 1,2,3,4,5,6,7,8,14,15
		if(letter == '0')
		{
			draw_seg1();draw_seg2();draw_seg3();draw_seg4();
			draw_seg5();draw_seg6();draw_seg7();draw_seg8();
			draw_seg14();draw_seg15();
		}


		//1 = 5,6
		if(letter == '1')
		{
			draw_seg5();draw_seg6();
		}

		//2 = 1,3,4,5,7,8,9,11
		if(letter == '2')
		{
			draw_seg1();draw_seg3();draw_seg4();draw_seg5();
			draw_seg7();draw_seg8();draw_seg9();draw_seg11();
		}

		//3 = 3,4,5,6,7,8,9,11
		if(letter == '3')
		{
			draw_seg3();draw_seg4();draw_seg5();draw_seg6();
			draw_seg7();draw_seg8();draw_seg9();draw_seg11();
		}

		//4 = 2,5,6,9,11
		if(letter == '4')
		{
			draw_seg2();draw_seg5();draw_seg6();
			draw_seg9();draw_seg11();
		}

		//5 = 2,3,4,7,8,9,16
		if(letter == '5')
		{
			draw_seg2();draw_seg3();draw_seg4();draw_seg7();
			draw_seg8();draw_seg9();draw_seg16();
		}

		//6 = 1,2,3,4,6,7,8,9,11
		if(letter == '6')
		{
			draw_seg1();draw_seg2();draw_seg3();draw_seg4();draw_seg6();
			draw_seg7();draw_seg8();draw_seg9();draw_seg11();
		}

		//7 = 3,4,5,6
		if(letter == '7')
		{
			draw_seg3();draw_seg4();draw_seg5();draw_seg6();
		}

		//8 = 1,2,3,4,5,6,7,8,9,11
		if(letter == '8')
		{
			draw_seg1();draw_seg2();draw_seg3();draw_seg4();
			draw_seg5();draw_seg6();draw_seg7();draw_seg8();
			draw_seg9();draw_seg11();
		}

		//9 = 2,3,4,5,6,7,8,9,11
		if(letter == '9')
		{
			draw_seg2();draw_seg3();draw_seg4();draw_seg5();draw_seg6();
			draw_seg7();draw_seg8();draw_seg9();draw_seg11();	
		}
		glEnd();
		
	glFlush();
	glutSwapBuffers();

}

void myMouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		if(letter!=90 && letter!=58)
			letter+=1;
		else
			if(letter == 90)
				letter = 48;
			if(letter == 58)
				letter = 65;
	}

	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		if(letter!=48 && letter!=64)
			letter-=1;
		else
			if(letter == 48)
				letter = 90;
			if(letter == 64)
				letter = 57;
	}
	glutPostRedisplay();
}

void myReshape(int w, int h)
{
 glViewport(0, 0, w, h);

/* Use a perspective view */

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-10.0, 10.0, -10.0, 10.0, 0.0, 20.0);
 glMatrixMode(GL_MODELVIEW);
}

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

	viewer[0] = 10.0 * sin(deg2rad(theta)) * sin(deg2rad(phi));
	viewer[1] = 10.0 * sin(deg2rad(theta)) * cos(deg2rad(phi));
	viewer[2] = 10.0 * cos(deg2rad(theta));

	glutPostRedisplay();
}

void main(int argc, char **argv)
{
	viewer[0] = 10.0 * sin(deg2rad(theta)) * sin(deg2rad(phi));
	viewer[1] = 10.0 * sin(deg2rad(theta)) * cos(deg2rad(phi));
	viewer[2] = 10.0 * cos(deg2rad(theta)); /* initial viewer location */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Sixteen Segment Display");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc (myMouse);
	glutSpecialFunc(specKeys);
	glutMainLoop();
}