#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include "msb.h"

using namespace std;

bool flag = true;

void init(){
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,100.0,0.0,100.0);
	glPointSize(5.0);
}

void bmprender(const char* str, GLfloat x, GLfloat y, int font)					//Render strings using bitmap fonts.
	{	
		glRasterPos2f(x,y);
		while(*str!='\0'){
			if(font==1)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str++);		//Bitmap helvetica 18 font
			else
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str++);  //Bitmap font Times Roman. Stroke fonts are overkill.
	}
}

void strings(){
	glColor3f(0.0,1.0,1.0);
	bmprender("Mun Or Bust", 43.0,70.0, 2);	 	
	bmprender("---------Authors---------",38,50,2);
	bmprender("Kiran Prasad",30,45,2);
	bmprender("1PE14CS055",30,40,2);
	bmprender("Mayur Bhatolia",53,45,2);
	bmprender("1PE14CS071",53,40,2);
	bmprender("Press any key to proceed",40	,30,2);
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
	if(flag){
		displaymain();
	}
	else{
		glutFullScreen();
		display();
	}
}



int main(int argc, char** argv){
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
		glutInitWindowSize(2000,2000);
		glutInitWindowPosition(500,500);
		glutCreateWindow("Mun Or Bust");
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
