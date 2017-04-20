/**********************Artificial terrain generator using fault algorithm********************/

#include<iostream>
#include<GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

GLdouble viewposx = 400.0;
GLdouble viewposz = 400.0;
GLdouble terrainviewer[] = {400.0,50.0,400.0};
int x, z, xmin = 0, zmin = 0, xmax = 400, zmax = 400;
GLfloat map[500][500]={0};	//map[][] stores the height values for each intersection point on the grid.
int iter = 0;
float theta[]={0.0,0.0,0.0};

void terrainCalc(){	
	GLfloat dely;
	float v, a, b, c, d;

	while(iter <256){

		(iter>128)?dely+=0.5/iter:dely=0.5; //Amazingly dynamic displacement formula 10/10. Don't ask don't tell shh. I should stop writing edgy comments.
		srand(iter);
		v= rand();
		a= sin(v);
		b= cos(v);
		d= sqrt(pow((xmax-xmin),2)+pow((zmax-zmin),2));
		c= (rand()/RAND_MAX)* d - d/2.4;

		for(x=xmin;x<=xmax;x+=5) //This loop caculates the y plane values for each point on the grid.
			for(z=zmin;z<=zmax;z+=5)
				(a*x+b*z-c>0)?map[x][z]+=dely:map[x][z]-=dely;


		iter++;
	}

}



void terrainGen(){
	glutFullScreen();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(terrainviewer[0],terrainviewer[1],terrainviewer[2],200,0,200, 0,100,0);
	glRotatef(theta[0],1.0,0.0,0.0);
	glRotatef(theta[1],0.0,1.0,0.0);
	glRotatef(theta[2],0.0,0.0,1.0);	


	int x, z;	

	for(x=xmin;x<=xmax;x+=5)	//Loop to draw the primitives
		for(z=zmin;z<=zmax;z+=5){
			glBegin(GL_POLYGON);
			glColor3f(0.7,0.7,0.7);
			glVertex3f(x,map[x][z],z);
			glColor3f(0.3,0.3,0.3);
			glVertex3f(x+5,map[x+5][z],z);
			glColor3f(0.3,0.3,0.3);
			glVertex3f(x+5,map[x+5][z+5],z+5);
			glColor3f(0.7,0.7,0.7);
			glVertex3f(x,map[x][z+5],z+5);
			glEnd();
		}
	glFlush();

glutSwapBuffers();

}


//F.S. Hill textbook

void size(int width,int height){

	glViewport(0,0,width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0,2.0,-2*(GLfloat)width/(GLfloat)height,2*(GLfloat)width/(GLfloat)height, 2.5,20.0);
	glMatrixMode(GL_MODELVIEW);

}


void keymove(int key, int x, int y){
	if(key==GLUT_KEY_UP) 
		{
		if(terrainviewer[0]<=400.0 && terrainviewer[2]<=400.0){ 
		terrainviewer[0]-=1.0;
		terrainviewer[2]-=1.0;
		terrainviewer[1]+=0.5;
			}
		}
	else if(key==GLUT_KEY_DOWN)
		{if(terrainviewer[0]>=0.0 && terrainviewer[2]>=0.0 && terrainviewer[0]<400.0 && terrainviewer[2]<400.0){
		terrainviewer[0]+=1.0;
		terrainviewer[2]+=1.0;
		terrainviewer[1]-=0.5;}}
/*	else if(key==GLUT_KEY_LEFT) {turn(GLUT_KEY_LEFT); terrainGen();}
	else if(key==GLUT_KEY_RIGHT){turn(GLUT_KEY_RIGHT); terrainGen();}*/
glutPostRedisplay();
}

/*void mouse(int but, int state, int x, int y){
if(but==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
int xworld = sin(theta + dtheta);
int zworld = -cos(theta+dtheta);
glTranslatef(xworld,0,zworld);
terrainGen();
}

}*/

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Terrain");
	terrainCalc();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,1.0);
	glutReshapeFunc(size);
	glutDisplayFunc(terrainGen);
	glutIdleFunc(terrainGen);
	glutSpecialFunc(keymove);
//	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);	
	glutMainLoop();
	return 0;

}

