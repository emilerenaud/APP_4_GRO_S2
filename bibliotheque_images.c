/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include "bibliotheque_images.h"

int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
             int *p_lignes, int *p_colonnes, 
             int *p_maxval, struct MetaData *p_metadonnees)
{
    FILE *pictureFile;
    char c_buffer = 0;
    int information = 0;
    int compteur_c = 0;

    pictureFile = fopen(nom_fichier,"r"); // r for reading.
    if(pictureFile == NULL) // return Null pointer if an error occur.
    {
        fclose(pictureFile);
        return ERREUR_FICHIER;
    }
    
    c_buffer = fgetc(pictureFile);
    if(c_buffer == '#')
    {
        for(int i = 0; i < MAX_CHAINE; i++)
        {            
            c_buffer = fgetc(pictureFile);
            // printf("%c",c_buffer);
            if(c_buffer == ';' || c_buffer == '\n') // final condition
            {
                switch(information)
                {
                    case 0:
                    {
                        p_metadonnees->auteur[compteur_c + 1] = '\0';
                        break;
                    }
                    case 1:
                    {
                        p_metadonnees->dateCreation[compteur_c + 1] = '\0';
                        break;
                    }
                    case 2:
                    {
                        p_metadonnees->lieuCreation[compteur_c + 1] = '\0';
                        break;
                    }
                }
                compteur_c = 0;
                information ++; // incrementer information quand l'autre est fini
            }
            else
            {
                switch(information)
                {
                    case 0:
                    {
                        p_metadonnees->auteur[compteur_c] = c_buffer;
                        break;
                    }
                    case 1:
                    {
                        p_metadonnees->dateCreation[compteur_c] = c_buffer;
                        break;
                    }
                    case 2:
                    {
                        p_metadonnees->lieuCreation[compteur_c] = c_buffer;
                        break;
                    }
                    case 3: // after the last info.
                    {
                        i = MAX_CHAINE; // stop For.
                        break;
                    }
                }
                compteur_c ++;
            } // end else c_buffer ; or \n
        } // end search for info.
    } // end if # was found for first character.
    else
    {
        rewind(pictureFile); // no header reset compteur
    }
    // Check type
    if(fgetc(pictureFile) == 'P')
    {
        if(fgetc(pictureFile) != '2')
        {
            printf("fail type picture\n");
            fclose(pictureFile);
            return ERREUR_FORMAT;
        }
    }
    // Check size
    fscanf(pictureFile,"%d %d", p_colonnes, p_lignes);
    if(*p_colonnes > MAX_LARGEUR || *p_lignes > MAX_HAUTEUR)
    {
        fclose(pictureFile);
        return ERREUR_TAILLE;
    }
    
    // Read max value
    fscanf(pictureFile, "%d", p_maxval);
    // Read matrix
    for(int i = 0; i < *p_lignes; i++)
    {
        for(int j = 0; j < *p_colonnes; j++)
        {
            fscanf(pictureFile, "%d", &matrice[i][j]);
        }
    }
    fclose(pictureFile);
    // printf("%s\n",p_metadonnees->auteur);
    // printf("%s\n",p_metadonnees->dateCreation);
    // printf("%s\n",p_metadonnees->lieuCreation);
    return OK;
}


int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
               int lignes, int colonnes, 
               int maxval, struct MetaData metadonnees)
{

    FILE *pictureFile;
    // verifier que le nom du fichier a un .txt dedans! peut-etre
    pictureFile = fopen(nom_fichier,"w");
    if(pictureFile == NULL)
        return -1;

    fprintf(pictureFile,"#%s;%s;%s\n",metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);
    fprintf(pictureFile,"P2\n");
    fprintf(pictureFile,"%d %d\n",colonnes,lignes);
    fprintf(pictureFile,"%d\n",maxval);
    int compteur_col = 0;
    int compteur_char = 0;
    for(int i = 0; i < lignes; i++)
    {
        for(int j = 0; j < colonnes; j++)
        {
            int longueurChar = 0;
            if(matrice[i][j] >= 100)
                longueurChar = 4;
            else if(matrice[i][j] >= 10)
                longueurChar = 3;
            else
                longueurChar = 2;
        
            if(compteur_char + longueurChar >= 80)
            {
                fprintf(pictureFile,"\n");
                compteur_char = 0;
            }
            compteur_char += longueurChar;

            fprintf(pictureFile,"%d ",matrice[i][j]);
            // compteur_col ++;
            // if(compteur_col >= 20)
            // {
            //     fprintf(pictureFile,"\n");
            //     compteur_col = 0;
            // }
        }
    }
    fclose(pictureFile);
    return OK;
}
