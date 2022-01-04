#ifndef _PPM_H
#define _PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Pixel struct
 *	uchar = 0-255 <=> color rgb
 * 
 */
typedef struct pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Pixel;

/**
 * @brief Image struct
 * 
 */
typedef struct image
{
	int w, h;
	Pixel **data;
} Image;

extern void FILEcheck(FILE * f);
extern void write(char * path, Image * img);
extern Image *read(char * path);

#endif