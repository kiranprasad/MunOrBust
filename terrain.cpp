#include<iostream>
#include<GL/glut.h>
//#include <tga.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


using namespace std;

void terrainGen(){
	/* Using artificial terrain generation */

	GLfloat map[100][100][100], x, z, xmin = 200, zmin = 200, xmax = 300, zmax = 300, y=0;
	int iter = 0;
	float displacement = 0.1; //Change this to make it dynamic with change in iterations Refer to section commented out below.
	float v = rand();
	float a = sin(v);
	float b = cos(v);
	float d = sqrt((xmax-xmin)*(xmax-xmin)+(zmax-zmin)*(zmax-zmin));
	float c = (rand()/RAND_MAX) * d - d/2;

	/*for(x=xmin;x<xmax;x++)
	  for(z=zmin;z<zmax;z++){
	  if( a*x+b*z-c > 0 )
	  map[x][y][z]=map[x][y+displacement][z];
	  else
	  map[x][y][z]=map[x][y-displacement][z];
	  }	
	 */
	//while(iter <100){

	for(x=xmin;x<=xmax;x+=10)
		for(z=zmin;z<=zmax;z+=10){
			glBegin(GL_LINE_LOOP);
			glVertex3f(x,0.0,z);
			glVertex3f(x+10,0.0,z);
			glVertex3f(x+10,0.0,z+10);
			glVertex3f(x,0.0,z+10);
			glEnd();
		}
	glFlush();
	//iter++;
	//}


	/*if(iter < n){
	  displacement = dispi;			Use this for dynamic update.
	  else 
	  displacement = dispn;

	  }
	 */

}

//F.S. Hill textbook

void init(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0,1.0,1.0, 500.0);				//void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
	//	glOrtho(0,500,-500,500,-500,500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,150.0,250.0,250.0,0.0,250.0,0.0,100.0,0.0);	//void gluLookAt(GLdouble eyeX,	GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Terrain Gen");
	glutDisplayFunc(terrainGen);
	init();
	glutMainLoop();
	return 0;

}

