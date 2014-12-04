#ifndef MODELO
#define MODELO

#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif

#ifndef PI
#define PI 3.1415
#endif

// Datos para cinematica
#define TAMANHO_ARTICULACION_PIE       TAMANHO_ARTICULACION_CABEZA
#define ALTURA_PIE           TAMANHO_ARTICULACION_PIE * 2.0
#define ANCHO_PIE            ANCHO_PIERNA_INFERIOR
#define FOOT						ANCHO_PIE * 2.0
#define ALTURA_BRAZO_SUPERIOR         ALTURA_TORSO * 0.625
#define ANCHO_BRAZO_SUPERIOR          ANCHO_TORSO/4.0
#define TAMANHO_ARTICULACION_BRAZO_SUPERIOR     TAMANHO_ARTICULACION_CABEZA * 2.0
#define ALTURA_BRAZO_INFERIOR         ALTURA_TORSO * 0.5
#define ANCHO_BRAZO_INFERIOR          ANCHO_BRAZO_SUPERIOR
#define TAMANHO_ARTICULACION_BRAZO_INFERIOR     TAMANHO_ARTICULACION_BRAZO_SUPERIOR * 0.75
#define ALTURA_MANO           ALTURA_BRAZO_INFERIOR / 2.0
#define ANCHO_MANO            ANCHO_BRAZO_INFERIOR
#define MANO                  ANCHO_BRAZO_INFERIOR / 2.0
#define TAMANHO_DEDO           0.1
#define ANCHO_TORSO           ALTURA_TORSO * 0.75
#define ALTURA_TORSO          0.8
#define TORSO                 ANCHO_TORSO / 3.0
#define ANCHO_CABEZA            ALTURA_CABEZA * 0.93
#define ALTURA_CABEZA 				ALTURA_TORSO * 0.375
#define TAMANHO_ARTICULACION_CABEZA       ALTURA_CABEZA/6
#define ANCHO_BASE            ANCHO_TORSO
#define ALTURA_BASE           ALTURA_TORSO / 4.0
#define ALTURA_PIERNA_SUPERIOR         ALTURA_BRAZO_INFERIOR
#define TAMANHO_ARTICULACION_PIERNA_SUPERIOR     TAMANHO_ARTICULACION_BRAZO_SUPERIOR
#define ANCHO_PIERNA_SUPERIOR         TAMANHO_ARTICULACION_PIERNA_SUPERIOR * 2.0
#define ALTURA_PIERNA_INFERIOR         ALTURA_PIERNA_SUPERIOR
#define ANCHO_PIERNA_INFERIOR          ANCHO_PIERNA_SUPERIOR
#define TAMANHO_ARTICULACION_PIERNA_INFERIOR     TAMANHO_ARTICULACION_PIERNA_SUPERIOR
#define ALTURA_PIERNA            ALTURA_PIERNA_SUPERIOR + ALTURA_PIERNA_INFERIOR + ALTURA_PIE + 2*(TAMANHO_ARTICULACION_PIE+TAMANHO_ARTICULACION_PIERNA_SUPERIOR+TAMANHO_ARTICULACION_PIERNA_INFERIOR)

#define FRAMES 20

#define SOLID 1
#define WIRE  2

#define LEFT  0
#define RIGHT 1

extern float angulos_caminado[2][6];
extern double movimiento;

extern float langle_count;
extern float langle_count2;
extern float rangle_count;
extern float rangle_count2;

extern float zoom;
extern int zoom_flag;
extern int rotate_flag;
extern int rotate;


double desplazamiento(double angle_up, double angle_lo, double up, double lo);

void animate(void);

void animar_base(void);

void dibujaBaseLegs(void);

void dibujaBase(int frame);

void dibujaPierna(int side, int frame);

#endif