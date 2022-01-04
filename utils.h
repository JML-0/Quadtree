#ifndef _UTILS_H
#define _UTILS_H
#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/**
 * @brief Quadtree struct
 * __________________________
 * |           |            |
 * |           |            |
 * |     NO    |     NE     |
 * |           |            |
 * |___________|____________|
 * |           |            |
 * |           |            |
 * |     SO    |     SE     |
 * |           |            |
 * |___________|____________|
 * 
 */
typedef struct Quadtree
{	
	Pixel color;

	struct Quadtree *NO, *NE;
	struct Quadtree *SO, *SE;
 } *Quadtree;

/**
 * @brief Struct Coord
 * 
 */
typedef struct Coord
{
	int x, y;
} Coord;

/**
 * @brief Enum Direction
 * 
 */
typedef enum Direction
{
  NO, NE, SO, SE
} Direction;

extern Pixel moyenneRGB(Image * img, Coord c, int h, int w);
extern double somErrorQuadtree(Image * img, Pixel mRGB, Coord c, int h, int w);
extern int feuille(Quadtree noeud);
extern Coord getCoord(Direction d, int x, int y, int w, int h);
extern double dist(Pixel p1, Pixel p2);
extern void ccRgb2tree(Quadtree *noeud, Pixel color);
extern void ccTree2matrix(Quadtree noeud, Image *img, Coord c, int h, int w);
extern void nullNoeud(Quadtree * noeud);
extern void clearQuadtree(Quadtree q);
extern void clearImage(Image * img);

#endif