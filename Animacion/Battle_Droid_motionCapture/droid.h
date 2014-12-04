#include "texture.h"
#include "objetos.h"
#include "motion.h"

/**Texturas**/


int piso,arm,arm2,arm3,arm4;
int which;/* Mov */
double angr = 45.0, waitt=0,ang=0,velh=0;


void cuerpo()
{
    glPushMatrix();
    
    glRotatef(180,0,1,0);
	
    //cadera
	glPushMatrix();
    glRotatef(90,1,0,0);
    glRotatef(90,0,0,1);
    glBindTexture(GL_TEXTURE_2D, arm3);
    gluSphere(p,.7,3,16);
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(0,0,-.8);
    cilindro(.2,1.5,arm2);
    glTranslatef(-.2,1.1,-.7);
    glRotatef(90,1,0,0);
    glScalef(.3,.3,1);
    glBindTexture(GL_TEXTURE_2D, arm4);
    gluSphere(p,.8,4,16);
    glTranslatef(1.5,0,.8);
    glRotatef(15,0,1,0);
    box(.4,.9,.3,arm4);
	glPopMatrix();
    
    //pecho
	glPushMatrix();
    glTranslatef(0,2.5,0);
    box(.55,1.05,.55,arm2);
    glRotatef(90,1,0,0);
    glScalef(.5,.55,.7);
    glBindTexture(GL_TEXTURE_2D, arm2);
    gluSphere(p,1.7,6,16);
    glTranslatef(0,0,-.5);
    gluSphere(p,1.7,6,16);
	glPopMatrix();
    
	glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(0,1.3,-.2);
    glBindTexture(GL_TEXTURE_2D, arm3);
    glutSolidTorus(.1,.60,5,8);
    glTranslatef(.06,3.3,.3);
    box(.04,.6,.06, arm3);
    glTranslatef(-.12,0,0);
    box(.04,.6,.06, arm3);
    glTranslatef(-.55,-1.5,-.1);
    box(.2,.6,.4, arm4);
    glTranslatef(1.2,0,0);
    box(.2,.6,.4, arm4);
    glTranslatef(-.6,.8,.1);
    glBindTexture(GL_TEXTURE_2D, arm3);
    gluSphere(p, 0.25, 64, 64);
	glPopMatrix();
    
    //hombros
	glPushMatrix();
    glTranslatef(0,3.7,.4);
    cilindro(.4,.4,arm4);
    cilindro(.35,.4,arm2);
    cilindro(.3,.2,arm2);
    glTranslatef(0,0,-2.2);
    cilindro(.4,.4,arm4);
    glTranslatef(0,0,-.8);
    cilindro(.35,.4,arm2);
    glTranslatef(0,0,-.6);
    cilindro(.3,.2,arm2);
    glTranslatef(0,0,-.5);
	glPopMatrix();
    //mochila
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,piso);
    glTranslatef(1.,3,0);
    glRotatef(90,1,0,0);
    glScalef(.2,.4,.4);
    gluSphere(p,1.7,8,16);
    glTranslatef(0,0,-.5);
    gluSphere(p,1.7,8,16);
    
	glPopMatrix();
    
	glPushMatrix();
    glTranslatef(1.05,6,.5);
    glRotatef(90,1,0,0);
    cilindro(.02,2.5,arm4);
    glTranslatef(0,0,-2.5);
    cilindro(.05,.2,arm4);
	glPopMatrix();
    
    glPopMatrix();
    
}

void pie()
{
	glPushMatrix();
    triangulo(.4,.3,.2, arm3);
    glTranslatef(.2,-.2,0);
    triangulo(.6,.2,.2, arm3);
	glPopMatrix();
}
//pierna izquierda
void piernaI()
{
    which =1;
    
    glPushMatrix();
	
    glRotatef(Walk_cycle[which][0][Step], 0.0, 0.0, 1.0);
	
    glPushMatrix();
    cilindro(.5,.6,arm3);
    glTranslatef(-.1,-1.8,-.3);
    box(.3,1.7,.15,arm2);
    glRotatef(90,1,0,0);
    glScalef(.4,.25,1);
    glBindTexture(GL_TEXTURE_2D,arm);
    gluSphere(p,1.5,64,4);
	glPopMatrix();
    
    glTranslatef(-.1,-3.5,.05);
	glRotatef(Walk_cycle[which][1][Step], 0.0, 0.0, 1.0);
	glPushMatrix();
    cilindro(.4,.5,arm3);
    glTranslatef(0,-1.4,-.25);
    glRotatef(3,0,0,1);
    box(.25,1.2,.1,arm2);
    glTranslatef(0,-.2,0);
    glRotatef(90,1,0,0);
    glScalef(.3,.2,1);
    glBindTexture(GL_TEXTURE_2D,arm);
    gluSphere(p,1.4,64,4);
    glTranslatef(0,0,.6);
    glBindTexture(GL_TEXTURE_2D,arm2);
    gluSphere(p,.9,64,32);
	glPopMatrix();
    
	glTranslatef(.2,-3.0,0.25);
	glRotatef(Walk_cycle[which][2][Step], 0.0, 0.0, 1.0);
	pie();
    
    glPopMatrix();
}

//pierna derecha
void piernaD()
{
    which = 0;
    glPushMatrix();
    glRotatef((Walk_cycle[which][0][Step]),0.0, 0.0, 1.0);
    
    glPushMatrix();
    //glRotatef(-5,0,0,1);
    cilindro(.5,.6,arm3);
    glTranslatef(-.1,-1.8,-.3);
    box(.3,1.7,.15,arm2);
    glRotatef(90,1,0,0);
    glScalef(.4,.25,1);
    glBindTexture(GL_TEXTURE_2D,arm);
    gluSphere(p,1.5,64,4);
	glPopMatrix();
	
	glTranslatef(-.1,-3.5,.05);
	glRotatef((Walk_cycle[which][1][Step]),0.0, 0.0, 1.0);
	
    glPushMatrix();
    cilindro(.4,.5,arm3);
    glTranslatef(0,-1.4,-.25);
    glRotatef(3,0,0,1);
    box(.25,1.2,.1,arm2);
    glTranslatef(0,-.2,0);
    glRotatef(90,1,0,0);
    glScalef(.3,.2,1);
    glBindTexture(GL_TEXTURE_2D,arm);
    gluSphere(p,1.4,64,4);
    glTranslatef(0,0,.6);
    glBindTexture(GL_TEXTURE_2D,arm2);
    gluSphere(p,.9,64,32);
	glPopMatrix();
    
	glTranslatef(.2,-3.0,0.25);
	glRotatef((Walk_cycle[which][2][Step]),0.0, 0.0, 1.0);
	pie();
    glPopMatrix();
	
}
void dedo(){
	glPushMatrix();
    glRotatef(15,1,0,0);
    box(.06,.2,.04,arm3);
    glTranslatef(0.,-.35,.1);
    glRotatef(-30,1,0,0);
    box(.06,.2,.04,arm3);
	glPopMatrix();
}
//brazo izquierdo
void brazoD()
{
    which=0;
    glPushMatrix();
	
    glRotatef((Walk_cycle[which][3][Step]),0.0, 0.0, 1.0);
	
    
    glPushMatrix();
    cilindro(.25,.3,arm3);
    glTranslatef(0,-.2,-.15);
    box(.2,.15,.1,arm);
    glTranslatef(0,-1.1,0);
    box(.1,1,.08,arm2);
    glTranslatef(0,.1,0);
    glRotatef(90,1,0,0);
    glBindTexture(GL_TEXTURE_2D,arm);
    glScalef(.3,.2,1);
    gluSphere(p,1,64,4);
	glPopMatrix();
    
    glTranslatef(0,-2.3,.0);
    glRotatef((Walk_cycle[which][4][Step]),0.0, 0.0, 1.0);
    glScalef(1.2,1.2,1.2);
    
	glPushMatrix();
    cilindro(.20,.3,arm3);
    glTranslatef(0,-.2,-.15);
    box(.05,.15,.05,arm);
    glTranslatef(0,-.15,0);
    box(.15,.1,.08,arm);
    glTranslatef(-.08,-.6,0);
    box(.04,.5,.04,arm);
    glTranslatef(.16,0,0);
    box(.04,.5,.04,arm);
    glTranslatef(-.06,-.5,0);
    box(.13,.08,.04,arm);
	glPopMatrix();
    
    //mano
	glPushMatrix();
	glTranslatef(0,-1.5,.15);
    box(.16,.12,.05,arm2);
    glTranslatef(.1,-.25,-.05);
    dedo();
    glTranslatef(-.2,0,0);
    dedo();
    glTranslatef(.1,0,.15);
    glRotatef(-30,1,0,0);
    box(.06,.2,.04,arm3);
	glPopMatrix();
    
    
    glPopMatrix();
}

//brazo derecho
void brazoI(){
    which=1;
    glPushMatrix();
   	glRotatef((Walk_cycle[which][3][Step]),0.0, 0.0, 1.0);
	glPushMatrix();
    cilindro(.25,.3,arm3);
    glTranslatef(0,-.2,-.15);
    box(.2,.15,.1,arm);
    glTranslatef(0,-1.1,0);
    box(.1,1,.08,arm2);
    glTranslatef(0,.1,0);
    glRotatef(90,1,0,0);
    glBindTexture(GL_TEXTURE_2D,arm);
    glScalef(.3,.2,1);
    gluSphere(p,1,64,4);
	glPopMatrix();
    
    glTranslatef(0,-2.3, 0.0);
    glRotatef(Walk_cycle[which][4][Step],0.0, 0.0, 1.0);
    glScalef(1.2,1.2,1.2);
	glPushMatrix();
    cilindro(.20,.3,arm3);
    glTranslatef(0,-.2,-.15);
    box(.05,.15,.05,arm);
    glTranslatef(0,-.15,0);
    box(.15,.1,.08,arm);
    glTranslatef(-.08,-.6,0);
    box(.04,.5,.04,arm);
    glTranslatef(.16,0,0);
    box(.04,.5,.04,arm);
    glTranslatef(-.06,-.5,0);
    box(.13,.08,.04,arm);
	glPopMatrix();
	//mano
	glPushMatrix();
    glTranslatef(0,-1.5,.15);
    glRotatef(180,0,1,0);
    box(.16,.12,.05,arm2);
    glTranslatef(.1,-.25,-.05);
    dedo();
    glTranslatef(-.2,0,0);
    dedo();
    glTranslatef(.1,0,.15);
    glRotatef(-30,1,0,0);
    box(.06,.2,.04,arm3);
	glPopMatrix();
    
    glPopMatrix();
	
}


void cabeza(){
    glPushMatrix();
    glRotatef(ang,0,0,1);
	glScalef(1.2,1.2,1.2);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,arm2);
    for(float i =0;i<=.1;i+=.01){
        glTranslatef(i,sqrt(.005-i*i),0);
        gluSphere(p,.3,16,16);
    }
    glPopMatrix();
    
    glPushMatrix();
	glTranslatef(.4,.4,0);
    gluSphere(p,.3,16,16);
    glTranslatef(.4,-.26,0);
    glRotatef(90,0,1,0);
    glRotatef(45,1,0,0);
    glScalef(.4,.3,1);
    glBindTexture(GL_TEXTURE_2D,arm2);
    gluSphere(p,.8,16,16);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(.2,.2,-.35);
    cilindro(.15,.7,arm4);
    glTranslatef(0,-.07,-.35);
    glRotatef(90,1,0,0);
    cilindro(.15,.3,arm4);
    glTranslatef(-.35,.2,-.25);
    cilindro(.07,.4,arm3);
    cilindro(.04,.1,arm3);
    glTranslatef(0,-.4,-.5);
    cilindro(.07,.4,arm3);
    cilindro(.04,.1,arm3);
    glPopMatrix();
    
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,piso);
    glTranslatef(.9,.3,.20);
    gluSphere(p,.05,16,16);
    glTranslatef(0,0,-.40);
    gluSphere(p,.05,16,16);
    
    glTranslatef(.35,-.62,.20);
    glRotatef(90,0,1,0);
    glRotatef(45,1,0,0);
    cilindro(.1,.155,arm3);
    glPopMatrix();
    
    glPopMatrix();
}

void droid(){
    glPushMatrix();
    glRotatef(90,0,1,0);
	piernaD();
	glTranslatef(0,0,2);
	piernaI();
	glTranslatef(0,0,-.7);
	cuerpo();	
	glTranslatef(0,3.7,1.4);
	brazoI();
	glTranslatef(0,0,-3.1);
	brazoD();
	glTranslatef(-.4,1.4,1.7);
	cabeza();
    glPopMatrix();
}