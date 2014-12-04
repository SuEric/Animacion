#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <GLUT/glut.h>

#include "texture.h"
/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

int num_texture = -1; //Counter to keep track of the last loaded texture

/**********************************************************
 *
 * FUNCTION LoadBitmap(char *)
 *
 * This function loads a bitmap file and return the OpenGL reference ID to use that texture
 *
 *********************************************************/

int  LoadBitmap(char *filename)
{
#define SAIR    {fclose(fp_arquivo); return -1;}
#define CTOI(C) (*(int*)&C)
    
    GLubyte     *image;
    GLubyte     Header[0x54];
    GLuint      DataPos, imageSize;
    GLsizei     Width,Height;
    
    num_texture++;
    
    // Abre un archivo y efectua la lectura del encabezado del archivo BMP
    FILE * fp_arquivo = fopen(filename, "rb");
    
    if (!fp_arquivo) return -1;
    
    if (fread(Header,1,0x36,fp_arquivo) != 0x36) SAIR;
    if (Header[0] != 'B' || Header[1] != 'M') SAIR;
    
    if (CTOI(Header[0x1E]) != 0) SAIR;
    if (CTOI(Header[0x1C]) != 24) SAIR;
    
    // Recupera los atributos de la altura y ancho de la imagen
    Width   = CTOI(Header[0x12]);
    Height  = CTOI(Header[0x16]);
    
    (CTOI(Header[0x0A]) == 0) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );
    
    imageSize = Width*Height*3;
    
    image = (GLubyte *) malloc (imageSize); // Llama a la imagen
    
    int retorno = (int)fread(image,1,imageSize,fp_arquivo);
    
    if (retorno !=imageSize){free(image); SAIR;}
    
    
    // Invierte los valores de R y B
    for (int i = 0; i < imageSize; i += 3 ){
        int t = image[i];
        image[i] = image[i+2];
        image[i+2] = t;
    }
    
    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter
    
    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.
    
    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    free(image); // Free the memory we used to load the texture
    
    return (num_texture); // Returns the current texture OpenGL ID
}