#ifndef _PPM_H
#define _PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 *	Pixel struct
 *	char = 0-255 <=> color rgb
 */ 
typedef struct pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Pixel;

/*
 *	Image struct
 */ 
typedef struct image
{
	int w, h;
	Pixel *data;
} Image;

extern void FILEcheck(FILE *);
extern void write(char *, Image *);
extern Image *read(char *);

#endif