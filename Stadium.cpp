//Creator:Cory Kelly
//CS 435 Project #3
//This project demonstrates the rotation, scaling, and translating
//capabilities of OPENGL.
//A stadium is created out of DISCS and CYLINDERS, signs are created
//out of DISCS and the field goal posts out of CYLINDERS.
//The point of view is set in the first person perspective of a fan
//sitting on the north side of the stadium.
//Since he is sitting on the North side, I did not create a sign on the north side.


#include <stdlib.h>
#include <math.h>
#include "glut.h"
#include <iostream>
using namespace std;

double deg2rad(double a)
{
	return 	a*3.1415926/180.0;
}
int x = 0;
int y = 4;
int z = 8;
static GLfloat xtheta = 25.0;
static GLfloat xphi = 0.0;
static GLfloat ytheta = 25.0;
static GLfloat yphi = 0.0;
static GLdouble viewer[3];
int south = 1,west = 2,east = 3;
bool sbool = false,wbool = false,ebool = false;

//16 segment display 
//each funtion draws a specific segment

void draw_seg1()
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-1.75f, 0.0f, 0.0f);
	glRotatef(90.0f, 1.5f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 3.0, 16, 16);
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 
}

void draw_disk()//creates seating for stadium as well as field
{
	GLUquadricObj *myDisk;
	myDisk = gluNewQuadric();
	gluQuadricDrawStyle(myDisk, GLU_FILL);
	glPushMatrix();
	glTranslatef(0.0f,-3.0f,0.0f);
	glTranslatef(0.0f,0.0f,5.0f);
	glTranslatef(0.0f,-5.0f,0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(0.2f, 0.2f, 0.2f);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-6.0f);
	gluDisk(myDisk, 11 ,12, 6, 1);
	glPopMatrix();
	gluDisk(myDisk, 11 ,12, 6, 1);
	glColor3f(0.3f, 0.3f, 0.3f);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-5.0f);
	gluDisk(myDisk, 10 ,11, 6, 1);
	glPopMatrix();
	gluDisk(myDisk, 10 ,11, 6, 1);
	glColor3f(0.4f, 0.4f, 0.4f);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-4.0f);
	gluDisk(myDisk, 9 ,10, 6, 1);
	glPopMatrix();
	gluDisk(myDisk, 9 ,10, 6, 1);
	glColor3f(0.5f, 0.5f, 0.5f);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-3.0f);
	gluDisk(myDisk, 8 ,9, 6, 1);
	glPopMatrix();
	gluDisk(myDisk, 8 ,9, 6, 1);
	glColor3f(0.6f, 0.6f, 0.6f);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-2.0f);
	gluDisk(myDisk, 7 ,8, 6, 1);
	glPopMatrix();
	glColor3f(0.1f, 1.0f, 0.1f);
	gluDisk(myDisk, 0 ,8, 6, 1);//field
	glColor3f(0.2f, 0.2f, 0.2f);
	gluDeleteQuadric(myDisk);
	glPopMatrix();

}

void draw_cylinder()//creates stadium
{
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glPushMatrix();
	glTranslatef(0.0f,-3.0f,0.0f);
	glTranslatef(0.0f,0.0f,5.0f);
	glTranslatef(0.0f,-5.0f,0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glColor3f(0.2f, 0.2f, 0.2f);
	gluCylinder(myCylinder, 12 ,12, 7,6, 1);
	glColor3f(0.3f, 0.3f, 0.3f);
	gluCylinder(myCylinder, 11 ,11, 6,6, 1);
	glColor3f(0.4f, 0.4f, 0.4f);
	gluCylinder(myCylinder, 10 ,10, 5,6, 1);
	glColor3f(0.5f, 0.5f, 0.5f);
	gluCylinder(myCylinder, 9 ,9, 4,6, 1);
	glColor3f(0.6f, 0.6f, 0.6f);
	gluCylinder(myCylinder, 8 ,8, 3,6, 1);
	gluDeleteQuadric(myCylinder);
	glPopMatrix();

}



void draw_signs()//creates signs 
{
	GLUquadricObj *myDisk;
	myDisk = gluNewQuadric();
	gluQuadricDrawStyle(myDisk, GLU_FILL);
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(30.0f,1.0f,1.0f,0.0f);
	glTranslatef(-1,2,-6);
	gluDisk(myDisk, 0 ,4, 4, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(-30.0f,1.0f,1.0f,0.0f);
	glTranslatef(1.5,-1,-7);
	gluDisk(myDisk, 0 ,4, 4, 1);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(-90.0f,1.0f,1.0f,0.0f);
	glTranslatef(4,-3,-10);
	gluDisk(myDisk, 0 ,4, 4, 1);
	glPopMatrix();
}

void draw_field()//draws field lines
{
	int line_count = 0;
	int x = -10;
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 8.0f);
	glTranslatef(0.0f, 6.0f, 0.0f);
	glTranslatef(-2.25f, 0.0f, 0.0f);
	glPushMatrix();
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glScalef(.275,.275,.275);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	//draws 13 field lines
	for(line_count ;line_count <13;line_count ++)
	{
	glPushMatrix();
	glTranslatef(x, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 20, 16, 16);
	x+=3;
	glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();//top line
	glScalef(.275,.275,.275);
	glTranslatef(-10, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 36, 16, 16);
	glPopMatrix();
	glPushMatrix();//bottom line
	glScalef(.275,.275,.275);
	glTranslatef(-10, -20.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 36, 16, 16);
	glPopMatrix();
	glPopMatrix();
	gluDeleteQuadric(myCylinder); 


}
//draws the field goal posts for the stadium
void draw_goal_posts()
{	
	int post = 0;
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	while(post<2)
	{
	glPushMatrix();
	glScalef(.4,.4,.4);
	if(post == 0)
	{
	glTranslatef(-13.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -18.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 8.0f);
	}
	if(post == 1)
	{
	glTranslatef(13.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -18.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 8.0f);
	}
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(-3.5, 2.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 2.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.5f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.75, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 1.75, 16, 16);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.75, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(myCylinder, 0.1, 0.1, 2.5, 16, 16);
	glPopMatrix();
	glPopMatrix();
	post++;
	}
	gluDeleteQuadric(myCylinder); 





}

void updatescreen()//changes the sign writing
{
	if (south == 1)
	{
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(20,10,-25);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg9();draw_seg11();draw_seg16();//R
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(23,10,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg7();draw_seg8();//O
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(26,10,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg7();draw_seg8();//L
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(29,10,-19);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg7();draw_seg8();//L
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(20,3,-25);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg10();draw_seg12();//T
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(23,3,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg7();draw_seg8();
		draw_seg10();draw_seg12();//I
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(26,3,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg5();draw_seg6();
		draw_seg7();draw_seg8();draw_seg10();draw_seg12();//D
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(29,3,-19);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();//E
		glPopMatrix();
	}
	if(south == 2)
	{
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(23,10,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg6();draw_seg7();draw_seg8();draw_seg11();//G
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(27,10,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg7();draw_seg8();//O
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(20,3,-25);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg5();draw_seg6();
		draw_seg7();draw_seg8();draw_seg10();draw_seg11();draw_seg12();//B
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(24,3,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(28,3,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg13();draw_seg14();//M
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(32,3,-19);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();

	}
	if(south == 3)
	{
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(20,10,-25);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(23,10,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();
		draw_seg6();draw_seg15();draw_seg16();//W
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(26,10,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(29,10,-19);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg2();draw_seg5();draw_seg9();
		draw_seg11();draw_seg12();//Y
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(23,3,-23);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(26,3,-21);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
	}
	if (west == 1)
	{

		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg9();draw_seg11();draw_seg16();//R
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,30);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg13();draw_seg14();//M
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg9();draw_seg11();//F
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,30);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg10();draw_seg12();//T
		glPopMatrix();

	}
	if(west == 2)
	{
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,20);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg9();draw_seg11();//H
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg7();draw_seg8();//O
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,28);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg13();draw_seg14();//M
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,32);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();//E
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg3();draw_seg4();draw_seg5();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();//2
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,28);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg2();draw_seg5();draw_seg6();
		draw_seg9();draw_seg11();//4
		glPopMatrix();
	}
	if(west == 3)
	{
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,20);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();
		draw_seg6();draw_seg15();draw_seg16();//W
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,28);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,10,32);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg2();draw_seg5();draw_seg9();
		draw_seg11();draw_seg12();//Y
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,24);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(50,4,28);
		glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
	}
	if (east == 1)
	{
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-30,10,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg9();draw_seg11();draw_seg16();//R
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,10,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg7();draw_seg8();//O
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,10,-19);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg7();draw_seg8();//L
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-18,10,-20);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg7();draw_seg8();//L
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-30,4,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg10();draw_seg12();//T
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,4,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg7();draw_seg8();
		draw_seg10();draw_seg12();//I
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,4,-19);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg3();draw_seg4();draw_seg5();draw_seg6();
		draw_seg7();draw_seg8();draw_seg10();draw_seg12();//D
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-17.5,4,-20);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();//E
		glPopMatrix();
	}
	if(east == 2)
	{
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-30,10,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg9();draw_seg11();//H
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,10,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg7();draw_seg8();//O
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,10,-19);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();draw_seg6();
		draw_seg13();draw_seg14();//M
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-18,10,-20);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg7();draw_seg8();draw_seg9();draw_seg11();//E
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,5,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,5,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg2();draw_seg5();draw_seg6();
		draw_seg9();draw_seg11();//4
		glPopMatrix();
	}
	if(east == 3)
	{
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-30,10,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,10,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg5();
		draw_seg6();draw_seg15();draw_seg16();//W
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,10,-19);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg1();draw_seg2();draw_seg3();draw_seg4();
		draw_seg5();draw_seg6();draw_seg9();draw_seg11();//A
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-18,10,-20);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg2();draw_seg5();draw_seg9();
		draw_seg11();draw_seg12();//Y
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-26,5,-17);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
		glPushMatrix();
		glScalef(.2,.2,.2);
		glTranslatef(-22,5,-18);
		glRotatef(-335.0f, 0.0f, 1.0f, 0.0f);
		draw_seg5();draw_seg6();//1
		glPopMatrix();
	}



}

void display(void)
{
	glClearColor(0,.5,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x,y,z, viewer[0], viewer[1], viewer[2], 0.0, 1.0, 0.0);
	draw_disk();
	draw_cylinder();
	draw_signs();
	draw_field();
	draw_goal_posts();
	updatescreen();	
	glFlush();
	glutSwapBuffers();

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
	float delta = .5;

	if(key == GLUT_KEY_UP)
	{
		ytheta += delta;
		viewer[1] = 2.0 * sin(deg2rad(ytheta)) * cos(deg2rad(yphi));
	}
	if(key == GLUT_KEY_DOWN)
	{
		ytheta -= delta;
		viewer[1] = 2.0 * sin(deg2rad(ytheta)) * cos(deg2rad(yphi));
	}
	if(key == GLUT_KEY_LEFT)
	{
		xphi -= delta;
		viewer[0] =10.0 * sin(deg2rad(xtheta)) * sin(deg2rad(xphi));
	}
	if(key == GLUT_KEY_RIGHT)
	{
		xphi += delta;
		viewer[0] =10.0 * sin(deg2rad(xtheta)) * sin(deg2rad(xphi));
	}

	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if(key == 's')
	{
		sbool = true;
		wbool = false;
		ebool = false;
	}
	if(key == '1' && sbool == true)
		south = 2;
	if(key == '2' && sbool == true)
		south = 1;
	if(key == '3' && sbool == true)
		south = 3;
	if(key == 'w')
	{
		sbool = false;
		wbool = true;
		ebool = false;
	}
	if(key == '1' && wbool == true)
		west = 2;
	if(key == '2' && wbool == true)
		west = 1;
	if(key == '3' && wbool == true)
		west = 3;
	if(key == 'e')
	{
		sbool = false;
		wbool = false;
		ebool = true;
	}
	if(key == '1' && ebool == true)
		east = 2;
	if(key == '2' && ebool == true)
		east = 1;
	if(key == '3' && ebool == true)
		east = 3;
	glutPostRedisplay();
}

void main(int argc, char **argv)
{
	viewer[0] = 0;
	viewer[1] = 0;
	viewer[2] = 0; /* initial viewer location */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Stadium");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(specKeys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}