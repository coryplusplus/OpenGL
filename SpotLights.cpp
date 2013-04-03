//Creator:Cory Kelly
//CS 435 Project #4
//The project is to test the spotlight effect.


#include <stdlib.h>
#include <math.h>
#include "glut.h"
#include <iostream>
using namespace std;

double deg2rad(double a)
{
	return 	a*3.1415926/180.0;
}
static GLdouble  a;
static GLdouble b;
static GLdouble c;
static GLfloat theta = 0.0;
static GLfloat phi = -10.0;
static GLdouble viewer[3];
int observation_station = 1;
float dx = 0,dy=0,dz=-3;
float direction[] = {dx, dy, dz};
float direction0[] = {dx, dy, dz};
float direction1[] = {dx, dy, dz};
float direction2[] = {dx, dy, dz};
float direction3[] = {dx, dy, dz};
float direction4[] = {dx, dy, dz};
float direction5[] = {dx, dy, dz};
float direction6[] = {dx, dy, dz};
float direction7[] = {dx, dy, dz};
int lightselect = 0;



void draw_disk()
{
	glPushMatrix();
	GLUquadricObj *myDisk;
	myDisk = gluNewQuadric();
	gluQuadricDrawStyle(myDisk, GLU_FILL);
	glTranslatef(0,1,0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(22.5f, 0.0f, 0.0f, 1.0f);
	//glColor3f(1.0f, 1.0f, 11.0f);
	gluDisk(myDisk, 0 ,10, 8, 1000);
	gluDeleteQuadric(myDisk);
	glPopMatrix();

}

void draw_cylinder()
{
	glPushMatrix();
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	//glTranslatef(0,-5,0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(22.5f, 0.0f, 0.0f, 1.0f);
	//glColor3f(0.6f, 0.6f, 0.6f);
	gluCylinder(myCylinder, 10 ,10, 15,8, 1000);
	gluDeleteQuadric(myCylinder);
	glPopMatrix();
	

}



void initSpot()
    {
                /*Particular properties of all the lights*/
        
		int px,py,pz;
		py = 10;
        float noAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};       //low ambient light
        float diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		float specular[]={1.0f, 1.0f, 1.0f, 1.0f};
		px = 10.0 * sin(deg2rad(0)) * sin(deg2rad(phi));
		pz=10.0 * cos(deg2rad(0));
        float position0[] = {px,py,pz, 1.0f};
		px = 10.0 * sin(deg2rad(-45)) * sin(deg2rad(phi));
		pz=10.0 * cos(deg2rad(-45));
		float position1[] = {px,py,pz, 1.0f};
		px = 10.0 * sin(deg2rad(-90)) * sin(deg2rad(phi));
		pz=10.0 * cos(deg2rad(-90));
		float position2[] = {px,py,pz, 1.0f};
		px = 10.0 * sin(deg2rad(-140)) * sin(deg2rad(phi));
		pz=10.0 * cos(deg2rad(-140));
		float position3[] = {px,py,pz, 1.0f};
		px = 10.0 * sin(deg2rad(-180)) * sin(deg2rad(phi));
		pz=10.0 * cos(deg2rad(-180));
		float position4[] = {px,py,pz, 1.0f};
		px = 10.0 * sin(deg2rad(-240)) * sin(deg2rad(phi));
		pz=10.0 * cos(deg2rad(-240));
		float position5[] = {px,py,pz, 1.0f};
		px = 10.0 * sin(deg2rad(-270)) * sin(deg2rad(phi));
		pz=10.0 * cos(deg2rad(-270));
		float position6[] = {px,py,pz, 1.0f};
		px = 10.0 * sin(deg2rad(-320)) * sin(deg2rad(phi));
		pz=10.0 * cos(deg2rad(-320));
		float position7[] = {px,py,pz, 1.0f};
		float position[] = {px,py,pz, 1.0f};
		
        
        //properties of the light
		
		glLightfv(GL_LIGHT1, GL_AMBIENT, noAmbient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT1, GL_POSITION, position1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT2, GL_AMBIENT, noAmbient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT2, GL_POSITION, position2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT3, GL_AMBIENT, noAmbient);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT3, GL_POSITION, position3);
		glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT4, GL_AMBIENT, noAmbient);
        glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT4, GL_POSITION, position4);
		glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT5, GL_AMBIENT, noAmbient);
        glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT5, GL_POSITION, position5);
		glLightfv(GL_LIGHT5, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT6, GL_AMBIENT, noAmbient);
        glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT6, GL_POSITION, position6);
		glLightfv(GL_LIGHT6, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT7, GL_AMBIENT, noAmbient);
        glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT7, GL_POSITION, position7);
		glLightfv(GL_LIGHT7, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_AMBIENT, noAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, position0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        
                /*Spot properties*/
        
        
        //define the spot direction and cut-off
       
        
        //spot direction
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
        //angle of the cone light emitted by the spot : value between 0 to 180
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 10);
		glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 10);
		glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 10);
		glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 10);
		glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 10);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10);
        
        //exponent propertie defines the concentration of the light
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0f);
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 5.0f);
		glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 5.0f);
		glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 5.0f);
		glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 5.0f);
		glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 5.0f);
		glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 5.0f);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0f);
        
        //light attenuation (default values used here : no attenuation with the distance)
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);

		glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0f);

		glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.0f);

		glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.0f);

		glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.0f);
		
		glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0.0f);

		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);


		glShadeModel(GL_SMOOTH); /*enable smooth shading */
		glEnable(GL_LIGHTING); /* enable lighting */
		glEnable(GL_LIGHT1);  /* enable lights */
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHT4);
		glEnable(GL_LIGHT5);
		glEnable(GL_LIGHT6);
		glEnable(GL_LIGHT7);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST); /* enable z buffer */
		
		//Material Properties
		GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
		GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
		GLfloat mat_ambient[]={0.0, 0.7, 0.3, 1.0};
		GLfloat mat_shininess={100.0};

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

		glClearColor (1.0, 1.0, 1.0, 1.0);
    }
    



void display(void)
{
	//glClearColor(0.0,0.0,0.0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(a,b,c, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	draw_disk();
	draw_cylinder();
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
	float delta = 10.0;

	if(key == GLUT_KEY_UP)
	{
		dy+=1;
		direction[1] = dy;
	}
	if(key == GLUT_KEY_DOWN)
	{
		dy-=1;
		direction[1] = dy;
	}
	if(key == GLUT_KEY_LEFT)
	{
		dx-=1;
		direction[0] = dx;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		dx+=1;
		direction[0] = dx;
		//theta += delta;
	}

	if(lightselect == 0){
		direction0[0]+=dx;direction0[1]+=dy;
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction0);
		cout<<"Light 0 is currently directed towards "<<direction0[0]<<" "<<direction0[1]<<endl;
	}
	if(lightselect == 1){
		direction1[0]+=dx;direction1[1]+=dy;
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
		cout<<"Light 1 is currently directed towards "<<direction1[0]<<" "<<direction1[1]<<endl;
	}
	if(lightselect == 2){
		direction2[0]+=dx;direction2[1]+=dy;
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction2);
		cout<<"Light 2 is currently directed towards "<<direction2[0]<<" "<<direction2[1]<<endl;
	}
	if(lightselect == 3){
		direction3[0]+=dx;direction3[1]+=dy;
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction3);
		cout<<"Light 3 is currently directed towards "<<direction3[0]<<" "<<direction3[1]<<endl;
	}
	if(lightselect == 4){
		direction4[0]+=dx;direction4[1]+=dy;
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direction4);
		cout<<"Light 4 is currently directed towards "<<direction4[0]<<" "<<direction4[1]<<endl;
	}
	if(lightselect == 5){
		direction5[0]+=dx;direction5[1]+=dy;
		glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, direction5);
		cout<<"Light 5 is currently directed towards "<<direction5[0]<<" "<<direction5[1]<<endl;
	}
	if(lightselect == 6){
		direction6[0]+=dx;direction6[1]+=dy;
		glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, direction6);
		cout<<"Light 6 is currently directed towards "<<direction6[0]<<" "<<direction6[1]<<endl;
	}
	if(lightselect == 7){
		direction7[0]+=dx;direction7[1]+=dy;
		glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, direction7);
		cout<<"Light 7 is currently directed towards "<<direction7[0]<<" "<<direction7[1]<<endl;
	}
	dx = 0,dy=0,dz=-10;
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if(key == 13){
		if(observation_station < 8)
			observation_station++;
		else
			observation_station = 1;
	}
	if(observation_station == 1)
		{a = 10.0 * sin(deg2rad(0)) * sin(deg2rad(phi));
		b=10; c= 10.0 * cos(deg2rad(0));}
	if(observation_station == 2)
		{a = 10.0 * sin(deg2rad(-45)) * sin(deg2rad(phi));
		b=10; c= 10.0 * cos(deg2rad(-45));}
	if(observation_station == 3)
		{a = 10.0 * sin(deg2rad(-90)) * sin(deg2rad(phi));
		b=10;c= 10.0 * cos(deg2rad(-90));}
	if(observation_station == 4)
		{a = 10.0 * sin(deg2rad(-140)) * sin(deg2rad(phi));
		b=10; c=10.0 * cos(deg2rad(-140));}
	if(observation_station == 5)
		{a = 10.0 * sin(deg2rad(-180)) * sin(deg2rad(phi));
		b=10; c=10.0 * cos(deg2rad(-180));}
	if(observation_station == 6)
		{a = 10.0 * sin(deg2rad(-230)) * sin(deg2rad(phi));
		b=10; c=10.0 * cos(deg2rad(-230));}
	if(observation_station == 7)
		{a = 10.0 * sin(deg2rad(-270)) * sin(deg2rad(phi));
		b=10; c= 10.0 * cos(deg2rad(-270));}
	if(observation_station == 8)
		{a = 10.0 * sin(deg2rad(-320)) * sin(deg2rad(phi));
		b=10; c=10.0 * cos(deg2rad(-320));}
	if(key == '0')
		lightselect = 0;
	if(key == '1')
		lightselect = 1;
	if(key == '2')
		lightselect = 2;
	if(key == '3')
		lightselect = 3;
	if(key == '4')
		lightselect = 4;
	if(key == '5')
		lightselect = 5;
	if(key == '6')
		lightselect = 6;
	if(key == '7')
		lightselect = 7;

	glutPostRedisplay();
}

void main(int argc, char **argv)
{
	a = 10.0 * sin(deg2rad(0)) * sin(deg2rad(phi));
	b=10; c= 10.0 * cos(deg2rad(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Spotlights");
	//myinit();
	initSpot();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(specKeys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}