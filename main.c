#include "quadtree.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		printf("Usage: ./quadtree <niveau> <entree>.ppm <sortie>.ppm\n");
		return 0;
	}

	int level;
	Image *img;
	Quadtree noeud = NULL;
	Coord c;
	c.x = c.y = 0;
	
	level = atoi(argv[1]);

	clock_t t1 = clock();

	printf("lecture...");
	fflush(stdout);         //clear buffer
	img = read(argv[2]);
	printf("ok\n");

	printf("decoupage...");
	fflush(stdout);
	decoupage(img, &noeud, c, img->h, img->w, level);
	printf("ok\n");

	printf("remplissage...");
	fflush(stdout);
	remplissage(noeud, img, c, img->h, img->w);
	printf("ok\n");

	printf("ecriture...");
	fflush(stdout);
	write(argv[3], img);
	printf("ok\n");

	printf("clear...");
	fflush(stdout);
	clearQuadtree(noeud);
	clearImage(img);
	printf("ok\n");

	clock_t t2 = clock();
	unsigned long t = ((t2 - t1) * 1000) / CLOCKS_PER_SEC;
	printf("Temps : %ld ms\n", t);
}