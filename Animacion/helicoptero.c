#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
void helice(void)
{
  glBegin(GL_QUADS);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(-10.0f, -10.0f,  20.0f);
      glVertex3f( 10.0f, -10.0f,  20.0f);
      glVertex3f( 10.0f,  10.0f,  20.0f);
      glVertex3f(-10.0f,  10.0f,  20.0f);

      glVertex3f( 10.0f, -10.0f, -20.0f);
      glVertex3f(-10.0f, -10.0f, -20.0f);
      glVertex3f(-10.0f,  10.0f, -20.0f);
      glVertex3f( 10.0f,  10.0f, -20.0f);

      glColor3f(0.0f, 1.0f, 1.0f);
      glVertex3f(-10.0f,-10.0f, -20.0f);
      glVertex3f(-10.0f,-10.0f,  20.0f);
      glVertex3f(-10.0f, 10.0f,  20.0f);
      glVertex3f(-10.0f, 10.0f, -20.0f);

      glVertex3f(10.0f, -10.0f,  20.0f);
      glVertex3f(10.0f, -10.0f, -20.0f);
      glVertex3f(10.0f,  10.0f, -20.0f);
      glVertex3f(10.0f,  10.0f,  20.0f);

      glColor3f(1.0f,0.0f, 0.0f);
      glVertex3f(-10.0f, 10.0f,  20.0f);
      glVertex3f( 10.0f, 10.0f,  20.0f);
      glVertex3f( 10.0f, 10.0f, -20.0f);
      glVertex3f(-10.0f, 10.0f, -20.0f);

      glVertex3f( 10.0f,-10.0f, -20.0f);
      glVertex3f( 10.0f,-10.0f,  20.0f);
      glVertex3f(-10.0f,-10.0f,  20.0f);
      glVertex3f(-10.0f,-10.0f, -20.0f);
  glEnd();
}
void held(void)
{
  glPushMatrix();//Helice uno delantera
    glScalef(0.2,0.1,1.5);
    glTranslatef(0.0,100.0,0.0);
    helice();
  glPopMatrix();
  glPushMatrix();//Helice dos delantera
    glRotatef(90.0,0.0,1.0,0.0);
    glScalef(0.2,0.1,1.5);
    glTranslatef(0.0,100.0,0.0);
    helice();
  glPopMatrix();
}
void helt(void)
{
  glPushMatrix();//Helices traseras
    glTranslatef(47.0,-5.0,0.0);
    glPushMatrix();//Helice uno trasera
      glScalef(0.1,0.1,0.3);
      glTranslatef(0.0,100.0,0.0);
      helice();
    glPopMatrix();
    glPushMatrix();//Helice dos trasera
      glRotatef(90.0,0.0,1.0,0.0);
      glScalef(0.1,0.1,0.3);
      glTranslatef(0.0,100.0,0.0);
      helice();
    glPopMatrix();
  glPopMatrix();//Fin helices traseras
}
void basehelices(void)
{
  glPushMatrix();//Base helices delanteras
    glScalef(0.1,0.1,0.1);
    glTranslatef(0.0,80.0,0.0);
    helice();
  glPopMatrix();//Fin base helices delanteras
  glPushMatrix();//Base helices traseras
    glScalef(0.1,0.2,0.1);
    glTranslatef(470.0,10.0,0.0);
    helice();
  glPopMatrix();//Fin base helices traseras
}
void cabina(void)
{
  glPushMatrix();//Cabina
    glColor3f(0.8f, 0.0f, 1.0f);
    glTranslatef(0.0,-7.0,0.0);
    glScalef(1.5,0.9,1.0);
    glutSolidSphere(15.0,30,10);
  glPopMatrix();//Fin cabina
}
void cola(void)
{     
  glColor3f(0.8f, 0.8f, 1.0f);
  glPushMatrix();//Cola 2
    glRotatef(90.0,0.0,1.0,0.0);
    glRotatef(-10.0,1.0,0.0,0.0);
    glTranslatef(0.0,-8.0,7.0);
    glutSolidCone(8.0,40.0,30,30);
  glPopMatrix();//Fin cola 2
}
void basehelicoptero(void)
{
  glPushMatrix();//Base 1
    glRotatef(90.0,0.0,1.0,0.0);
    glScalef(0.2,0.1,0.8);
    glTranslatef(40.0,-300.0,0.0);
    helice();
  glPopMatrix();//Fin base 1
  glPushMatrix();//Base 2
    glRotatef(90.0,0.0,1.0,0.0);
    glScalef(0.2,0.1,0.8);
    glTranslatef(-40.0,-300.0,0.0);
    helice();
  glPopMatrix();//Fin base 2
}
void basehelicop(void)
{
  glPushMatrix();//Base 1
    glRotatef(90.0,0.0,1.0,0.0);
    glRotatef(90.0,1.0,0.0,0.0);
    glScalef(0.2,0.1,0.5);
    glTranslatef(-40.0,-40.0,100.0);
    helice();
  glPopMatrix();//Fin base 1
  glPushMatrix();//Base 2
    glRotatef(90.0,0.0,1.0,0.0);
    glRotatef(-90.0,1.0,0.0,0.0);
    glScalef(0.2,0.1,0.5);
    glTranslatef(-40.0,-40.0,-100.0);
    helice();
  glPopMatrix();//Fin base 2
  /////////////////////////////////
  glPushMatrix();//Base 1
    glRotatef(90.0,0.0,1.0,0.0);
    glRotatef(90.0,1.0,0.0,0.0);
    glScalef(0.2,0.1,0.5);
    glTranslatef(40.0,-40.0,100.0);
    helice();
  glPopMatrix();//Fin base 1
  glPushMatrix();//Base 2
    glRotatef(90.0,0.0,1.0,0.0);
    glRotatef(-90.0,1.0,0.0,0.0);
    glScalef(0.2,0.1,0.5);
    glTranslatef(40.0,-40.0,-100.0);
    helice();
  glPopMatrix();//Fin base 2
}

void RenderScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();//Inicia helicoptero
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);//Variables para
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);//la rotacion del objeto
    held();
    helt();
    basehelices();
    cabina();
    cola();
    basehelicoptero();
    glTranslatef(0.0,30.0,0.0);
    basehelicop();
  glPopMatrix();//Fin helicoptero
  glutSwapBuffers();
}

void SetupRC()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glClearColor(0.0f, 0.0f, 0.0f,0.0f);
}

void SpecialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
        xRot-= 5.0f;
    if(key == GLUT_KEY_DOWN)
        xRot += 5.0f;
    if(key == GLUT_KEY_LEFT)
        yRot -= 5.0f;
    if(key == GLUT_KEY_RIGHT)
        yRot += 5.0f;
    if(key > 356.0f)
        xRot = 0.0f;
    if(key < -1.0f)
        xRot = 355.0f;
    if(key > 356.0f)
        yRot = 0.0f;
    if(key < -1.0f)
        yRot = 355.0f;
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 80.0f;

    if(h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else
        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(150,150);
    glutCreateWindow("Helicoptero");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}