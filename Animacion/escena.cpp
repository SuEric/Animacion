#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif

float alpha=0,beta=5,scale=8.0,tx=0.0,ty=-10.0;
int x0,y0,cuar=2,obj=2,s=2,m=1,tipo;

GLfloat luz_difusa[]=    {.1,.1,.1,1};	
GLfloat luz_ambiente[]=  {.1,.1,.1,1};
GLfloat luz_especular[]= {.1,.1,.1,1};
GLfloat posicion[]=      {40,40,45};

void MyCubo(void)
{	
	GLfloat verticesFi[]={-0.5,-0.5,-0.5,
					      -0.5,-0.5,0.5,
						   0.5,-0.5,0.5,
						   0.5,-0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFi);
  	glDrawArrays(GL_POLYGON,0,4);
    
	GLfloat verticesFs[]={-0.5,0.5,-0.5,
					      -0.5,0.5,0.5,
						   0.5,0.5,0.5,
						   0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFs);
	glDrawArrays(GL_POLYGON,0,4);


    GLfloat vertices[]={ -0.5,0.5,-0.5,
					     -0.5,-0.5,-0.5,
					     -0.5,-0.5,0.5,
					     -0.5,0.5,0.5};     

	glEnableClientState (GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,0,vertices);
   glDrawArrays(GL_POLYGON,0,4);

	GLfloat verticesFd[]={0.5,0.5,0.5,
						  0.5,-0.5,0.5,
						  0.5,-0.5,-0.5,
						  0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFd);
	glDrawArrays(GL_POLYGON,0,4);

	GLfloat verticesFp[]={-0.5,0.5,-0.5,
					     -0.5,-0.5,-0.5,
						  0.5,-0.5,-0.5,
						  0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFp);
	glColor3f(0.0, 1.0, 1.0);//rosa
	glDrawArrays(GL_POLYGON,0,4);



	GLfloat verticesF[]={-0.5,0.5,0.5,
					     -0.5,-0.5,0.5,
						  0.5,-0.5,0.5,
						  0.5,0.5,0.5};
	
	glEnableClientState (GL_VERTEX_ARRAY);
	
	glVertexPointer(3,GL_FLOAT,0,verticesF);
	glDrawArrays(GL_POLYGON,0,4);

}

void MyCubo2(void)
{	
	GLfloat verticesFi[]={-0.5,-0.5,-0.5,
					      -0.5,-0.5,0.5,
						   0.5,-0.5,0.5,
						   0.5,-0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFi);
  	glDrawArrays(GL_POLYGON,0,4);
    
	GLfloat verticesFs[]={-1.5,0.5,-0.5,
					      -1.5,0.5,0.5,
						   -0.5,0.5,0.5,
						  -0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFs);
	glDrawArrays(GL_POLYGON,0,4);


   GLfloat vertices[]={ -1.5,0.5,-0.5,
					     -0.5,-0.5,-0.5,
					     -0.5,-0.5,0.5,
					     -1.5,0.5,0.5};     

   glEnableClientState (GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,0,vertices);
  
   glDrawArrays(GL_POLYGON,0,4);

   GLfloat verticesFd[]={-0.5,0.5,0.5,
						  0.5,-0.5,0.5,
						  0.5,-0.5,-0.5,
						  -0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFd);
	glDrawArrays(GL_POLYGON,0,4);

	GLfloat verticesFp[]={-1.5,0.5,-0.5,
					     -0.5,-0.5,-0.5,
						  0.5,-0.5,-0.5,
						  -0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFp);
	glDrawArrays(GL_POLYGON,0,4);



	GLfloat verticesF[]={-1.5,0.5,0.5,
					     -0.5,-0.5,0.5,
						  0.5,-0.5,0.5,
						  -0.5,0.5,0.5};
	
	glEnableClientState (GL_VERTEX_ARRAY);
	
	glVertexPointer(3,GL_FLOAT,0,verticesF);
	glDrawArrays(GL_POLYGON,0,4);

}

void MyCubo3(void)
{	
	GLfloat verticesFi[]={-0.5,-0.5,-0.5,
					      -0.5,-0.5,0.5,
						   0.5,-0.5,0.5,
						   0.5,-0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFi);
  	glDrawArrays(GL_POLYGON,0,4);
    
	GLfloat verticesFs[]={1.5,0.5,-0.5,
					      1.5,0.5,0.5,
						   0.5,0.5,0.5,
						  0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFs);
	glDrawArrays(GL_POLYGON,0,4);


   GLfloat vertices[]={ 1.5,0.5,-0.5,
					     0.5,-0.5,-0.5,
					     0.5,-0.5,0.5,
					     1.5,0.5,0.5};     

   glEnableClientState (GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,0,vertices);
  
   glDrawArrays(GL_POLYGON,0,4);

GLfloat verticesFd[]={0.5,0.5,0.5,
						  -0.5,-0.5,0.5,
						  -0.5,-0.5,-0.5,
						  0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFd);
	glDrawArrays(GL_POLYGON,0,4);

   
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFd);
	glDrawArrays(GL_POLYGON,0,4);
 
	GLfloat verticesFp[]={1.5,0.5,-0.5,
					     0.5,-0.5,-0.5,
						  -0.5,-0.5,-0.5,
						  0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFp);
	glDrawArrays(GL_POLYGON,0,4);
	



	GLfloat verticesF[]={1.5,0.5,0.5,
					     0.5,-0.5,0.5,
						  -0.5,-0.5,0.5,
						  0.5,0.5,0.5};
	
	glEnableClientState (GL_VERTEX_ARRAY);
	
	glVertexPointer(3,GL_FLOAT,0,verticesF);
	glDrawArrays(GL_POLYGON,0,4);

}

void MyCubo4(void)
{	
	GLfloat verticesFi[]={-0.5,-0.5,-0.5,
					      -0.5,-0.5,0.5,
						   0.5,-0.5,0.5,
						   0.5,-0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFi);
  	glDrawArrays(GL_POLYGON,0,4);
    
	GLfloat verticesFs[]={-13.5,1.5,-0.5,
					      -13.5,1.5,0.5,
						   -12.5,1.5,0.5,
						  -12.5,1.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFs);
	glDrawArrays(GL_POLYGON,0,4);


   GLfloat vertices[]={ -13.5,1.5,-0.5,
					     -0.5,-0.5,-0.5,
					     -0.5,-0.5,0.5,
					     -13.5,1.5,0.5};     

   glEnableClientState (GL_VERTEX_ARRAY);
   glVertexPointer(3,GL_FLOAT,0,vertices);
  
   glDrawArrays(GL_POLYGON,0,4);

   GLfloat verticesFd[]={-12.5,1.5,0.5,
						  0.5,-0.5,0.5,
						  0.5,-0.5,-0.5,
						  -12.5,1.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFd);
	glDrawArrays(GL_POLYGON,0,4);

	GLfloat verticesFp[]={-13.5,1.5,-0.5,
					     -0.5,-0.5,-0.5,
						  0.5,-0.5,-0.5,
						  -12.5,1.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFp);
	glDrawArrays(GL_POLYGON,0,4);



	GLfloat verticesF[]={-13.5,1.5,0.5,
					     -0.5,-0.5,0.5,
						  0.5,-0.5,0.5,
						  -12.5,1.5,0.5};
	
	glEnableClientState (GL_VERTEX_ARRAY);
	
	glVertexPointer(3,GL_FLOAT,0,verticesF);
	glDrawArrays(GL_POLYGON,0,4);

}




void init(void)
{
	glClearColor(0.0,0.8,1.0,1.0); 
glEnable(GL_DEPTH_TEST);   
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);

	glEnable(GL_LIGHTING);				
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
}

GLfloat ambiente1[] = {1.0,0.5,0.6,1.0}; //rosa////////////////
	GLfloat ambiente2[] = {0.0,0.7,0.0,1.0}; //verde///////////////
	GLfloat ambiente3[] = {0.0,0.8,1.0,1.0}; //azul//////////////
	GLfloat ambiente4[] = {0.5,0.3,0.7,1.0}; //morado/////////////
	GLfloat ambiente5[] = {1.0,1.0,0.0,1.0}; //amarillo////////////
	GLfloat ambiente6[] = {0.9,0.3,0.3,1.0}; //rojo
	GLfloat ambiente7[] = {0.7,0.5,0.0,1.0}; //cafe
	GLfloat ambiente8[] = {1.0,1.0,1.0,1.0}; //blanco///////////////
    GLfloat ambiente9[] = {1.0,0.5,0.0,1.0};////naranja
	
	GLfloat difusa1[] = {1.0,0.5,0.6,1.0};
	GLfloat difusa2[] = {0.0,0.7,0.0,1.0};
	GLfloat difusa3[] = {0.0,0.8,1.0,1.0};
	GLfloat difusa4[] = {0.5,0.3,0.7,1.0};
	GLfloat difusa5[] = {1.0,1.0,0.0,1.0};
	GLfloat difusa6[] = {0.9,0.3,0.3,1.0};
	GLfloat difusa7[] = {0.7,0.5,0.0,1.0};
	GLfloat difusa8[] = {1.0,1.0,1.0,1.0};
	GLfloat difusa9[] = {1.0,0.5,0.0,1.0};


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    
    glRotatef(alpha,1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);
    
    glPushMatrix();
	glTranslatef(0,1,0);

	 glPushMatrix();
	 glTranslatef(0,5,0);
	
    glScalef(1.2,1.2,1.2);
	
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa2);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente2);
	glPushMatrix();
	glTranslatef(0.0,-50.0,0.0);
	glScalef(120.0,4.0,100.0);
	MyCubo();
    glPopMatrix();

   
   ////pasamanos 
	///////////barras izquierda
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-50.0,-43.0,-45.0);
	glScalef(2.0,15.0,2.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-50.0,-43.0,-35.0);
	glScalef(2.0,15.0,2.0);
	MyCubo();
	glPopMatrix();
    //////////////////////////////////barras derecha
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-20.0,-43.0,-45.0);
	glScalef(2.0,15.0,2.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-20.0,-43.0,-35.0);
	glScalef(2.0,15.0,2.0);
	MyCubo();
	glPopMatrix();
	//////////////////////////////////////////barras superiores
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-35,-35.0,-45.0);
	glScalef(32.5,2.0,2.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-35,-35.0,-35.0);
	glScalef(32.5,2.0,2.0);
	MyCubo();
	glPopMatrix();
	//////////////////////////////////////////escalerss derecha
   

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-50.0,-39.0,-41.0);
	glScalef(2.0,2.0,10.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-50.0,-43.0,-41.0);
	glScalef(2.0,2.0,10.0);
	MyCubo();
	glPopMatrix();
	//////////////////////escaleras izquierda

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-20.0,-39.0,-41.0);
	glScalef(2.0,2.0,10.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-20.0,-43.0,-41.0);
	glScalef(2.0,2.0,10.0);
	MyCubo();
	glPopMatrix();
	//////////////escaleras superiores

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-45.0,-35.0,-41.0);
	glScalef(2.0,2.0,10.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-41.0,-35.0,-41.0);
	glScalef(2.0,2.0,10.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-37.0,-35.0,-41.0);
	glScalef(2.0,2.0,10.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-33.0,-35.0,-41.0);
	glScalef(2.0,2.0,10.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-29.0,-35.0,-41.0);
	glScalef(2.0,2.0,10.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-25.0,-35.0,-41.0);
	glScalef(2.0,2.0,10.0);
	MyCubo();
	glPopMatrix();
  /////////////////////////////////////////////nubes
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(0.0,0.0,0.-40);
	glScalef(7.0,7.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(-3.0,0.0,0.-40);
	glScalef(5.0,5.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(3.0,0.0,0.-40);
	glScalef(5.0,5.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(-5.0,0.0,0.-40);
	glScalef(5.0,3.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(5.0,0.0,0.-40);
	glScalef(5.0,3.0,6.0);
	MyCubo();
	glPopMatrix();
	///////////////////////////////////////77
	  glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(30.0,0.0,0.-30);
	glScalef(7.0,7.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(27.0,0.0,0.-30);
	glScalef(5.0,5.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(33.0,0.0,-30.0);
	glScalef(5.0,5.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(25.0,0.0,0.-30);
	glScalef(5.0,3.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(35.0,0.0,0.-30);
	glScalef(5.0,3.0,6.0);
	MyCubo();
	glPopMatrix();
//////////////////////
	 glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(-30.0,0.0,0.-30);
	glScalef(7.0,7.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(-27.0,0.0,0.-30);
	glScalef(5.0,5.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(-33.0,0.0,-30.0);
	glScalef(5.0,5.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(-25.0,0.0,0.-30);
	glScalef(5.0,3.0,6.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
	glPushMatrix();
    glTranslatef(-35.0,0.0,0.-30);
	glScalef(5.0,3.0,6.0);
	MyCubo();
	glPopMatrix();
	///////////////////sol
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(-55.0,10.0,0.-50);
	glScalef(5.0,5.0,5.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(-60.0,4.0,-50);
	glScalef(2.0,5.0,2.0);
	MyCubo3();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(-50.0,4.0,-50);
	glScalef(2.0,5.0,2.0);
	MyCubo2();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(-52.0,16.0,-50);
	glScalef(2.0,5.0,2.0);
	MyCubo3();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(-58.0,16.0,-50);
	glScalef(2.0,5.0,2.0);
	MyCubo2();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(-62.0,9.5,-50);
	glScalef(5.0,2.0,2.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(-48.0,9.5,-50);
	glScalef(5.0,2.0,2.0);
	MyCubo();
	glPopMatrix();


	
	

/////////////////////columpios
	////pastas frontal
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(55.0,-43.0,40.0);
	glScalef(2.0,17.0,2.0);
	MyCubo2();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(48.0,-43.0,40.0);
	glScalef(2.0,17.0,2.0);
	MyCubo3();
	glPopMatrix();
	////////////////////////////patas trasera

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(55.0,-43.0,0.0);
	glScalef(2.0,17.0,2.0);
	MyCubo2();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(48.0,-43.0,0.0);
	glScalef(2.0,17.0,2.0);
	MyCubo3();
	glPopMatrix();

	/////////////////////////////////barra de arriba 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
	glPushMatrix();
    glTranslatef(51.0,-35.0,20.0);
	glScalef(2.5,2.0,40.0);
	MyCubo();
	glPopMatrix();
	/////////////////////columpio 1
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
	glPushMatrix();
    glTranslatef(51.0,-40.0,3.0);
	glScalef(1.5,10.0,1.5);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
	glPushMatrix();
    glTranslatef(51.0,-40.0,8.0);
	glScalef(1.5,10.0,1.5);
	MyCubo();
	glPopMatrix();
    
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(51.0,-45.0,5.5);
	glScalef(1.5,1.5,6.0);
	MyCubo();
	glPopMatrix();
////////////columpio2
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
	glPushMatrix();
    glTranslatef(51.0,-40.0,12.0);
	glScalef(1.5,10.0,1.5);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
	glPushMatrix();
    glTranslatef(51.0,-40.0,17.0);
	glScalef(1.5,10.0,1.5);
	MyCubo();
	glPopMatrix();
    
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(51.0,-45.0,14.5);
	glScalef(1.5,1.5,6.0);
	MyCubo();
	glPopMatrix();

///////////////////////columpio3
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
	glPushMatrix();
    glTranslatef(51.0,-40.0,21.0);
	glScalef(1.5,10.0,1.5);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
	glPushMatrix();
    glTranslatef(51.0,-40.0,26.0);
	glScalef(1.5,10.0,1.5);
	MyCubo();
	glPopMatrix();
    
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(51.0,-45.0,23.5);
	glScalef(1.5,1.5,6.0);
	MyCubo();
	glPopMatrix();
	////////////////////////////columpio4
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
	glPushMatrix();
    glTranslatef(51.0,-40.0,30.0);
	glScalef(1.5,10.0,1.5);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
	glPushMatrix();
    glTranslatef(51.0,-40.0,35);
	glScalef(1.5,10.0,1.5);
	MyCubo();
	glPopMatrix();
    
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(51.0,-45.0,32.5);
	glScalef(1.5,1.5,6.0);
	MyCubo();
	glPopMatrix();
/////////////sube y baja 
	/////////patas frontal
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(30.0,-45.0,-25.0);
	glScalef(2.0,7.0,2.0);
	MyCubo2();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(25.0,-45.0,-25.0);
	glScalef(2.0,7.0,2.0);
	MyCubo3();
	glPopMatrix();
///////////patras posterior
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(30.0,-45.0,-40.0);
	glScalef(2.0,7.0,2.0);
	MyCubo2();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(25.0,-45.0,-40.0);
	glScalef(2.0,7.0,2.0);
	MyCubo3();
	glPopMatrix();
/////////////barra
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(27.0,-42.0,-33.0);
	glScalef(2.0,2.0,16.0);
	MyCubo();
	glPopMatrix();
////////////////////
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
	glTranslatef(40.0,-45.0,-37.0);
	glScalef(2.0,6.0,2.0);
	MyCubo4();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
	glTranslatef(40.0,-45.0,-29.0);
	glScalef(2.0,6.0,2.0);
	MyCubo4();
	glPopMatrix();

/////////////////////////////////girador
	//base
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa3);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente3);
	glPushMatrix();
    glTranslatef(5.0,-46.0,10.0);
	glScalef(15.0,2.0,15.0);
	MyCubo();
	glPopMatrix();

	//tubo de enmedio

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
    glTranslatef(5.0,-43.0,10.0);
	glScalef(2.0,12.0,2.0);
	MyCubo();
	glPopMatrix();

	/////////////////////

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
    glTranslatef(-1.5,-43.0,17.0);
	glScalef(2.0,7.0,2.0);
	MyCubo3();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
    glTranslatef(11.0,-43.0,17.0);
	glScalef(2.0,7.0,2.0);
	MyCubo2();
	glPopMatrix();
//////////////////////
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
    glTranslatef(-1.5,-43.0,3.0);
	glScalef(2.0,7.0,2.0);
	MyCubo3();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
    glTranslatef(11.0,-43.0,3.0);
	glScalef(2.0,7.0,2.0);
	MyCubo2();
	glPopMatrix();
////////////////////////7
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
    glTranslatef(4.5,-40.0,17.0);
	glScalef(10.0,2.0,2.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
    glTranslatef(4.5,-40.0,3.0);
	glScalef(10.0,2.0,2.0);
	MyCubo();
	glPopMatrix();
/////////////////////
	 glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
    glTranslatef(4.5,-40.0,10.0);
	glScalef(10.0,2.0,2.0);
	MyCubo();
	glPopMatrix();
	//////////////////////
		glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
    glTranslatef(-1.5,-43.0,10.0);
	glScalef(2.0,7.0,2.0);
	MyCubo3();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
    glTranslatef(11.0,-43.0,10.0);
	glScalef(2.0,7.0,2.0);
	MyCubo2();
	glPopMatrix();
/////////////////////77
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
	glPushMatrix();
    glTranslatef(5.0,-40.0,10.0);
	glScalef(2.0,2.0,12.0);
	MyCubo();
	glPopMatrix();

////////////bancas

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(-10.0,-47.0,-40.0);
	glScalef(2.0,3.0,3.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(4.0,-47.0,-40.0);
	glScalef(2.0,3.0,3.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(-3.0,-45.0,-40.0);
	glScalef(16.0,2.0,3.0);
	MyCubo();
	glPopMatrix();
///////////////7777

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(12.0,-47.0,40.0);
	glScalef(2.0,3.0,3.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(26.0,-47.0,40.0);
	glScalef(2.0,3.0,3.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(19.0,-45.0,40.0);
	glScalef(16.0,2.0,3.0);
	MyCubo();
	glPopMatrix();
/////////////////
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(-55.0,-47.0,-12.0);
	glScalef(2.0,3.0,3.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(-55.0,-47.0,-3.0);
	glScalef(2.0,3.0,3.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
	glPushMatrix();
    glTranslatef(-55.0,-45.0,-7.0);
	glScalef(3.0,2.0,16.0);
	MyCubo();
	glPopMatrix();
	///////////////////resbaladilla
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-50.0,-43.0,17.0);
	glScalef(2.0,17.5,2.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-50.0,-43.0,23.0);
	glScalef(2.0,17.5,2.0);
	MyCubo();
	glPopMatrix();
///////////////////////////7
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-50.0,-46.0,20.0);
	glScalef(2.0,2.0,5.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-50.0,-43.0,20.0);
	glScalef(2.0,2.0,5.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-50.0,-40.0,20.0);
	glScalef(2.0,2.0,5.0);
	MyCubo();
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
	glPushMatrix();
	glTranslatef(-50.0,-37.0,20.0);
	glScalef(2.0,2.0,5.0);
	MyCubo();
	glPopMatrix();
///////////////////////

glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa4);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente4);
	glPushMatrix();
	glTranslatef(-30.0,-45.0,20.0);
	glScalef(1.5,6.0,7.0);
	MyCubo4();
	glPopMatrix();





   

     
    

	
	glFlush();
	glPopMatrix();
	glPopMatrix();
 

    glutSwapBuffers();
}

void special(int key, int x, int y)
{
    switch(key)
	{
	case GLUT_KEY_LEFT:
		tx--;
		break;
	case GLUT_KEY_UP:
		ty++;
		break;
	case GLUT_KEY_RIGHT:
		tx++;
		break;
	case GLUT_KEY_DOWN:
		ty--;
		break;

	case GLUT_KEY_HOME:
		scale-=0.5;
		break;

	case GLUT_KEY_END:
		scale+=0.5;
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-80.0, 80.0, -80.0 * (GLfloat) h / (GLfloat) w,
            80.0 * (GLfloat) h / (GLfloat) w, -200.0, 200.0);
    else
        glOrtho(-80.0 * (GLfloat) w / (GLfloat) h,
            80.0 * (GLfloat) w / (GLfloat) h, -80.0, 80.0, -200.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void onMouse(int button, int state, int x, int y) 
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) 
	{
		x0 = x; y0 = y;
	}
}

void onMotion(int x, int y) 
{
	alpha = (alpha + (y - y0));
	beta = (beta + (x - x0));
	x0 = x; y0 = y;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(150, 150);
	glutInitWindowSize(700,700);
    glutCreateWindow("***********************Parque!!!!!***************************");
	init();
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutDisplayFunc(display);

	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
    
    glutMainLoop();

    return 0;
}
