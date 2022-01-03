#include "ppm.h"

void FILEcheck(FILE *f)
{
	if (f == NULL) 
	{
    	perror("FILE Error: ");
    	exit(1);
	}
}

void write(char *path, Image *img)
{
    FILE *f;
    f = fopen(path, "wb");
    FILEcheck(f);

    /* PPM Header */
    fprintf(f, "P6\n");							/*MagicNum*/
    fprintf(f, "%d %d\n", img->w, img->h);		/*Size*/
    fprintf(f, "%d\n", 255);					/*Color*/

    fwrite(img->data, 3 * img->w, img->h, f);	/*Data (pixels)*/

    fclose(f);
}

Image *read(char *path)
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
	
	img->data = (Pixel *)malloc(img->w * img->h * sizeof(Pixel));
	assert(img->data);

	//lecture d'une ligne sur la largeur * la hauteur pour toute l'image
    if (fread(img->data, img->w * 3, img->h, f) != img->h) {
         printf("Erreur chargement des données de l'image (pixels)\n");
         exit(1);
    }

	fclose(f);

	return img;
}