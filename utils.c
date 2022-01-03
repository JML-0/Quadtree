#include "utils.h"

Pixel moyenneRGB(Image *img, int x, int y, int h, int w)
{
	Pixel c;
 	int r = 0, g = 0, b = 0;

	/* Parcours de la matrix */
	Pixel (*pixels)[img->w] = (Pixel(*)[img->w]) img->data;

	for(int i = y; i < y + h; i++)
		for(int j = x; j < x + w; j++)
		{
			r += pixels[i][j].r;
			g += pixels[i][j].g;
			b += pixels[i][j].b;
		}

	c.r = r / (h * w);
	c.g = g / (h * w);
	c.b = b / (h * w);

	return c;
}

void colorCopy_of_rgb_to_tree(Quadtree *noeud, Pixel color)
{
	(*noeud)->color.r = color.r;
	(*noeud)->color.g = color.g;
	(*noeud)->color.b = color.b;
}

void colorCopy_of_tree_to_matrix(Quadtree noeud, Image *img, int x, int y, int h, int w)
{
	Pixel (*pixels)[img->w] = (Pixel(*)[img->w]) img->data;
	
	for(int i = y; i < y + h; i++)
		for(int j = x; j < x + w; j++)
		{
			pixels[i][j].r = noeud->color.r;
			pixels[i][j].g = noeud->color.g;
			pixels[i][j].b = noeud->color.b;
		}
}

int errorQuadtree(Image *img, Quadtree *noeud, Pixel *c, int x, int y, int h, int w)
{
	unsigned int m = 0;
	*c = moyenneRGB(img, x, y, h, w);

	/* Parcours de la matrix */
	Pixel (*pixels)[img->w] = (Pixel(*)[img->w]) img->data;

	for(int i = y; i < y + h; i++)
		for(int j = x; j < x + w; j++)
		{
			m += sqrt(pow(c->r - pixels[i][j].r, 2) + 
					  pow(c->g - pixels[i][j].g, 2) + 
					  pow(c->b - pixels[i][j].b, 2));
			//m += (pow((c->r - pixels[i][j].r), 2)) + 
		 	//	 (pow((c->g - pixels[i][j].g), 2)) + 
		 	//	 (pow((c->b - pixels[i][j].b), 2));
		}

	return m /= (3 * h * w);
	//return m /= (3 * size * size);
}

int feuille(Quadtree noeud)
{
	return (noeud->NO == NULL && noeud->NE == NULL && noeud->SO == NULL && noeud->SE == NULL);
}

void clearQuadtree(Quadtree q)
{
	if (!q) return;
	clearQuadtree(q->NO);
	clearQuadtree(q->NE);
	clearQuadtree(q->SO);
	clearQuadtree(q->SE);

	free(q);
}

void clearImage(Image *img)
{
	if (!img) return;
	if (!img->data) return;
	free(img->data); free(img);
}