/**********************Artificial terrain generator using fault algorithm********************/

#include<iostream>
#include<GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

GLdouble viewpos = 550.0;
int x, z, xmin = 0, zmin = 0, xmax = 400, zmax = 400;
GLfloat map[500][500]={0};	//map[][] stores the height values for each intersection point on the grid.
int iter = 0;


void terrainCalc(){	
	GLfloat dely;
	float v, a, b, c, d;

	while(iter <100){

		(iter>50)?dely=0.5:dely=1; //Amazingly dynamic displacement formula 10/10

		v= rand();
		a= sin(v);
		b= cos(v);
		d= sqrt(pow((xmax-xmin),2)+pow((zmax-zmin),2));
		c= (rand()/RAND_MAX)* d - d/2;

		for(x=xmin;x<=xmax;x+=5) //This loop caculates the y plane values for each point on the grid.
			for(z=zmin;z<=zmax;z+=5)
				(a*x+b*z-c>0)?map[x][z]+=dely:map[x][z]-=dely;


		iter++;
	}

}



void terrainGen(){

    terrainCalc();    
	
	int x, z;	

	for(x=xmin;x<=xmax;x+=5)	//Loop to draw the primitives
		for(z=zmin;z<=zmax;z+=5){
			glBegin(GL_POLYGON);
			glVertex3f(x,map[x][z],z);
			glColor3f(0.0,0.0,0.0);
			glVertex3f(x+5,map[x+5][z],z);
			glColor3f(1.0,0.0,0.0);
			glVertex3f(x+5,map[x+5][z+5],z+5);
			glColor3f(0.0,0.0,0.0);
			glVertex3f(x,map[x][z+5],z+5);
			glEnd();
		}
	glFlush();

}


//F.S. Hill textbook

void init(int width, int height){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0,GLdouble(width)/GLdouble(height),100.0, 600.0);				//void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewpos,150.0,viewpos, 0.0,0.0,0.0, 0.0,100.0,0.0);	//void gluLookAt(GLdouble eyeX,	GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ);
	glEnable(GL_DEPTH_TEST);	
}

void inout(int key, int x, int y){

	if(key == GLUT_KEY_UP){
		viewpos -= 10.0;
		glutReshapeFunc(init);
	}
	else if(key == GLUT_KEY_DOWN){
		viewpos += 10.0;
		glutReshapeFunc(init);
	}
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Terrain");
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,1.0);
	glutReshapeFunc(init);
	glutDisplayFunc(terrainGen);
	glutSpecialFunc(inout);
	glutMainLoop();
	return 0;

}

