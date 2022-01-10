#ifndef _QUADTREE_H
#define _QUADTREE_H
#include "utils.h"
#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

extern void decoupage(Image *img, Quadtree **noeud, Coord c, int h, int w, int lvl);
extern void remplissage(Quadtree *noeud, Image *img, Coord c, int h, int w);

#endif