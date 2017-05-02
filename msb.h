#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "terrain.h"



void display();

const int SKY_FRONT=0,SKY_RIGHT=1,SKY_LEFT=2,SKY_BACK=3,SKY_UP=4,SKY_DOWN=5; //for skybox matrix
int prevx=0, sumfuk=0;
GLint skybox[6],moon,x_r=0, y_r=0, z_r=0;
GLfloat viewer[3] = {1.0f, 0.0f, 0.0f},camera[3] = {0.0f, 0.0, 0.0};
GLdouble curr=0, prev=0,gw_spin = 0.0,angle=0.0,c_angle=90.0,gw_width = 8.0, gw_radius=45.0;
GLdouble gw_x=-180.0, gw_y=50.0, gw_z=220.0,co_x=180.0, co_y=0.0, co_z=80.0;
GLdouble movcord[3]={-150,-10,200};
extern int skyboxID;


void initSky()
{
	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);														
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	//load BMP images into the skybox matrix
		skybox[SKY_DOWN] = LoadBMP("BMP/down.bmp");
		skybox[SKY_FRONT] = LoadBMP("BMP/front.bmp");
		skybox[SKY_BACK] = LoadBMP("BMP/back.bmp");
		skybox[SKY_RIGHT] = LoadBMP("BMP/right.bmp");
		skybox[SKY_LEFT] = LoadBMP("BMP/left.bmp");
		skybox[SKY_UP] = LoadBMP("BMP/up.bmp");
		moon=LoadBMP("BMP/moon.bmp");
}

void initLights()
{

	GLfloat whiteSpecularMaterial[] = {10.0,10.0,10.0},light_post0[]={100.0,-10.0,10.0,1.0};
	GLfloat whiteSpecularLight[] = {10.0, 10.0, 10.0},blackAmbientLight[] = {0.3, 0.3, 0.3};
	GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0},mShininess[] = {50},twoModel[]={GL_TRUE}; 
	GLfloat whiteSpotlight[] = {0.0,100.0,0.0};
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
   	glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, light_post0);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, twoModel);
 	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
	// glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, whiteSpotlight);
	// glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
}

void Draw_Skybox(float x, float y, float z, float width, float height, float length){

	glDisable(GL_DEPTH_TEST);
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_UP]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z); 
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();
 
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,skybox[SKY_DOWN]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
	glEnd();
 	glDisable(GL_TEXTURE_2D);

}



void display(){
	glutFullScreen();
	if(sumfuk==0) //U wan sum fuk?
	{
		initLights();
		initSky();
		sumfuk=1;
	}
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0,1.0,1.0,1.0);
	glLoadIdentity();	
	gluLookAt(viewer[0], viewer[1], viewer[2],camera[0], camera[1], camera[2],0, 1, 0);
	glRotatef(x_r, 0, 1, 0);
	glRotatef(y_r, 0, 0, 1);

	Draw_Skybox(viewer[0]+(0.05*movcord[0]),viewer[1]+(0.05*movcord[1]),viewer[2]+(0.05*movcord[2]),250,250,250);

	glTranslatef(movcord[0],movcord[1],movcord[2]);
	terrainGen();
	glPushMatrix();
	glTranslatef(80,0,165);
	
	
	glutSwapBuffers();

}

void displayReshape(int width,int height)
{	
	if(sumfuk==0){
	glViewport(0,0,width,height);						
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();
	gluPerspective(65,(GLfloat)width/(GLfloat)height,0.01f,1000.0f);
	glMatrixMode(GL_MODELVIEW);						
	glLoadIdentity();
	}
	else{			
	glViewport(0,0,width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(height<=width)
		glFrustum(-2.0,2.0,-2*(GLfloat)width/(GLfloat)height,2*(GLfloat)width/(GLfloat)height, 3.0,100.0);
	else
		glFrustum(-2.0,2.0,-2*(GLfloat)width/(GLfloat)height,2*(GLfloat)width/(GLfloat)height, 3.0,100.0);
	glMatrixMode(GL_MODELVIEW);
}
}


void handleMouse(int x,int y)
{
	if((x-prevx)>=0)
	x_r+=1;
	else
	x_r-=1;
	prevx=x;
}

void passiveMouse(int x, int y)
{
	prevx=x;
}


