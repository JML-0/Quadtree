#ifndef _QUADTREE_H
#define _QUADTREE_H

#include "utils.h"
#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

extern void FILEcheck(FILE *);
extern void write(char *, Image *);
extern Image *read(char *);

#endif