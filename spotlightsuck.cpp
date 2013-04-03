//Creator:Cory Kelly
//CS 435 Project #4
//This project demonstrates the spotlight effect.
//Each spotlight has been "given" a different color for your viewing pleasure.
//In the spirit of Halloween I created the floor out of triagles, 
//giving it a spider-web effect :)


#include <stdlib.h>
#include <math.h>
#include "glew.h"
#include "glut.h"
#include <fstream>
#include <iostream>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265
#endif

#define TWO_PI	(2*M_PI)



int n;
GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);




double deg2rad(double a)
{
	return 	a*3.1415926/180.0;
}
static GLfloat theta = 0.0;
static GLfloat phi = -10.0;
static GLfloat light_theta = 0.0;
static GLfloat light_phi = 0.0;
static GLdouble viewer[3];
int lightselect = 0;



typedef struct lightRec {
  float amb[4];
  float diff[4];
  float spec[4];
  float pos[4];
  float spotDir[3];
  float spotExp;
  float spotCutoff;
  float atten[3];
  float trans[3];
  float rot[3];
  float swing[3];
  float arc[3];
  float arcIncr[3];
  int theta;
  int phi;

} Light;

static Light spots[] =
{
  {//Light0
    {0.0, 0.5, 0.6, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {0.0, 0.0, 0.0, 1.0},  /* position */
    {0.0, 0.0, -1.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}, /* arc increment */
	{0},{0}

  }
};

static float modelAmb[4] = {0.2, 0.2, 0.2, 1.0};

static float matAmb[4] = {0.5, 0.5, 0.5, 1.0};
static float matDiff[4] = {0.8, 0.8, 0.8, 1.0};
static float matSpec[4] = {0.4, 0.4, 0.4, 1.0};
static float matEmission[4] = {0.0, 0.0, 0.0, 1.0};




void polygon()

/* display one square  */
{
    glBegin(GL_POLYGON);
	   //glColor3f(1.0,0.0,1.0);
       glVertex3f(-9.0,-9.0,-5.0);
       glVertex3f(-9.0,9.0,-5.0);
	    glVertex3f(9.0,9.0,-5.0);
       glVertex3f(9.0,-9.0,-5.0);
	  
    glEnd();
}




void initLights()
{

    int lt = GL_LIGHT0;
	Light *light = &spots[0];
    glEnable(lt);
    glLightfv(lt, GL_AMBIENT, light->amb);
    glLightfv(lt, GL_DIFFUSE, light->diff);


      glLightfv(lt, GL_SPECULAR, light->amb);

      glLightfv(lt, GL_SPECULAR, light->spec);

    glLightf(lt, GL_SPOT_EXPONENT, light->spotExp);
    glLightf(lt, GL_SPOT_CUTOFF, light->spotCutoff);
    glLightf(lt, GL_CONSTANT_ATTENUATION, light->atten[0]);
    glLightf(lt, GL_LINEAR_ATTENUATION, light->atten[1]);
    glLightf(lt, GL_QUADRATIC_ATTENUATION, light->atten[2]);

    
}
    
static void
aimLights(void)
{

    Light *light = &spots[0];

    light->rot[0] = light->swing[0] * sin(light->arc[0]);
    light->arc[0] += light->arcIncr[0];
    if (light->arc[0] > TWO_PI)
      light->arc[0] -= TWO_PI;

    light->rot[1] = light->swing[1] * sin(light->arc[1]);
    light->arc[1] += light->arcIncr[1];
    if (light->arc[1] > TWO_PI)
      light->arc[1] -= TWO_PI;

    light->rot[2] = light->swing[2] * sin(light->arc[2]);
    light->arc[2] += light->arcIncr[2];
    if (light->arc[2] > TWO_PI)
      light->arc[2] -= TWO_PI;
 
}

static void
setLights(void)
{
    int lt = GL_LIGHT0;
    Light *light = &spots[0];

    glPushMatrix();
    glTranslatef(light->trans[0], light->trans[1], light->trans[2]);
    glRotatef(light->rot[0], 1, 0, 0);
    glRotatef(light->rot[1], 0, 1, 0);
    glRotatef(light->rot[2], 0, 0, 1);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glLightfv(lt, GL_POSITION, light->pos);
    glLightfv(lt, GL_SPOT_DIRECTION, light->spotDir);
    glPopMatrix();
  
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	polygon();
	glFlush();
	glutSwapBuffers();

}


void myReshape(int w, int h)
{
 glViewport(0, 0, w, h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-10.0, 10.0, -10.0, 10.0, 0.0, 20.0);
 glMatrixMode(GL_MODELVIEW);
}

void specKeys(int key, int x, int y)
{
	float light_delta = 10.0;
	int x1;
	int y1;
	int z1;

	if(key == GLUT_KEY_UP)
	{
		spots[0].phi -= light_delta;
	}
	if(key == GLUT_KEY_DOWN)
	{
		spots[0].phi += light_delta;
	}
	if(key == GLUT_KEY_LEFT)
	{
		spots[0].theta -= light_delta;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		spots[0].theta += light_delta;
	}
	int t = spots[0].theta;
	int p = spots[0].phi;
	x1 = 10.0 * sin(deg2rad(t)) * sin(deg2rad(p));
	y1 = 10.0 * sin(deg2rad(t)) * cos(deg2rad(p));
	z1 = 10.0 * cos(deg2rad(t));
	spots[0].spotDir[0] = x1;
	spots[0].spotDir[1] = y1;
	spots[0].spotDir[2] = z1;
	 Light *light = &spots[0];
	int lt = GL_LIGHT0;
	glLightfv(lt, GL_SPOT_DIRECTION, light->spotDir);
	glutPostRedisplay();
}




void main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Spotlights");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutSpecialFunc(specKeys);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmb);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matEmission);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);

	initLights();
	setLights();
	aimLights();


	glutMainLoop();
}