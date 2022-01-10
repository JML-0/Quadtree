#include "quadtree.h"

/** matrice ** -> http://c-faq.com/aryptr/dynmuldimary.html
 * 
 * A = {x:0 y:0 h:1024 w:1024}
 * (0,0)
 * x-------------------------
 * |                        |
 * |                        |
 * |                        |
 * |                        |
 * |           A            |
 * |                        |
 * |                        |
 * |                        |
 * |                        |
 * |                        |
 * -------------------------x
 *                          (1024,1024) 
 * B = {x:0   y:0 h:512 w:512}
 * C = {x:512 y:0 h:512 w:512}
 * (0,0)       (512, 0)
 * x-----------x-------------
 * |           |            |
 * |           |            |
 * |     B     |     C      |
 * |           |            |
 * |___________|____________|
 * |                        |
 * |                        |
 * |                        |
 * |                        |
 * |                        |
 * -------------------------x
 *                          (1024, 1024)
 * [...]
 * @brief Découpe l'image en quatre zones avec leur couleur moyenne
 * 
 * @param img Image
 * @param noeud Noeud dans l'arbre
 * @param c Coordonnées dans l'image en fonction du découpage
 * @param h Hauteur de l'image
 * @param w Largeur de l'image
 * @param lvl Niveau de découpe
 */
void decoupage(Image *img, Quadtree **noeud, Coord c, int h, int w, int lvl)
{
	Pixel moyenne;
	double error;

	*noeud = (Quadtree*)malloc(sizeof(struct Quadtree)); assert(*noeud);

	moyenne = moyenneRGB(img, c, h, w);
	error 	= somErrorQuadtree(img, moyenne, c, h, w);

#ifdef DEBUG
	printf("r:%d g:%d b:%d error:%d x:%d y:%d\n", moyenne.r, moyenne.g, moyenne.b, error, x, y);
#endif

	ccRgb2tree(noeud, moyenne, h, w);
	
	if(error > lvl)
	{
		decoupage(img, &(*noeud)->NO, getCoord(NO, c.x, c.y, h, w), (h / 2), (w / 2), lvl);
		decoupage(img, &(*noeud)->NE, getCoord(NE, c.x, c.y, h, w), (h / 2), (w / 2), lvl);
		decoupage(img, &(*noeud)->SO, getCoord(SO, c.x, c.y, h, w), (h / 2), (w / 2), lvl);
		decoupage(img, &(*noeud)->SE, getCoord(SE, c.x, c.y, h, w), (h / 2), (w / 2), lvl);
	}
	else 
	{
		nullNoeud(noeud);
		return;
	}
}

/**
 * @brief Parcours l'arbre tant que, noeud != feuille,
 * Sinon, rempli la matrice 
 * 
 * @param noeud Noeud dans l'abre
 * @param img Image
 * @param c Coordonnées dans l'image en fonction du remplissage
 * @param h Hauteur de l'image
 * @param w Largeur de l'image
 */
void remplissage(Quadtree *noeud, Image *img, Coord c, int h, int w)
{
	if(!feuille(noeud))
	{
		remplissage(noeud->NO, img, getCoord(NO, c.x, c.y, h, w), (h / 2), (w / 2));
		remplissage(noeud->NE, img, getCoord(NE, c.x, c.y, h, w), (h / 2), (w / 2));
		remplissage(noeud->SO, img, getCoord(SO, c.x, c.y, h, w), (h / 2), (w / 2));
		remplissage(noeud->SE, img, getCoord(SE, c.x, c.y, h, w), (h / 2), (w / 2));
	}
	else ccTree2matrix(noeud, img, c, h, w);
}