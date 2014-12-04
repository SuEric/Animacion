#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define XSIZE 500
#define YSIZE 500
#define REAL double
#define NUMPOSITIONS 4
#define QUADC 0.4*2.0
#define QUADH 0.08*2.0
#define MAG_DIST 5.3f

struct point3d
{
    REAL x, y, m;
};

float spin = 25.0f, userXPos = 0.0f, userYPos = 0.0f;
int thisPosition = 1, spinFlag = 0, userInControl = 0;
int xOnButtonDown, yOnButtonDown;
REAL w = 0.01, delta = 0.03;

GLfloat red[] = {0.6, 0.03, 0.03, 1.0};
GLfloat red2[] = {1.0, 0.01, 0.01, 1.0};
GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
GLfloat gray[] = {0.6, 0.6, 0.6, 1.0};
GLfloat gray2[] = {0.25, 0.25, 0.25, 1.0};
GLfloat light_position[] = {0.5, 0.0, 2.0, 0.0};

static struct point3d
a = { 0.0,  0.45818, 1.0}, /* Should be 0.433 somehow, who cares */
b = { 0.5, -0.433, 1.0},
c = {-0.5, -0.433, 1.0},

p = {-1.0, -0.010, 1.0}, /* Actual position of pendulum */
vp = {0.0,  0.000, 0.0}, /* Actual velocity of pendulum */

startP[NUMPOSITIONS] = {
	{-1.0, -0.010, 1.0},
	{ 0.0,  0.000, 1.0},
	{ 0.5,  0.500, 1.0},
	{ 0.2, -0.300, 1.0}},

startVp[NUMPOSITIONS] = {
	{ 0.0,  0.000, 0.0},
	{ 0.7,  0.000, 0.0},
	{-0.5, -0.330, 0.0},
	{ 1.6, -1.432, 0.0}};

void normalize(float v[3])
{
    float d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    if (d != 0.0) /* avoid division by zero */
    {
        v[0] /= d;
        v[1] /= d;
        v[2] /= d;
    }
}

void normCrossProd(float v1[3], float v2[3], float out[3])
{
    out[0] = v1[1]*v2[2] - v1[2]*v2[1];
    out[1] = v1[2]*v2[0] - v1[0]*v2[2];
    out[2] = v1[0]*v2[1] - v1[1]*v2[0];
    normalize(out);
}

REAL normexp3(REAL rx, REAL ry, REAL px, REAL py)
{
    REAL i=sqrt((rx-px)*(rx-px)+(ry-py)*(ry-py)+0.1);
    return i*i*i;
}

REAL f(REAL am, REAL bm, REAL cm, REAL ax, REAL bx, REAL cx,
       REAL ay, REAL by, REAL cy, REAL x0, REAL y0, REAL vx0, REAL vy0)
{
    return am*(ax-x0)/normexp3(ax, ay, x0, y0)+
	bm*(bx-x0)/normexp3(bx, by, x0, y0)+
	cm*(cx-x0)/normexp3(cx, cy, x0, y0)-
	w*vx0*sqrt(vx0*vx0 +vy0*vy0);
}

REAL g(REAL am, REAL bm, REAL cm, REAL ax, REAL bx, REAL cx,
       REAL ay, REAL by, REAL cy, REAL x0, REAL y0, REAL vx0, REAL vy0)
{
    return am*(ay-y0)/normexp3(ax, ay, x0, y0)+
	bm*(by-y0)/normexp3(bx, by, x0, y0)+
	cm*(cy-y0)/normexp3(cx, cy, x0, y0)-
	w*vy0*sqrt(vx0*vx0 +vy0*vy0);
}

void newton(void)
{
    REAL k1, k2, k3, k4, l1, l2, l3, l4, n1, n2, n3, n4,
	x0, x1, x2, x3, y0, y1, y2, y3, vx0, vx1, vx2, vx3,
	vy0, vy1, vy2, vy3, m1, m2, m3, m4, h=delta;
    
    x0=p.x;
    y0=p.y;
    vx0=vp.x;
    vy0=vp.y;
    
    k1=h*vx0;
    l1=h*vy0;
    m1=h*f(a.x, b.m, c.m, a.x, b.x, c.x, a.y, b.y, c.y, x0, y0, vx0, vy0);
    n1=h*g(a.x, b.m, c.m, a.x, b.x, c.x, a.y, b.y, c.y, x0, y0, vx0, vy0);
    x1=x0+k1/2.0;
    y1=y0+l1/2.0;
    vx1=vx0+m1/2.0;
    vy1=vy0+n1/2.0;
    k2=h*(vx0+m1/2.0);
    l2=h*(vy0+n1/2.0);
    m2=h*f(a.m, b.m, c.m, a.x, b.x, c.x, a.y, b.y, c.y, x1, y1, vx1, vy1);
    n2=h*g(a.m, b.m, c.m, a.x, b.x, c.x, a.y, b.y, c.y, x1, y1, vx1, vy1);
    x2=x0+k2/2.0;
    y2=y0+l2/2.0;
    vx2=vx0+m2/2.0;
    vy2=vy0+n2/2.0;
    k3=h*(vx0+m2/2.0);
    l3=h*(vy0+n2/2.0);
    m3=h*f(a.m, b.m, c.m, a.x, b.x, c.x, a.y, b.y, c.y, x2, y2, vx2, vy2);
    n3=h*g(a.m, b.m, c.m, a.x, b.x, c.x, a.y, b.y, c.y, x2, y2, vx2, vy2);
    x3=x0+k3;
    y3=y0+l3;
    vx3=vx0+m3;
    vy3=vy0+n3;
    k4=h*(vx0+m3);
    l4=h*(vy0+n3);
    m4=h*f(a.m, b.m, c.m, a.x, b.x, c.x, a.y, b.y, c.y, x3, y3, vx3, vy3);
    n4=h*g(a.m, b.m, c.m, a.x, b.x, c.x, a.y, b.y, c.y, x3, y3, vx3, vy3);
    if (!userInControl)
    {
        p.x+=(1.0/6.0)*(k1+2.0*k2+2.0*k3+k4);
        p.y+=(1.0/6.0)*(l1+2.0*l2+2.0*l3+l4);
        vp.x+=(1.0/6.0)*(m1+2.0*m2+2.0*m3+m4);
        vp.y+=(1.0/6.0)*(n1+2.0*n2+2.0*n3+n4);
    }
}

void drawQuad(void)
{
    glBegin(GL_QUADS);
    
    /* Front */
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-QUADC, QUADC, QUADH);
    glVertex3f(-QUADC, -QUADC, QUADH);
    glVertex3f(QUADC, -QUADC, QUADH);
    glVertex3f(QUADC, QUADC, QUADH);
    
    /* Right */
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(QUADC, QUADC, QUADH);
    glVertex3f(QUADC, -QUADC, QUADH);
    glVertex3f(QUADC, -QUADC, -QUADH);
    glVertex3f(QUADC, QUADC, -QUADH);
    
    /* Rear */
    /*
     glNormal3f(0.0f, 0.0f, -1.0f);
     glVertex3f(QUADC, QUADC, -QUADH);
     glVertex3f(QUADC, -QUADC, -QUADH);
     glVertex3f(-QUADC, -QUADC, -QUADH);
     glVertex3f(-QUADC, QUADC, -QUADH);
     */
    
    /* Left */
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-QUADC, QUADC, -QUADH);
    glVertex3f(-QUADC, -QUADC, -QUADH);
    glVertex3f(-QUADC, -QUADC, QUADH);
    glVertex3f(-QUADC, QUADC, QUADH);
    
    /* Top */
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-QUADC, QUADC, -QUADH);
    glVertex3f(-QUADC, QUADC, QUADH);
    glVertex3f(QUADC, QUADC, QUADH);
    glVertex3f(QUADC, QUADC, -QUADH);
    
    /* Bottom */
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(QUADC, -QUADC, -QUADH);
    glVertex3f(QUADC, -QUADC, QUADH);
    glVertex3f(-QUADC, -QUADC, QUADH);
    glVertex3f(-QUADC, -QUADC, -QUADH);
    
    glEnd();
}

/*  Draw a cylinder with height "h" and "c" segments and "s" size
 *  The bottom is not drawn because it's not visible
 */
void almostSolidCylinder(float s, int c, float h)
{
    GLfloat normal[3];
    
    int i;
    float angle, step = 2.0f*M_PI/(float)c;
    GLfloat p1[3], p2[3], p3[3], p4[3], v1[3], v2[3];
    
    /* Draw top */
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, 1.0f);
    for (i=0, angle=0.0; i<c; i++, angle+=step)
        glVertex3f(cos(angle)*s, sin(angle)*s, 0.0f);
    glEnd();
    
    /* Draw stick */
    glBegin(GL_QUADS);
    for (i=0, angle=0.0; i<c; i++, angle+=step)
    {
        p1[0] = p2[0] = cos(angle)*s;
        p1[1] = p2[1] = sin(angle)*s;
        p1[2] = 0.0f;
        p2[2] = h;
        
        p3[0] = p4[0] = cos(angle+step)*s;
        p3[1] = p4[1] = sin(angle+step)*s;
        p3[2] = 0.0f;
        p4[2] = h;
        
        /* Do the normal vector */
        v1[0] = p1[0] - p3[0];
        v1[1] = p1[1] - p3[1];
        v1[2] = p1[2] - p3[2];
	    
        v2[0] = p2[0] - p3[0];
        v2[1] = p2[1] - p3[1];
        v2[2] = p2[2] - p3[2];
        
        normCrossProd(v1, v2, normal);
        glNormal3fv(normal);
        
        /* Here's the vertexes */
        glVertex3f(p2[0], p2[1], p2[2]);
        glVertex3f(p4[0], p4[1], p4[2]);
        glVertex3f(p3[0], p3[1], p3[2]);
        glVertex3f(p1[0], p1[1], p1[2]);
    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, gray2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
    
    glPushMatrix();
    glTranslatef(MAG_DIST*a.x, MAG_DIST*a.y, -9.0);
    glCallList(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(MAG_DIST*b.x, MAG_DIST*b.y, -9.0);
    glCallList(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(MAG_DIST*c.x, MAG_DIST*c.y, -9.0);
    glCallList(1);
    glPopMatrix();
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, red);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red2);
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, -2.0);
    glRotatef(-p.x*50.0f, 0.0, 1.0, 0.0);
    glRotatef(p.y*50.0f, 1.0, 0.0, 0.0);
    glCallList(2);
    glTranslatef(0.0, 0.0, -6.5);
    glCallList(3);
    glPopMatrix();
    
    glPopMatrix();
    
    glFinish();
    glutSwapBuffers();
}

void idle(void)
{
    if (spinFlag)
    {
        spin += 1.0f;
        if (spin >= 360.0f)
            spin -= 360.0f;
    }
    
    newton();
    
    glutPostRedisplay();
}

void compileDisplayLists(void)
{
    glNewList(1, GL_COMPILE);
    drawQuad();
    glEndList();
    
    glNewList(2, GL_COMPILE);
    almostSolidCylinder(0.1, 12, -6.7);
    glEndList();
    
    glNewList(3, GL_COMPILE);
    glutSolidSphere(0.6, 20, 20);
    glEndList();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_AMBIENT, red);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red2);
    glMaterialf(GL_FRONT, GL_SHININESS, 90.0);
    
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, gray);
    glLightfv(GL_LIGHT0, GL_AMBIENT, gray2);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    compileDisplayLists();
}

void keyboard(unsigned char key, int xPos, int yPos)
{
    switch (key)
    {
        case 27:
            exit(0);
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 6.2, -10.0);
    glRotatef(290.0f, 1.0, 0.0, 0.0);
}

void menu(int item)
{
    switch(item)
    {
        case 0:
            exit(0);
            
        case 1:
            spinFlag = !spinFlag;
            break;
            
        case 2:
            w += 0.05;
            break;
            
        case 3:
            w -= 0.05;
            break;
            
        case 4:
            delta += 0.01;
            break;
            
        case 5:
            delta -= 0.01;
            break;
            
        case 6:
            w = 0.01;
            delta = 0.03;
            break;
            
        case 7:
            p = startP[thisPosition];
            vp = startVp[thisPosition];
            thisPosition++;
            if (thisPosition >= NUMPOSITIONS)
                thisPosition = 0;
            break;
    }
}

void motion(int xPos, int yPos)
{
    vp.x = vp.y = vp.m = 0.0;
    p.x = (REAL)(xPos-xOnButtonDown)/(REAL)(XSIZE-XSIZE/2);
    p.y = -(REAL)(yPos-yOnButtonDown)/(REAL)(YSIZE-YSIZE/2);
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            userInControl = 1;
            xOnButtonDown = x;
            yOnButtonDown = y;
            motion(x, y);
        }
        else if (state == GLUT_UP)
            userInControl = 0;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(XSIZE, YSIZE);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pendulo");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Toggle spin", 1);
    glutAddMenuEntry("Next", 7);
    glutAddMenuEntry("", -1);
    glutAddMenuEntry("Increase weight", 2);
    glutAddMenuEntry("Decrease weight", 3);
    glutAddMenuEntry("Increase delta", 4);
    glutAddMenuEntry("Decrease delta", 5);
    glutAddMenuEntry("Reset weight and delta", 6);
    glutAddMenuEntry("", -1);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMainLoop();
    return 0;
}

