#include "utils.h"

/**
 * @brief Calcul une couleur moyenne pour chaque zone
 * 
 * @param img Image
 * @param c Coordonées dans l'image
 * @param h Hauteur de l'image
 * @param w Largeur de l'image
 * @return Pixel 
 */
Pixel moyenneRGB(Image * img, Coord c, int h, int w)
{
	Pixel p;
 	unsigned long long r = 0, g = 0, b = 0;

	/* Parcours de la matrice */
	for(int i = c.y; i < c.y + h; i++)
		for(int j = c.x; j < c.x + w; j++)
		{
			r += img->data[i][j].r;
			g += img->data[i][j].g;
			b += img->data[i][j].b;
		}

	p.r = r / (h * w);
	p.g = g / (h * w);
	p.b = b / (h * w);

	return p;
}

/**
 * @brief Calcul la somme des erreurs sur chaque zone
 * 
 * @param img Image
 * @param mRGB Moyenne RGB
 * @param c Coordonnées dans l'image
 * @param h Hauteur de l'image
 * @param w Largeur de l'image
 * @return double 
 */
double somErrorQuadtree(Image * img, Pixel mRGB, Coord c, int h, int w)
{
	double d = 0;

	/* Parcours de la matrice */
	for(int i = c.y; i < c.y + h; i++)
		for(int j = c.x; j < c.x + w; j++)
			d += dist(mRGB, img->data[i][j]);

	return d;
}

/**
 * @brief Distance euclidienne pour deux pixels p1 et p2
 * 
 * @param p1 r1,g1,b1
 * @param p2 r2,g2,b2
 * @return double 
 */
double dist(Pixel p1, Pixel p2)
{
	return sqrt(pow(p1.r - p2.r, 2) + pow(p1.g - p2.g, 2) + pow(p1.b - p2.b, 2));
}

/**
 * @brief Indique si le noeud est une feuille (vide, pas de branche/fils)
 * 
 * @param noeud 
 * @return int 
 */
int feuille(Quadtree noeud)
{
	return (noeud->NO == NULL && noeud->NE == NULL && noeud->SO == NULL && noeud->SE == NULL);
}

/**
 * @brief Copie la couleur moyenne dans l'arbre
 * 
 * @param noeud 
 * @param color 
 */
void ccRgb2tree(Quadtree *noeud, Pixel color)
{
	(*noeud)->color.r = color.r;
	(*noeud)->color.g = color.g;
	(*noeud)->color.b = color.b;
}

/**
 * @brief Copie dans la matrice les couleurs dans l'arbre
 * 
 * @param noeud 
 * @param img 
 * @param c 
 * @param h 
 * @param w 
 */
void ccTree2matrix(Quadtree noeud, Image *img, Coord c, int h, int w)
{
	for(int i = c.y; i < c.y + h; i++)
		for(int j = c.x; j < c.x + w; j++)
		{
			img->data[i][j].r = noeud->color.r;
			img->data[i][j].g = noeud->color.g;
			img->data[i][j].b = noeud->color.b;
		}
}

/**
 * @brief Met les noeuds à NULL lorsque "l'erreur" est inférieur au niveau
 * 
 * @param noeud 
 */
void nullNoeud(Quadtree * noeud)
{
	(*noeud)->NO = NULL;
	(*noeud)->NE = NULL;
	(*noeud)->SO = NULL;
	(*noeud)->SE = NULL;
}

/**
 * @brief Libère la mémoire de l'image
 * 
 * @param img 
 */
void clearImage(Image * img)
{
	if (!img) 		return;
	if (!img->data) return;

	for(int i = 0; i < img->w; i++)
		free(img->data[i]);
	free(img->data);
	free(img);
}

/**
 * @brief Libère la mémoire de l'arbre
 * 
 * @param q 
 */
void clearQuadtree(Quadtree q)
{
	if (!q) return;
	clearQuadtree(q->NO);
	clearQuadtree(q->NE);
	clearQuadtree(q->SO);
	clearQuadtree(q->SE);

	free(q);
}

/**
 * @brief Retourne les coordonnées x,y dans l'image en fonction de la découpe
 * 
 * @param d Direction/zone (NO,NE,SO,SE)
 * @param x x actuel
 * @param y y actuel
 * @param w Largeur de l'image
 * @param h Hauteur de l'image
 * @return Coord 
 */
Coord getCoord(Direction d, int x, int y, int w, int h)
{	
	Coord c;
	switch (d)
    {
    case NO:
		c.x = x;
		c.y = y;
        return c;
    case NE:
        c.x = x + (w / 2);
		c.y = y;
        return c;
    case SO:
        c.x = x;
		c.y = y + (h / 2);
        return c;
    case SE:
        c.x = x + (w / 2);
		c.y = y + (h / 2);
        return c;
	default:
		c.x = c.y = 0;
		return c;
    }
}
