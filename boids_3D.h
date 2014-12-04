//
//  boids_3D.h
//  Animacion
//
//  Created by sueric on 14/11/13.
//  Copyright (c) 2013 SuEric. All rights reserved.
//

#ifndef __Animacion__boids_3D__
#define __Animacion__boids_3D__

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const double tamano = 0.48,	trianguloy = tamano * 8,	posicion = 0.05,	angulo = 1.0,
gmedida  = tamano * 200,	grmedida  = tamano * 200, minX = -gmedida/2.0, maxX = gmedida/2.0,
minZ = -gmedida/2.0,		maxZ =  gmedida/2.0,		x_umbral = gmedida / 10.0,
z_umbral = grmedida / 10.0;

struct Dist {
    int i;
    double d;
};

int aleatorio(int min, int max)
{
    return ( min + (rand() % (max-min)) );
}

class boids {
    int inicio;
    
public:
    boids(int i)
    {
        inicioo = i;
        
        curX = aleatorio((-gmedida/2.0), (gmedida/2.0));
        curZ = aleatorio((-grmedida/2.0), (grmedida/2.0));
        
        curAng = aleatorio(-180, 180);
        
        
        prevX = curX;
        prevZ = curZ;
        prevAng = curAng;
        
        colorR = 0.88;
        colorG = 0.44;
        colorB = 0.88;
    }
    
    void encuentracerca(vector<boids> objetos)
    {
        vector<Dist> dists;
        cerca.clear();
        int min;
        
        for (int i = 0; i < objetos.size(); i++) {
            
            if (objetos[i].inicioo == inicioo)
                continue;
            
            Dist dist;
            dist.i = i;
            dist.d = sqrt(pow((objetos[i].prevX - prevX), 2.0) +
                          pow((objetos[i].prevZ - prevZ), 2.0));
            dists.push_back(dist);
        }
        for (int i = 0; ((i<8) && (i<dists.size()-1)); i++) {
            min = i;
            for (int j = i+1; j < dists.size(); j++) {
                if (dists[j].d < dists[min].d)
                    min = j;
            }
            cerca.push_back(dists[min].i);
            swap(dists[i], dists[min]);
        }
    }
    
    void mover(void)
    {
        double dx = sin(curAng * d2r)/2, dz = cos(curAng * d2r)/2;
        
        curX += (dx * posicion);
        curZ += (dz * posicion);
        
        double distizquierda = fabs(curX - maxX),
        distderecha = fabs(curX - minX),
        distarriba = fabs(curZ - maxZ),
        distabajo = fabs(curZ - minZ);
        
        bool cercaizquierda = (distizquierda <= x_umbral),
        cercaderecha = (distderecha <= x_umbral),
        cercaarriba = (distarriba <= z_umbral),
        cercaabajo = (distabajo <= z_umbral);
        
        distizquierda = fabs((x_umbral - distizquierda) / x_umbral);
        distderecha = fabs((x_umbral - distderecha) / x_umbral);
        distarriba = fabs((z_umbral - distarriba) / z_umbral);
        distabajo = fabs((z_umbral - distabajo) / z_umbral);
        
        
        double targetAng = 0,dist = 0;
        if (cercaarriba && cercaderecha) {
            if ((90 <= curAng) && (curAng <= 180))
                return;
            targetAng = 180.0 + curAng;
            dist = sqrt(pow(distarriba,2) + pow(distderecha, 2));
        }
        else if (cercaarriba && cercaizquierda) {
            if ((-180 <= curAng) && (curAng <= -90))
                return;
            targetAng = 180.0 + curAng;
            dist = sqrt(pow(distarriba,2) + pow(distizquierda, 2));
        }
        else if (cercaabajo && cercaderecha) {
            if ((0 <= curAng) && (curAng <= 90))
                return;
            
            targetAng = 180.0 + curAng;
            dist = sqrt(pow(distabajo,2) + pow(distderecha, 2));
        }
        else if (cercaabajo && cercaizquierda) {
            if ((-90 <= curAng) && (curAng <= 0))
                return;
            targetAng = 180.0 + curAng;
            dist = sqrt(pow(distabajo,2) + pow(distizquierda, 2));
        }
        else if (cercaarriba) {
            dist = distarriba;
            if ((0 <= curAng) && (curAng < 180))
                targetAng = 180.0 - curAng;
            else if ((-180 < curAng) && (curAng < 0))
                targetAng = curAng - 180.0;
            else
                return;
        }
        else if (cercaabajo) {
            dist = distabajo;
            if ((0 < curAng) && (curAng <= 180))
                targetAng = 180.0 - curAng;
            else if ((-180 < curAng) && (curAng < 0))
                targetAng = 180.0 - curAng;
            else
                return;
        }
        else if (cercaizquierda) {
            dist = distizquierda;
            if ((-90 < curAng) && (curAng <= 90))
                targetAng = -curAng;
            else if ((90 < curAng) && (curAng < 270))
                targetAng = 360 - curAng;
            else
                return;
        }
        else if (cercaderecha) {
            dist = distderecha;
            if ((-270 < curAng) && (curAng <= -90))
                targetAng = -curAng - 360.0;
            else if ((-90 < curAng) && (curAng < 90))
                targetAng = -curAng;
            else
                return;
        }
        
        double targetAngChg = targetAng - curAng;
        
        curAng += (dist / 20.0) * targetAngChg;
        while (curAng < -180)
            curAng += 360;
        while (curAng > 180)
            curAng -= 360;
        
    }
    
    double curX;   double curZ;   double curAng;
    double prevX;  double prevZ;  double prevAng;
    double colorR; double colorG; double colorB;
    int inicioo;
    vector<int> cerca;

};

#endif /* defined(__Animacion__boids_3D__) */
