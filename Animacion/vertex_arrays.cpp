#include <iostream>
#include <cmath>
#include <vector>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;
#define PI 3.1415265359

struct SVertex
{
	GLfloat x,y,z;
	GLfloat r,g,b;
};

//Datos para los vertices de la esfera:
SVertex * Vertices;
int NumVertices;  //tamaño del arreglo de vertices
vector <GLuint> IndexVect;  
GLuint * Indices;
int NumIndices;   //tamaño del arreglo de indices

GLfloat ChangeY = 0.025;
						
float yRotated = 0.0;
bool PointsOnly = false;

void CreateSphere(int PointRows, int PointsPerRow)
{
	NumVertices = (PointRows-2)*PointsPerRow + 2;
	Vertices = new SVertex[NumVertices];
	IndexVect.clear();  
	float x,y,z;
	int i,j;
	double r;
	for (i = 1; i < (PointRows-1); i++)
	{
		for (j = 0; j < PointsPerRow; j++)
		{
			y = 1.0 - float(i) / float(PointRows-1)*2.0;
			r = sin (acos(y));  //radius of the row
			x = r * sin(float(j) / float(PointsPerRow)*PI*2.0);
			
			z = r * cos(float(j) / float(PointsPerRow)*PI*2.0);
			Vertices[(i-1)*PointsPerRow+j].x = x;
			Vertices[(i-1)*PointsPerRow+j].y = y;
			Vertices[(i-1)*PointsPerRow+j].z = z;
			Vertices[(i-1)*PointsPerRow+j].r = (float)(i) / float(PointRows);
			Vertices[(i-1)*PointsPerRow+j].g = 0.7;
			Vertices[(i-1)*PointsPerRow+j].b = (float)(j) / float(PointsPerRow);
		}

	}
	
	Vertices[(PointRows-2)*PointsPerRow].x = 0.0;
	Vertices[(PointRows-2)*PointsPerRow].y = 1.0;
	Vertices[(PointRows-2)*PointsPerRow].z = 0.0;
	Vertices[(PointRows-2)*PointsPerRow].r = 1.0;
	Vertices[(PointRows-2)*PointsPerRow].g = 0.7;
	Vertices[(PointRows-2)*PointsPerRow].b = 1.0;
	Vertices[(PointRows-2)*PointsPerRow+1].x = 0.0;
	Vertices[(PointRows-2)*PointsPerRow+1].y = -1.0;
	Vertices[(PointRows-2)*PointsPerRow+1].z = 0.0;
	Vertices[(PointRows-2)*PointsPerRow+1].r = 1.0;
	Vertices[(PointRows-2)*PointsPerRow+1].g = 0.7;
	Vertices[(PointRows-2)*PointsPerRow+1].b = 1.0;
	
	for (i = 1; i < (PointRows-2); i++)
	{
		for (j = 0; j < (PointsPerRow-1); j++)
		{
			IndexVect.push_back((i-1)*PointsPerRow+j);
			IndexVect.push_back((i-1)*PointsPerRow+j+1);
			IndexVect.push_back((i)*PointsPerRow+j);

			IndexVect.push_back((i-1)*PointsPerRow+j+1);
			IndexVect.push_back((i)*PointsPerRow+j+1);
			IndexVect.push_back((i)*PointsPerRow+j);
		}

		IndexVect.push_back((i-1)*PointsPerRow+PointsPerRow-1);
		IndexVect.push_back((i-1)*PointsPerRow);
		IndexVect.push_back((i)*PointsPerRow+j);

		IndexVect.push_back((i)*PointsPerRow);
		IndexVect.push_back((i-1)*PointsPerRow);
		IndexVect.push_back((i)*PointsPerRow+j);
	}		

	for (j = 0; j< (PointsPerRow-1); j++)
	{
		IndexVect.push_back(j);
		IndexVect.push_back(j+1);
		IndexVect.push_back((PointRows-2)*PointsPerRow);
	}
	IndexVect.push_back(j);
	IndexVect.push_back(0);
	IndexVect.push_back((PointRows-2)*PointsPerRow);

	for (j = 0; j< (PointsPerRow-1); j++)
	{
		IndexVect.push_back((PointRows-3)*PointsPerRow+j);
		IndexVect.push_back((PointRows-3)*PointsPerRow+j+1);
		IndexVect.push_back((PointRows-2)*PointsPerRow+1);
	}
	IndexVect.push_back((PointRows-3)*PointsPerRow+j);
	IndexVect.push_back((PointRows-3)*PointsPerRow);
	IndexVect.push_back((PointRows-2)*PointsPerRow+1);
	Indices = new GLuint[IndexVect.size()];  
	for (i = 0; i < IndexVect.size(); i++)
	{
		Indices[i] = IndexVect[i];
	}
	NumIndices = IndexVect.size();
	IndexVect.clear();  
}

void DrawSphere(void)
{
	if (!PointsOnly)
		glDrawElements(	GL_TRIANGLES, 
						NumIndices,  
						GL_UNSIGNED_INT,
						Indices);
	else 
		glDrawArrays(GL_POINTS,0,NumVertices);

}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-4.0);
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	DrawSphere();
	glFlush();			
	glutSwapBuffers();
}

void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;  
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
	glViewport(0,0,x,y);
	glMatrixMode(GL_MODELVIEW);
	
}

void Idle(void)
{
	Vertices[NumVertices-2].y += ChangeY;
	Vertices[NumVertices-1].y -= ChangeY;

	if (Vertices[NumVertices-2].y> 1.5 || Vertices[NumVertices-2].y< 0.5)
		 ChangeY *= -1;
	yRotated += 0.3;
	Display();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'p': 
		PointsOnly = !PointsOnly;
		break;
	}
}

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(300,300);
	glutCreateWindow("Arreglos de vertices");
	// calcula los vertices e indices
	CreateSphere(16,16);
	// como no se un depth buffer, no podemos rellenar la esfera
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// habilita la funcionalidad del arreglo de vertices:
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(	3,   //3 componentes por vertice (x,y,z)
						GL_FLOAT,
						sizeof(SVertex),
						Vertices);
	glColorPointer(		3,   //3 componentes por vertice (r,g,b)
						GL_FLOAT,
						sizeof(SVertex),
						&Vertices[0].r);  // apuntador al primer color
	glPointSize(2.0);
	glClearColor(0.0,0.0,0.0,0.0);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Idle);
	glutMainLoop();
	return 0;
}
