GLUquadricObj *p = gluNewQuadric();

void esfera(float t,int text)
{
	glPushMatrix();	
		glBindTexture(GL_TEXTURE_2D,text);
		glRotatef(90, 1, 0, 0);
		gluSphere(p,t,23,23);
	glPopMatrix();
}

void cilindro(float radio, float alto, int text){
	   glBindTexture(GL_TEXTURE_2D,text);
		glDisable(GL_CULL_FACE);
		gluDisk(p,0.0,radio,26,26);
		gluCylinder(p,radio,radio,alto,26,26);
		glTranslatef(0,0,alto);
		gluDisk(p,0.0,radio,26,26);
}

void box(float x, float y, float z,int text){
		glBindTexture(GL_TEXTURE_2D,text);
		glNormal3f(0.0f, 1.0f, 0.0f);
		//Front Face
		glBegin(GL_POLYGON);
			glTexCoord2f(0,0);			glVertex3f(-x,-y,z);
			glTexCoord2f(1,0);			glVertex3f( x,-y,z);
			glTexCoord2f(1,1);			glVertex3f( x, y,z);
			glTexCoord2f(0,1);			glVertex3f(-x,y ,z);
		glEnd();
		glNormal3f(0.0f, -1.0f, 0.0f);
		//Back Face
		glBegin(GL_POLYGON);
			glTexCoord2f(1,0);			glVertex3f(-x,-y,-z);
			glTexCoord2f(1,1);			glVertex3f(-x, y,-z);
			glTexCoord2f(0,1);			glVertex3f( x, y,-z);
			glTexCoord2f(0,0);			glVertex3f( x,-y,-z);
		glEnd();

		glNormal3f(-1.0f, 0.0f, 0.0f);
		//Left Face
		glBegin(GL_POLYGON);
			glTexCoord2f(1,0);			glVertex3f(-x,-y, z);
			glTexCoord2f(1,1);			glVertex3f(-x, y, z);
			glTexCoord2f(0,1);			glVertex3f(-x, y,-z);
			glTexCoord2f(0,0);			glVertex3f(-x,-y,-z);
		glEnd();

		glNormal3f(1.0f, 0.0f, 0.0f);
		//Right Face
		glBegin(GL_POLYGON);
			glTexCoord2f(0,0);			glVertex3f(x,-y, z);
			glTexCoord2f(1,0);			glVertex3f(x,-y,-z);
			glTexCoord2f(1,1);			glVertex3f(x, y,-z);
			glTexCoord2f(0,1);			glVertex3f(x, y, z);
		glEnd();
		
		glNormal3f(0.0f, 0.0f, -1.0f);
		//Top Face
		glBegin(GL_POLYGON);
			glTexCoord2f(1,1);			glVertex3f(-x, y,  z);
			glTexCoord2f(0,1);			glVertex3f( x, y,  z);
			glTexCoord2f(0,0);			glVertex3f( x, y, -z);
			glTexCoord2f(1,0);			glVertex3f(-x, y, -z);
		glEnd();

		glNormal3f(0.0f, 0.0f, 1.0f);
		//Botton Face
		glBegin(GL_POLYGON);
			glTexCoord2f(0,0);			glVertex3f(-x, -y,  z);
			glTexCoord2f(0,1);			glVertex3f(-x, -y, -z);
			glTexCoord2f(1,1);			glVertex3f( x, -y, -z);
			glTexCoord2f(1,0);			glVertex3f( x, -y,  z);
		glEnd();

}

void triangulo(float x,float y, float z, int text){
	glBindTexture(GL_TEXTURE_2D,text);
	//Left Face
		glBegin(GL_POLYGON);
			glTexCoord2f(1,0);
			glVertex3f(-x,-y, z);
			glTexCoord2f(1,1);
			glVertex3f(-x, y, z);
			glTexCoord2f(0,1);
			glVertex3f(-x, y,-z);
			glTexCoord2f(0,0);
			glVertex3f(-x,-y,-z);
		glEnd();

			//Botton Face
		glBegin(GL_POLYGON);
			glTexCoord2f(0,1);
			glVertex3f(-x, -y,  z);
			glTexCoord2f(0,0);
			glVertex3f(-x, -y, -z);
			glTexCoord2f(1,0);
			glVertex3f( x, -y, -z);
			glTexCoord2f(1,1);
			glVertex3f( x, -y,  z);
		glEnd();

		glBegin(GL_POLYGON);
			glTexCoord2f(0,1);
			glVertex3f(-x, y, z);
			glTexCoord2f(0,0);
			glVertex3f(-x, y, -z);
			glTexCoord2f(1,0);
			glVertex3f( x, -y, -z);
			glTexCoord2f(1,1);
			glVertex3f( x, -y, z);
		glEnd();

		glBegin(GL_POLYGON);
			glTexCoord2f(0,1);
			glVertex3f(-x, -y, z);
			glTexCoord2f(0,0);
			glVertex3f(-x, y, z);
			glTexCoord2f(1,0);
			glVertex3f( x, -y, z);
		glEnd();

		glBegin(GL_POLYGON);
			glTexCoord2f(0,1);
			glVertex3f(-x, y, -z);
			glTexCoord2f(0,0);
			glVertex3f(-x, -y, -z);
			glTexCoord2f(1,0);
			glVertex3f( x, -y, -z);
		glEnd();
}

void cuadro(float ancho, float largo, int text){
	
	glBindTexture(GL_TEXTURE_2D,text);
	glDisable(GL_CULL_FACE);
	glBegin(GL_POLYGON); 
		glTexCoord2f(1,0);		glVertex3f(-ancho/2,-largo/2,0);
		glTexCoord2f(1,1);		glVertex3f(ancho,-largo/2,0);
		glTexCoord2f(0,1);		glVertex3f(ancho,largo,0);
		glTexCoord2f(0,0);		glVertex3f(-ancho/2,largo,0);
	glEnd(); 

}

void quad(int larg,int tam){
	float at =0;
	int id=0;
	glBegin(GL_QUAD_STRIP);
		for(int i = 0;i<=larg;i++){	
			glTexCoord2f(id,0);glVertex3f(at,0,0);
			glTexCoord2f(id,1);glVertex3f(at,tam,0);
			at+=tam;
			id==0?id=1:id=0;
		}
	glEnd();

}

void mosaico(int ancho, int largo, int tam,int text){
	glBindTexture(GL_TEXTURE_2D,text);
	for(int i =0;i<ancho;i++){
		quad(largo,tam);
		glTranslatef(0,tam,0);
	}

}