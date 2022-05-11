//CSE4200 Final Project 
//Project Name: Drive Safe Animation
//NAMES: Andrea Morales and Brenden Hernandez

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string>

using namespace std;

int counter = 0;

int frame = 0;
int walkframe = 0;
int scalecounter = 0;
int chicken1[4][2];
int chicken2[4][2];
int chicken3[4][2];


int tweenPoly[10][2];
int tweenPoly2[6][2];
float proportion = 0.0;
float tx = 0.0;			//moving person
float ty = 0.0;

float cx = 0.5;			//scaling for crash scene
float cy = 0.5;
float mcx = 0.0;		//moving car1 scene2
float mcy = 0.0;
float mc2x = 0.0;		//moving car2 scene2
float mc2y = 0.0;


void init() 
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 300.0);
	glLineWidth(2.0);
	
    //this are the open legs of the chicken 
	chicken1[0][0] = 200;
	chicken1[0][1] = 80;
	chicken1[1][0] = 160;
	chicken1[1][1] = 40;
	chicken1[2][0] = 200;
	chicken1[2][1] = 80;
	chicken1[3][0] = 240;
	chicken1[3][1] = 40;
    //this are the close legs (when taking a step) legs of the chicken
    chicken2[0][0] = 200;
	chicken2[0][1] = 80;
	chicken2[1][0] = 199;
	chicken2[1][1] = 40;
	chicken2[2][0] = 200;
	chicken2[2][1] = 80;
	chicken2[3][0] = 201;
	chicken2[3][1] = 40;
    //this frame are the closed legs 
    chicken3[0][0] = 200;
	chicken3[0][1] = 80;
	chicken3[1][0] = 199;
	chicken3[1][1] = 40;
	chicken3[2][0] = 200;
	chicken3[2][1] = 80;
	chicken3[3][0] = 201;
	chicken3[3][1] = 40;

}

//this function will create a circle given the radius, and the X and Y position 
void circle(double radius, double xc, double yc) 
{
	int i;
	double angle = 2 * 3.1415 / 20;
	double circle_xy[40][2];

	circle_xy[0][0] = radius + xc;
	circle_xy[0][1] = yc;

    glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 0.0);
	for (i = 1; i < 20; i++) {
		circle_xy[i][0] = radius*cos(i*angle) + xc;
		circle_xy[i][1] = radius*sin(i*angle) + yc;

		glVertex2f(circle_xy[i - 1][0], circle_xy[i - 1][1]);
		glVertex2f(circle_xy[i][0], circle_xy[i][1]);
	}
	glEnd();
}

//same function but circle is filled in 
void circleClouds(double radius, double xc, double yc) 
{
	int i;
	double angle = 2 * 3.1415 / 20;
	double circle_xy[40][2];

	circle_xy[0][0] = radius + xc;
	circle_xy[0][1] = yc;

	glBegin(GL_POLYGON);
	for (i = 1; i < 20; i++) {
		circle_xy[i][0] = radius*cos(i*angle) + xc;
		circle_xy[i][1] = radius*sin(i*angle) + yc;

		glVertex2f(circle_xy[i - 1][0], circle_xy[i - 1][1]);
		glVertex2f(circle_xy[i][0], circle_xy[i][1]);
	}
	glEnd();
}

//This creates the road where the chicken walks 
void road() 
{
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
	glVertex2d(0.0, 50.0);
	glVertex2d(800.0, 50.0);
	glVertex2d(800.0, 0.0);
	glVertex2d(0.0, 0.0);
	glEnd();
}
//this creates the blue sky for when the chicken is walking 
void sky() 
{
	glColor3f(0.5, 0.8, 0.9);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
	glVertex2d(0.0, 50.0);
	glVertex2d(0.0, 300.0);
	glVertex2d(800.0, 300.0);
	glVertex2d(800.0, 0.0);
	glEnd();
}
//this creates the background for the crash 
void background2() 
{
	//Grass
	glColor3f(0.5, 0.8, 0.3);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);   
	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, 300.0);
	glVertex2d(800.0, 300.0);
	glVertex2d(800.0, 0.0);
	glEnd();
    //Road 1
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);             
	glVertex2d(0.0, 50.0);
	glVertex2d(0.0, 150.0);
	glVertex2d(800.0, 150.0);
	glVertex2d(800.0, 50.0);
	glEnd();
    //Road 2
	glBegin(GL_POLYGON);             
	glVertex2d(500.0, 0.0);
	glVertex2d(500.0, 300.0);
	glVertex2d(700.0, 300.0);
	glVertex2d(700.0, 0.0);
	glEnd();
    //road slipt
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);         
	glVertex2d(10.0, 95.0);
	glVertex2d(10.0, 105.0);
	glVertex2d(60.0, 105.0);
	glVertex2d(60.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(110.0, 95.0);
	glVertex2d(110.0, 105.0);
	glVertex2d(160.0, 105.0);
	glVertex2d(160.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(210.0, 95.0);
	glVertex2d(210.0, 105.0);
	glVertex2d(260.0, 105.0);
	glVertex2d(260.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(310.0, 95.0);
	glVertex2d(310.0, 105.0);
	glVertex2d(360.0, 105.0);
	glVertex2d(360.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(410.0, 95.0);
	glVertex2d(410.0, 105.0);
	glVertex2d(460.0, 105.0);
	glVertex2d(460.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(510.0, 95.0);
	glVertex2d(510.0, 105.0);
	glVertex2d(560.0, 105.0);
	glVertex2d(560.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(610.0, 95.0);
	glVertex2d(610.0, 105.0);
	glVertex2d(660.0, 105.0);
	glVertex2d(660.0, 95.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(710.0, 95.0);
	glVertex2d(710.0, 105.0);
	glVertex2d(760.0, 105.0);
	glVertex2d(760.0, 95.0);
	glEnd();
    //Road split 
	glBegin(GL_POLYGON);        
	glVertex2d(595.0, 300.0);
	glVertex2d(605.0, 300.0);
	glVertex2d(605.0, 250.0);
	glVertex2d(595.0, 250.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(595.0, 200.0);
	glVertex2d(605.0, 200.0);
	glVertex2d(605.0, 150.0);
	glVertex2d(595.0, 150.0);
	glEnd();
	//Chicken in the scene 
  	//body
	glColor3f(1.0, 1.0, 0.0);
    circleClouds(8, 620, 120);
	//head
    circleClouds(6, 632, 127);
	//legs
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2d(620.0, 112.0);
	glVertex2d(615.0, 107.0);
	glVertex2d(620.0, 112.0);
	glVertex2d(625.0, 107.0);
	glEnd();
	//eye
	glPointSize(3.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2d(634.0, 129.0);
	glEnd();
	//wing
	/*glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex2d(617.0, 120.0);
	glVertex2d(620.0, 115.0);
	glVertex2d(620.0, 115.0);
	glVertex2d(623.0, 120.0);
	glEnd();*/
	
}

void scene2car1() 
{ //first car in crash scene
	glColor3f(0.0, 0.5, 0.5);
	glLineWidth(1.0);
	//car body 
	glBegin(GL_POLYGON);		
	glVertex2d(20.0, 115.0);
	glVertex2d(20.0, 135.0);
	glVertex2d(70.0, 135.0);
	glVertex2d(70.0, 115.0);
	glEnd();
    //first set of wheels 
	glBegin(GL_POLYGON);		
	glVertex2d(25.0, 110.0);
	glVertex2d(35.0, 110.0);
	glVertex2d(35.0, 140.0);
	glVertex2d(25.0, 140.0);
	glEnd();
    //second set of wheels 
	glBegin(GL_POLYGON);		
	glVertex2d(65.0, 110.0);
	glVertex2d(55.0, 110.0);
	glVertex2d(55.0, 140.0);
	glVertex2d(65.0, 140.0);
	glEnd();
}


void roadsplit() 
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_POLYGON);
	glVertex2d(10.0, 30.0);
	glVertex2d(110.0, 30.0);
	glVertex2d(110.0, 10.0);
	glVertex2d(10.0, 10.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(210.0, 30.0);
	glVertex2d(310.0, 30.0);
	glVertex2d(310.0, 10.0);
	glVertex2d(210.0, 10.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(410.0, 30.0);
	glVertex2d(510.0, 30.0);
	glVertex2d(510.0, 10.0);
	glVertex2d(410.0, 10.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(610.0, 30.0);
	glVertex2d(710.0, 30.0);
	glVertex2d(710.0, 10.0);
	glVertex2d(610.0, 10.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(810.0, 30.0);
	glVertex2d(910.0, 30.0);
	glVertex2d(910.0, 10.0);
	glVertex2d(810.0, 10.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(1010.0, 30.0);
	glVertex2d(1110.0, 30.0);
	glVertex2d(1110.0, 10.0);
	glVertex2d(1010.0, 10.0);
	glEnd();
}

void tween(int source[4][2], int destination[4][2], int numPoints, double proportion, int tweenPoly[4][2]) 
{
	for (int p = 0; p < numPoints; p++) {
		double sourceX = source[p][0]; //get all points for source 
		double sourceY = source[p][1];

		double destinationX = destination[p][0]; //get all matching points for detination 
		double destinationY = destination[p][1];

		double differenceX = (destinationX - sourceX); //calculate the difference 
		double differenceY = (destinationY - sourceY);

		double tweenX = sourceX + (differenceX*proportion); //calculates how far it has to move to reach destination 
		double tweenY = sourceY + (differenceY*proportion);

		tweenPoly[p][0] = int(tweenX); //send points 
		tweenPoly[p][1] = int(tweenY);
	}
}

void drawText(const char *text, int length, int x, int y)
{
	int i;
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glPushMatrix();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	}
	glPopMatrix();
	glLoadMatrixd(matrix);
}



void movingp() 
{//moves the chicken forward 
	tx = tx + 5;  //chicken moves 5 steps in X-dir
	ty = ty + 0; //chicken stays in same Y-dir 
	glutPostRedisplay();
}

void setViewport( int left, int right, int bottom, int top )
{
  glViewport( left, bottom, right - left, top - bottom );
}

void clouds() 
{
    //sun
	glColor3f(1.0, 1.0, 0.0);
	setViewport(550, 800, 200, 300);
	circleClouds(150, 750, 300);
    //clouds
	glColor3f(1.0, 1.0, 1.0);
	setViewport(0, 250, 200, 300);
	circleClouds(55, 100, 200);
	circleClouds(100, 200, 200);
	circleClouds(55, 300, 200);

	setViewport(100, 350, 200, 300);
	circleClouds(70, 200, 200);
	circleClouds(100, 275, 200);
	circleClouds(70, 333, 200);
	
	setViewport(250, 500, 200, 300);
	circleClouds(100, 350, 200);
	circleClouds(40, 230, 200);
	circleClouds(55, 430, 200);

    setViewport(300, 570, 200, 300);
	circleClouds(50, 320, 200);
	circleClouds(100, 400, 200);
	circleClouds(60, 490, 200);

	setViewport(400, 700, 200, 300);
	circleClouds(55, 350, 200);
	circleClouds(100, 450, 200);
	circleClouds(55, 550, 200);

	setViewport(510, 760, 200, 300);
	circleClouds(65, 480, 200);
	circleClouds(100, 570, 200);
	circleClouds(100, 700, 200);
	
}

void movecar1() 
{
	glPushMatrix();
	glTranslatef(mcx, mcy, 0.0);
	scene2car1();
	glPopMatrix();
	mcx = mcx + 10;
	mcy = mcy + 0;
}

void crashscene() 
{
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(400.0, 150.0, 0.0);
	glScalef(cx, cy, 1.0);
	glTranslatef(-400.0, -150.0, 0.0);

	glBegin(GL_POLYGON);
	glVertex2d(400.0, 280.0);
	glVertex2d(450.0, 220.0);
	glVertex2d(580.0, 240.0);
	glVertex2d(550.0, 170.0);
	glVertex2d(650.0, 130.0);
	glVertex2d(550.0, 90.0);
	glVertex2d(510.0, 20.0);
	glVertex2d(400.0, 70.0);
	glVertex2d(280.0, 50.0);
	glVertex2d(300.0, 110.0);
	glVertex2d(200.0, 170.0);
	glVertex2d(370.0, 200.0);
	glVertex2d(380.0, 250.0);
	glEnd();

	//print text 
	string text;
	text = "CRASH";
	glColor3f(0.0, 0.0, 0.0);
	drawText(text.data(), text.size(), 50, 200);

	glPopMatrix();
	cx = cx*1.05;
	cy = cy*1.05;
}

void message1() 
{
	
	//print text 
	string text2;
	string text3;
	text2 = "ALWAYS BE AWARE WHEN DRIVING!!!";
	text3 = "TAKE CARE OF WILDLIFE/ANIMALS";
	glColor3f(0.0, 0.0, 0.0);
	drawText(text2.data(), text2.size(), 200, 150);
	drawText(text3.data(), text2.size(), 200, 120);
}

void message2()
{
	//print text
	string text4;
	text4 = "The End";
	glColor3f(0.0, 0.0, 0.0);
	drawText(text4.data(), text4.size(), 350, 150);
}
void walk1() 
{
	int i;
	glLineWidth(4.0);
	glColor3f(1.0, 1.0, 0.0);
	circle(50, 200, 130);
	circle(30, 260, 185);
	circle(3, 270, 195);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	 glVertex2i(185, 135);
	 glVertex2i(200, 110);
	 glVertex2i(215, 135);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2i(286, 190);
	 glVertex2i(318, 186);
	 glVertex2i(286, 182);
	 glVertex2i(286, 190);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	for (i = 0; i < 4; i++)
		glVertex2i(tweenPoly[i][0], tweenPoly[i][1]);
	glEnd();
}

void walk2() 
{
	int i;
	glLineWidth(4.0);
	glColor3f(1.0, 1.0, 0.0);
	circle(50, 200, 130);
	circle(30, 260, 185);
	circle(3, 270, 195);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	 glVertex2i(185, 135);
	 glVertex2i(200, 110);
	 glVertex2i(215, 135);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2i(286, 190);
	 glVertex2i(318, 186);
	 glVertex2i(286, 182);
	 glVertex2i(286, 190);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	for (i = 0; i < 4; i++)
		glVertex2i(chicken3[i][0], chicken3[i][1]);
	glEnd();
}

void walk3() {
	int i;
	glLineWidth(4.0);
	glColor3f(1.0, 1.0, 0.0);
	circle(50, 200, 130);
	circle(30, 260, 185);
	circle(3, 270, 195);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	 glVertex2i(185, 135);
	 glVertex2i(200, 110);
	 glVertex2i(215, 135);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2i(286, 190);
	 glVertex2i(318, 186);
	 glVertex2i(286, 182);
	 glVertex2i(286, 190);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	for (i = 0; i < 4; i++)
		glVertex2i(tweenPoly[i][0], tweenPoly[i][1]);
	glEnd();
}

void walk4() 
{
	int i;
	glLineWidth(4.0);
	glColor3f(1.0, 1.0, 0.0);
	circle(50, 200, 130);
	circle(30, 260, 185);
	circle(3, 270, 195);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	 glVertex2i(185, 135);
	 glVertex2i(200, 110);
	 glVertex2i(215, 135);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2i(286, 190);
	 glVertex2i(318, 186);
	 glVertex2i(286, 182);
	 glVertex2i(286, 190);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);  //For a stick figure is might be good to do Lines instead. Points are not all connected.
	for (i = 0; i < 4; i++)
		glVertex2i(chicken1[i][0], chicken1[i][1]);
	glEnd();
}

void walk5() 
{
	int i;
	glLineWidth(4.0);
	glColor3f(1.0, 1.0, 0.0);
	circle(50, 200, 130);
	circle(30, 260, 185);
	circle(3, 270, 195);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	 glVertex2i(185, 135);
	 glVertex2i(200, 110);
	 glVertex2i(215, 135);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	 glVertex2i(286, 190);
	 glVertex2i(318, 186);
	 glVertex2i(286, 182);
	 glVertex2i(286, 190);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	for (i = 0; i < 10; i++)
		glVertex2i(chicken2[i][0], chicken2[i][1]);
	glEnd();
}


void main1() 
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	init();
	glDisable(GL_DEPTH_TEST);
}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	frame++;
	glLineWidth(1.0);

	if (frame == 1) main1();
	else if ((frame >= 1) && (frame < 520)) 
	{			//Scene 1
		glViewport(0, 0, 800, 300);
		sky();
		road();
		roadsplit();
		walkframe++;
		if ((walkframe >= 0) && (walkframe < 16)) 
		{
			if (walkframe == 0) proportion = 0.0;
			glPushMatrix();
			glTranslatef(tx, ty, 0.0);
			tween(chicken1, chicken2, 4, proportion, tweenPoly);
			walk1();
			glPopMatrix();
			proportion = proportion + 0.05;
			if (proportion > 1.0) proportion = 0.0;
		}
		else if ((walkframe >= 16) && (walkframe < 22)) 
		{
			if (walkframe == 16) proportion = 0.0;
			glPushMatrix();
			glTranslatef(tx, ty, 0.0);
			walk2();
			glPopMatrix();
		}
		else if ((walkframe >= 22) && (walkframe < 36)) 
		{
			if (walkframe == 22) proportion = 0.0;
			glPushMatrix();
			glTranslatef(tx, ty, 0.0);
			tween(chicken2, chicken1, 4, proportion, tweenPoly);
			walk3();
			glPopMatrix();
			proportion = proportion + 0.05;
			if (proportion > 1.0) proportion = 0.0;
		}
		else if ((walkframe >= 36) && (walkframe < 40)) 
		{
			if (walkframe == 36) proportion = 0.0;
			glPushMatrix();
			glTranslatef(tx, ty, 0.0);
			walk4();
			glPopMatrix();
			movingp(); //moves the whole chicken forward 
		}
		else if (walkframe > 40) 
		{
			walkframe = 0;
		}
		clouds();
	}
	else if ((frame >= 520) && (frame < 575)) 
	{	//Scene 2
	    glViewport(0, 0, 800, 300);
		background2();
		movecar1();
	}
	else if ((frame >= 575) && (frame < 635)) 
	{	//Scene 3
	    glViewport(0, 0, 800, 300);
		crashscene();
	}
	else if ((frame >= 635) && (frame < 695)) 
	{	//Scene 4
	    glViewport(0, 0, 800, 300);
		message1();
	}
	else if ((frame >= 695 ) && (frame < 755 ))
	{
		//scene 5
		glViewport(0, 0, 800, 300);
		message2();
	}
	else if (frame >= 755) 
	{   
		frame = 0;
		walkframe = 0;
		proportion = 0.0;
	}
	glFlush();
	glutSwapBuffers();
	printf("Frame number= %i\n", frame);
}

void Timer(int) 
{
	glutPostRedisplay();
	//glutTimerFunc(1000/60, Timer, 0);
	glutTimerFunc(40, Timer, 0);
}

void visibility(int state) 
{
	switch (state) {
	case GLUT_VISIBLE:
		Timer(1);
		break;
	case GLUT_NOT_VISIBLE:
		Timer(0);
		break;
	default:
		break;
	}
}


int main(int argc, char** argv) 
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Final Project");
	init();
	glutDisplayFunc(display);
	glutVisibilityFunc(visibility);

	glutMainLoop();

	return 0;
}



