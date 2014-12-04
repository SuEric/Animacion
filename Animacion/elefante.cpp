#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static GLfloat x=0, z2=0, RT=0, angR=1;
static GLint numPaso =1;
int s=1, cont=0;

int R1[4] = {75,100,75,100};
int R2[4] = {5,15,5,15};



void init();										//declaracion de funciones
void reshape();
void onMouse(int button, int state, int x, int y); 
void onMotion(int x, int y);
void teclado(unsigned char opcion, int x, int y);
void reshape(int w, int h);
void Esfera ( float radio,float longitud,float latitud  );
void Cilindro( float baseI,float baseS,float altura, float slices, float stacks);
void disco(
           radioI,float radioE,float slices,float loops);
int  CargaImagen(char *filename);
void luz1();
void Piso();


void cuerpo();
void cola();
void trompa(int r);
void cuernos();
void pata1(int R1, int R2);
void pata2(int R1, int R2);
void pata3(int R1, int R2);
void pata4(int R1, int R2);

GLuint  texture_id[4];

GLfloat mat_ambient[] ={0.19225,0.19225,0.19225,1.0};
GLfloat mat_diffuse[] ={0.50754,0.50754,0.50754,1.0};
GLfloat mat_specular[]={0.508273,0.508273,0.508273,1.0};
GLfloat shininess=51.2;

GLfloat mat_ambient2[] ={0.05375,0.05,0.06625,0.82};
GLfloat mat_diffuse2[] ={0.18275,0.17,0.22525,0.82};
GLfloat mat_specular2[]={0.332741,0.328634,0.346435,0.82};
GLfloat shininess2=38.4;

float alpha=0, beta=0;
int x00, y00;
float tx=0,ty=0,tz=0,sx=0.5,sy=0.7,sz=0.7;




int i;
int efe=1;

void Elefante()
{
	glPushMatrix();
	glScalef(.25,.25,.25);
	
	cuernos();

	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular2);
	glMaterialf  (GL_FRONT, GL_SHININESS, shininess2);


	cuerpo();
	cola();
	trompa(RT);
	
	pata1(R1[0],R2[0]);
	pata2(R1[1],R2[1]);
	pata3(R1[2],R2[2]);
	pata4(R1[3],R2[3]);

	glPopMatrix();
}

void display()
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 3.0f, 10.0,0.0f, 0.0f, 0.0f,0.0f,1.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glTranslatef(tx,ty,tz);
	glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);
	glScalef(sx,sy,sz);
	

	Piso();
	
	glColor3f(.7807,.7807,.7807);	
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
		
	glTranslatef(0,0,-0.25);
	glTranslatef (x, 0.0, -z2);
	glRotatef (angR, 0,1,0);
	glRotatef(90,0,1,0);

	Elefante();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}


void rota(int paso)
{

	switch(paso)
	{
		case 1: R1[0]=75;R1[1]=100;R1[2]=75;R1[3]=100;
				R2[0]=5;R2[1]=15;R2[2]=5;R2[3]=15;
				break;

		case 2: R1[0]=90;R1[1]=100;R1[2]=90;R1[3]=75;
				R2[0]=5;R2[1]=15;R2[2]=5;R2[3]=5;
				break;

		case 3: R1[0]=100;R1[1]=75;R1[2]=100;R1[3]=75;
				R2[0]=15;R2[1]=5;R2[2]=15;R2[3]=5;
				break;

		case 4: R1[0]=100;R1[1]=90;R1[2]=75;R1[3]=90;
				R2[0]=15;R2[1]=5;R2[2]=5;R2[3]=5;
				break;
	}
}

void teclado(unsigned char opcion, int x, int y)	//caracteres del teclado
{
	switch(opcion)
	{
		case '+':	sx+=.2;
					sy+=.2;
					sz+=.2;
					break;
		case '-':	sx-=.2;
					sy-=.2;
					sz-=.2;
					break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}		

	//fin caracteres del teclado

void keyboard(int key, int z, int y)
{
	float temp, tempx, tempz2;
	
	if(numPaso ==4)
		numPaso =1;
	else 
		numPaso =numPaso +1;
	switch(key)
	{
		case GLUT_KEY_RIGHT:if(angR>=360) angR=0;
							else	angR = angR-10.0;
								rota(numPaso);

							break;
		case GLUT_KEY_LEFT:	if(angR<=-360) angR=0;
							else	angR = angR+10.0;
								rota(numPaso);
							//if(numPaso ==4) numPaso =1;
							//else numPaso =numPaso +1;
							break;
		case GLUT_KEY_UP:	temp=angR*3.1415926535897932384626433832795/180;
							tempx=x;
							tempz2=z2;
							x+=cos(temp)*0.1;
							z2+=sin(temp)*0.1;

							if((x>=2.2 | x<=-2.2) | (z2>=2.2 | z2 <= -2.2))
							{
								x = tempx;
								z2 = tempz2;
							}
							rota(numPaso);
							//if(numPaso == 4) numPaso =1;
							//else numPaso = numPaso + 1;
							cont++;
							break;
		case GLUT_KEY_HOME:	temp=angR*3.1415926535897932384626433832795/180;
							tempx=x;
							tempz2=z2;
							x-=cos(temp)*0.1;
							z2-=sin(temp)*0.1;

							if((x>=2.2 | x<=-2.2) | (z2>=2.2 | z2 <= -2.2))
							{
								x = tempx;
								z2 = tempz2;
							}
							rota(numPaso);
							//if(numPaso == 4) numPaso =1;
							//else numPaso = numPaso + 1;
							cont++;
							break;
	}
	glutPostRedisplay();
}

void anima()
{
	sleep(0.2);
		if(RT >= 10)
			s=1;
		if(RT <= -25.0)
			s=0;
		if(s==0)
			RT+=.5;
		else
			RT-=.5;
		cont=0;
	
	
	glutPostRedisplay();

}



void init()
{	
	GLfloat light_ambient[]={0.35,0.25,0.75,1.0};
	GLfloat light_diffuse[]={1.0,1.0,1.0,1.0};
	GLfloat light_specular[]={0.5,0.5,0.5,1.0};
	GLfloat light_position[]={0.0,0,1,0.0};


	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);

	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glShadeModel (GL_SMOOTH);

	glClearColor (0, 0, 0.7, 0.0);
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glClearDepth (1.0);

	//cargamos texturas
	glEnable ( GL_TEXTURE_2D );
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
	glGenTextures ( 4, texture_id );
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	CargaImagen ("piso.bmp");   
	/*glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
	CargaImagen (".bmp");
	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
	CargaImagen (".bmp");
	glBindTexture ( GL_TEXTURE_2D, texture_id[3] );
	CargaImagen (".bmp");
	*/
}

void reshape(int w, int h)
{
	glViewport (0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	if (w<=h)
		glOrtho(-2.2,2.2,-2.2 * (GLfloat)h / (GLfloat)w, 2.2 * (GLfloat)h/(GLfloat)w, -4.4,4.4);
	else
		glOrtho(-2.2 * (GLfloat)w / (GLfloat)h, 2.2 * (GLfloat)w/(GLfloat)h,-2.2,2.2, -4.4,4.4);
	glMatrixMode(GL_MODELVIEW);
}


void onMouse(int button, int state, int x, int y) 
{
	if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) 
	{
		x00= x; y00 = y;
		
	}
			
}

void onMotion(int x, int y) 
{
	alpha = (alpha + (y - y00));
	beta = (beta + (x - x00));
	x00 = x; y00 = y;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(950, 750);
    glutInitWindowPosition(40,10);
    glutCreateWindow("Elefante");
	//glutFullScreen();
	init();
	glutDisplayFunc(display);			//llama funcion display
	glutReshapeFunc(reshape);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(keyboard);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	glutIdleFunc(anima);
	
	glutMainLoop();
    return 0;
}



void disco(float radioI,float radioE,float slices,float loops)		//cuadrico del disco
{
	GLUquadricObj*  q = gluNewQuadric ( );
	gluQuadricDrawStyle ( q, GLU_FILL   );
	gluQuadricNormals   ( q, GLU_SMOOTH );
	gluQuadricTexture   ( q, GL_TRUE    );
	gluDisk(q,radioI,radioE,slices,loops);
	gluDeleteQuadric ( q );

}

void Esfera ( float radio,float longitud,float latitud  )			//cuadrico de la esfera
{   
   GLUquadricObj*  q = gluNewQuadric ( );
   gluQuadricDrawStyle ( q, GLU_FILL   );
   gluQuadricNormals   ( q, GLU_SMOOTH );
   gluQuadricTexture   ( q, GL_TRUE    );
   //gluCube(q,0.2);
   gluSphere ( q, radio, longitud, latitud );
   gluDeleteQuadric ( q );
}

void Cilindro( float baseI,float baseS,float altura, float slices, float stacks)		//cuadrico del cilindro
{   
	GLUquadricObj*  q = gluNewQuadric ( );
	GLUquadricObj*  a = gluNewQuadric ( );
	GLUquadricObj*  b = gluNewQuadric ( );
	gluQuadricOrientation(a, GLU_INSIDE);
	gluDisk(a, 0, baseI, slices, stacks);
	gluCylinder ( q, baseI, baseS, altura,slices,stacks);
	glTranslatef(0,0,altura);
	gluDisk(b, 0, baseS, slices, stacks);
	gluDeleteQuadric ( q );
	gluDeleteQuadric ( a );
	gluDeleteQuadric ( b );
}


void cuerpo()
{
		glPushMatrix();
			Esfera(1,25,20);
		glPopMatrix();

		glPushMatrix();
			glRotatef(5,1,0,0);
			Cilindro(1,1.1,.75,20,20);

			Esfera(1.1,25,20);
			glRotatef(-10,1,0,0);
			Cilindro(1.1,1,.75,20,20);
			
			Esfera(1,25,20);

		glPopMatrix();
}

void cola()
{

		//cola

	glPushMatrix();
		glTranslatef(0,0.5,-.75);
		glRotatef(135,1,0,0);
		Cilindro(.08,.08,.25,25,25);

		
		glRotatef(-10,1,0,0);
		Cilindro(.08,.07,.25,25,25);

		glRotatef(-15,1,0,0);
		Cilindro(.08,.06,.25,25,25);

		glRotatef(-15,1,0,0);
		Cilindro(.07,.06,.25,25,25);

		glRotatef(-10,1,0,0);
		Cilindro(.065,.06,.25,25,25);
		Cilindro(.065,.06,.25,25,25);
		Cilindro(.06,.05,.25,25,25);
		Cilindro(.05,.04,.25,25,25);
		Cilindro(.04,.03,.25,25,25);
	glPopMatrix();

		//cabeza
	glPushMatrix();
		glTranslatef(0,.25,2);
		glRotatef(-10,1,0,0);
		glScalef(.9,1,.8);
		Cilindro(.65,.75,.75,25,25);

		glRotatef(-15,1,0,0);
		Esfera(.75,25,25);
		
	glPopMatrix();


	//orejas

	glPushMatrix();
		glTranslatef(.7,.2,2.55);
		glRotatef(18,0,0,1);
		glRotatef(90,1,0,0);
		glScalef(.2,1.1,1.75);
		Esfera(.4,25,25);

	glPopMatrix();

	glPushMatrix();
		glTranslatef(-.7,.2,2.55);
		glRotatef(-18,0,0,1);
		glRotatef(90,1,0,0);
		glScalef(.2,1.1,1.75);
		Esfera(.4,25,25);

	glPopMatrix();

}

void trompa(int r)
{
		//trompa
		glPushMatrix();
		glTranslatef(0,0,2.75);
		glRotatef(75,1,0,0);
		Cilindro(.45,.3,.5,25,25);

		glTranslatef(0,0,-.105);
		glRotatef(r,1,0,0);
		Cilindro(.3,.25,.5,25,25);

		glTranslatef(0,0,-.105);
		glRotatef(r,1,0,0);
		Cilindro(.25,.2,.5,25,25);

		glTranslatef(0,0,-.105);
		glRotatef(r,1,0,0);
		Cilindro(.2,.18,.5,25,25);

		glTranslatef(0,0,-.105);
		glRotatef(r,1,0,0);
		Cilindro(.18,.14,.5,25,25);
	glPopMatrix();
}

void cuernos()
{
		//cuernos

	
	glPushMatrix();
	
		glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf  (GL_FRONT, GL_SHININESS, shininess);
		

		glTranslatef(-.45,0,2.7);
		glRotatef(60,1,0,0);
		Cilindro(.1,.09,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.1,.07,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.08,.06,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.07,.05,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.06,.04,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.05,.03,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.04,.02,.25,25,25);

	glPopMatrix();


	glPushMatrix();
		glTranslatef(0.45,0,2.7);
		glRotatef(60,1,0,0);
		Cilindro(.1,.09,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.1,.07,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.08,.06,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.07,.05,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.06,.04,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.05,.03,.25,25,25);

		glTranslatef(0,0,-.11);
		glRotatef(-10,1,0,0);
		Cilindro(.04,.02,.25,25,25);

	glPopMatrix();
}

void pata1(int R1, int R2)
{
		//pata1
		glPushMatrix();
			glTranslatef(-.5,-.25,-.35);
			glRotatef(R1,1,0,0);
			glScalef(.7,1,1);
			Cilindro(.4,.25,1.2,20,20);


			glPushMatrix();
			glScalef(1,1.05,.75);
			Esfera(.25,25,20);
			glPopMatrix();

			glTranslatef(0,0,-.1);
			glRotatef(R2,1,0,0);
			Cilindro(.25,.25,1.2,20,20);

			glTranslatef(0,.01,0);
			glScalef(1,1.1,.5);
			Esfera(.25,25,20);
		glPopMatrix();

}

void pata2(int R1, int R2)
{
		//pata2
		glPushMatrix();
			glTranslatef(.5,-.25,-.35);
			glRotatef(R1,1,0,0);
			glScalef(.7,1,1);
			Cilindro(.4,.25,1.2,20,20);


			glPushMatrix();
			glScalef(1,1.05,.75);
			Esfera(.25,25,20);
			glPopMatrix();

			glTranslatef(0,0,-.1);
			glRotatef(R2,1,0,0);
			Cilindro(.25,.25,1.2,20,20);

			glTranslatef(0,.01,0);
			glScalef(1,1.1,.5);
			Esfera(.25,25,20);

		glPopMatrix();

}

void pata3(int R1, int R2)
{
		//pata3
		glPushMatrix();
			glTranslatef(.5,-.25,1.85);
			glRotatef(R1,1,0,0);
			glScalef(.7,1,1);
			Cilindro(.4,.25,1.2,20,20);


			glPushMatrix();
			glScalef(1,1.05,.75);
			Esfera(.25,25,20);
			glPopMatrix();

			glTranslatef(0,0,-.1);
			glRotatef(R2,1,0,0);
			Cilindro(.25,.25,1.2,20,20);

			glTranslatef(0,.01,0);
			glScalef(1,1.1,.5);
			Esfera(.25,25,20);

		glPopMatrix();

}

void pata4(int R1, int R2)
{
		//pata4
		glPushMatrix();
			glTranslatef(-.5,-.25,1.85);
			glRotatef(R1,1,0,0);
			glScalef(.7,1,1);
			Cilindro(.4,.25,1.2,20,20);


			glPushMatrix();
			glScalef(1,1.05,.75);
			Esfera(.25,25,20);
			glPopMatrix();

			glTranslatef(0,0,-.1);
			//glRotatef(15,1,0,0);
			glRotatef(R2,1,0,0);
			Cilindro(.25,.25,1.2,20,20);

			glTranslatef(0,.01,0);
			glScalef(1,1.1,.5);
			Esfera(.25,25,20);

		glPopMatrix();

}


int  CargaImagen(char *filename)				//carga las imagenes como texturas.
{
    #define SAIR        {fclose(fp_arquivo); return -1;}
    #define CTOI(C)     (*(int*)&C)
 
    GLubyte     *image;
    GLubyte     Header[0x54]; 
    GLuint      DataPos, imageSize;
    GLsizei     Width,Height;

    int nb = 0;
    
    
    // Abre un archivo y efectua la lectura del encabezado del archivo BMP
    FILE * fp_arquivo = fopen(filename,"rb");
    if (!fp_arquivo) 
        return -1;
    if (fread(Header,1,0x36,fp_arquivo)!=0x36) 
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
    int retorno;
    retorno = fread(image,1,imageSize,fp_arquivo);
    
    if (retorno != imageSize) 
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
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
   
    // Manipulacion en memoria de la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
                        
    fclose (fp_arquivo);
    free (image);
    return 1;
 }



void Piso()
{
	glPushMatrix();
		glTranslatef(-3,-.45,-3.25);
		Esfera(.25,25,25);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3,-.45,-3.25);
		Esfera(.25,25,25);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3,-.45,2.5);
		Esfera(.25,25,25);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-3,-.45,2.5);
		Esfera(.25,25,25);
	glPopMatrix();


	GLfloat mat_ambient[] ={0.0215,0.1745,0.0215,0.55};
	GLfloat mat_diffuse[] ={0.07568,0.61424,0.07568,0.55};
	GLfloat mat_specular[]={0.633,0.727811,0.633,0.55};
	GLfloat shininess=96.8;	



	glPushMatrix();
		glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf  (GL_FRONT, GL_SHININESS, shininess);
		
		glTranslatef(0,-.65,-0.5);
		glRotatef(45,0,1,0);
		glRotatef(90,1,0,0);
		disco(0,4.5,4,4);
	glPopMatrix();
}
