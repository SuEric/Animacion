#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
float alpha=0,beta=5,scale=8.0,tx=0.0,ty=-10.0;
int x0,y0,cuar=2,obj=2,s=2,m=1,tipo,shoulder=0;
GLUquadricObj *qobj;


GLfloat luz_difusa[]=    {.1,.1,.1,1};
GLfloat luz_ambiente[]=  {.1,.1,.1,1};
GLfloat luz_especular[]= {.1,.1,.1,1};
GLfloat posicion[]=      {40,40,45};

GLuint texture_id[4];
int LoadBMP(char *filename, int tex_name)
{
#define SAIR        {fclose(fp_archivo); return -1;}
#define CTOI(C)     (*(int*)&C)
    
    GLubyte     *image;
    GLubyte     Header[0x54];
    GLuint      DataPos, imageSize;
    GLsizei     Width,Height;
    
    // Abre un archivo y efectua la lectura del encabezado del archivo BMP
    FILE * fp_archivo = fopen(filename,"rb");
    if (!fp_archivo)
        return -1;
    if (fread(Header,1,0x36,fp_archivo)!=0x36)
        SAIR;
    if (Header[0]!='B' || Header[1]!='M')
        SAIR;
    if (CTOI(Header[0x1E])!=0)
        SAIR;
    if (CTOI(Header[0x1C])!=24)
        SAIR;
    
    // Recupera los atributos de la altura y ancho de la imagen
    
    Width   = CTOI(Header[0x12]);
    Height  = CTOI(Header[0x16]);
    ( CTOI(Header[0x0A]) == 0 ) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );
    
    imageSize=Width*Height*3;
    
    // Llama a la imagen
    image = (GLubyte *) malloc ( imageSize );
    int retorno = (int) fread(image,1,imageSize,fp_archivo);
    
    if (retorno !=imageSize)
    {
        free (image);
        SAIR;
    }
    
    // Invierte los valores de R y B
    int t, i;
    
    for ( i = 0; i < imageSize; i += 3 )
    {
        t = image[i];
        image[i] = image[i+2];
        image[i+2] = t;
    }
    
    // Tratamiento de textura para OpenGL
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MODULATE);
    
    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    
    // Manipulacion en memoria de la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    
    fclose (fp_archivo);
    free (image);
    return 1;
}

GLfloat ambiente1[] = {1.0,0.5,0.6,1.0}; //rosa////////////////
GLfloat ambiente2[] = {0.0,0.7,0.0,1.0}; //verde///////////////
GLfloat ambiente3[] = {0.0,0.0,1.0,1.0}; //azul//////////////
GLfloat ambiente4[] = {0.5,0.3,0.7,1.0}; //morado/////////////
GLfloat ambiente5[] = {1.0,1.0,0.0,0.0}; //amarillo////////////
GLfloat ambiente6[] = {0.9,0.3,0.3,1.0}; //rojo
GLfloat ambiente7[] = {0.7,0.5,0.0,1.0}; //cafe
GLfloat ambiente8[] = {1.0,1.0,1.0,1.0}; //blanco///////////////
GLfloat ambiente9[] = {1.0,0.5,0.0,1.0};////naranja
GLfloat ambiente10[] = {0.925, 0.66, 0.4,1};///carne////
GLfloat ambiente11[] = {0,0,0,1};/////////negro//////////////
GLfloat ambiente12[] = {0,0.8,1,1};/////////Turquoise//////////////
GLfloat ambiente13[] = {0,0,0.5,1};///azul marino///////
GLfloat ambiente14[] = {0.9, 0.3, 0.5, 0.0,1}; ///rosa fuerte////

GLfloat difusa1[] = {1.0,0.5,0.6,1.0};
GLfloat difusa2[] = {0.0,0.7,0.0,1.0};
GLfloat difusa3[] = {0.0,0.0,1.0,1.0};
GLfloat difusa4[] = {0.5,0.3,0.7,1.0};
GLfloat difusa5[] = {1.0,1.0,0.0,0.0};
GLfloat difusa6[] = {0.9,0.3,0.3,1.0};
GLfloat difusa7[] = {0.7,0.5,0.0,1.0};
GLfloat difusa8[] = {1.0,1.0,1.0,1.0};
GLfloat difusa9[] = {1.0,0.5,0.0,1.0};
GLfloat difusa10[] = {0.925, 0.66, 0.4};
GLfloat difusa11[] = {0,0,0,1};
GLfloat difusa12[] = {0,0.8,1,1};
GLfloat difusa13[] = {0,0,0.5,1};
GLfloat difusa14[] = {0.9, 0.3, 0.5, 0.0};


void init()
{
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
	glClearColor(0.925, 0.66, 0.4,1);
	
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
    
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(5,texture_id);
	glBindTexture(GL_TEXTURE_2D,texture_id[0]);
    LoadBMP("goku_c.bmp",0);
	glBindTexture(GL_TEXTURE_2D,texture_id[1]);
    LoadBMP("n2.bmp",1);
    glBindTexture(GL_TEXTURE_2D,texture_id[2]);
    LoadBMP("azul-rey.BMP",2);
	glBindTexture(GL_TEXTURE_2D,texture_id[3]);
    LoadBMP("rojo-naranja.BMP",3);
	glBindTexture(GL_TEXTURE_2D,texture_id[4]);
    LoadBMP("negro-cabello.BMP",4);
	glBindTexture(GL_TEXTURE_2D,texture_id[5]);
    LoadBMP("carne.BMP",5);
}
void MyCubo(void)
{
	glColor3f(0,0,0);
	GLfloat verticesFi[]={-0.5,-0.5,-0.5, -0.5,-0.5,0.5, 0.5,-0.5,0.5, 0.5,-0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFi);
  	glDrawArrays(GL_POLYGON,0,4);
	GLfloat verticesFs[]={-0.5,0.5,-0.5, -0.5,0.5,0.5, 0.5,0.5,0.5, 0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFs);
	glDrawArrays(GL_POLYGON,0,4);
    GLfloat vertices[]={ -0.5,0.5,-0.5, -0.5,-0.5,-0.5, -0.5,-0.5,0.5, -0.5,0.5,0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,vertices);
    glDrawArrays(GL_POLYGON,0,4);
	GLfloat verticesFd[]={0.5,0.5,0.5, 0.5,-0.5,0.5, 0.5,-0.5,-0.5, 0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFd);
	glDrawArrays(GL_POLYGON,0,4);
	GLfloat verticesFp[]={-0.5,0.5,-0.5, -0.5,-0.5,-0.5, 0.5,-0.5,-0.5, 0.5,0.5,-0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesFp);
	glDrawArrays(GL_POLYGON,0,4);
	GLfloat verticesF[]={-0.5,0.5,0.5, -0.5,-0.5,0.5, 0.5,-0.5,0.5, 0.5,0.5,0.5};
	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,verticesF);
	glDrawArrays(GL_POLYGON,0,4);
    
}
void papos()
{
	glPushMatrix();
    glTranslatef(-51.5,-48,2);
    glRotatef(180, 0,1,1);
    glScalef(5.0,8.0,4.0);
    glutSolidCone(0.5, 0.6, 25, 20);
    glPopMatrix();
	glPushMatrix();
    glTranslatef(-42.0,-48,2);
    glRotatef(180, 0,1,1);
    glScalef(5.0,8.0,4.0);
    glutSolidCone(0.5, 0.6, 25, 20);
    glPopMatrix();
}
void botas()
{
    glPushMatrix();
    glTranslatef(-51.5,-45.0,0.0);
    glScalef(3.5,7.0,4.0);
    glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-42.0,-45.0,0.0);
    glScalef(3.5,7.0,4.0);
    glutSolidCube(0.8);
    glPopMatrix();
}
void Goku()
{
    //piernas
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(-50.0,-36.0,0.0);
    glRotatef(-10, 0,0,1);
    glScalef(6.0,17.0,5.0);
    glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-43.0,-36.0,0.0);
    glRotatef(10, 0,0,1);
    glScalef(6.0,17.0,5.0);
    glutSolidCube(0.8);
    glPopMatrix();
    
    papos();
    botas();
    //torso
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(-46.5,-25,0.0);
    glScalef(12,14,4);
    glutSolidCube(0.8);
    glPopMatrix();
	////cinta
	glColor3f(0,0,1);
    glPushMatrix();
    glTranslatef(-46.5,-18,0.0);
    glScalef(12,3.3,4);
    glutSolidCube(0.8);
    glPopMatrix();
	glColor3f(0,0,0);
	glPushMatrix();
    glTranslatef(-47.0,-14,0.0);
    glScalef(11,7.3,4);
    glutSolidCube(0.8);
	glPopMatrix();
	
    //  // glBindTexture(GL_TEXTURE_2D,texture_id[0]);
	//glPushMatrix();
    //   glTranslatef(0.9,-0.2,-0.7);
	//glRotatef(88, 1.0f, 0.0f, 0.0f);
	//glScalef(0.2,0.2,0.2);
	////gluQuadricTexture( qobj, GL_TRUE    );
	//gluCylinder(qobj, 0.5, 0.5,10, 12, 3);
	//glPopMatrix();
	
}
void cara(){
    //pico
	/*glBegin(GL_TRIANGLES);
     glTexCoord2f(0.5,0);
     glVertex3f(0.0f, 0.0f, 0.0f);
     glTexCoord2f(0,1);
     glVertex3f(-5.0f, 10.0f, 0.0f);
     glTexCoord2f(1,1);
     glVertex3f(5.0f,10.0f,0.0f);
     glEnd();*/
	glBegin(GL_POLYGON);
    glTexCoord2f(0.5,0);
    glVertex3f(-5.0f, 0.0f, 0.0f);
    
	glTexCoord2f(0,1);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glTexCoord2f(1,1);
    glVertex3f(5.0f,10.0f,0.0f);
	glTexCoord2f(0,0);
    glVertex3f(10.0f, 0.0f, 0.0f);
    
	glTexCoord2f(0.5,0);
    glVertex3f(2.5f, -5.0f, 0.0f);
	glEnd();
    
}
void mechon()
{
	glColor3f(0,0,0);
	glPushMatrix();
	glScalef(1,.6,.7);
    gluCylinder(qobj,0.5,.5,3,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(0,0,2);
    glRotatef(45,0,1,0);
    glScalef(1,.5,.7);
    gluSphere(qobj,.5,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(0,0,2);
    glRotatef(45,0,1,0);
    glScalef(1,.5,.7);
    gluCylinder(qobj,.5,.2,2,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(1,0,3);
    glRotatef(90,0,1,0);
    glScalef(1,.5,.7);
    gluCylinder(qobj,.2,0,2,15,15);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(1,0,3);
    glRotatef(90,0,1,0);
    glScalef(1,.4,.7);
    gluSphere(qobj,.2,15,15);
	glPopMatrix();
}
void cabello(){
	
	glPushMatrix();
    //declaraMaterial(vRojo);
	
    glBindTexture(GL_TEXTURE_2D,texture_id[4]);//++++++++++++++++++++++++++++++++++++++++++++++4
    gluSphere(qobj,.10,.100,.20);
	glPopMatrix();
    
	glPushMatrix();
    mechon();
	glPopMatrix();
	glPushMatrix();
    glRotatef(180,1,0,0);
    mechon();
	glPopMatrix();
	glPushMatrix();
    glRotatef(120,1,0,0);
    glRotatef(18,0,0,1);
    mechon();
	glPopMatrix();
	glPushMatrix();
    glRotatef(45,1,0,0);
    //glRotatef(0,0,0,1);
    mechon();
	glPopMatrix();
    
}
void piernas(){
	//pierna izquierda
    glPushMatrix();
    glTranslatef(-51.5,-41.5,0.0);
    glRotatef(-9, 0,0,1);
    glScalef(4.0,2.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-51,-39.5,0.0);
    glRotatef(-9, 0,0,1);
    glScalef(4.0,4.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-50.5,-35.5,0.0);
    glRotatef(-8, 0,0,1);
    glScalef(3.5,6.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-50,-31.5,0.0);
    glRotatef(-15, 0,0,1);
    glScalef(3,5.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-49.5,-29,0.0);
    glRotatef(-15, 0,0,1);
    glScalef(3.0,5.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    //pierna derecha
    glPushMatrix();
    glTranslatef(-42,-41.5,0.0);
    glRotatef(9, 0,0,1);
    glScalef(4.0,2.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-42.5,-39.5,0.0);
    glRotatef(9, 0,0,1);
    glScalef(4.0,4.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-43,-35.5,0.0);
    glRotatef(8, 0,0,1);
    glScalef(3.5,6.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-43.5,-31.5,0.0);
    glRotatef(15, 0,0,1);
    glScalef(3.0,5.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44.5,-29,0.0);
    glRotatef(15, 0,0,1);
    glScalef(3.0,5.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
	//pompis
    glPushMatrix();
    glTranslatef(-49.1,-28,-1.2);
    glScalef(2.8,5,3);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-44.8,-28,-1.2);
    glScalef(2.8,5,3);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    //torso
    glPushMatrix();
    glTranslatef(-47,-25,0.0);
    glScalef(5,7.5,2.5);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-47,-25,0.0);
    glScalef(5,7.5,2.5);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
}
void accesorios(){
    //mangas
    glPushMatrix();
    glTranslatef(-53,-14,0.5);
    glRotatef(6, 0,0,1);
    glScalef(1.5,3.5,2);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-41.25,-14,0.5);
    glRotatef(-6, 0,0,1);
    glScalef(1.5,3.5,2);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    //playera
    glPushMatrix();
    glTranslatef(-47,-15,0.0);
    glRotatef(90, 0,0,1);
    glScalef(5.0,6.0,2);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
}
void cinta(){
	////cinta
    glPushMatrix();
    glTranslatef(-47,-21,0.0);
    glScalef(10,3.5,5);
    glutSolidCube(0.8);
    glPopMatrix();
}
void pulseras(){
    //pulseras
    glPushMatrix();
    glTranslatef(-53,-20,5);
    glRotatef(20, 0,0,1);
    glScalef(1.5,3,2);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-41.25,-20,5);
    glRotatef(-20, 0,0,1);
    glScalef(1.5,3,2);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
}
void playera(){
    //pecho
    glPushMatrix();
    glTranslatef(-44,-16.5,0.0);
    glRotatef(-21, 0,0,1);
    glScalef(3.25,7.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-50,-16.5,0.0);
    glRotatef(21, 0,0,1);
    glScalef(3.25,7.0,3.0);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-47,-17,-1.0);
    glRotatef(90, 0,0,1);
    glScalef(5.0,7.0,1);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-47,-14,-1.0);
    glRotatef(90, 0,0,1);
    glScalef(6.0,9.0,1);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    
}
void bubis(){
	//bubis
    glColor4f(0.925, 0.66, 0.4, 0.0);
    glPushMatrix();
    glTranslatef(-45,-14,0.0);
    glRotatef(-70, 0,0,1);
    glRotatef(20, 0,1,0);
    glScalef(4.0,5.0,1.5);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-49,-14,0.0);
    glRotatef(70, 0,0,1);
    glRotatef(-20, 0,1,0);
    glScalef(4.0,5.0,1.5);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
}
void cuadros(){
    //cuadros();
    glPushMatrix();
    glTranslatef(-9,-10,0);
    glScalef(0.8,0.5,1);
    bubis();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-9,-11,0);
    glScalef(0.8,0.5,1);
    bubis();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-9,-12,0);
    glScalef(0.8,0.5,1);
    bubis();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-9,-14,0);
    glScalef(0.8,0.5,1);
    bubis();
    glPopMatrix();
}
void cuerpo(){
    //bubis
    //glColor4f(0.925, 0.66, 0.4, 0.0); //carne
    bubis();
	//cuello
    glPushMatrix();
    glTranslatef(-47.25,-11.75,0.5);
    glRotatef(-90, 1,0,0);
    glScalef(9,2,2);
    glutSolidCone(0.5,2, 25, 20);
    glPopMatrix();
	////cara
    glPushMatrix();
    glTranslatef(-47.25,-6,0.5);
    glScalef(4,4.5,2);
    glutSolidIcosahedron();
    glPopMatrix();
}
void brazotes(){
    //brazotes
    glPushMatrix();
    glTranslatef(-54,-14.5,0.5);
    glRotatef(-15, 0,0,1);
    glScalef(2,3.5,2.3);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55,-18,0.5);
    glScalef(2.5,5,2.3);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-55.5,-20.5,0.5);
    glRotatef(-15, 0,0,1);
    glScalef(1.5,2,2);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-54.5,-20,3);
    glRotatef(90, 1,0,0);
    glRotatef(-30, 0,0,1);
    glScalef(2.5,5,1.8);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
	//mano izquierda
    glPushMatrix();
    glTranslatef(-51.5,-18,4);
    glRotatef(120, 1,0,0);
    glRotatef(-70, 0,0,1);
    glScalef(2.5,1,3.5);
    glutSolidIcosahedron();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-40,-14.5,0.5);
    glRotatef(15, 0,0,1);
    glScalef(2,3.5,2.3);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-39,-18,0.5);
    glScalef(2.5,5,2.3);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-38.5,-20.5,0.5);
    glRotatef(15, 0,0,1);
    glScalef(1.5,2,2);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-39.5,-20,3);
    glRotatef(90, 1,0,0);
    glRotatef(30, 0,0,1);
    glScalef(2.5,5,1.8);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
	////mano derecha
    glPushMatrix();
    glTranslatef(-42.5,-18,4);
    glRotatef(120, 1,0,0);
    glRotatef(70, 0,0,1);
    glScalef(2.5,1,3.5);
    glutSolidIcosahedron();
    glPopMatrix();
}
void fleco()
{
    //fleco
    glPushMatrix();
    glTranslatef(-8,-2,1);
    glRotatef(-30, 1,0,0);
    glRotatef(90, 0,1,0);
    glScalef(1,1,2);
    cabello();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8,-2.5,0);
    glRotatef(90, 1,0,0);
    glRotatef(45, 0,1,0);
    glScalef(2,2,1);
    cabello();
    glPopMatrix();}
void melena()
{
    glPushMatrix();
    glTranslatef(-8,0,-1);
    glRotatef(70, 1,0,0);
    glRotatef(-90, 0,1,0);
    glScalef(2,2,1);
    cabello();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8,-1,-1);
    glRotatef(70, 1,0,0);
    glRotatef(-90, 0,1,0);
    glScalef(2,2,1);
    cabello();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8,-3,-1);
    glRotatef(70, 1,0,0);
    glRotatef(-90, 0,1,0);
    glScalef(2,2,1);
    cabello();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8,-4,-0.5);
    glRotatef(70, 1,0,0);
    glRotatef(-90, 0,1,0);
    glScalef(2,2,1);
    cabello();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8,-5,-0.5);
    glRotatef(70, 1,0,0);
    glRotatef(-90, 0,1,0);
    glScalef(2,2,1);
    cabello();
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(-8,-1,-1.5);
    glRotatef(120, 1,0,0);
    glRotatef(-90, 0,1,0);
    glScalef(2,2,2);
    cabello();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8,-4,-1.5);
    glRotatef(-35, 0,0,1);
    glRotatef(90, 0,1,0);
    glScalef(2,2,2);
    cabello();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8,-4,-1.5);
    glRotatef(90, 0,1,0);
    glScalef(3,2,2);
    cabello();
    glPopMatrix();
}
void Goku1(){
    //AZUL
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa3);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente3);
    //playera   //pulseras //manga  //cinta
    accesorios();
    cinta();
    pulseras();
    //NARANJA
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa9);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente9);
    //pecho, playera
    playera();
    //piernas   //pompis   //torso
    piernas();
    
    //CARNE
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa10);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente10);
    //bubis    //cuello    //cara
    cuerpo();
    //brazos   //manos
    brazotes();
    //AZUL
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa3);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente3);
    botas();
    papos();
    //NEGRO
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa11);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente11);
    glPushMatrix();
    glTranslatef(-38.5,0,0);
    glScalef(1.2,1.2,1);
    fleco();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-38.5,0,0.5);
    glScalef(1.2,1.2,1);
    melena();
    glPopMatrix();
}
void picoro(){
    //azul cielo
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa12);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente12);
    glPushMatrix();
    glTranslatef(0,10,0);
    glScalef(1,1.5,1);
    cinta();
    glPopMatrix();
    //blanco
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
    //...............capa
    glPushMatrix();
    glTranslatef(-40.8,-12.5,0.5);
    glRotatef(180, 0,1,1);
    glRotatef(-32, 0,1,0);
    glScalef(10.0,4.0,6.0);
    glutSolidCone(0.5, 0.6, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-53,-12.5,0.5);
    glRotatef(180, 0,1,1);
    glRotatef(32, 0,1,0);
    glScalef(10.0,4.0,6.0);
    glutSolidCone(0.5, 0.6, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-54,-37,-7);
    glRotatef(13,1,0,0);
    glScalef(3,2.8,10.0);
    cara();
    glPopMatrix();
    
    //...........sombrero
    glPushMatrix();
    glTranslatef(-38,28,1);
    glRotatef(40,0,0,1);
    glScalef(0.6,0.8,0.8);
    cinta();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-13,-3,1);
    glRotatef(-30,0,0,1);
    glScalef(0.6,0.8,0.8);
    cinta();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5,17,1);
    glScalef(0.9,1,0.8);
    cinta();
    glPopMatrix();
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa4);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente4);
    glPushMatrix();
    glTranslatef(-47.5,-2.5,1.0);/*
                                  glRotatef(70, 0,0,1);
                                  glRotatef(-20, 0,1,0);*/
    glScalef(4.0,3,2);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    
    //ROSA
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa14);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente14);
    pulseras();
    //VERDE
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa2);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente2);
    //bubis    //cuello    //cara
    cuerpo();
    //brazos   //manos
    brazotes();
    cuadros();
    //azul marino
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa13);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente13);
    //piernas   //pompis   //torso
    piernas();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa11);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente11);
    botas();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
    papos();
}
void Goku2(){
    //AZUL
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa13);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente13);
    //playera   //pulseras //manga  //cinta
    accesorios();
    cinta();
    pulseras();
    botas();
    papos();
    //AZUL MARINO
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
    //pecho, playera
    playera();
    //piernas   //pompis   //torso
    piernas();
    //CARNE
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa10);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente10);
    //bubis    //cuello    //cara
    cuerpo();
    //brazos   //manos
    brazotes();
    //AMARILLO
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
    glPushMatrix();
    glTranslatef(-38.5,0,1);
    glScalef(1.2,1.8,1);
    fleco();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-38.5,0,0);
    glScalef(1.2,1.8,1);
    melena();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-38.5,-3,-2.5);
    glScalef(1.2,1.2,1);
    melena();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-38.5,-5,-2.5);
    glScalef(1.2,1.2,1);
    melena();
    glPopMatrix();
}
void majinboo(){
    //ROSA
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente1);
    glPushMatrix();
    glTranslatef(0,2,0);
    glScalef(13,10,10);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,6,4);
    glScalef(7,5,5);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,10,-3);
    glScalef(5,8,5);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,10,-2);
    glScalef(5,5,5);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    //cuerno
    glPushMatrix();
    glTranslatef(0,15,-2);
    glRotatef(90, 0,1,0);
    glRotatef(-110, 1,0,0);
    glScalef(2,2,2);
    mechon();
    glPopMatrix();
    //brazos
    glPushMatrix();
    glTranslatef(-4,6,-2);
    glRotatef(-90, 0,1,0);
    glScalef(5,5,5);
    mechon();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4,6,-2);
    glRotatef(90, 0,1,0);
    glRotatef(90, 0,0,1);
    glScalef(5,5,5);
    mechon();
    glPopMatrix();
    //BLANCO
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa8);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente8);
    glPushMatrix();
    glTranslatef(0,0,0.5);
    glScalef(13,10,10);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5,-3.5,8);
    glRotatef(-45, 0,1,0);
    glScalef(7,6,10);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5,-3.5,8);
    glRotatef(45, 0,1,0);
    glScalef(7,6,10);
    glutSolidSphere(0.8, 25, 20);
    glPopMatrix();
    //AZUL MARINO
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa13);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente13);
    glPushMatrix();
    glTranslatef(0,2,0);
    glRotatef(75, 1,0,0);
    glScalef(14.5,12,7);
    glutSolidTorus(0.25, 0.50, 30, 80);
    glPopMatrix();
    //AMARILLO
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
    glPushMatrix();
    glTranslatef(-8,-4.0,15.0);
    glRotatef(-75,1,0,0);
    glScalef(3.5,7.0,4.0);
    glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7.0,-4.0,15.0);
    glRotatef(-75,1,0,0);
    glScalef(3.5,7.0,4.0);
    glutSolidCube(0.8);
    glPopMatrix();
    //guantes
    glPushMatrix();
    glTranslatef(19,18,-2);
    glRotatef(90,1,0,0);
    glScalef(2,1.5,2);
    gluCylinder(qobj,0.5,.5,3,15,15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-19,6,3);
    glScalef(2,1.5,2);
    gluCylinder(qobj,0.5,.5,3,15,15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(19,18,-2);
    glScalef(2,3,1);
    glutSolidIcosahedron();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-19,6,10);
    glScalef(2,1,3);
    glutSolidIcosahedron();
    glPopMatrix();
    //CAFE
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
    glPushMatrix();
    glTranslatef(-8,-4,20);
    glRotatef(-130, 1,0,0);
    glScalef(5.0,8.0,4.0);
    glutSolidCone(0.5, 0.6, 25, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7,-4,20);
    glRotatef(-130, 1,0,0);
    glScalef(5.0,8.0,4.0);
    glutSolidCone(0.5, 0.6, 25, 20);
    glPopMatrix();
    //MORADO
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa4);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente4);
    glPushMatrix();
    glTranslatef(-4,0,-10);
    glRotatef(25,1,0,0);
    glScalef(2,.8,1.0);
    cara();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,7,-4);
    glRotatef(75, 1,0,0);
    glScalef(12,10,5);
    glutSolidTorus(0.25, 0.50, 30, 80);
    glPopMatrix();
}
void Goku3(){
    //AZUL
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa13);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente13);
    ////playera   //pulseras //manga  //cinta
    //   accesorios();
    cinta();
    pulseras();
    botas();
    papos();
    //AZUL MARINO
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa5);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente5);
    //piernas   //pompis   //torso
    piernas();
    //CARNE
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa10);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente10);
    //bubis    //cuello    //cara
    cuerpo();
    cuadros();
	
	////mano izquierda
    glPushMatrix();
    glTranslatef(-51.5,-18,4);
    glRotatef(120, 1,0,0);
    glRotatef(-70, 0,0,1);
    glScalef(2.5,1,3.5);
    glutSolidIcosahedron();
    glPopMatrix();
	////mano derecha
    glPushMatrix();
    glTranslatef(-42.5,-18,4);
    glRotatef(120, 1,0,0);
    glRotatef(70, 0,0,1);
    glScalef(2.5,1,3.5);
    glutSolidIcosahedron();
    glPopMatrix();
    //brazos   //manos
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa6);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente6);
    brazotes();
    //pecho, playera
    playera();
    //NEGRO
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa11);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente11);
    glPushMatrix();
    glTranslatef(-38.5,2,1);
    glScalef(1.2,1.8,1);
    fleco();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-38.5,0,0);
    glScalef(1.2,1.8,1);
    melena();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-38.5,-3,-2.5);
    glScalef(1.2,1.2,1);
    melena();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-38.5,-5,-2.5);
    glScalef(1.2,1.2,1);
    melena();
    glPopMatrix();
}
void reshape(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    //glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	//gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    if (w <= h)
        glOrtho(-80.0, 80.0, -80.0 * (GLfloat) h / (GLfloat) w,
                80.0 * (GLfloat) h / (GLfloat) w, -200.0, 200.0);
    else
        glOrtho(-80.0 * (GLfloat) w / (GLfloat) h,
                80.0 * (GLfloat) w / (GLfloat) h, -80.0, 80.0, -200.0, 200.0);
    
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -7.0);
    glClearColor(0.196078,0.6,0.8,1); //color indefinido
    
}
void display(void)
{
	GLfloat posicion_luz[] = { -50, 15, 15, 0.0 };
	GLfloat spotDir[] = { 0.0,0.0,-1.0 };
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    //Objeto Compuesto
    qobj = gluNewQuadric();
	glLoadIdentity();
    glPushMatrix();
    glRotatef(alpha,1.0f, 0.0f, 0.0f);
    glRotatef(beta, 0.0f, 1.0f, 0.0f);
    
    glTranslatef(0,1,0);
    
    glPushMatrix();
    glTranslatef(0,5,0);
    glScalef(1.2,1.2,1.2);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa7);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente7);
    glPushMatrix();
    glTranslatef(0.0,-40.0,0.0);
    glScalef(120.0,4.0,100.0);
    MyCubo();
    glPopMatrix();
	////////////GOKU 1...............................
    glPushMatrix();
    glTranslatef(30,0,0);
    glScalef(0.8,0.8,0.8);
    Goku1();
    glPopMatrix();
    
	////////////////PICORO...............................
    glPushMatrix();
    glTranslatef(60,0,-30);
    glScalef(0.8,0.8,0.8);
    picoro();
    glPopMatrix();
    
	////////////////GOKU2.........
    glPushMatrix();
    glTranslatef(0,0,-30);
    glScalef(0.8,0.8,0.8);
    Goku2();
    glPopMatrix();
    
	////////////////MAJINBOO.........
    glPushMatrix();
    glTranslatef(-20,-33,48.5);/*
                                glScalef(0.8,0.8,0.8);*/
    majinboo();
    glPopMatrix();
    
	////////////////GOKU3.........
    glPushMatrix();
    glTranslatef(90,10,30);/*
                            glScalef(0.8,0.8,0.8);*/
    Goku3();
    glPopMatrix();
    
    glPopMatrix();
    
	glFlush();
	glPopMatrix();
    glutSwapBuffers();
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
    
    /*if(key > 300.0f)
     xRot = 0.0f;
     
     if(key < -1.0f)
     xRot = 299.0f;
     
     if(key > 300.0f)
     yRot = 0.0f;
     
     if(key < -1.0f)
     yRot = 199.0f;*/
    
    glutPostRedisplay();
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
    glutInitWindowPosition(100,100);
	glutInitWindowSize(900,700);
    glutCreateWindow("Dragon Ball Z");
	init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
    glutSpecialFunc(SpecialKeys);
    
    glutMainLoop();
    
    return 0;
}
