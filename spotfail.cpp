//Creator:Cory Kelly
//CS 435 Project #4
//The project is to test the spotlight effect.


#include <stdlib.h>
#include <math.h>
#include "glut.h"
#include <iostream>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265
#endif

#define TWO_PI	(2*M_PI)

#define NUM_LIGHTS 1;

double deg2rad(double a)
{
	return 	a*3.1415926/180.0;
}
static GLfloat theta = 0.0;
static GLfloat phi = -10.0;
static GLfloat light_theta = 0.0;
static GLfloat light_phi = 0.0;
static GLdouble viewer[3];
float dx = 0,dy=-1,dz=0;
float direction[] = {dx, dy, dz};
float direction0[] = {dx, dy, dz};
float direction1[] = {dx, dy, dz};
float direction2[] = {dx, dy, dz};
float direction3[] = {dx, dy, dz};
float direction4[] = {dx, dy, dz};
float direction5[] = {dx, dy, dz};
float direction6[] = {dx, dy, dz};
float direction7[] = {dx, dy, dz};
float position[] = {viewer[0],viewer[1],viewer[2],1.0f};
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

} Light;

static Light spots[] =
{
  {//Light0
    {1.0, 0.3, 0.3, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {0.0, 10.0, 0.0, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    {20.0},
    {45.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */

  },
   {//Light1
    {1.0, 0.0, 0.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {-1.227878, 10.0, 7.0710678, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */

  },
    {//Light2
    {0.0, 1.0, 0.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {-1.7364818, 10.0, 2.6794896e-007, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */

  },
	 {//Light3
    {0.0, 0.0, 1.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {-1.2278781, 10.0, -7.0710673, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */

  },
	  {//Light4
    {0.0, 1.0, 1.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {-9.3057700e-008, 10.0, -10.0, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */

  },
	  		 {//Light5
    {1.0, 1.0, 1.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {1.2278780, 10.0, -7.0710683, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */

  },
	   {//Light6
    {1.0, 0.0, 1.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {1.7364818, 10.0, -8.0384689e-007, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */

  },
	    {//Light7
    {1.0, 1.0, 0.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {1.2278781, 10.0, 7.071067, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */

  },

};

static float modelAmb[4] = {0.2, 0.2, 0.2, 1.0};

static float matAmb[4] = {0.2, 0.2, 0.2, 1.0};
static float matDiff[4] = {0.8, 0.8, 0.8, 1.0};
static float matSpec[4] = {0.4, 0.4, 0.4, 1.0};
static float matEmission[4] = {0.0, 0.0, 0.0, 1.0};


void draw_disk()
{
	glPushMatrix();
	GLUquadricObj *myDisk;
	myDisk = gluNewQuadric();
	gluQuadricDrawStyle(myDisk, GLU_FILL);
	glTranslatef(0,1,0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(22.5f, 0.0f, 0.0f, 1.0f);
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
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(22.5f, 0.0f, 0.0f, 1.0f);
	gluCylinder(myCylinder, 10 ,10, 15,8, 1000);
	gluDeleteQuadric(myCylinder);
	glPopMatrix();
	

}



void initLights()
{
                /*Particular properties of all the lights*/
	int k;
	for(k=0;k<8;++k)
	{
    int lt = GL_LIGHT0 + k;
    Light *light = &spots[k];

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
}
    
static void
aimLights(void)
{
  int k;

  for (k = 0; k < 8; ++k) {
    Light *light = &spots[k];

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
}

static void
setLights(void)
{
  int k;

  for (k = 0; k < 8; ++k) {
    int lt = GL_LIGHT0 + k;
    Light *light = &spots[k];

    glPushMatrix();
    glTranslatef(light->trans[0], light->trans[1], light->trans[2]);
    glRotatef(light->rot[0], 1, 0, 0);
    glRotatef(light->rot[1], 0, 1, 0);
    glRotatef(light->rot[2], 0, 0, 1);
    glLightfv(lt, GL_POSITION, light->pos);
    glLightfv(lt, GL_SPOT_DIRECTION, light->spotDir);
    glPopMatrix();
	///glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction0);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
	//glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction2);
	//glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction3);
	//glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direction4);
	//glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, direction5);
	//glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, direction6);
	//glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, direction7);
  }
}

static void
drawLights(void)
{
  int k;

  glDisable(GL_LIGHTING);
  for (k = 0; k < 8; ++k) {
    Light *light = &spots[k];

    glColor4fv(light->diff);

    glPushMatrix();
    glTranslatef(light->trans[0], light->trans[1], light->trans[2]);
    glRotatef(light->rot[0], 1, 0, 0);
    glRotatef(light->rot[1], 0, 1, 0);
    glRotatef(light->rot[2], 0, 0, 1);
    glBegin(GL_LINES);
	glVertex3f(light->pos[0], light->pos[1], light->pos[2]);
	glVertex3f(light->spotDir[0], light->spotDir[1], light->spotDir[2]);
    glEnd();
    glPopMatrix();
  }
  glEnable(GL_LIGHTING);
}


void display(void)
{
	glClearColor(0.0,0.0,0.0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	draw_disk();
	draw_cylinder();
	aimLights();
	setLights();
	drawLights();
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
	float light_delta = 10.0;
	int i;
	if(key == GLUT_KEY_UP)
	{
		light_phi -= light_delta;
	}
	if(key == GLUT_KEY_DOWN)
	{
		light_phi += light_delta;
	}
	if(key == GLUT_KEY_LEFT)
	{
		light_theta -= light_delta;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		light_theta += light_delta;
	}

	direction[0] = 1.0 * sin(deg2rad(light_theta)) * sin(deg2rad(light_phi));
	direction[1] = 1.0 * sin(deg2rad(light_theta)) * cos(deg2rad(light_phi));
	direction[2] = 1.0 * cos(deg2rad(light_theta));
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	if(lightselect==0)
	{
		i=0;
		spots[0].spotDir[0] +=direction[0];spots[0].spotDir[1]+=direction[1];spots[0].spotDir[2]+=direction[2];
		//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction0);
	}
	if(lightselect==1)
	{
		i=1;
		spots[1].spotDir[0] +=direction[0];spots[1].spotDir[1]+=direction[1];spots[1].spotDir[2]+=direction[2];
		//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
	}
	if(lightselect==2)
	{
		i=2;
		spots[2].spotDir[0] +=direction[0];spots[2].spotDir[1]+=direction[1];spots[2].spotDir[2]+=direction[2];
		//glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction2);
	}
	if(lightselect==3)
	{
		i=3;
		spots[3].spotDir[0] +=direction[0];spots[3].spotDir[1]+=direction[1];spots[3].spotDir[2]+=direction[2];
		//glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction3);
	}
	if(lightselect==4)
	{
		i=4;
		spots[4].spotDir[0] +=direction[0];spots[4].spotDir[1]+=direction[1];spots[4].spotDir[2]+=direction[2];
		//glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direction4);
	}
	if(lightselect==5)
	{
		i=5;
		spots[5].spotDir[0] +=direction[0];spots[5].spotDir[1]+=direction[1];spots[5].spotDir[2]+=direction[2];
		//glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, direction5);
	}
	if(lightselect==6)
	{
		i=6;
		spots[6].spotDir[0] +=direction[0];spots[6].spotDir[1]+=direction[1];spots[6].spotDir[2]+=direction[2];
		//glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, direction6);
	}
	if(lightselect==7)
	{
		i=7;
		spots[7].spotDir[0] +=direction[0];spots[7].spotDir[1]+=direction[1];spots[7].spotDir[2]+=direction[2];
		//glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, direction7);
	}

	//light_theta = 0;
	//light_phi = 0;

	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if(key == 13)
	{
		float delta = 45.0;
		if(theta == 0)
			glLightfv(GL_LIGHT0, GL_POSITION, position);
		theta += delta;
		viewer[0] = 10.0 * sin(deg2rad(theta)) * sin(deg2rad(phi));
		viewer[2] = 10.0 * cos(deg2rad(theta));
		position[0] = viewer[0];position[1] = viewer[1];position[2] = viewer[2];
	}

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
	viewer[0] = 10.0 * sin(deg2rad(theta)) * sin(deg2rad(phi));
	viewer[1] = 10;
	viewer[2] = 10.0 * cos(deg2rad(theta)); /* initial viewer location */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Spotlights");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(specKeys);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmb);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

	initLights();

	glutMainLoop();
}