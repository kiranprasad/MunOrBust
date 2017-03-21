#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
//#define step 10

using namespace std;

int rx = 10, ry = 150; 			//If these values look arbitrary to you, that is probably because they are arbitrary.
bool flag = true;

void bmprender(const char* str){	//Render strings
	glRasterPos2f(rx,ry);
	while(*str!='\0'){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str++);  //Times *old* roman as it turns out.
	}
	ry-=10;
}

//TODO: Do away with this entire function.
void strings(){
	glClear(GL_COLOR_BUFFER_BIT);

	//TODO Put the strings in a list format

	bmprender(" 	 	      Lunar Rover Simulator");	 	//There are better ways to do this. This is the simplest.
	bmprender(" "); 						//Placeholders to skip lines.
	bmprender("Authors: ");
	bmprender("Kiran Prasad 1PE14CS055");
	bmprender("Mayur Bhatolia 1PE14CS071");
	bmprender(" ");
	bmprender("Press any key to proceed");
	glFlush();
}


void secondpage(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0,0.5,0.0,0.0);
	glColor3f(0.0,1.0,1.0);
	bmprender("Terrain goes here");   
	glFlush();
}

void kbrd(unsigned char key, int x, int y){
	if(int(key) > 0){
		flag=false;
		glutPostRedisplay();

	}
}

void display(){
	if(flag){
		strings();}
	glutKeyboardFunc(kbrd);
	if(!flag){
		secondpage();
		glFlush();
	}
}

void init(){
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,100.0,0.0,100.0);
	glPointSize(5.0);
}

int main(int argc, char** argv){
	/* Probably should write something here. */
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("PostRedisplay Test"); 
	init();
	glutDisplayFunc(display);
//	glutIdleFunc(display);
	glutMainLoop();
	return 0; 
}
