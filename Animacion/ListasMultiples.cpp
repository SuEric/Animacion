#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

static unsigned int base; 
static unsigned int junk[6] = {0, 2, 1, 1, 0, 2}; 

static void setup(void)
{
   base = glGenLists(3); 
   glListBase(base); 
   glNewList(base, GL_COMPILE);
      glColor3f (1.0, 0.0, 0.0); 
      glBegin(GL_TRIANGLES);
      glVertex2f(10.0, 10.0);
      glVertex2f(20.0, 10.0);
      glVertex2f(20.0, 40.0);
      glEnd();
      glTranslatef(15.0, 0.0, 0.0); 
   glEndList();

   glNewList(base + 1, GL_COMPILE);
      glColor3f(0.0, 1.0, 0.0); 
      glBegin(GL_QUADS);
      glVertex2f(10.0, 10.0);
      glVertex2f(20.0, 10.0);
      glVertex2f(20.0, 40.0);
      glVertex2f(10.0, 40.0);
      glEnd();
      glTranslatef(15.0, 0.0, 0.0); 
   glEndList();

   glNewList(base + 2, GL_COMPILE);
      glColor3f(0.0, 0.0, 1.0);  
      glBegin(GL_POLYGON);
      glVertex2f(10.0, 10.0);
      glVertex2f(20.0, 10.0);
      glVertex2f(20.0, 20.0);
      glVertex2f(15.0, 40.0);
      glVertex2f(10.0, 20.0);
      glEnd();
      glTranslatef(15.0, 0.0, 0.0); 
   glEndList();

   glClearColor(1.0, 1.0, 1.0, 0.0); 
}

void drawScene(void)
{ 
   glClear(GL_COLOR_BUFFER_BIT); 
   glLoadIdentity();
   glCallLists(6, GL_INT, junk); 
   glFlush();
}

void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char **argv) 
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("Listas multiples");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMainLoop(); 

   return 0;  
}
