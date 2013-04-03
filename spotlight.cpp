//Creator:Cory Kelly
//CS 435 Project #4
//This project demonstrates the spotlight effect.
//Each spotlight has been "given" a different color for your viewing pleasure.
//In the spirit of Halloween I created the floor out of triagles, 
//giving it a spider-web effect :)


#include <stdlib.h>
#include <math.h>
#include "glut.h"
#include <iostream>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265
#endif

#define TWO_PI	(2*M_PI)

typedef float point2[25];
point2 v[]={{0.0, 0.0}, {-5.0, -10.0}, {5.0,-10.0},
			{0.0, 0.0}, {5.0,-10.0}, {10.0, -5.0},
			{0.0, 0.0}, {10.0, 5.0}, {10.0, -5.0},
			{0.0, 0.0}, {10.0, 5.0}, {5.0, 10.0},
			{0.0, 0.0}, {5.0, 10.0}, {-5.0, 10.0},
			{0.0, 0.0}, {-5.0, 10.0}, {-10.0, 5.0},
			{0.0, 0.0}, {-10.0, 5.0}, {-10.0, -5.0},
			{0.0, 0.0}, {-10.0, -5.0}, {-5.0, -10.0},};


int n;



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
    {1.0, 0.3, 0.3, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {0.0, 15.0, -10.0, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}, /* arc increment */
	{0},{0}

  },
   {//Light1

    {1.0, 0.0, 0.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {7.0,15.0, -7.0, 1.0},  /* position */
    {-7.0, -15.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0},  /* arc increment */
	{0},{0}

  },
    {//Light2
    {0.0, 1.0, 0.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {10.0, 15.0, 0.0, 1.0},  /* position */
    {-10.0, -15.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0},/* arc increment */
	{0},{0}

  },
	 {//Light3
    {0.0, 0.0, 1.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {7.0, 15.0, 7.0, 1.0},  /* position */
    {-7.0, -15.0, -7.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0},  /* arc increment */
	{0},{0}

  },
	  {//Light4
    {0.0, 1.0, 1.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {0.0, 15.0, 10.0, 1.0},  /* position */
    {0.0, 1-5.0, -10.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0},  /* arc increment */
	{0},{0}

  },
	   {//Light5
    {1.0, 1.0, 1.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {-7.0, 15.0, 7.0, 1.0},  /* position */
    {7.0, -15.0, -7.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0},  /* arc increment */
	{0},{0}

  },
	    {//Light6
    {1.0, 0.0, 1.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {-10.0,15.0, 0.0, 1.0},  /* position */
    {10.0, -15.0, 0.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0},  /* arc increment */
	{0},{0}

  },
		 {//Light7
    {1.0, 1.0, 0.0, 1.0},  /* ambient */
    {1.0, 1.0, 1.0, 1.0},  /* diffuse */
    {1.0, 1.0, 1.0, 1.0},  /* specular */
    {-7.0, 15.0, -7.0, 1.0},  /* position */
    {7.0, -15.0, 7.0},   /* direction */
    {20.0},
    {60.0},             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
	{0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0},  /* arc increment */
	{0},{0}

  }
};

static float modelAmb[4] = {0.2, 0.2, 0.2, 1.0};

static float matAmb[4] = {0.5, 0.5, 0.5, 1.0};
static float matDiff[4] = {0.8, 0.8, 0.8, 1.0};
static float matSpec[4] = {0.4, 0.4, 0.4, 1.0};
static float matEmission[4] = {0.0, 0.0, 0.0, 1.0};



void draw_cylinder()
{
	glPushMatrix();
	GLUquadricObj *myCylinder;
	myCylinder = gluNewQuadric();
	gluQuadricDrawStyle(myCylinder, GLU_FILL);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(22.5f, 0.0f, 0.0f, 1.0f);
	gluCylinder(myCylinder, 10.9 ,10.9, 15,8, 1000);
	gluDeleteQuadric(myCylinder);
	glPopMatrix();
	

}

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



void initLights()
{
               
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
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glLightfv(lt, GL_POSITION, light->pos);
    glLightfv(lt, GL_SPOT_DIRECTION, light->spotDir);
    glPopMatrix();
  }
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0,5,0);
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
	draw_cylinder();
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
		spots[lightselect].phi -= light_delta;
	}
	if(key == GLUT_KEY_DOWN)
	{
		spots[lightselect].phi += light_delta;
	}
	if(key == GLUT_KEY_LEFT)
	{
		spots[lightselect].theta -= light_delta;
	}
	if(key == GLUT_KEY_RIGHT)
	{
		spots[lightselect].theta += light_delta;
	}
	int t = spots[lightselect].theta;
	int p = spots[lightselect].phi;
	x1 = 10.0 * sin(deg2rad(t)) * sin(deg2rad(p));
	y1 = 10.0 * sin(deg2rad(t)) * cos(deg2rad(p));
	z1 = 10.0 * cos(deg2rad(t));
	spots[lightselect].spotDir[0] = x1;
	spots[lightselect].spotDir[1] = y1;
	spots[lightselect].spotDir[2] = z1;
	 Light *light = &spots[lightselect];
	int lt = GL_LIGHT0 + lightselect;
	glLightfv(lt, GL_SPOT_DIRECTION, light->spotDir);
	glutPostRedisplay();
}
void processNormalKeys(unsigned char key, int x, int y)
{
	int t;
	float delta = 45.0;
	if(key == 13)
	{
		int x=0;
		int y=0;
		int z=0;
		int degr = 0;
		theta -= delta;
		light_theta-=delta;
		viewer[0] = 10.0 * sin(deg2rad(theta)) * sin(deg2rad(phi));
		viewer[2] =10.0 * cos(deg2rad(theta));


		glutPostRedisplay();
		
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
	n=5;
	viewer[0] = 10.0 * sin(deg2rad(theta)) * sin(deg2rad(phi));
	viewer[1] = 15;
	viewer[2] = -10.0 * cos(deg2rad(theta)); 
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