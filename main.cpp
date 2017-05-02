#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include "msb.h"
//#define step 10

using namespace std;

bool flag = true;

void init(){
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,100.0,0.0,100.0);
	glPointSize(5.0);
}

void bmprender(const char* str, GLfloat x, GLfloat y)					//Render strings using bitmap fonts.
	{	
		glRasterPos2f(x,y);
		while(*str!='\0'){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str++);  //Bitmap font Times Roman. Stroke fonts are overkill.
	}
}

void strings(){
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glColor3f(0.0,0.0,0.0);
	bmprender("Mun Or Bust", 30.0, 90.0);	 	
	glColor3f(1.0,0.0,0.0);
	bmprender("Authors:",32,82);
	bmprender("Kiran Prasad 1PE14CS055",32,75);
	bmprender("Mayur Bhatolia 1PE14CS071",32,70);
	glColor3f(0.0,1.0,0.0);
	bmprender("Press any key to proceed",32,60);
	glFlush();
}


void displaymain(){
		init();
		strings();

}

void windowSpecial(int key,int x,int y){
	
	if(key==GLUT_KEY_UP)
	{
		
		y_r+=3;	
	}
	if(key== GLUT_KEY_DOWN)
	{
		y_r-=3;
	}
	if(key==GLUT_KEY_RIGHT) x_r+=3;
	if(key==GLUT_KEY_LEFT) x_r-=3;


	display();

}

void  kb(unsigned char key, int x, int y)
{   
	if(key=='n')
		{flag = false;
		glutPostRedisplay();	
	}
	if(key=='+') {movcord[1]--;display();}
	if(key=='-') {movcord[1]++;display();}
	if(key=='*')
	{
		movcord[0]+=5*cos(-1*x_r*3.14/180.0);
		movcord[2]+=5*sin(1*x_r*3.14/180.0);
		display();
	}
	if(key=='/')
	{
		movcord[0]-=5*cos(-1*x_r*3.14/180.0);
		movcord[2]-=5*sin(1*x_r*3.14/180.0);
		display();
	}
}

void displayall(){
	glClear(GL_COLOR_BUFFER_BIT);
	// glutFullScreen();
	
	if(flag)
		displaymain();
	else
		display();
}



int main(int argc, char** argv){
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
		glutInitWindowSize(500,500);
		glutCreateWindow("Lunar Surface!");
		initLights();
		initSky();
  		glutDisplayFunc(displayall);
	 	glutReshapeFunc(displayReshape);
	 	glutKeyboardFunc(kb);
		glutMotionFunc(handleMouse);
		glutPassiveMotionFunc(passiveMouse);
		glutIdleFunc(displayall);
		glutSpecialFunc(windowSpecial);
		glutMainLoop();
	return 0; 
}
