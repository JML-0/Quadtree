#ifndef _UTILS_H
#define _UTILS_H
#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/*
 *	Quadtree struct
 */ 
typedef struct Quadtree
{	
	Pixel color;

	struct Quadtree *NO, *NE;
	struct Quadtree *SO, *SE;
 } *Quadtree;

extern Pixel moyenneRGB(Image *, int, int, int, int);
extern void colorCopy_of_rgb_to_tree(Quadtree *, Pixel);
extern void colorCopy_of_tree_to_matrix(Quadtree, Image *, int, int, int, int);
extern int errorQuadtree(Image *, Quadtree *, Pixel *, int, int, int, int);
extern int feuille(Quadtree);
extern void clearQuadtree(Quadtree);
extern void clearImage(Image *);

#endif