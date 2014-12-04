#include <iostream>
#include <cmath>
#include <GLUT/glut.h>

using namespace std;

float xtarg = 5.0, ytarg = 4.0;  //target position (changeable via mouse input)
int windowWidth = 600, windowHeight = 600;
float a=0,s=0; float d=0,z=0,x=0,c=0;
float aa=0,ss=0; float dd=0,zz=0,xx=0,cc=0;

float theta[6] = {a,s,d,z,x,c};   //joint angles
float thetaInv[6] = {aa,ss,dd,zz,xx,cc};   //joint angles

int k;
static char label[100];

static int isAnimate = 0; // Animated?
static int animationPeriod = 50; // Time interval between frames.

void drawString (char *s){
	unsigned int i;
	for (i = 0; i < strlen (s); i++)
		glutBitmapCharacter (GLUT_BITMAP_HELVETICA_10, s[i]);
    
}

//-------Reset the chain ----------------------------------------------------
void reset()
{
    for	(int i = 0; i < 10; i++) theta[i] = 0.0;
}

//-------Draws a link of the joint chain ------------------------------------
void drawTriangle(int i)
{
    
	if(i%2==0 ) glColor3f( 0, 255, 0);
	else glColor3f( 0, 0, 255);
    //   if(k==' '){
    glRotatef(theta[i], 0.0, 0.0, 1.);
	glBegin(GL_POLYGON);
    glVertex2f(0.0, -0.5);
    glVertex2f(2.0, -0.5);
    glVertex2f(2.0, 0.5);
    glVertex2f(0.0, 0.5);
	glEnd();
	//glColor3f(0., 0., 0.);
	glBegin(GL_LINE_LOOP);
    glVertex2f(0.0, -0.5);
    glVertex2f(2.0, -0.5);
    glVertex2f(2.0, 0.5);
    glVertex2f(0.0, 0.5);
	glEnd();
}

//-------Draws target location and target vector ------------------------------
void drawTarget()
{
    glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0);
	//glRotated(90,0,0,1);
	glBegin(GL_LINES);
    glVertex2d(xtarg-0.2, ytarg);
    glVertex2d(xtarg+0.2, ytarg);
    glVertex2d(xtarg, ytarg-0.2);
    glVertex2d(xtarg, ytarg+0.2);
	glEnd();
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex2f(xtarg, ytarg);
	glVertex2f(0, 0);
	glEnd();
}

//-------Computes joint angles -----------------------------------------------
void computeAngles()
{
	float dTarg = sqrt(xtarg*xtarg + ytarg*ytarg);   //distance from base to target
	float len = 2.0;  //link length;
	float n = 6.0;   //number of links
	float beta = 0.0,  betaPrev;  // initial condition
	float diff = 1000.0;  //A large value
	float numerator, denominator;
    float pi2 = 3.141593*0.5;
    float toDeg = 180.0/3.141593;
	float angle1, angle2;
    
	cout << "dtarg = " << dTarg << endl;
	cout << "xtarg = " << xtarg<< endl;
	cout << "ytarg = " << ytarg << endl;
    if(len*6 < dTarg)
    {
        //reset();
        thetaInv[0] = atan2(ytarg, xtarg)*toDeg;
    }
    else
    {
        if(len*6 < pi2*dTarg) beta = pi2;  //Initial condition
		else beta = 3.0*pi2;
 		while (diff > 0.0001)  //Newton-Raphson solver
	    {
		    betaPrev = beta;
		    numerator = len*sin(betaPrev*0.5) - dTarg*sin(betaPrev*0.5/n);
		    denominator = len*0.5*cos(betaPrev*0.5) - dTarg*0.5*cos(betaPrev*0.5/n)/n;
		    beta = betaPrev - (numerator/denominator);
		    diff = fabs(beta - betaPrev);
	    }
		angle1 = atan2(ytarg, xtarg) + (pi2 - beta*0.5);
		angle2 = (pi2 - beta*0.5/n);
		thetaInv[0] = (angle1-angle2)*toDeg;
		for	(int i = 1; i < 6; i++) thetaInv[i] = beta*toDeg/n;
    }
    
}

//-------Initializes drawing parameters ------------------------------------
void initialize(void) {
    
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-25.0, 25.0, -25., 25.);
}

//----------- Display:  The main display module ------------------------------
void display(void) {
    
	GLUquadric *myQuad;
	myQuad=gluNewQuadric();
	
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
	glColor3f(255,0,0);
	glBegin(GL_POLYGON);
	glVertex2d( -2, 0);
	glVertex2d( -2, -1);
 	glVertex2d( 2, -1);
  	glVertex2d( 2, 0);
	glEnd();
	
	drawTarget();
	for(int i = 0; i < 6; i++)
	{
		if(i > 0) glTranslatef(2.0, 0.0, 0.0);
        //		glRotatef(theta[i], 0., 0., 1.);
		drawTriangle(i);
		if(i%2==0 ) glColor3f( 0, 255, 0);
        else glColor3f( 0, 0, 255);
		gluSphere(myQuad, .5, 100, 100);
	}
    
	glutSwapBuffers();
    glFlush();
}

//----------- Mouse callback to accept target location ------------------------
void mouse(int b, int s, int x, int y){
	if(b==GLUT_LEFT_BUTTON && s==GLUT_DOWN){
		xtarg = (float)(x*50)/windowWidth - 25.0;
		ytarg = (float)(windowHeight-y)*50.0/windowHeight - 25.0;
		glutPostRedisplay();
	}
}

//-------Keyboard callback to step to next iteration ----------------------
/*void keyboard(unsigned char k, int xp, int yp)
 {
 switch(k)
 {
 case ' ':
 computeAngles();
 glutPostRedisplay();
 break;
 case 'a':
 theta[0]++;
 //glutPostRedisplay();
 break;
 case 's':
 theta[1]++;
 glutPostRedisplay();
 break;
 case 'd':
 theta[2]++;
 glutPostRedisplay();
 break;
 case 'z':
 theta[3]++;
 glutPostRedisplay();
 break;
 case 'x':
 theta[4]++;
 glutPostRedisplay();
 break;
 case 'c':
 theta[5]++;
 glutPostRedisplay();
 break;
 }
 }*/

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'w':
        case 'W':
            //if(theta1<90)
            theta[0]=theta[0]+10;
            glutPostRedisplay();                                //theta1 + ...
            break;
        case 'q':
        case 'Q':
            //if(theta1>-90)
            theta[0]=theta[0]-10;
            glutPostRedisplay();                                //theta1 - ...
            break;
        case 's':
        case 'S':
            //if(theta2<90)
            theta[1]=theta[1]+10;
            glutPostRedisplay();                                //theta2 + ...
            break;
        case 'a':
        case 'A':
            //if(theta2>-90)
            theta[1]=theta[1]-10;
            glutPostRedisplay();                                //theta2 - ...
            break;
        case 'x':
        case 'X':
            //if(theta3<90)
            theta[2]=theta[2]+10;
            glutPostRedisplay();                                //theta3 + ...
            break;
        case 'z':
        case 'Z':
            //if(theta3>-90)
            theta[2]=theta[2]-10;
            glutPostRedisplay();                                //theta3 - ...
            break;
        case 'p':
        case 'P':
            //if(theta4<90)
            theta[3]=theta[3]+10;
            glutPostRedisplay();                                //theta4 + ...
            break;
        case 'o':
        case 'O':
            //if(theta4>-90)
            theta[3]=theta[3]-10;
            glutPostRedisplay();                                //theta4 - ...
            break;
        case 'l':
        case 'L':
            //if(theta5<90)
            theta[4]=theta[4]+10;
            glutPostRedisplay();                                //theta5 + ...
            break;
        case 'k':
        case 'K':
            //if(theta5>-90)
            theta[4]=theta[4]-10;
            glutPostRedisplay();                                //theta5 - ...
            break;
        case 'm':
        case 'M':
            //if(theta6<90)
            theta[5]=theta[5]+10;
            glutPostRedisplay();                                //theta6 + ...
            break;
        case 'n':
        case 'N':
            //if(theta6>-90)
            theta[5]=theta[5]-10;
            glutPostRedisplay();                                //theta6 - ...
            break;
        case 'b':
        case 'B':
            computeAngles();
            glutPostRedisplay();                                //theta6 - ...
            break;
        case ' ':
			computeAngles();
            if(isAnimate) isAnimate = 0;                        //inversa...
            else isAnimate = 1;
            break;
        default:
            break;
        case 27:
            exit(0);                                            //Salir...
            break;
    }
}

void inversa()
{
    if(theta[0]>thetaInv[0])
        theta[0]--;
    if(theta[0]<thetaInv[0])
        theta[0]++;
    if(theta[1]>thetaInv[1])
        theta[1]--;
    if(theta[1]<thetaInv[1])
        theta[1]++;
    if(theta[2]>thetaInv[2])
        theta[2]--;
    if(theta[2]<thetaInv[2])
        theta[2]++;
    if(theta[3]>thetaInv[3])
        theta[3]--;
    if(theta[3]<thetaInv[3])
        theta[3]++;
    if(theta[4]>thetaInv[4])
        theta[4]--;
    if(theta[4]<thetaInv[4])
        theta[4]++;
    if(theta[5]>thetaInv[5])
        theta[5]--;
    if(theta[5]<thetaInv[5])
        theta[5]++;
    glutPostRedisplay();
    
}

//----------- Reshape function callback ----------------------------------
void reshape(int wid, int hgt)
{
	windowWidth = wid;
	windowHeight = hgt;
	glViewport(0, 0, wid, hgt);
}

void animate(int someValue)
{
    if (isAnimate) inversa();
    
    // Note that glutTimerFunc() calls animate() *once* after the
    // specified msecs. Therefore, to make repeated calls, animate()
    // must call itself again with glutTimerFunc() as below.
    glutTimerFunc(animationPeriod, animate, 1);
}

//  ------- Main: Initialize glut window and register call backs -----------
int main( int argc, char **argv) {
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Puma 2D...");
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    initialize();
    
    glutTimerFunc(5, animate, 1);
    glutMainLoop();
    return 0;
}
