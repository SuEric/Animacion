#include "modelo2.h"

double desplazamiento(double langle_up, double langle_lo, double rangle_up, double rangle_lo){
    double resultado1, resultado2, primer_resultado, segundo_resultado, radianes_superior, radianes_inferior ;
    
    radianes_superior = (PI*langle_up)/180.0 ;
    radianes_inferior = (PI*langle_lo-langle_up)/180.0 ;
    resultado1 = (ALTURA_PIERNA_SUPERIOR + 2*TAMANHO_ARTICULACION_PIERNA_SUPERIOR) * cos(radianes_superior) ;
    resultado2 = (ALTURA_PIERNA_INFERIOR + 2*(TAMANHO_ARTICULACION_PIERNA_INFERIOR+TAMANHO_ARTICULACION_PIE)+ALTURA_PIE)* cos(radianes_inferior) ;
    primer_resultado = ALTURA_PIERNA - (resultado1 + resultado2) ;
    
    radianes_superior = (PI*rangle_up)/180.0 ;
    radianes_inferior = (PI*rangle_lo-rangle_up)/180.0 ;
    resultado1 = (ALTURA_PIERNA_SUPERIOR + 2*TAMANHO_ARTICULACION_PIERNA_SUPERIOR) * cos(radianes_superior) ;
    resultado2 = (ALTURA_PIERNA_INFERIOR + 2*(TAMANHO_ARTICULACION_PIERNA_INFERIOR+TAMANHO_ARTICULACION_PIE)+ALTURA_PIE)* cos(radianes_inferior) ;
    segundo_resultado = ALTURA_PIERNA - (resultado1 + resultado2) ;
    
    if (primer_resultado <= segundo_resultado) return (- primer_resultado) ;
    else return (- segundo_resultado) ;
}


void animar_base()
{
    
    static frames = FRAMES, zoom_fl = 0, flag = 1;
    
    float l_upleg_dif, r_upleg_dif,
    l_upleg_add, r_upleg_add,
    l_loleg_dif, r_loleg_dif,
    l_loleg_add,r_loleg_add;
    
    switch (flag) {
        case 1:
            l_upleg_dif = 15;
            r_upleg_dif = 5;
            l_loleg_dif = 15;
            r_loleg_dif = 5;
            
            l_upleg_add = l_upleg_dif/FRAMES;
            r_upleg_add = r_upleg_dif/FRAMES;
            l_loleg_add = l_loleg_dif/FRAMES;
            r_loleg_add = r_loleg_dif/FRAMES;
            
            angulos_caminado[0][3] += r_upleg_add;
            angulos_caminado[1][3] += l_upleg_add;
            angulos_caminado[0][4] += r_loleg_add;
            angulos_caminado[1][4] += l_loleg_add;
            
            langle_count  -= l_upleg_add;
            langle_count2 -= l_loleg_add;
            rangle_count -= r_upleg_add;
            rangle_count2 -= r_loleg_add;
            
            movimiento = desplazamiento(langle_count, langle_count2, rangle_count, rangle_count2);
            
            frames--;
            
            if (frames == 0) {
                flag = 2;
                frames = FRAMES;
            }
            break;
            
        case 2:
            l_upleg_dif = 20;
            r_upleg_dif = -65;
            l_loleg_dif = -15;
            r_loleg_dif = 85;
            
            l_upleg_add = l_upleg_dif/FRAMES;
            r_upleg_add = r_upleg_dif/FRAMES;
            l_loleg_add = l_loleg_dif/FRAMES;
            r_loleg_add = r_loleg_dif/FRAMES;
            
            angulos_caminado[0][3] += r_upleg_add;
            angulos_caminado[1][3] += l_upleg_add;
            angulos_caminado[0][4] += r_loleg_add;
            angulos_caminado[1][4] += l_loleg_add;
            
            langle_count  -= l_upleg_add;
            langle_count2 -= l_loleg_add;
            rangle_count -= r_upleg_add;
            rangle_count2 -= r_loleg_add;
            
            movimiento = desplazamiento(langle_count, langle_count2, rangle_count, rangle_count2);
            
            frames--;
            
            if (frames == 0) {
                flag = 3;
                frames = FRAMES;
            }
            break;
            
        case 3:
            l_upleg_dif = 5;
            r_upleg_dif = -25;
            l_loleg_dif = 10;
            r_loleg_dif = -40;
            
            l_upleg_add = l_upleg_dif/FRAMES;
            r_upleg_add = r_upleg_dif/FRAMES;
            l_loleg_add = l_loleg_dif/FRAMES;
            r_loleg_add = r_loleg_dif/FRAMES;
            
            angulos_caminado[0][3] += r_upleg_add;
            angulos_caminado[1][3] += l_upleg_add;
            angulos_caminado[0][4] += r_loleg_add;
            angulos_caminado[1][4] += l_loleg_add;
            
            langle_count  -= l_upleg_add;
            langle_count2 -= l_loleg_add;
            rangle_count -= r_upleg_add;
            rangle_count2 -= r_loleg_add;
            
            movimiento = desplazamiento(langle_count,langle_count2,rangle_count,rangle_count2 ) ;
            
            frames--;
            
            if (frames == 0){
                flag = 4 ;
                frames = FRAMES ;
            }
            break ;
        case 4 :
            l_upleg_dif = 20 ;
            r_upleg_dif = 25 ;
            l_loleg_dif = -10 ;
            r_loleg_dif = -50 ;
            
            l_upleg_add = l_upleg_dif / FRAMES ;
            r_upleg_add = r_upleg_dif / FRAMES ;
            l_loleg_add = l_loleg_dif / FRAMES ;
            r_loleg_add = r_loleg_dif / FRAMES ;
            
            angulos_caminado[0][3] += r_upleg_add ;
            angulos_caminado[1][3] += l_upleg_add ;
            angulos_caminado[0][4] += r_loleg_add ;
            angulos_caminado[1][4] += l_loleg_add ;
            
            langle_count  -= l_upleg_add ;
            langle_count2 -= l_loleg_add ;
            rangle_count -= r_upleg_add ;
            rangle_count2 -= r_loleg_add ;
            movimiento = desplazamiento(langle_count,langle_count2,rangle_count,rangle_count2 ) ;
            frames-- ;
            if (frames == 0){
                flag = 5 ;
                frames = FRAMES ;
            }
            break ;
        case 5 :
            l_upleg_dif = 5 ;
            r_upleg_dif = 15 ;
            l_loleg_dif = 5 ;
            r_loleg_dif = 15 ;
            
            l_upleg_add = l_upleg_dif / FRAMES ;
            r_upleg_add = r_upleg_dif / FRAMES ;
            l_loleg_add = l_loleg_dif / FRAMES ;
            r_loleg_add = r_loleg_dif / FRAMES ;
            
            angulos_caminado[0][3] += r_upleg_add ;
            angulos_caminado[1][3] += l_upleg_add ;
            angulos_caminado[0][4] += r_loleg_add ;
            angulos_caminado[1][4] += l_loleg_add ;
            
            langle_count  += r_upleg_add ;
            langle_count2 += r_loleg_add ;
            rangle_count -= r_upleg_add ;
            rangle_count2 -= r_loleg_add ;
            movimiento = desplazamiento(langle_count,langle_count2,rangle_count,rangle_count2 ) ;
            frames-- ;
            if (frames == 0){
                flag = 6 ;
                frames = FRAMES ;
            }
            break ;
        case 6 :
            l_upleg_dif = -65 ;
            r_upleg_dif = 20 ;
            l_loleg_dif = 85 ;
            r_loleg_dif = -15 ;
            
            l_upleg_add = l_upleg_dif / FRAMES ;
            r_upleg_add = r_upleg_dif / FRAMES ;
            l_loleg_add = l_loleg_dif / FRAMES ;
            r_loleg_add = r_loleg_dif / FRAMES ;
            
            angulos_caminado[0][3] += r_upleg_add ;
            angulos_caminado[1][3] += l_upleg_add ;
            angulos_caminado[0][4] += r_loleg_add ;
            angulos_caminado[1][4] += l_loleg_add ;
            
            langle_count  += r_upleg_add ;
            langle_count2 += r_loleg_add ;
            rangle_count -= r_upleg_add ;
            rangle_count2 -= r_loleg_add ;
            movimiento = desplazamiento(langle_count,langle_count2,rangle_count,rangle_count2 ) ;
            frames-- ;
            if (frames == 0){
                flag = 7 ;
                frames = FRAMES ;
            }
            break ;
        case 7 :
            l_upleg_dif = -25 ;
            r_upleg_dif = 5 ;
            l_loleg_dif = -40 ;
            r_loleg_dif = 10 ;
            
            l_upleg_add = l_upleg_dif / FRAMES ;
            r_upleg_add = r_upleg_dif / FRAMES ;
            l_loleg_add = l_loleg_dif / FRAMES ;
            r_loleg_add = r_loleg_dif / FRAMES ;
            
            angulos_caminado[0][3] += r_upleg_add ;
            angulos_caminado[1][3] += l_upleg_add ;
            angulos_caminado[0][4] += r_loleg_add ;
            angulos_caminado[1][4] += l_loleg_add ;
            
            langle_count  += r_upleg_add ;
            langle_count2 += r_loleg_add ;
            rangle_count -= r_upleg_add ;
            rangle_count2 -= r_loleg_add ;
            movimiento = desplazamiento(langle_count,langle_count2,rangle_count,rangle_count2 ) ;
            frames-- ;
            if (frames == 0){
                flag = 8 ;
                frames = FRAMES ;
            }
            break ;
        case 8 :
            l_upleg_dif = 25 ;
            r_upleg_dif = 20 ;
            l_loleg_dif = -50 ;
            r_loleg_dif = -10 ;
            
            l_upleg_add = l_upleg_dif / FRAMES ;
            r_upleg_add = r_upleg_dif / FRAMES ;
            l_loleg_add = l_loleg_dif / FRAMES ;
            r_loleg_add = r_loleg_dif / FRAMES ;
            
            angulos_caminado[0][3] += r_upleg_add ;
            angulos_caminado[1][3] += l_upleg_add ;
            angulos_caminado[0][4] += r_loleg_add ;
            angulos_caminado[1][4] += l_loleg_add ;
            
            langle_count  += r_upleg_add ;
            langle_count2 += r_loleg_add ;
            rangle_count -= r_upleg_add ;
            rangle_count2 -= r_loleg_add ;
            movimiento = desplazamiento(langle_count,langle_count2,rangle_count,rangle_count2 ) ;
            frames-- ;
            if (frames == 0){
                flag = 1 ;
                frames = FRAMES ;
            }
            break ;
        default :
            break ;
    }
    
    if (zoom_flag){
        switch (zoom_fl)
        {
            case 0 :
                zoom += 0.05 ;
                if (zoom > 2.5) zoom_fl = 1 ;
                break ;
            case 1 :
                zoom -= 0.05 ;
                if (zoom < -2.5) zoom_fl = 0 ;
                break ;
            default :
                break ;
        }
    }
    
    if (rotate_flag){
        rotate = (rotate + 1) % 360 ;
    }
    glutPostRedisplay() ;
}

void dibujaBaseLegs(void)
{
    glPushMatrix();
    
    glTranslatef(0.0, movimiento, 0.0);
    dibujaBase(SOLID);
    glTranslatef(0.0, -(ALTURA_BASE), 0.0);
    
    glPushMatrix();
    glTranslatef(ANCHO_TORSO * 0.33,0.0,0.0);
    dibujaPierna(LEFT, SOLID);
    glPopMatrix();
    
    glTranslatef(- ANCHO_TORSO * 0.33,0.0,0.0);
    dibujaPierna(RIGHT, SOLID);
    
    glPopMatrix() ;
}

void dibujaBase(int frame)
{
	glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(ANCHO_BASE, ALTURA_BASE, TORSO);
    if (frame == WIRE) glutWireCube(1.0);
    else glutSolidCube(1.0);
    glPopMatrix();
}

void dibujaPierna_Superior(int frame)
{
    glPushMatrix() ;
    glScalef(TAMANHO_ARTICULACION_PIERNA_SUPERIOR, TAMANHO_ARTICULACION_PIERNA_SUPERIOR, TAMANHO_ARTICULACION_PIERNA_SUPERIOR);
    glColor3f(0.0, 1.0, 0.0);
    if (frame == WIRE) glutWireSphere(1.0,8,8);
    else glutSolidSphere(1.0,8,8);
    glPopMatrix();
    
    glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0.0,- ALTURA_PIERNA_SUPERIOR * 0.75, 0.0);
    
    glPushMatrix();
    glScalef(ANCHO_PIERNA_SUPERIOR, ALTURA_PIERNA_SUPERIOR, ANCHO_PIERNA_SUPERIOR);
    if (frame == WIRE) glutWireCube(1.0) ;
    else glutSolidCube(1.0) ;
    glPopMatrix() ;
}

void dibujaPierna_Inferior(int frame)
{
    glPushMatrix() ;
    glScalef(TAMANHO_ARTICULACION_PIERNA_INFERIOR,TAMANHO_ARTICULACION_PIERNA_INFERIOR,TAMANHO_ARTICULACION_PIERNA_INFERIOR);
    glColor3f(0.0, 1.0, 0.0);
    if (frame == WIRE) glutWireSphere(1.0, 8, 8);
    else glutSolidSphere(1.0, 8, 8);
    glPopMatrix();
    
    glTranslatef(0.0,- ALTURA_PIERNA_INFERIOR * 0.75, 0.0);
    
    glPushMatrix();
    glScalef(ANCHO_PIERNA_INFERIOR,ALTURA_PIERNA_INFERIOR,ANCHO_PIERNA_INFERIOR);
    glColor3f(0.4, 0.4, 0.4);
    if (frame == WIRE) glutWireCube(1.0);
    else glutSolidCube(1.0);
    glPopMatrix();
}

void Dibuja_Pie(int frame)
{
    glPushMatrix();
    glScalef(TAMANHO_ARTICULACION_PIE,TAMANHO_ARTICULACION_PIE,TAMANHO_ARTICULACION_PIE);
    glColor3f(0.0,1.0,0.0);
    if (frame == WIRE) glutWireCube(1.0);
    else glutSolidCube(1.0);
    glPopMatrix() ;
    
    glTranslatef(0.0,- TAMANHO_ARTICULACION_PIE * 2.0, ANCHO_PIE * 0.5);
    
    glPushMatrix();
    glScalef(ANCHO_PIE, ALTURA_PIE, FOOT);
    glColor3f(0.0, 0.0, 0.0);
    if (frame == WIRE) glutWireCube(1.0);
    else glutSolidCube(1.0);
    glPopMatrix() ;
}

void dibujaPierna(int side, int frame)
{
    glPushMatrix() ;
    glRotatef(angulos_caminado[side][3],1.0,0.0,0.0) ;
    dibujaPierna_Superior(frame) ;
    glTranslatef(0.0,- ALTURA_PIERNA_SUPERIOR * 0.75,0.0) ;
    glRotatef(angulos_caminado[side][4],1.0,0.0,0.0) ;
    dibujaPierna_Inferior(frame) ;
    glTranslatef(0.0,- ALTURA_PIERNA_INFERIOR * 0.625, 0.0) ;
    glRotatef(angulos_caminado[side][5],1.0,0.0,0.0) ;
    Dibuja_Pie(frame) ;
    glPopMatrix() ;
}