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
 * id = -1 -> feuille
 * Chaques noeuds a un id unique,
 * cela permet de l'identifier
 * afin de pouvoir construire, et lire
 * un arbre dans un fichier
 * 
 * La taille de l'image est stockée
 * afin de pouvoir décompresser
 * car si le logiciel est relancé
 * la taille n'est plus stockée dans
 * ce dernier
 */
typedef struct Quadtree
{	
	Pixel color;
	int id;
	int h, w;

	struct Quadtree *NO, *NE;
	struct Quadtree *SO, *SE;
 } Quadtree;

/**
 * @brief Struct QuadtreeVector
 * La taille de l'image compressée
 * dépend de celle de la structure
 * 
 */
typedef struct QuadtreeVector
{
	Pixel color;
	int h, w;
	
	int NOid, NEid;	// Id des noeuds de l'arbre
	int SOid, SEid;	//
} QuadtreeVector;

/**
 * @brief Struct Coord
 * 
 */
typedef struct Coord
{
	unsigned int x, y;
} Coord;

/**
 * @brief Enum Direction
 * 
 */
typedef enum Direction
{
  NO, NE, SO, SE
} Direction;

int feuilleVec(QuadtreeVector qv);
double dist(Pixel p1, Pixel p2);
void ccVector2tree(QuadtreeVector *qv, Quadtree **noeud, int id);
unsigned long long getSizeFile(char * path);
void showSizeFile(unsigned long long size);
void createNoeudsVector(QuadtreeVector *qv, Quadtree **AdressesNoeuds);
void createVector(QuadtreeVector **qv, Quadtree **AdressesNoeuds, unsigned int nbNoeuds);
void readFileQuadtree(QuadtreeVector **v, char *path);
void copyAdressesNoeuds(Quadtree *noeud, Quadtree ***AdressesNoeuds, unsigned int * id);
void writeQuadtree(QuadtreeVector **qv, char *path, unsigned int nbNoeuds);
void createQuadtree(QuadtreeVector *qv, Quadtree **noeud, int id);
void addNoeuds(Quadtree *** AdressesNoeuds, unsigned int nbNoeuds);
/**/
extern Pixel moyenneRGB(Image * img, Coord c, int h, int w);
extern double somErrorQuadtree(Image * img, Pixel mRGB, Coord c, int h, int w);
extern void ccRgb2tree(Quadtree **noeud, Pixel color, int h, int w);
extern void nullNoeud(Quadtree **noeud);
extern Coord getCoord(Direction d, int x, int y, int w, int h);
extern void ccTree2matrix(Quadtree *noeud, Image *img, Coord c, int h, int w);
extern int feuille(Quadtree *noeud);
extern void clearQuadtree(Quadtree *q);
extern void clearImage(Image * img);
extern void clearQuadtreeVector(Quadtree ***q, unsigned int nbNoeuds);

#endif