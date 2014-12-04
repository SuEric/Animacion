#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float z_rotation, view_angle = 0, alpha = 6.0;
double toRadians = 3.141593/180.0;
int sign = -1;


void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);
    
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    
    // Materiales
	float mamb[]={0.24725f, 0.1995f, 0.0745f, 1.0f};
	float mdif[]={0.75164f, 0.60648f, 0.22648f, 1.0f};
	float mspe[]={0.628281f, 0.555802f, 0.366065f, 1.0f};
    
	glMaterialfv(GL_FRONT, GL_AMBIENT, mamb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mdif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mspe);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    
    // Luces
	float lint[]={1.0f, 1.0f, 1.0f, 1.0f};
	float lamb[]={0.3f, 0.3f, 0.3f, 1.0f};
    
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lint);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lint);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lamb);
    
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-12., 12., -12., 12., 0., 100.);
}


void normal(double x1, double y1, double z1, double x2, double y2, double z2,
			double x3, double y3, double z3)
{
	double nx, ny, nz;
    
	nx = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
	ny = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
	nz = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    
    glNormal3f(nx, ny, nz);
}

void cylinder()
{
	float x1, x2, y1, y2, z1, z2;
	
    glBegin(GL_QUADS);
    
	for(int angle = 0; angle < 360; angle += 20) {
		y1 = 2.0*cos(angle*toRadians);
		z1 = 2.0*sin(angle*toRadians);
		y2 = 2.0*cos((angle+20)*toRadians);
		z2 = 2.0*sin((angle+20)*toRadians);
		
        for(int x = 0; x < 6; x++) {
			x1 = x; x2 = x+1;
			glNormal3f(0, y1, z1); glVertex3f(x1, y1, z1);
			glNormal3f(0, y2, z2); glVertex3f(x1, y2, z2);
			glNormal3f(0, y2, z2); glVertex3f(x2, y2, z2);
			glNormal3f(0, y1, z1); glVertex3f(x2, y1, z1);
		}
	}
    
	glEnd();
}

float hermite(float p0, float p3, float tangent1, float tangent2, float t){
	float p, t2 = t*t, t3 = t2*t;
    
	p = (1 - 3*t2 + 2*t3)*p0 + (t - 2*t2 + t3)*alpha*tangent1 +(-t2 + t3)*alpha*tangent2 + (3*t2 - 2*t3)*p3;
	
    return p;
}

// Hermite Interpolation
void blendingSurface()
{
	float xe1, ye1, ze1, xe2, ye2, ze2, xe3, ye3, xe4, ye4;
	float xe3T, ye3T, xe4T, ye4T;
	float x1, y1, x2, y2, x3, y3, x4, y4;
	float t;
	float cosRotn = cos(z_rotation*toRadians);
	float sinRotn = sin(z_rotation*toRadians);
    
	glBegin(GL_QUADS);
    for(int angle = 0; angle < 360; angle += 20){
        //------End Point 1 (stationary)-------
        xe1 = -3.0;
        ye1 = 2.0*cos(angle*toRadians);
        ze1 = 2.0*sin(angle*toRadians);
        //------End Point 2 (stationary)-------
        xe2 = -3.0;
        ye2 = 2.0*cos((angle+20)*toRadians);
        ze2 = 2.0*sin((angle+20)*toRadians);
        //------End Point 3 (initial)-------
        xe3 = 3.0;
        ye3 = ye2;
        //------End Point 4 (initial)-------
        xe4 = 3.0;
        ye4 = ye1;
        //------End Point 3 (transformed)-------
        xe3T = xe3*cosRotn - ye3*sinRotn;
        ye3T = xe3*sinRotn + ye3*cosRotn;
        //------End Point 4 (transformed)-------
        xe4T = xe4*cosRotn - ye4*sinRotn;
        ye4T = xe4*sinRotn + ye4*cosRotn;
        
        for(int j = 0; j <= 10; j ++){		//Interpolate between end points
            t = 0.1*j;				//parameter of interpolation
            x3 = hermite(xe2, xe3T, 1.0, cosRotn, t);
            y3 = hermite(ye2, ye3T, 0.0, sinRotn, t);
            x4 = hermite(xe1, xe4T, 1.0, cosRotn, t);
            y4 = hermite(ye1, ye4T, 0.0, sinRotn, t);
            
            if(j > 0) {
                normal(x1, y1, ze1, x2, y2, ze2, x3, y3, ze2);
                glVertex3f(x1, y1, ze1);
                glVertex3f(x2, y2, ze2);
                glVertex3f(x3, y3, ze2);
                glVertex3f(x4, y4, ze1);
            }
            x1 = x4;  y1 = y4;
            x2 = x3;  y2 = y3;
        }
	}
	glEnd();
}

void display()
{
	float lpos[]={10.0f, 5.0f, 20.0f, 1.0f};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.,0., 20.,0., 0.,0., 0., 1., 0.);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    
	glRotated(view_angle, 0., 1., 0.);
    
	glPushMatrix();
    glRotated(z_rotation, 0., 0., 1.);
    glTranslated(3, 0, 0);
    cylinder();
	glPopMatrix();
    
	glPushMatrix();
    glTranslated(-9, 0, 0);
    cylinder();
	glPopMatrix();
    
    blendingSurface();
    
	glFlush();
	glutSwapBuffers();
}


void animate(int value)
{
	if(value < 600)   //Animate for 1 minute
	{
		z_rotation += sign;  // Z Axis Rotation
        
		if( (z_rotation < 0.0) || (z_rotation > 90) ) sign =- sign;
		
        glutPostRedisplay();
		
        value++;
		glutTimerFunc(100, animate, value);
	}
}


void mouse(int b, int s, int x, int y)
{
	if(b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
		glutTimerFunc(100, animate, 0);
    
	glutPostRedisplay();
}


void special(int key, int x, int y)
{
	switch(key) {
	    case GLUT_KEY_LEFT: view_angle--; break;
	    case GLUT_KEY_RIGHT: view_angle++; break;
	    case GLUT_KEY_UP: alpha++; break;
	    case GLUT_KEY_DOWN: alpha--; break;
	}
    
    if(alpha < 0) alpha = 0.0;
    if(alpha > 6) alpha = 6.0;
    
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Vertex Blending with Hermite Interpolation");
    
    init();
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutSpecialFunc(special);
    
    glutMainLoop();
    return 0;
}