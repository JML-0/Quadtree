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
	long double d = 0;

	/* Parcours de la matrice */
	for(int i = c.y; i < c.y + h; i++)
		for(int j = c.x; j < c.x + w; j++)
			d += dist(mRGB, img->data[i][j]);

	return d /= (3 * h * w);
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
int feuille(Quadtree * noeud)
{
	return (noeud->NO == NULL && noeud->NE == NULL && noeud->SO == NULL && noeud->SE == NULL);
}

/**
 * @brief Indique si une case est une feuille (-1)
 * 
 * @param qv 
 * @return int 
 */
int feuilleVec(QuadtreeVector qv)
{
	return (qv.NOid == -1 && qv.NEid == -1 && qv.SOid == -1 && qv.SEid == -1);
}

/**
 * @brief Copie la couleur moyenne dans l'arbre
 * 
 * @param noeud 
 * @param color 
 */
void ccRgb2tree(Quadtree **noeud, Pixel color, int h, int w)
{
	(*noeud)->color.r = color.r;
	(*noeud)->color.g = color.g;
	(*noeud)->color.b = color.b;
	(*noeud)->h = h;
	(*noeud)->w = w;
}

/**
 * @brief Copie les données du vecteur dans l'arbre
 * 
 * @param qv 
 * @param noeud 
 * @param id 
 */
void ccVector2tree(QuadtreeVector *qv, Quadtree **noeud, int id)
{
	(*noeud)->id   	  = id;
	(*noeud)->color.r = qv[id].color.r;
	(*noeud)->color.g = qv[id].color.g;
	(*noeud)->color.b = qv[id].color.b;
	(*noeud)->h   	  = qv[id].h;
	(*noeud)->w   	  = qv[id].w;
}

/**
 * @brief Copie les données de l'arbre dans le vecteur
 * 
 * @param qv 
 * @param noeud 
 */
void ccTree2Vector(QuadtreeVector *qv, Quadtree **AdressesNoeuds)
{
	qv->color.r = (*AdressesNoeuds)->color.r;
	qv->color.g = (*AdressesNoeuds)->color.g;
	qv->color.b = (*AdressesNoeuds)->color.b;
	qv->h 		= (*AdressesNoeuds)->h;
	qv->w 		= (*AdressesNoeuds)->w;
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
void ccTree2matrix(Quadtree * noeud, Image *img, Coord c, int h, int w)
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
 * @brief Copie les adresses des noeuds dans un vecteur
 * 1) on copie les adresses des noeuds dans le vecteur @AdressesNoeuds en fonction de l'id
 * 2) on "relit" l'id du vecteur où on vient de copier l'adresse du noeud
 * Chaques noeuds est maintenant reliés à un id
 * 
 * @param noeud 
 * @param AdressesNoeuds 
 * @param id 
 */
void copyAdressesNoeuds(Quadtree * noeud, Quadtree *** AdressesNoeuds, unsigned int * id)
{
	if(noeud)
	{
		addNoeuds(AdressesNoeuds, *id);
		//  	** 			*
		(*AdressesNoeuds)[(*id)] = noeud;
		noeud->id = (*id)++;

        copyAdressesNoeuds(noeud->NO, AdressesNoeuds, id);
        copyAdressesNoeuds(noeud->NE, AdressesNoeuds, id);
        copyAdressesNoeuds(noeud->SO, AdressesNoeuds, id);
        copyAdressesNoeuds(noeud->SE, AdressesNoeuds, id);
	} 
	else return;
}

/**
 * @brief Copie les id de l'arbre dans le vecteur
 * 
 * @param qv 
 * @param noeud 
 */
void createNoeudsVector(QuadtreeVector *qv, Quadtree **AdressesNoeuds)
{
	if((*AdressesNoeuds)->NO) /*->*/ (*qv).NOid = (*AdressesNoeuds)->NO->id;
	else 			 		  /*->*/ (*qv).NOid = -1;

	if((*AdressesNoeuds)->NE) /*->*/ (*qv).NEid = (*AdressesNoeuds)->NE->id;
	else 			 		  /*->*/ (*qv).NEid = -1;

	if((*AdressesNoeuds)->SO) /*->*/ (*qv).SOid = (*AdressesNoeuds)->SO->id;
	else 			 		  /*->*/ (*qv).SOid = -1;

	if((*AdressesNoeuds)->SE) /*->*/ (*qv).SEid = (*AdressesNoeuds)->SE->id;
	else 			 		  /*->*/ (*qv).SEid = -1;

	ccTree2Vector(qv, AdressesNoeuds);
}

/**
 * @brief Crée un vecteur
 * 
 * @param qv 
 * @param noeud 
 * @param nbNoeuds 
 */
void createVector(QuadtreeVector **qv, Quadtree **AdressesNoeuds, unsigned int nbNoeuds)
{
	if(!(*qv)) (*qv) = malloc(sizeof(QuadtreeVector) * nbNoeuds); assert((*qv));
	for(unsigned int i = 0; i < nbNoeuds; i++)
		createNoeudsVector(&(*qv)[i], &AdressesNoeuds[i]);
}

/**
 * @brief Lit un fichier arbre
 * https://koor.fr/C/cstdio/fopen.wp
 * @param v 
 * @param path 
 */
void readFileQuadtree(QuadtreeVector **v, char * path)
{
	FILE * f;
	unsigned int nbNoeuds;
	f = fopen(path, "rb"); //read binary
	FILEcheck(f);

	fread(&nbNoeuds, sizeof(unsigned int), 1, f); //on récupère le nombre de noeuds

	*v = malloc(sizeof(QuadtreeVector) * nbNoeuds); assert(*v);
	fread(*v, sizeof(QuadtreeVector), nbNoeuds, f); //taille bloc * nbNoeuds

	fclose(f);
}

/**
 * @brief Réalloue/alloue de la mémoire en fonction du nombre de noeuds
 * 
 * @param AdressesNoeuds 
 * @param nbNoeuds 
 */
void addNoeuds(Quadtree *** AdressesNoeuds, unsigned int nbNoeuds)
{
	if(!(*AdressesNoeuds)) /*->*/ (*AdressesNoeuds) = malloc(sizeof(Quadtree*)); assert((*AdressesNoeuds));
	// On incrémente la taille en fonction du nombre de noeuds
	if(nbNoeuds) (*AdressesNoeuds) = realloc((*AdressesNoeuds), sizeof(Quadtree*) * (++nbNoeuds));
}

/**
 * @brief Crée un fichier .arbre contenant l'arbre
 * 
 * @param qv 
 * @param path 
 * @param nbNoeuds 
 */
void writeQuadtree(QuadtreeVector ** qv, char * path, unsigned int nbNoeuds)
{
	FILE * f;
	f = fopen(path, "wb"); //write binary
	FILEcheck(f);

	fwrite(&nbNoeuds, sizeof(unsigned int), 1, f);

	for(unsigned int i = 0; i < nbNoeuds; i++)
		fwrite(&(*qv)[i], sizeof(QuadtreeVector), 1, f);

	fclose(f);
}

/**
 * @brief Crée un arbre à partir du vecteur
 * 
 * @param qv 
 * @param noeud 
 * @param i 
 */
void createQuadtree(QuadtreeVector * qv, Quadtree ** noeud, int id)
{
	*noeud = malloc(sizeof(Quadtree)); assert(noeud);
	ccVector2tree(qv, noeud, id);

	if(!feuilleVec(qv[id])) //on parcours tant que ce n'est pas une feuille
	{
		createQuadtree(qv, &(*noeud)->NO, qv[id].NOid);
		createQuadtree(qv, &(*noeud)->NE, qv[id].NEid);
		createQuadtree(qv, &(*noeud)->SO, qv[id].SOid);
		createQuadtree(qv, &(*noeud)->SE, qv[id].SEid);

	}
	else nullNoeud(noeud); //feuille
}

/**
 * @brief Retourne la taille d'un fichier en Oct
 * https://stackoverflow.com/a/238607
 * @param path 
 * @return unsigned long long 
 */
unsigned long long getSizeFile(char * path)
{
	FILE* f = fopen(path, "r");
	FILEcheck(f);
  
    fseek(f, 0L, SEEK_END);
    unsigned long long r = ftell(f);
    fclose(f);
	
	return r;
}

/**
 * @brief Affiche la taille d'un fichier
 * Récupérer d'un autre projet
 * 
 * @param size 
 */
void showSizeFile(unsigned long long size)
{
	int Ko = 1024;
	int Mo = Ko * 1024;
	int Go = Mo * 1024;

	if (size >= Go)
		if (size % Go == 0)
			printf("%d Go\n", (int)size / Go);
		else
			printf("%.1f Go\n", (float)size / Go);
	else if (size >= Mo)
		if (size % Mo == 0)
			printf("%d Mo\n", (int)size / Mo);
		else
			printf("%.1f Mo\n", (float)size / Mo);
	else
		if (size % Ko == 0)
			printf("%d Ko\n", (int)size / Ko);
		else
			printf("%.1f Ko\n", (float)size / Ko);
}

/**
 * @brief Met les noeuds à NULL lorsque "l'erreur" est inférieur au niveau
 * 
 * @param noeud 
 */
void nullNoeud(Quadtree ** noeud)
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
void clearQuadtree(Quadtree * q)
{
	if (!q) return;
	clearQuadtree(q->NO);
	clearQuadtree(q->NE);
	clearQuadtree(q->SO);
	clearQuadtree(q->SE);

	free(q);
}

/**
 * @brief Libère la mémoire du vecteur
 * 
 * @param q 
 * @param nbNoeuds 
 */
void clearQuadtreeVector(Quadtree *** q, unsigned int nbNoeuds)
{
	if (!*q) return;
	for(unsigned int i = 0; i < nbNoeuds; i++)
		free((*q)[i]);
	free(*q);
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