#include "quadtree.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		printf("Usage compression: ./quadtree -c <niveau> <entree>.ppm <sortie>.arbre\n");
		printf("Usage decompression: ./quadtree -d <entree>.arbre <sortie>.ppm\n");
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0 && argc == 5) // A ? B -> <0:!A | 0:== | >0:!B
	{
		unsigned int id = 0;
		int level;
	
		Quadtree * noeud 			= NULL;
		Quadtree ** adressesNoeuds	= NULL;
		QuadtreeVector * vecteur	= NULL;
		Image *img					= NULL;
		Coord c; c.x = c.y = 0;

		level = atoi(argv[2]);

		clock_t t1 = clock();

		printf("lecture...");
		fflush(stdout);         //clear buffer
		img = read(argv[3]);
		printf("ok\n");

		printf("decoupage...");
		fflush(stdout);
		decoupage(img, &noeud, c, img->h, img->w, level);
		printf("ok\n");

		printf("ecriture...");
		fflush(stdout);
		copyAdressesNoeuds(noeud, &adressesNoeuds, &id);
		createVector(&vecteur, adressesNoeuds, id);
		writeQuadtree(&vecteur, argv[4], id);
		printf("ok\n");
		
		clock_t t2 = clock();
		
		printf("clear...");
		fflush(stdout);
		free(vecteur);
		clearImage(img);
		clearQuadtree(noeud);
		printf("ok\n");

		unsigned long long f1 = getSizeFile(argv[3]);
		unsigned long long f2 = getSizeFile(argv[4]);

		printf("Taille de l'image : "); fflush(stdout);
		showSizeFile(f1);
		printf("Taille de l'image compressee : "); fflush(stdout);
		showSizeFile(f2);

		printf("Ratio de compression : %.1f\n", (float)(f1/f2));
		printf("Taux de compression : %.1f%%\n", (1 - (float)f2/f1) * 100);

		unsigned long t = ((t2 - t1) * 1000) / CLOCKS_PER_SEC;
		printf("Temps de compression : %ld ms\n", t);

	}
	else if (strcmp(argv[1], "-d") == 0 && argc == 4)
	{
		QuadtreeVector * vecteur = NULL;
		Quadtree *noeud 		 = NULL;
		Image *img 				 = NULL;
		Coord c; c.x = c.y = 0;

		printf("lecture...");
		fflush(stdout);
		readFileCompressed(&vecteur, argv[2]);
		printf("ok\n");
		
		printf("creation arbre...");
		fflush(stdout);
		createQuadtree(vecteur, &noeud, 0);
		printf("ok\n");

		printf("remplissage...");
		fflush(stdout);
		img = createImage(noeud->h, noeud->w);
		remplissage(noeud, img, c, img->h, img->w);
		printf("ok\n");

		printf("ecriture image...");
		fflush(stdout);
		write(argv[3], img);
		printf("ok\n");

		printf("clear...");
		fflush(stdout);
		free(vecteur);
		clearImage(img);
		clearQuadtree(noeud);
		printf("ok\n");
	}
	return 0;
}