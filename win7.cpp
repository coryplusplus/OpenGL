//Creator: Cory Kelly
//CS 435 Project 6
//This program simulates the windows 7 user interface and demonstrates 
//the effects of texture mapping.

#include <stdlib.h>
#include "glut.h"

#include "bmp_io.cpp"




	int count = 0;
	 ////////initial values for window locations
	float calc_init_x[4] =  {-1.5,-1.5,1.5,1.5};
	 float calc_init_y[4] = {-1.3,1.1,1.1,-1.3};
	 float calc_init_z[4] = {2.0,2.0,2.0,2.0};

	 float paint_init_x[4] =  {-2.5,-2.5,2.5,2.5};
	 float paint_init_y[4] = {-1.9,1.7,1.7,-1.9};
	 float paint_init_z[4] = {2.0,2.0,2.0,2.0};

	 float explorer_init_x[4] =  {-2.0,-2.0,2.0,2.0};
	 float explorer_init_y[4] = {-1.8,1.9,1.9,-1.8};
	 float explorer_init_z[4] = {2.0,2.0,2.0,2.0};

	/////////////initial title bar area
	 float calc_title_x[2] =  {253.0,752.0};
	 float calc_title_y[2] = {150.0,178.0};

	 float paint_title_x[2] =  {85.0,921.0};
	 float paint_title_y[2] = {48.0,72.0};

	 float explorer_title_x[2] =  {169.0,837.0};
	 float explorer_title_y[2] = {13.0,41.0};
	 //////////////////////////////////////////////////

	 	/////////////initial exit button area
	 float calc_exit_x[2] =  {722.0,748.0};
	 float calc_exit_y[2] = {159.0,175.0};

	 float paint_exit_x[2] =  {892.0,917.0};
	 float paint_exit_y[2] = {57.0,73.0};

	 float explorer_exit_x[2] =  {808.0,832.0};
	 float explorer_exit_y[2] = {23.0,39.0};
	 //////////////////////////////////////////////////

	 int direction_x;//used to decide the direction to drag.
	 int direction_y;

	static GLuint texName[6];
	bool start = false;
	int current = 1;//current window
	int now = 0;

	#define MAX_WINDOWS 200	/*maximum number of windows*/

typedef struct window
{ 
     bool used; /* TRUE if stroke exists */
	 float x[4];	
     float y[4];
	 float z[4];
	 float title_x[2];	
     float title_y[2];
	 float exit_x[2];	
     float exit_y[2];
	 int id;
	 int window_type;//1= calculator //2 = paint // 3 = explorer
} window;

window windows[MAX_WINDOWS];





void background()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D,texName[0] );
 	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); 
	glVertex3f(-3.0,-2.1,-0.5);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-3.0,2.8,-0.5);
	glTexCoord2f(1.0,1.0);
	glVertex3f(3.0,2.8,-0.5);
	glTexCoord2f(1.0,0.0);
	glVertex3f(3.0,-2.1,-0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void taskbar()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[1]);
 	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0); 
	glVertex3f(-3.0,-2.1,2.9);
	glTexCoord2f(0.0,.04);
	glVertex3f(-3.0,-1.9,2.9);
	glTexCoord2f(0.99,0.04);
	glVertex3f(3.0,-1.9,2.9);
	glTexCoord2f(0.99,0.0);
	glVertex3f(3.0,-2.1,2.9);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void startmenu()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[2]);
 	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.05); 
	glVertex3f(-3.0,-1.9,2.9);
	glTexCoord2f(0.0,0.67);
	glVertex3f(-3.0,1.3,2.9);
	glTexCoord2f(0.4,0.67);
	glVertex3f(-0.4,1.3,2.9);
	glTexCoord2f(0.4,0.05);
	glVertex3f(-0.4,-1.9,2.9);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}



void create_nonclient(int i)
{
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor4f(0.0,0.0,0.0,0);

	glVertex3f(windows[i].x[2]-.25,windows[i].y[2]+.15,windows[i].z[2]);
	glVertex3f(windows[i].x[3]-.25,windows[i].y[2]+.05,windows[i].z[3]);

	glVertex3f(windows[i].x[2]-.40,windows[i].y[1]+.05,windows[i].z[0]);
	glVertex3f(windows[i].x[2]-.40,windows[i].y[1]+.15,windows[i].z[1]);
	glEnd();
	
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor4f(1.0,1.0,1.0,0.0);
	glVertex3f(windows[i].x[2]-.21,windows[i].y[1]+.13,windows[i].z[1]);
	glVertex3f(windows[i].x[3]-.15,windows[i].y[2]+.07,windows[i].z[3]);
	glVertex3f(windows[i].x[3]-.15,windows[i].y[2]+.13,windows[i].z[2]);
	glVertex3f(windows[i].x[2]-.21,windows[i].y[1]+.07,windows[i].z[0]);
	glEnd();
	
	//exit button
	glBegin(GL_POLYGON);
	glColor4f(1.0,0.0,0.0,0.0);
	glVertex3f(windows[i].x[2]-.25,windows[i].y[1]+.05,windows[i].z[0]);
	glVertex3f(windows[i].x[2]-.25,windows[i].y[1]+.15,windows[i].z[1]);
	glVertex3f(windows[i].x[2]-.1,windows[i].y[2]+.15,windows[i].z[2]);
	glVertex3f(windows[i].x[3]-.1,windows[i].y[2]+.05,windows[i].z[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnd();
	


		
	
	glBegin(GL_POLYGON);//minimize
	glColor4f(0.0,0.5,1.0,0.0);
	glVertex3f(windows[i].x[2]-.40,windows[i].y[1]+.05,windows[i].z[0]);
	glVertex3f(windows[i].x[2]-.40,windows[i].y[1]+.15,windows[i].z[1]);
	glVertex3f(windows[i].x[2]-.25,windows[i].y[2]+.15,windows[i].z[2]);
	glVertex3f(windows[i].x[3]-.25,windows[i].y[2]+.05,windows[i].z[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnd();




	glBegin(GL_POLYGON);//maximize
	glColor4f(0.0,0.5,1.0,0.0);
	glVertex3f(windows[i].x[2]-.55,windows[i].y[1]+.05,windows[i].z[0]);
	glVertex3f(windows[i].x[2]-.55,windows[i].y[1]+.15,windows[i].z[1]);
	glVertex3f(windows[i].x[2]-.40,windows[i].y[2]+.15,windows[i].z[2]);
	glVertex3f(windows[i].x[3]-.40,windows[i].y[2]+.05,windows[i].z[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnd();

	
	glEnable (GL_BLEND);
	glBegin(GL_POLYGON);//triangles are used to round out the angles
	glColor4f(0.0,0.0,0.0,0.0);
	//top left
	glVertex3f(windows[i].x[1]-.05,windows[i].y[1]+.2,windows[i].z[1]);
	glVertex3f(windows[i].x[1]-.05,windows[i].y[1]+.1,windows[i].z[1]);
	glVertex3f(windows[i].x[1]+.05,windows[i].y[1]+.2,windows[i].z[1]);
	glEnd();

	glBegin(GL_POLYGON);//triangles are used to round out the angles
	glColor4f(0.0,0.0,0.0,0.0);
	//bottom left
	glVertex3f(windows[i].x[0]-.05,windows[i].y[0]-.05,windows[i].z[0]);
	glVertex3f(windows[i].x[0]-.05,windows[i].y[0],windows[i].z[0]);
	glVertex3f(windows[i].x[0],windows[i].y[0]-.05,windows[i].z[0]);
	glEnd();

	glBegin(GL_POLYGON);//triangles are used to round out the angles
	glColor4f(0.0,0.0,0.0,0.0);
	//top right
	glVertex3f(windows[i].x[2]+.05,windows[i].y[2]+.2,windows[i].z[2]);
	glVertex3f(windows[i].x[2]-.05,windows[i].y[2]+.2,windows[i].z[2]);
	glVertex3f(windows[i].x[2]+.05,windows[i].y[2]+.1,windows[i].z[2]);
	glEnd();

	glBegin(GL_POLYGON);//triangles are used to round out the angles
	glColor4f(0.0,0.0,0.0,0.0);
	//bottom right
	glVertex3f(windows[i].x[3]+.05,windows[i].y[3]-.05,windows[i].z[3]);
	glVertex3f(windows[i].x[3],windows[i].y[3]-.05,windows[i].z[3]);
	glVertex3f(windows[i].x[3]+.05,windows[i].y[3],windows[i].z[3]);
	glEnd();





	glBegin(GL_POLYGON);//border and title bar
	glColor4f(0.3,0.3,1.0,0.5);
	glVertex3f(windows[i].x[0]-.05,windows[i].y[0]-.05,windows[i].z[0]);
	glVertex3f(windows[i].x[1]-.05,windows[i].y[1]+.2,windows[i].z[1]);
	glVertex3f(windows[i].x[2]+.05,windows[i].y[2]+.2,windows[i].z[2]);
	glVertex3f(windows[i].x[3]+.05,windows[i].y[3]-.05,windows[i].z[3]);
	glEnd();
	glDisable (GL_BLEND); 
	





}


void create_window()
{
for(int z = 1;z<MAX_WINDOWS;z++)
	{
	for(int i = 1;i<MAX_WINDOWS;i++)
	{
	if(windows[i].used && windows[i].id == z)
	{
	now = i;
	
	glEnable(GL_TEXTURE_2D);
	if(windows[i].window_type == 1)
		glBindTexture( GL_TEXTURE_2D,texName[3] );
	if(windows[i].window_type == 2)
		glBindTexture( GL_TEXTURE_2D,texName[4] );
	if(windows[i].window_type == 3)
		glBindTexture( GL_TEXTURE_2D,texName[5] );
 	glBegin(GL_POLYGON);
	glTexCoord2f(0.025,0.025); 
	glVertex3f(windows[i].x[0],windows[i].y[0],windows[i].z[0]);
	glTexCoord2f(0.025,0.94);
	glVertex3f(windows[i].x[1],windows[i].y[1],windows[i].z[1]);
	glTexCoord2f(0.96,0.94);
	glVertex3f(windows[i].x[2],windows[i].y[2],windows[i].z[2]);
	glTexCoord2f(0.96,0.025);
	glVertex3f(windows[i].x[3],windows[i].y[3],windows[i].z[3]);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	create_nonclient(i);
	
	
	}
	}
	}
}





void get_current()
{
	current=1;
	int i=1;
	while(windows[i].used != false)
	{
	current++;
	i++;
	}
}

void set_z()
{
	for(int i = 1;i<MAX_WINDOWS;i++)
	{
	if(windows[i].used)
		for(int p = 0;p<4;p++)
		{
		windows[i].z[p] = .1 * windows[i].id;
		}
	}
	glutPostRedisplay();
}




void display(void)
{
// display callback, clear frame buffer and z buffer,
   

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	taskbar();
	background();
	if(start == true)
	startmenu();
	create_window();//creates windows
	glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{
	if(x > 5 && x < 33 && y < 715 && y > 683)
		start = true;
	if((x > 437 && x < 1006 && y < 709 && y > 1) ||
	   (x > 1 && x < 437 && y > 1 && y < 146)||
	   (x > 33 && x < 437 && y > 686 && y < 709))
		start = false;
	if(start == true && x>285 && x<385 && y>648 && y<671)
		exit(0);
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && start == false && x>42 && x<83 && y>685 && y<709)//internet explorer is clicked
	{
	count++;
	start = false;
	get_current();
	windows[current].used = true;
	windows[current].id = count;
	set_z();
	for(int i = 0;i<4;i++)
	{
		windows[current].x[i] = explorer_init_x[i];
		windows[current].y[i] = explorer_init_y[i];
		windows[current].z[i] = .1*windows[current].id;
	}

		for(int i = 0;i<2;i++)//set initial title bar area and exit button
		{
		windows[current].title_x[i] = explorer_title_x[i];
		windows[current].title_y[i] = explorer_title_y[i];

		windows[current].exit_x[i] = explorer_exit_x[i];
		windows[current].exit_y[i] = explorer_exit_y[i];
		

		}

	windows[current].window_type = 3;

	}
	
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN&& start == true && x>9 && x<273 && y>325 && y<371)//calculator is clicked
	{
	count++;
	start = false;
	get_current();
	windows[current].used = true;
	windows[current].id = count;
	set_z();
	for(int i = 0;i<4;i++)
	{
		windows[current].x[i] = calc_init_x[i];
		windows[current].y[i] = calc_init_y[i];
		windows[current].z[i] = .1*windows[current].id;
	}

	for(int i = 0;i<2;i++)//set initial title bar area and exit button
	{
		windows[current].title_x[i] = calc_title_x[i];
		windows[current].title_y[i] = calc_title_y[i];
		windows[current].exit_x[i] = calc_exit_x[i];
		windows[current].exit_y[i] = calc_exit_y[i];

	}
	windows[current].window_type = 1;


	}

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN&&start == true && x>9 && x<275 && y>384 && y<415)//paint is clicked
	{
	count++;
	start = false;
	get_current();
	windows[current].used = true;
	windows[current].id = count;
	set_z();
	for(int i = 0;i<4;i++)
	{
		windows[current].x[i] = paint_init_x[i];
		windows[current].y[i] = paint_init_y[i];
		windows[current].z[i] = .1*windows[current].id;
	}

		for(int i = 0;i<2;i++)//set initial title bar area and exit button
	{
		windows[current].title_x[i] = paint_title_x[i];
		windows[current].title_y[i] = paint_title_y[i];

		windows[current].exit_x[i] = paint_exit_x[i];
		windows[current].exit_y[i] = paint_exit_y[i];

	}

	windows[current].window_type = 2;
	}



	//if x and y coordinates are in title bar of any window, set that window
	//to current and bring it to the front
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
	for(int i = 1;i<MAX_WINDOWS;i++)
	{
		if(windows[i].used)
		{
			if(x>windows[i].title_x[0] && x<windows[i].title_x[1] &&
				y>windows[i].title_y[0] && y<windows[i].title_y[1])
			{
				int temp = windows[current].id;
				windows[current].id = windows[i].id;
				windows[i].id = temp;
				
				current = i;
				set_z();

			}


		   }
	   

	}			
	}
	//if exit button is clicked
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		
	if(x>windows[current].exit_x[0] && x<windows[current].exit_x[1] &&
		y>windows[current].exit_y[0] && y<windows[current].exit_y[1])
	{
		count--;
		windows[current].used = false;
	}
	}
	
	direction_x = x;
	direction_y = y;

	glutPostRedisplay();

}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
        glOrtho(-3, 3, -3.00 * (GLfloat) h / (GLfloat) w,
            3.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}


void myMotion(int x, int y)
{
	for(int p = 0;p<4;p++)
	{
		windows[current].z[p] = .1*windows[current].id;
	}
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	if(x>direction_x)right =true;
	else left = true;
	if(y<direction_y)up = true;
	else down = true;
	int factorX = 0;
	int factorY = 0;


	if(x>windows[current].title_x[0] && x<windows[current].title_x[1] &&
		y>windows[current].title_y[0] && y<windows[current].title_y[1])
	{
		if(x!=direction_x)
		{
		if(right)
		{
			factorX = x - direction_x;
			windows[current].x[0] +=.01*factorX;
			windows[current].x[1] +=.01*factorX;
			windows[current].x[2] +=.01*factorX;
			windows[current].x[3] +=.01*factorX;
			
			windows[current].title_x[0] +=1.7*factorX;
			windows[current].title_x[1] +=1.7*factorX;

			windows[current].exit_x[0] +=1.7*factorX;
			windows[current].exit_x[1] +=1.7*factorX;


		}
		else
		{
			factorX = direction_x - x;
			windows[current].x[0] -=.01*factorX;
			windows[current].x[1] -=.01*factorX;
			windows[current].x[2] -=.01*factorX;
			windows[current].x[3] -=.01*factorX;

			windows[current].title_x[0] -= 1.7*factorX;
			windows[current].title_x[1] -= 1.7*factorX;

			windows[current].exit_x[0] -=1.7*factorX;
			windows[current].exit_x[1] -=1.7*factorX;

		}
		}

		if(y!=direction_y){
		if(down)
		{
			factorY =y - direction_y;
			windows[current].y[0] -=.01*factorY;
			windows[current].y[1] -=.01*factorY;
			windows[current].y[2] -=.01*factorY;
			windows[current].y[3] -=.01*factorY;

			windows[current].title_y[1] += 1.7*factorY;
			windows[current].title_y[0] += 1.7*factorY;

			windows[current].exit_y[0] +=1.7*factorY;
			windows[current].exit_y[1] +=1.7*factorY;
		}
		else
		{
			factorY =  direction_y - y ;
			windows[current].y[0] +=.01*factorY;
			windows[current].y[1] +=.01*factorY;
			windows[current].y[2] +=.01*factorY;
			windows[current].y[3] +=.01*factorY;

			windows[current].title_y[0]-=1.7*factorY;
			windows[current].title_y[1]-=1.7*factorY;

			windows[current].exit_y[0] -=1.7*factorY;
			windows[current].exit_y[1] -=1.7*factorY;

		}
		}




		direction_x = x;
		direction_y = y;
	}
	glutPostRedisplay();
		


}

void key(unsigned char k, int x, int y)
{
	
}

#define MAP_TB_WIDTH		1440
#define MAP_TB_HEIGHT		900
#define TB_FILE_NAME		"taskbar.bmp"
static GLubyte taskbar_image[MAP_TB_HEIGHT][MAP_TB_WIDTH][4];

void makeTaskBarImage(void)
{
	unsigned long int width;
	long int height;
	unsigned char *rarray;
	unsigned char *garray;
	unsigned char *barray;
	if (bmp_read (TB_FILE_NAME, &width, &height, &rarray, &garray, &barray)) return;
   int i, j;
   for(i=0; i<MAP_TB_HEIGHT; i++) {
     for(j=0; j< MAP_TB_WIDTH; j++) {
	   taskbar_image[i][j][0]=255;
       taskbar_image[i][j][1]=255;
       taskbar_image[i][j][2]=255;
     }
   }

   int tex_sx, tex_sy;
   int img_sx, img_sy;
   int width2copy, height2copy;


   if (width<MAP_TB_WIDTH) {
	   img_sx = 0;
	   tex_sx = (MAP_TB_WIDTH-width)/2;
	   width2copy = width;
   }
   else {
	   img_sx = (width-MAP_TB_WIDTH)/2;
	   tex_sx = 0;
	   width2copy = MAP_TB_WIDTH;
   }
   if (height<MAP_TB_HEIGHT) {
	   img_sy = 0;
	   tex_sy = (MAP_TB_HEIGHT-height)/2;
	   height2copy = height;
   }
   else {
	   img_sy = (height-MAP_TB_HEIGHT)/2;
	   tex_sy = 0;
	   height2copy = MAP_TB_HEIGHT;
   }

   for(i=0; i<height2copy; i++) {
     for(j=0; j<width2copy; j++) {
	   taskbar_image[tex_sy+i][tex_sx+j][0]= rarray[(img_sy+i)*width+img_sx+j];
       taskbar_image[tex_sy+i][tex_sx+j][1]= garray[(img_sy+i)*width+img_sx+j];
       taskbar_image[tex_sy+i][tex_sx+j][2]= barray[(img_sy+i)*width+img_sx+j];
     }
   }
   delete rarray;
   delete garray;
   delete barray;
}


#define MAP_BG_WIDTH		480
#define MAP_BG_HEIGHT		300
#define BG_FILE_NAME		"background.bmp"
static GLubyte background_image[MAP_BG_HEIGHT][MAP_BG_WIDTH][4];

void makeBackgroundImage(void)
{
	unsigned long int width;
	long int height;
	unsigned char *rarray;
	unsigned char *garray;
	unsigned char *barray;
	if (bmp_read (BG_FILE_NAME, &width, &height, &rarray, &garray, &barray)) return;
   int i, j;
   for(i=0; i<MAP_BG_HEIGHT; i++) {
     for(j=0; j< MAP_BG_WIDTH; j++) {
	   background_image[i][j][0]=255;
       background_image[i][j][1]=255;
       background_image[i][j][2]=255;
     }
   }

   int tex_sx, tex_sy;
   int img_sx, img_sy;
   int width2copy, height2copy;


   if (width<MAP_BG_WIDTH) {
	   img_sx = 0;
	   tex_sx = (MAP_BG_WIDTH-width)/2;
	   width2copy = width;
   }
   else {
	   img_sx = (width-MAP_BG_WIDTH)/2;
	   tex_sx = 0;
	   width2copy = MAP_BG_WIDTH;
   }
   if (height<MAP_BG_HEIGHT) {
	   img_sy = 0;
	   tex_sy = (MAP_BG_HEIGHT-height)/2;
	   height2copy = height;
   }
   else {
	   img_sy = (height-MAP_BG_HEIGHT)/2;
	   tex_sy = 0;
	   height2copy = MAP_BG_HEIGHT;
   }

   for(i=0; i<height2copy; i++) {
     for(j=0; j<width2copy; j++) {
	   background_image[tex_sy+i][tex_sx+j][0]= rarray[(img_sy+i)*width+img_sx+j];
       background_image[tex_sy+i][tex_sx+j][1]= garray[(img_sy+i)*width+img_sx+j];
       background_image[tex_sy+i][tex_sx+j][2]= barray[(img_sy+i)*width+img_sx+j];
     }
   }
      delete rarray;
   delete garray;
   delete barray;
}

#define MAP_SM_WIDTH		1024
#define MAP_SM_HEIGHT		768
#define SM_FILE_NAME		"startmenu.bmp"
static GLubyte startmenu_image[MAP_SM_HEIGHT][MAP_SM_WIDTH][4];

void makeStartMenuImage(void)
{
	unsigned long int width;
	long int height;
	unsigned char *rarray;
	unsigned char *garray;
	unsigned char *barray;
	if (bmp_read (SM_FILE_NAME, &width, &height, &rarray, &garray, &barray)) return;
   int i, j;
   for(i=0; i<MAP_SM_HEIGHT; i++) {
     for(j=0; j< MAP_SM_WIDTH; j++) {
	   startmenu_image[i][j][0]=255;
       startmenu_image[i][j][1]=255;
       startmenu_image[i][j][2]=255;
     }
   }

   int tex_sx, tex_sy;
   int img_sx, img_sy;
   int width2copy, height2copy;


   if (width<MAP_SM_WIDTH) {
	   img_sx = 0;
	   tex_sx = (MAP_SM_WIDTH-width)/2;
	   width2copy = width;
   }
   else {
	   img_sx = (width-MAP_SM_WIDTH)/2;
	   tex_sx = 0;
	   width2copy = MAP_SM_WIDTH;
   }
   if (height<MAP_SM_HEIGHT) {
	   img_sy = 0;
	   tex_sy = (MAP_SM_HEIGHT-height)/2;
	   height2copy = height;
   }
   else {
	   img_sy = (height-MAP_SM_HEIGHT)/2;
	   tex_sy = 0;
	   height2copy = MAP_SM_HEIGHT;
   }

   for(i=0; i<height2copy; i++) {
     for(j=0; j<width2copy; j++) {
	   startmenu_image[tex_sy+i][tex_sx+j][0]= rarray[(img_sy+i)*width+img_sx+j];
       startmenu_image[tex_sy+i][tex_sx+j][1]= garray[(img_sy+i)*width+img_sx+j];
       startmenu_image[tex_sy+i][tex_sx+j][2]= barray[(img_sy+i)*width+img_sx+j];
     }
   }
   delete rarray;
   delete garray;
   delete barray;
}

#define MAP_CALC_WIDTH		428
#define MAP_CALC_HEIGHT		423
#define CALC_FILE_NAME		"calculator.bmp"
static GLubyte calculator_image[MAP_CALC_HEIGHT][MAP_CALC_WIDTH][4];
void makeCalculatorImage(void)
{
	unsigned long int width;
	long int height;
	unsigned char *rarray;
	unsigned char *garray;
	unsigned char *barray;
	if (bmp_read (CALC_FILE_NAME, &width, &height, &rarray, &garray, &barray)) return;
   int i, j;
   for(i=0; i<MAP_CALC_HEIGHT; i++) {
     for(j=0; j< MAP_CALC_WIDTH; j++) {
	   calculator_image[i][j][0]=255;
       calculator_image[i][j][1]=255;
       calculator_image[i][j][2]=255;
     }
   }

   int tex_sx, tex_sy;
   int img_sx, img_sy;
   int width2copy, height2copy;


   if (width<MAP_CALC_WIDTH) {
	   img_sx = 0;
	   tex_sx = (MAP_CALC_WIDTH-width)/2;
	   width2copy = width;
   }
   else {
	   img_sx = (width-MAP_CALC_WIDTH)/2;
	   tex_sx = 0;
	   width2copy = MAP_CALC_WIDTH;
   }
   if (height<MAP_CALC_HEIGHT) {
	   img_sy = 0;
	   tex_sy = (MAP_CALC_HEIGHT-height)/2;
	   height2copy = height;
   }
   else {
	   img_sy = (height-MAP_CALC_HEIGHT)/2;
	   tex_sy = 0;
	   height2copy = MAP_CALC_HEIGHT;
   }

   for(i=0; i<height2copy; i++) {
     for(j=0; j<width2copy; j++) {
	  calculator_image[tex_sy+i][tex_sx+j][0]= rarray[(img_sy+i)*width+img_sx+j];
      calculator_image[tex_sy+i][tex_sx+j][1]= garray[(img_sy+i)*width+img_sx+j];
      calculator_image[tex_sy+i][tex_sx+j][2]= barray[(img_sy+i)*width+img_sx+j];
     }
   }
      delete rarray;
   delete garray;
   delete barray;
}

#define MAP_PAINT_WIDTH		914
#define MAP_PAINT_HEIGHT	586
#define PAINT_FILE_NAME		"paint.bmp"
static GLubyte paint_image[MAP_PAINT_HEIGHT][MAP_PAINT_WIDTH][4];
void makePaintImage(void)
{
	unsigned long int width;
	long int height;
	unsigned char *rarray;
	unsigned char *garray;
	unsigned char *barray;
	if (bmp_read (PAINT_FILE_NAME, &width, &height, &rarray, &garray, &barray)) return;
   int i, j;
   for(i=0; i<MAP_PAINT_HEIGHT; i++) {
     for(j=0; j< MAP_PAINT_WIDTH; j++) {
	   paint_image[i][j][0]=255;
       paint_image[i][j][1]=255;
       paint_image[i][j][2]=255;
     }
   }

   int tex_sx, tex_sy;
   int img_sx, img_sy;
   int width2copy, height2copy;


   if (width<MAP_PAINT_WIDTH) {
	   img_sx = 0;
	   tex_sx = (MAP_PAINT_WIDTH-width)/2;
	   width2copy = width;
   }
   else {
	   img_sx = (width-MAP_PAINT_WIDTH)/2;
	   tex_sx = 0;
	   width2copy = MAP_PAINT_WIDTH;
   }
   if (height<MAP_PAINT_HEIGHT) {
	   img_sy = 0;
	   tex_sy = (MAP_PAINT_HEIGHT-height)/2;
	   height2copy = height;
   }
   else {
	   img_sy = (height-MAP_PAINT_HEIGHT)/2;
	   tex_sy = 0;
	   height2copy = MAP_PAINT_HEIGHT;
   }

   for(i=0; i<height2copy; i++) {
     for(j=0; j<width2copy; j++) {
	  paint_image[tex_sy+i][tex_sx+j][0]= rarray[(img_sy+i)*width+img_sx+j];
       paint_image[tex_sy+i][tex_sx+j][1]= garray[(img_sy+i)*width+img_sx+j];
       paint_image[tex_sy+i][tex_sx+j][2]= barray[(img_sy+i)*width+img_sx+j];
     }
   }
   delete rarray;
   delete garray;
   delete barray;
}

#define MAP_EXPLORER_WIDTH		690
#define MAP_EXPLORER_HEIGHT		566
#define EXPLORER_FILE_NAME		"explorer.bmp"
static GLubyte explorer_image[MAP_EXPLORER_HEIGHT][MAP_EXPLORER_WIDTH][4];
void makeExplorerImage(void)
{
	unsigned long int width;
	long int height;
	unsigned char *rarray;
	unsigned char *garray;
	unsigned char *barray;
	if (bmp_read (EXPLORER_FILE_NAME, &width, &height, &rarray, &garray, &barray)) return;
   int i, j;
   for(i=0; i<MAP_EXPLORER_HEIGHT; i++) {
     for(j=0; j< MAP_EXPLORER_WIDTH; j++) {
	   explorer_image[i][j][0]=255;
       explorer_image[i][j][1]=255;
       explorer_image[i][j][2]=255;
     }
   }

   int tex_sx, tex_sy;
   int img_sx, img_sy;
   int width2copy, height2copy;


   if (width<MAP_EXPLORER_WIDTH) {
	   img_sx = 0;
	   tex_sx = (MAP_EXPLORER_WIDTH-width)/2;
	   width2copy = width;
   }
   else {
	   img_sx = (width-MAP_EXPLORER_WIDTH)/2;
	   tex_sx = 0;
	   width2copy = MAP_EXPLORER_WIDTH;
   }
   if (height<MAP_EXPLORER_HEIGHT) {
	   img_sy = 0;
	   tex_sy = (MAP_EXPLORER_HEIGHT-height)/2;
	   height2copy = height;
   }
   else {
	   img_sy = (height-MAP_EXPLORER_HEIGHT)/2;
	   tex_sy = 0;
	   height2copy = MAP_EXPLORER_HEIGHT;
   }

   for(i=0; i<height2copy; i++) {
     for(j=0; j<width2copy; j++) {
	  explorer_image[tex_sy+i][tex_sx+j][0]= rarray[(img_sy+i)*width+img_sx+j];
       explorer_image[tex_sy+i][tex_sx+j][1]= garray[(img_sy+i)*width+img_sx+j];
       explorer_image[tex_sy+i][tex_sx+j][2]= barray[(img_sy+i)*width+img_sx+j];
     }
   }
   delete rarray;
   delete garray;
   delete barray;
}


void init(void)
{    
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);
   makeBackgroundImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(6, texName);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
   glBindTexture(GL_TEXTURE_2D, texName[0]);


   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MAP_BG_WIDTH, 
                MAP_BG_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                background_image);

   makeTaskBarImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glBindTexture(GL_TEXTURE_2D, texName[1]);


   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MAP_TB_WIDTH, 
                MAP_TB_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                taskbar_image);

   makeStartMenuImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glBindTexture(GL_TEXTURE_2D, texName[2]);


   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MAP_SM_WIDTH, 
                MAP_SM_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                startmenu_image);

   makeCalculatorImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glBindTexture(GL_TEXTURE_2D, texName[3]);


   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MAP_CALC_WIDTH, 
                MAP_CALC_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                calculator_image);

   makePaintImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glBindTexture(GL_TEXTURE_2D, texName[4]);


   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MAP_PAINT_WIDTH, 
                MAP_PAINT_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                paint_image);

   makeExplorerImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glBindTexture(GL_TEXTURE_2D, texName[5]);


   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MAP_EXPLORER_WIDTH, 
                MAP_EXPLORER_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                explorer_image);
	
}




void main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(2100, 2100);
    glutCreateWindow("Windows 7");
	init();


/* need both double buffering and z buffer */

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutKeyboardFunc(key);
   glutMotionFunc(myMotion);
   glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

   glutMainLoop();
}

