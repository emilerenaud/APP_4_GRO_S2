/********
Fichier: gestion_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include <string.h>
#include "bibliotheque_images.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

int main()
{
    int lignes1, colonnes1;
    int lignes2, colonnes2;
    int maxval;
    int histogramme[MAX_VALEUR+1];
    char nom[MAX_CHAINE];
    struct MetaData metadonnees;

	int retour;

    printf("-> Debut!\n");

	// exemple d'appel de fonction
    char filename[] = "Sherbrooke_Frontenac_nuit.pgm";
    retour = pgm_lire(filename, image1, 
                      &lignes1, &colonnes1, 
                      &maxval, &metadonnees);

	// exemple detraitement d'un code de retour (erreur ou reussite)
    printf("%s\n",metadonnees.auteur);
    printf("%s\n",metadonnees.dateCreation);
    printf("%s\n",metadonnees.lieuCreation);
    printf("%d %d\n",lignes1, colonnes1);
    printf("%d\n",maxval);

	printf("-> Retour: ");
	if (retour == OK)
		printf("-> OK");
	else
		printf("-> ERREUR");
	printf("\n");

	// autre exemple d'appel de fonction
    char filename2[] = "SFUCK_Frontenac_nuit.pgm";
    pgm_ecrire(filename2, image1, 
               lignes1, colonnes1, 
               maxval, metadonnees);

    printf("-> Fin!\n");

    return 0;
}
