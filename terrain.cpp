/**********************Artificial terrain generator using fault algorithm********************/

#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <unistd.h>

using namespace std;

void terrainGen();

GLdouble vectormat[2][3]={{-5,0,-5},{-5,0,5}};
GLdouble terrainviewer[] = {400.0,50.0,400.0};
GLdouble move[] = {400.0,50.0,400.0};
int x, z, xmin = 0, zmin = 0, xmax = 400, zmax = 400;
GLfloat map[1000][1000]={0};	//map[][] stores the height values for each intersection point on the grid.
int iter = 0;
int quadx, quadz, xter, zter;
float theta[]={0.0,0.0,0.0};
GLdouble centre[3]={200,50,200};
GLdouble viewnorm[3]={0};
GLdouble angle, dotproduct, mag;
bool pausesim = true;
int rx = 10, ry = 150, upcount=0, downcount=0;
const char* str = "PAUSE";

/************************************norm class starts here****************************************/

class norm{

	GLdouble VecX;
	GLdouble VecY;
	GLdouble VecZ;
	GLdouble VecConst;
public:
	static int cnt;
	norm(){

		VecY = 50.0;
	};
	void normie(int, int);
	void vecangle();
	void elevation();

};
norm normals[1000][1000];

int norm::cnt = 0;
	void norm::normie(int x, int z){

			this->VecX = ((vectormat[0][1] * vectormat[1][2]) - (vectormat[1][1] * vectormat[0][2]));
			this->VecZ = ((vectormat[0][0] * vectormat[1][1]) - (vectormat[1][0] * vectormat[0][1]));
			this->VecConst = VecX*x+VecY*map[x][z]+VecZ*z;
			cout << this->VecX<<" "<<this->VecY<<" "<<this->VecZ<<endl;
	}

	void norm::vecangle(){

		if(viewnorm[0]==0&&viewnorm[1]==0&&viewnorm[2]==0)
		{
			viewnorm[0] = VecX;
			viewnorm[1] = VecY;
			viewnorm[2] = VecZ;
		}
		else{
			dotproduct = (viewnorm[0]*VecX)+(viewnorm[1]*VecY)+(viewnorm[2]*VecZ);
			mag = (sqrt(pow(viewnorm[0],2)+pow(viewnorm[1],2)+pow(viewnorm[2],2)))*(sqrt(pow(VecX,2)+pow(VecY,2)+pow(VecZ,2)));
		
//		if((angle = acos(dotproduct/mag))!=0){

//				glRotatef(-angle, viewnorm[0],viewnorm[1],viewnorm[2]);
//				terrainGen();

//		}
			}
	}



void norm::elevation(){

	terrainviewer[1] = (this->VecConst - this->VecX * terrainviewer[0] - this->VecZ * terrainviewer[2])/VecY;
	cout <<"norm::elevation"<<endl<< this->VecConst<<endl<<this->VecX<<endl<<this->VecY<<endl<<this->VecZ<<endl<<"end of norm::elevation"<<endl;
	terrainGen();


}

/******************************End of class norm***********************/


void quadcalc(){

	xter = terrainviewer[0];
	zter = terrainviewer[2];

	if(xter<10)
	{
		quadx = xter;
	}
	else if (xter<100)
	{
		quadx = xter%10;
	}
	else
	{
		quadx = xter%100;
	}

	if(zter<10)
	{
		quadz = zter;
	}
	else if (zter<100)
	{
		quadz = zter%10;
	}
	else
	{
		quadz = zter%100;
	}

	quadx-5>0?xter-=(quadx-5):xter+=(quadx-5);
	quadz-5>0?zter-=(quadz-5):zter+=(quadz-5);
	cout << "quadcalc"<<endl<<xter << " "<<zter<<endl<<"end of quadcalc"<<endl;
	normals[xter][zter].elevation();


}


void terrainCalc(){	
	GLfloat dely;
	float v, a, b, c, d;
	srand(time(NULL)+rand());
	while(iter <100){
		(iter>50)?dely+=1/iter:dely=1; //Amazingly dynamic displacement formula 10/10. Don't ask don't tell shh. I should stop writing edgy comments.
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

	
			//Surface normal evaluation function

		int i = 0; z = 0;

	for(x=xmin;x<xmax;x+=5){
		for(z=zmin;z<zmax;z+=5){
			vectormat[0][1] = map[x][z+5] - map[x+5][z];
			vectormat[1][1] = map[x][z] - map[x+5][z+5];
			normals[x][z].normie(x,z);
		}
	}

}

void terrainGen()
{	
	while(!pausesim){
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0,1.0,1.0);
		glRasterPos2f(rx,ry);
		while(*str!='\0'){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str++);  //Times *old* roman as it turns out.
	}
	glFlush();
		cout << "pause"<<endl;
		return;
	}

	int x, z;	
	cout << terrainviewer[1]<<endl;
	//glutFullScreen();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//normals[x][z].vecangle();
	gluLookAt(terrainviewer[0],terrainviewer[1]+0.75,terrainviewer[2],terrainviewer[0]-5,terrainviewer[1]+5.0,terrainviewer[2]-5, 0,400,0);
	 glRotatef(theta[0],1.0,0.0,0.0);
	 glRotatef(theta[1],0.0,1.0,0.0);
	 glRotatef(theta[2],0.0,0.0,1.0);	



	for(x=xmin;x<=xmax;x+=5)	//Loop to draw the primitives
		for(z=zmin;z<=zmax;z+=5){
			glBegin(GL_POLYGON);
			glColor3f(0.7,0.7,0.7);
			glVertex3f(x,map[x][z],z);
			glColor3f(0.5,0.5,0.5);
			glVertex3f(x+5,map[x+5][z],z);
			glColor3f(0.7,0.7,0.7);
			glVertex3f(x+5,map[x+5][z+5],z+5);
			glColor3f(0.3,0.3,0.3);
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
	glFrustum(-2.0,2.0,-2*(GLfloat)width/(GLfloat)height,2*(GLfloat)width/(GLfloat)height, 2.0,200.0);
	glMatrixMode(GL_MODELVIEW);

}


void keymove(int key, int x, int y){

	if(key==GLUT_KEY_UP) 
		{
		if(terrainviewer[0]<=400.0 && terrainviewer[2]<=400.0){ 
		terrainviewer[0]-=0.1;
		terrainviewer[2]-=0.1;
		centre[0]-=1.0;
		centre[2]-=1.0;
		quadcalc();
		// if(upcount==5){
		// quadcalc();
		// upcount=0;
		// }
		// else upcount++;


			}
		}
	else if(key==GLUT_KEY_DOWN)
		{if(terrainviewer[0]>0.0 && terrainviewer[2]>0.0 && terrainviewer[0]<400.0 && terrainviewer[2]<400.0){
			terrainviewer[0]+=0.1;
			terrainviewer[2]+=0.1;
			quadcalc();
		// 	if(downcount==5){
		// quadcalc();
		// downcount=0;
		// }
		// else downcount++;

		}}
	else if(key==GLUT_KEY_LEFT) 
		{
		theta[1]+=0.25;
		glPushMatrix();
		glRotatef(theta[1],0.0,1.0,0.0);
		 terrainGen();
		 glPopMatrix();
		 return;	
		}
	else if(key==GLUT_KEY_RIGHT)
		{

			glRotatef(theta[1],0.0,1.0,0.0);
			theta[1]+=-0.25;
		terrainGen();	
		 return;	
		}
glutPostRedisplay();
}

void kbrd(unsigned char key, int x, int y){

	if(key=='w'){
		terrainviewer[1]++;
		centre[1]++;
		terrainGen();
	}
	else if(key=='s'){
		terrainviewer[1]--;
		centre[1]--;
		terrainGen();
	}


	else if(key=='*'){
		if(terrainviewer[1]>map[int(terrainviewer[0])][int(terrainviewer[2])])
		terrainviewer[1]+=-0.25;
		terrainGen();
	}


	else if(key=='/'){
		terrainviewer[1]+=0.25;
		terrainGen();
	}

	else if(key=='p'||key=='P'){

		pausesim = false;
	}

		else if(key=='r'||key=='R'){

		pausesim = true;
	}
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
	quadcalc();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,1.0);
	glutReshapeFunc(size);
	glutDisplayFunc(terrainGen);
	glutIdleFunc(terrainGen);
	glutSpecialFunc(keymove);
	glutKeyboardFunc(kbrd);
//	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;

}

