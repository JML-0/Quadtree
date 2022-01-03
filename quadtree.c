#include "quadtree.h"

/*
 * matrix ** -> http://c-faq.com/aryptr/dynmuldimary.html
 */

/*
 *	Compression function
 */
void compression(Image *img, Quadtree *noeud, int x, int y, int h, int w, int profondeur)
{
	Pixel moyenne;
	int error;

	*noeud = malloc(sizeof(struct Quadtree)); assert(*noeud);
	error = errorQuadtree(img, noeud, &moyenne, x, y, h, w);

#ifdef DEBUG
	printf("r:%d g:%d b:%d error:%d x:%d y:%d\n", moyenne.r, moyenne.g, moyenne.b, error, x, y);
#endif

	colorCopy_of_rgb_to_tree(noeud, moyenne);
	
	if(error > profondeur)
	{
		compression(img, &(*noeud)->NO, x,           y,           (h / 2), (w / 2), profondeur);
		compression(img, &(*noeud)->NE, x + (w / 2), y,           (h / 2), (w / 2), profondeur);
		compression(img, &(*noeud)->SO, x,	 		 y + (h / 2), (h / 2), (w / 2), profondeur);
		compression(img, &(*noeud)->SE, x + (w / 2), y + (h / 2), (h / 2), (w / 2), profondeur);
	}
	else
	{
		(*noeud)->NO = NULL;
		(*noeud)->NE = NULL;
		(*noeud)->SO = NULL;
		(*noeud)->SE = NULL;
	}
}
/*
 *	Traverses tree and computes based on leafes
 *	the rgb matrix
 */
void tree2matrix(Quadtree noeud, Image *img, int x, int y, int h, int w)
{
	if(feuille(noeud))
	{
		colorCopy_of_tree_to_matrix(noeud, img, x, y, h, w);
	}
	else
	{
		tree2matrix(noeud->NO, img, x,           y,           (h / 2), (w / 2));
		tree2matrix(noeud->NE, img, x + (w / 2), y,           (h / 2), (w / 2));
		tree2matrix(noeud->SO, img, x,		     y + (h / 2), (h / 2), (w / 2));
		tree2matrix(noeud->SE, img, x + (w / 2), y + (h / 2), (h / 2), (w / 2));
	}
}

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		printf("Usage: ./quadtree <profondeur> <input image>.ppm <output image>.ppm\n");
		return 0;
	}

	int profondeur;
	Image *img;
	Quadtree noeud = NULL;
	
	profondeur = atoi(argv[1]);

	printf("read...");
	fflush(stdout); //clear buffer
	img = read(argv[2]);
	printf("ok\n");

	printf("compress...");
	fflush(stdout);
	compression(img, &noeud, 0, 0, img->h, img->w, profondeur);
	printf("ok\n");

	printf("decompress...");
	fflush(stdout);
	tree2matrix(noeud, img, 0, 0, img->h, img->w);
	printf("ok\n");

	printf("write...");
	fflush(stdout);
	write(argv[3], img);
	printf("ok\n");

	printf("clear...");
	fflush(stdout);
	clearQuadtree(noeud);
	clearImage(img);
	printf("ok\n");
}