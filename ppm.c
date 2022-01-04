#include "ppm.h"

/**
 * @brief Vérifie les erreurs FILE
 * 
 * @param f 
 */
void FILEcheck(FILE * f)
{
	if (f == NULL) 
	{
    	perror("FILE Error: ");
    	exit(1);
	}
}

/**
 * @brief Écrit une image ppm
 * Vu en cours de programmation Graphique
 * 
 * @param path Chemin de sauvegarde
 * @param img Image
 */
void write(char * path, Image * img)
{
    FILE *f;
    f = fopen(path, "wb");
    FILEcheck(f);

    /* PPM Header */
    fprintf(f, "P6\n");							/*MagicNum*/
    fprintf(f, "%d %d\n", img->w, img->h);		/*Size*/
    fprintf(f, "%d\n", 255);					/*Color*/

    //fwrite(img->data, 3 * img->w, img->h, f);	/*Data (pixels)*/

	for(int i = 0; i < img->h; i++)
		for(int j = 0; j < img->w; j++)
		{
			fwrite(&img->data[i][j].r, sizeof(unsigned char), 1, f);
			fwrite(&img->data[i][j].g, sizeof(unsigned char), 1, f);
			fwrite(&img->data[i][j].b, sizeof(unsigned char), 1, f);
		}

    fclose(f);
}

/**
 * @brief Lit une image ppm
 * Vu en cours de programmation Graphique
 * 
 * @param path Chemin de l'image
 * @return Image* 
 */
Image *read(char * path)
{
	FILE * f;
	Image *img;
	char magicNum[3]; /* P6\0 */
	int color;

	f = fopen(path, "rb");
	FILEcheck(f);

	img = (Image *)malloc(sizeof(Image)); assert(img);

	/* PPM Header */
	fscanf(f, "%s"   , magicNum);	/*MagicNum*/
	fscanf(f, "%d "  , &img->w);	/*Largeur*/
	fscanf(f, "%d\n" , &img->h);	/*Hauteur*/
	fscanf(f, "%d"   , &color);		/*Color*/

	while (fgetc(f) != '\n'); //données inutiles
	
	img->data = (Pixel **)malloc(img->w * img->h * sizeof(Pixel));
	assert(img->data);

	for(int i = 0; i < img->h; i++)
	{
		img->data[i] = malloc(img->w * sizeof(Pixel));
		assert(img->data[i]);
	}
	
	for(int i = 0; i < img->h; i++)
		for(int j = 0; j < img->w; j++)
		{
			fread(&img->data[i][j].r, sizeof(unsigned char), 1, f);
			fread(&img->data[i][j].g, sizeof(unsigned char), 1, f);
			fread(&img->data[i][j].b, sizeof(unsigned char), 1, f);
		}

	//lecture d'une ligne sur la largeur * la hauteur pour toute l'image
    /* if (fread(img->data, img->w * 3, img->h, f) != img->h) {
         printf("Erreur chargement des données de l'image (pixels)\n");
         exit(1);
    } */

	fclose(f);

	return img;
}