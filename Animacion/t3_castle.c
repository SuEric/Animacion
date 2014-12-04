#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

// Tamaño inicial de la ventana de despliegue
GLsizei winWidth=400, winHeight=400;
float alpha=30, beta=30;
int x0, y0, fill=0;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void init(void);
void display(void);
void figura(void);

void Fmenu(GLint sel);
void onMouse(int button, int state, int x, int y);
void onMotion(int x, int y);
void winReshapeFcn(GLint newWidth, GLint newHeight);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void main(int argc, char **argv) 
{
	glutInit(&argc,argv);
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	glutReshapeFunc(winReshapeFcn);

	glutCreateMenu(Fmenu);
	glutAddMenuEntry("Lineas",0);
	glutAddMenuEntry("Solido",1);
	glutAddMenuEntry("Salir",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}

void init(void){
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Objeto 3D compuesto");
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250,250, -250,250, -250,250);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(!fill){
		glPolygonMode(GL_FRONT,GL_LINE);
		glPolygonMode(GL_BACK,GL_LINE);
	}
	else{
		glPolygonMode(GL_FRONT,GL_FILL);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);

	//castillo grande
	glPushMatrix();
	glTranslatef(0.0, 0.0, 100.0);
	figura();

	//izquierdo
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-100.0, -50.0, -100.0);
	glRotatef(45.0, 0.0f, 1.0f, 0.0f);
	glScalef(0.5, 0.5, 0.5);
	figura();

	//derecho
	glPopMatrix();
	//glPushMatrix();
	glTranslatef(100.0, -50.0, -150.0);
	glRotatef(45.0, 0.0f, 1.0f, 0.0f);
	glScalef(0.7, 0.5, 0.7);
	figura();

	//glPopMatrix();
	glutSwapBuffers();
}

void Fmenu(GLint sel){
	switch(sel){
	case 0:
	case 1:  if(fill != sel){  fill=sel;  glutPostRedisplay();  }  break;
	case 2:  exit(0);  break;
	}
}

void onMouse(int button, int state, int x, int y){
	if ( (button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) ){
		x0 = x;  y0 = y;  }
}

void onMotion(int x, int y){
	alpha = (alpha + (y - y0));
	beta = (beta + (x - x0));
	x0 = x; y0 = y;
	glutPostRedisplay();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	GLfloat wr;
	GLint esp;
	winWidth=newWidth;  winHeight=newHeight;

	if(!winHeight)  winHeight=1;
	if(!winWidth)  winWidth=1;
	wr=winHeight*1.0/winWidth;

	if(wr >= 1.0){	//ajustar al ancho
		esp=(winHeight-winWidth)/2;
		glViewport(0,esp,winWidth,winWidth);  }
	else{		//ajustar al alto
		esp=(winWidth-winHeight)/2;
		glViewport(esp,0,winHeight,winHeight);  }
}



void figura(void){
	
	glPushMatrix();
	glFrontFace(GL_CW);

	glTranslatef(0.0, -125.0, 0.0);
	//paredes ----------------------------
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUAD_STRIP);  //p1
		glVertex3f(-69.6, 0.0, 69.6);
		glVertex3f(-69.6, 50.0, 69.6);
		glVertex3f(69.6, 0.0, 69.6);
		glVertex3f(69.6, 50.0, 69.6); //*
		glVertex3f(69.6, 0.0, -69.6);
		glVertex3f(69.6, 50.0, -69.6); //*
		glVertex3f(-69.6, 0.0, -69.6);
		glVertex3f(-69.6, 50.0, -69.6); //*
		glVertex3f(-69.6, 0.0, 69.6);
		glVertex3f(-69.6, 50.0, 69.6); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);  //p2
		glVertex3f(-63.15, 50.0, 63.15);
		glVertex3f(-63.15, 100.0, 63.15);
		glVertex3f(63.15, 50.0, 63.15);
		glVertex3f(63.15, 100.0, 63.15); //*
		glVertex3f(63.15, 50.0, -63.15);
		glVertex3f(63.15, 100.0, -63.15); //*
		glVertex3f(-63.15, 50.0, -63.15);
		glVertex3f(-63.15, 100.0, -63.15); //*
		glVertex3f(-63.15, 50.0, 63.15);
		glVertex3f(-63.15, 100.0, 63.15); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);  //p3
		glVertex3f(-51.3, 100.0, 51.3);
		glVertex3f(-51.3, 150.0, 51.3);
		glVertex3f(51.3, 100.0, 51.3);
		glVertex3f(51.3, 150.0, 51.3); //*
		glVertex3f(51.3, 100.0, -51.3);
		glVertex3f(51.3, 150.0, -51.3); //*
		glVertex3f(-51.3, 100.0, -51.3);
		glVertex3f(-51.3, 150.0, -51.3); //*
		glVertex3f(-51.3, 100.0, 51.3);
		glVertex3f(-51.3, 150.0, 51.3); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);  //p4
		glVertex3f(-39.5, 150.0, 39.5);
		glVertex3f(-39.5, 200.0, 39.5);
		glVertex3f(39.5, 150.0, 39.5);
		glVertex3f(39.5, 200.0, 39.5); //*
		glVertex3f(39.5, 150.0, -39.5);
		glVertex3f(39.5, 200.0, -39.5); //*
		glVertex3f(-39.5, 150.0, -39.5);
		glVertex3f(-39.5, 200.0, -39.5); //*
		glVertex3f(-39.5, 150.0, 39.5);
		glVertex3f(-39.5, 200.0, 39.5); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);  //p5
		glVertex3f(-35.95, 200.0, 35.95);
		glVertex3f(-35.95, 250.0, 35.95);
		glVertex3f(35.95, 200.0, 35.95);
		glVertex3f(35.95, 250.0, 35.95); //*
		glVertex3f(35.95, 200.0, -35.95);
		glVertex3f(35.95, 250.0, -35.95); //*
		glVertex3f(-35.95, 200.0, -35.95);
		glVertex3f(-35.95, 250.0, -35.95); //*
		glVertex3f(-35.95, 200.0, 35.95);
		glVertex3f(-35.95, 250.0, 35.95); //*
	glEnd();
	//base -------------------------------
	glBegin(GL_QUADS);
		glVertex3f(-69.6, 0.0, 69.6);
		glVertex3f(69.6, 0.0, 69.6);
		glVertex3f(69.6, 0.0, -69.6);
		glVertex3f(-69.6, 0.0, -69.6);
	glEnd();
	//tejados ------------------------------------
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUAD_STRIP);  //t1
		glVertex3f(-82.45, 40.0, 82.45);
		glVertex3f(-63.15, 60.0, 63.15);
		glVertex3f(82.45, 40.0, 82.45);
		glVertex3f(63.15, 60.0, 63.15); //*
		glVertex3f(82.45, 40.0, -82.45);
		glVertex3f(63.15, 60.0, -63.15); //*
		glVertex3f(-82.45, 40.0, -82.45);
		glVertex3f(-63.15, 60.0, -63.15); //*
		glVertex3f(-82.45, 40.0, 82.45);
		glVertex3f(-63.15, 60.0, 63.15); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);
		glVertex3f(-69.6, 50.0, 69.6);
		glVertex3f(-82.45, 40.0, 82.45);
		glVertex3f(69.6, 50.0, 69.6);
		glVertex3f(82.45, 40.0, 82.45); //*
		glVertex3f(69.6, 50.0, -69.6);
		glVertex3f(82.45, 40.0, -82.45); //*
		glVertex3f(-69.6, 50.0, -69.6);
		glVertex3f(-82.45, 40.0, -82.45); //*
		glVertex3f(-69.6, 50.0, 69.6);
		glVertex3f(-82.45, 40.0, 82.45); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);  //t2
		glVertex3f(-77.4, 90.0, 77.4);
		glVertex3f(-51.3, 110.0, 51.3);
		glVertex3f(77.4, 90.0, 77.4);
		glVertex3f(51.3, 110.0, 51.3); //*
		glVertex3f(77.4, 90.0, -77.4);
		glVertex3f(51.3, 110.0, -51.3); //*
		glVertex3f(-77.4, 90.0, -77.4);
		glVertex3f(-51.3, 110.0, -51.3); //*
		glVertex3f(-77.4, 90.0, 77.4);
		glVertex3f(-51.3, 110.0, 51.3); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);
		glVertex3f(-63.15, 100.0, 63.15);
		glVertex3f(-77.4, 90.0, 77.4);
		glVertex3f(63.15, 100.0, 63.15);
		glVertex3f(77.4, 90.0, 77.4); //*
		glVertex3f(63.15, 100.0, -63.15);
		glVertex3f(77.4, 90.0, -77.4); //*
		glVertex3f(-63.15, 100.0, -63.15);
		glVertex3f(-77.4, 90.0, -77.4); //*
		glVertex3f(-63.15, 100.0, 63.15);
		glVertex3f(-77.4, 90.0, 77.4); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);  //t3
		glVertex3f(-64.05, 140.0, 64.05);
		glVertex3f(-39.5, 162.0, 39.5);
		glVertex3f(64.05, 140.0, 64.05);
		glVertex3f(39.5, 162.0, 39.5); //*
		glVertex3f(64.05, 140.0, -64.05);
		glVertex3f(39.5, 162.0, -39.5); //*
		glVertex3f(-64.05, 140.0, -64.05);
		glVertex3f(-39.5, 162.0, -39.5); //*
		glVertex3f(-64.05, 140.0, 64.05);
		glVertex3f(-39.5, 162.0, 39.5); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);
		glVertex3f(-51.3, 150.0, 51.3);
		glVertex3f(-64.05, 140.0, 64.05);
		glVertex3f(51.3, 150.0, 51.3);
		glVertex3f(64.05, 140.0, 64.05); //*
		glVertex3f(51.3, 150.0, -51.3);
		glVertex3f(64.05, 140.0, -64.05); //*
		glVertex3f(-51.3, 150.0, -51.3);
		glVertex3f(-64.05, 140.0, -64.05); //*
		glVertex3f(-51.3, 150.0, 51.3);
		glVertex3f(-64.05, 140.0, 64.05); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);  //t4
		glVertex3f(-52.5, 190.0, 52.5);
		glVertex3f(-35.95, 210.0, 35.95);
		glVertex3f(52.5, 190.0, 52.5);
		glVertex3f(35.95, 210.0, 35.95); //*
		glVertex3f(52.5, 190.0, -52.5);
		glVertex3f(35.95, 210.0, -35.95); //*
		glVertex3f(-52.5, 190.0, -52.5);
		glVertex3f(-35.95, 210.0, -35.95); //*
		glVertex3f(-52.5, 190.0, 52.5);
		glVertex3f(-35.95, 210.0, 35.95); //*
	glEnd();
	glBegin(GL_QUAD_STRIP);
		glVertex3f(-39.5, 200.0, 39.5);
		glVertex3f(-52.5, 190.0, 52.5);
		glVertex3f(39.5, 200.0, 39.5);
		glVertex3f(52.5, 190.0, 52.5); //*
		glVertex3f(39.5, 200.0, -39.5);
		glVertex3f(52.5, 190.0, -52.5); //*
		glVertex3f(-39.5, 200.0, -39.5);
		glVertex3f(-52.5, 190.0, -52.5); //*
		glVertex3f(-39.5, 200.0, 39.5);
		glVertex3f(-52.5, 190.0, 52.5); //*
	glEnd();
	glBegin(GL_QUADS); //t5
		//tejado frente y atras
		glVertex3f(-47.25, 240.0, 47.25);
		glVertex3f(-30.0, 260.0, 30.0);
		glVertex3f(30.0, 260.0, 30.0);
		glVertex3f(47.25, 240.0, 47.25); //*
		glVertex3f(47.25, 240.0, -47.25);
		glVertex3f(30.0, 260.0, -30.0);
		glVertex3f(-30.0, 260.0, -30.0);
		glVertex3f(-47.25, 240.0, -47.25); //*
	glEnd();
	glBegin(GL_TRIANGLES);
		//triangulos
		glVertex3f(-30.0, 260.0, 30.0);
		glVertex3f(0.0, 300.0, 30.0);
		glVertex3f(30.0, 260.0, 30.0); //*
		glVertex3f(30.0, 260.0, -30.0);
		glVertex3f(0.0, 300.0, -30.0);
		glVertex3f(-30.0, 260.0, -30.0);
	glEnd();
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_STRIP);
		//lateral derecha
		glVertex3f(0.0, 300.0, -30.0);
		glVertex3f(0.0, 300.0, 30.0);
		glVertex3f(30.0, 260.0, -30.0);
		glVertex3f(30.0, 260.0, 30.0);
		glVertex3f(47.25, 240.0, -47.25);
		glVertex3f(47.25, 240.0, 47.25);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
		//lateral izquierda
		glVertex3f(0.0, 300.0, 30.0);
		glVertex3f(0.0, 300.0, -30.0);
		glVertex3f(-30.0, 260.0, 30.0);
		glVertex3f(-30.0, 260.0, -30.0);
		glVertex3f(-47.25, 240.0, 47.25);
		glVertex3f(-47.25, 240.0, -47.25);
	glEnd();
	glFrontFace(GL_CW);
	glBegin(GL_QUAD_STRIP);
		//inferior
		glVertex3f(-35.95, 250.0, 35.95);
		glVertex3f(-47.25, 240.0, 47.25);
		glVertex3f(35.95, 250.0, 35.95);
		glVertex3f(47.25, 240.0, 47.25); //*
		glVertex3f(35.95, 250.0, -35.95);
		glVertex3f(47.25, 240.0, -47.25); //*
		glVertex3f(-35.95, 250.0, -35.95);
		glVertex3f(-47.25, 240.0, -47.25); //*
		glVertex3f(-35.95, 250.0, 35.95);
		glVertex3f(-47.25, 240.0, 47.25); //*
	glEnd();

	glPopMatrix();
}




