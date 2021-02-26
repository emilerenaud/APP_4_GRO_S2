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
#include "AutoValidation.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

int main()
{
    // ************ NOIR ET BLANC ************ //
    // test_pgm_lire(); // OK 100%
    // test_pgm_ecrire(); // OK 100%
    // test_pgm_copier(); // OK 100%
    // test_pgm_couleur_preponderante(); // OK 100%
    // test_pgm_creer_histogramme(); // OK 100%
    // test_pgm_eclaircir_noircir(); // OK 100%
    // test_pgm_creer_negatif();   // OK 100%
    // test_pgm_extraire(); // OK 100%
    // test_pgm_sont_identiques(); // OK 100%
    // test_pgm_pivoter90(); // OK 100%

    // ************ COULEUR ************ //
    // test_ppm_lire(); // OK 100%
    // test_ppm_ecrire(); // OK 100%
    // test_ppm_copier(); // OK 100%
    // test_ppm_sont_identiques(); // OK 100%
    // test_ppm_pivoter90(); // OK 100%

    AutoValidation();
    // int lignes1, colonnes1;
    // int lignes2, colonnes2;
    // int maxval;
    // int histogramme[MAX_VALEUR+1];
    // char nom[MAX_CHAINE];
    // struct MetaData metadonnees;

	// int retour;

    // printf("-> Debut!\n");

	// // exemple d'appel de fonction
    // char filename[] = "meta.pgm";
    // retour = pgm_lire(filename, image1, 
    //                   &lignes1, &colonnes1, 
    //                   &maxval, &metadonnees);
                      

	// // exemple detraitement d'un code de retour (erreur ou reussite)
    // printf("%s\n",metadonnees.auteur);
    // printf("%s\n",metadonnees.dateCreation);
    // printf("%s\n",metadonnees.lieuCreation);
    // printf("%d %d\n",lignes1, colonnes1);
    // printf("%d\n",maxval);

	// printf("-> Retour: ");
	// if (retour == OK)
	// 	printf("-> OK");
	// else
	// 	printf("-> ERREUR");
	// printf("\n");

	// // autre exemple d'appel de fonction
    // char filename2[] = "SFUCK_Frontenac_nuit.pgm";
    // pgm_ecrire(filename2, image1, 
    //            lignes1, colonnes1, 
    //            maxval, metadonnees);

    // printf("-> Fin!\n");

    return 0;
}
