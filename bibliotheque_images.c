/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Modification 2021-02-25 : Émile Renaud
                          Maxence Mougin
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
    int checkformat = 0;

    if(strstr(nom_fichier,".pgm") == NULL)
        return ERREUR_FICHIER;
        

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
            if(c_buffer == ';') // final condition
            {
                switch(information)
                {
                    case 0:
                    {
                        p_metadonnees->auteur[compteur_c] = 0x00;
                        break;
                    }
                    case 1:
                    {
                        p_metadonnees->dateCreation[compteur_c] = 0x00;
                        break;
                    }
                }
                compteur_c = 0;
                information ++; // incrementer information quand l'autre est fini
            }
            else if(c_buffer == '\n')
            {
                if(information != 2)
                    return ERREUR_FORMAT;
                p_metadonnees->lieuCreation[compteur_c] = 0x00;
                information ++;
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
                        checkformat ++; // sert a rien ici
                        break;
                    }
                }
                compteur_c ++;
            } // end else c_buffer ; or \n
        } // end search for info.
        // printf("%s  %s  %s\n",p_metadonnees->auteur,p_metadonnees->dateCreation,p_metadonnees->lieuCreation)
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
        checkformat ++;
    }
    // Check size
    fscanf(pictureFile,"%d %d", p_colonnes, p_lignes);
    if(*p_colonnes > MAX_LARGEUR || *p_lignes > MAX_HAUTEUR)
    {
        fclose(pictureFile);
        return ERREUR_TAILLE;
    }
    checkformat ++;
    
    // Read max value
    fscanf(pictureFile, "%d", p_maxval);
    checkformat ++;

    if(checkformat != 3) // verifier que le format respect le pgm.
    {
        return ERREUR_FORMAT;
    }

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

    int compteur_char = 0;
    for(int i = 0; i < lignes; i++)
    {
        for(int j = 0; j < colonnes; j++)
        {
            int longueurChar = 0;
            if(matrice[i][j] >= 100) // check lenght on char.
                longueurChar = 4;
            else if(matrice[i][j] >= 10)
                longueurChar = 3;
            else
                longueurChar = 2;
        
            if(compteur_char + longueurChar >= 80) // dont exceed 80 char.
            {
                fprintf(pictureFile,"\n");
                compteur_char = 0;
            }
            compteur_char += longueurChar;

            fprintf(pictureFile,"%d ",matrice[i][j]);
        }
    }
    fclose(pictureFile);
    return OK;
}


int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR],
               int lignes1, int colonnes1,
               int matrice2[MAX_HAUTEUR][MAX_LARGEUR],
               int *p_lignes2, int *p_colonnes2)
{
    if(lignes1 == 0 || colonnes1 == 0)
        return -1;
    
    *p_lignes2 = lignes1;
    *p_colonnes2 = colonnes1;

    for(int i = 0; i < lignes1; i++)
    {
        for(int j = 0; j < colonnes1; j++)
        {
            matrice2[i][j] = matrice1[i][j];
        }
    }
    return OK;

}


int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
                          int lignes, int colonnes, int histogramme[MAX_VALEUR+1])
{
    // reset histogramme
    for(int i = 0; i < MAX_VALEUR + 1; i++)
        histogramme[i] = 0;

    // increase histo at each value of the matrix
    for(int i = 0; i < lignes; i++)
    {
        for(int j = 0; j < colonnes; j++)
        {
            histogramme[matrice[i][j]] ++;
        }
    }
    return OK;
}


int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
                              int lignes, int colonnes)
{
    int histogramme[MAX_VALEUR + 1];
    pgm_creer_histogramme(matrice,lignes,colonnes,histogramme);
    int brightnessValue = 0;
    int brightnessPos = 0;

    for(int i = 0; i < MAX_VALEUR; i++) // find highest value
    {
        if(histogramme[i] > brightnessValue)
        {
            brightnessValue = histogramme[i];
            brightnessPos = i;
        }
    }
    return brightnessPos; // return the brightness value.
}

int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
                          int lignes, int colonnes, int maxval, int valeur)
{
	for(int i=0;i<lignes;i++)
	{
		for(int j=0;j<colonnes;j++)
		{
            matrice[i][j] = matrice[i][j] + valeur;
			if (matrice[i][j]>maxval)
			{
				matrice[i][j]=maxval;
			}
			else if (matrice[i][j]<0)
			{
				matrice[i][j]=0;
			}
		}
	}
    return OK;
}


int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
                      int lignes, int colonnes, int maxval)
{
    for(int i=0;i<lignes;i++)
	{
		for(int j=0;j<colonnes;j++)
		{
			matrice[i][j]=maxval-matrice[i][j];

            if(matrice[i][j] < 0)
                matrice[i][j] = 0;

            if(matrice[i][j] > maxval)
                matrice[i][j] = maxval;
		}
	}
    return OK;
}


int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
                 int lignes1, int colonnes1, int lignes2, int colonnes2,
                 int *p_lignes, int *p_colonnes)
{   
    // if(lignes1 < 0 || colonnes1 <0 || lignes2 > *p_lignes || colonnes2 > *p_colonnes)
    //     return ERREUR;
    if(lignes1 >= *p_lignes || lignes2 >= *p_lignes ||
       colonnes1 >= *p_colonnes || colonnes2 >= *p_colonnes)
        return ERREUR;

    *p_lignes=lignes2-lignes1+1;
	*p_colonnes=colonnes2-colonnes1+1;

    int matrice2[MAX_HAUTEUR][MAX_LARGEUR];

	for (int i=lignes1;i<=lignes2;i++)
	{
		for (int j=colonnes1;j<=colonnes2;j++)
		{
			matrice2[i-lignes1][j-colonnes1]=matrice[i][j];
            
		}
	}

    for(int i = 0; i < *p_lignes; i++)
    {
        for(int j = 0; j < *p_colonnes; j++)
        {
            matrice[i][j] = matrice2[i][j];
        }
    }
    return OK;
}


int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], 
                        int lignes1, int colonnes1, 
                        int matrice2[MAX_HAUTEUR][MAX_LARGEUR],
                        int lignes2, int colonnes2)
{
    if(lignes1 != lignes2 || colonnes1 !=  colonnes2)
        return ERREUR;

    for(int i = 0; i < lignes1; i++)
    {
        for(int j = 0; j < colonnes1; j++)
        {
            if(matrice1[i][j] != matrice2[i][j])
                return DIFFERENTES;
        }
    }
    return IDENTIQUES;
}


int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR],
                  int *p_lignes, int *p_colonnes, int sens)
{
    int lignes2 = *p_lignes;
    int colonnes2 = *p_colonnes;

    if(sens != 0 && sens != 1)
        return ERREUR;
    
    
    int MatriceCopie[MAX_HAUTEUR][MAX_LARGEUR];

	for (int a=0;a<*p_lignes;a++)
	{
		for (int b=0;b<*p_colonnes;b++)
		{
			MatriceCopie[a][b]=matrice[a][b];
		}
	}

	for (int i=0;i<*p_lignes;i++)
	{
		for (int j=0;j<*p_colonnes;j++)
		{
			if (sens==1)
			{
				matrice[j][*p_lignes-i-1]=MatriceCopie[i][j];

			}
			else
			{
				matrice[*p_colonnes-j-1][i]=MatriceCopie[i][j];
			}
		}
	}
    *p_lignes = colonnes2;
    *p_colonnes = lignes2;
    return OK;
}


// *************************************** C O U L E U R *************************************** // 

int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
    FILE *pictureFile;
    char c_buffer = 0;
    int information = 0;
    int compteur_c = 0;
    int checkformat = 0;

    if(strstr(nom_fichier,".ppm") == NULL)
        return ERREUR_FICHIER;
        
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
            if(c_buffer == ';') // final condition
            {
                switch(information)
                {
                    case 0:
                    {
                        p_metadonnees->auteur[compteur_c] = 0x00;
                        break;
                    }
                    case 1:
                    {
                        p_metadonnees->dateCreation[compteur_c] = 0x00;
                        break;
                    }
                }
                compteur_c = 0;
                information ++; // incrementer information quand l'autre est fini
            }
            else if(c_buffer == '\n')
            {
                if(information != 2)
                    return ERREUR_FORMAT;
                p_metadonnees->lieuCreation[compteur_c] = 0x00;
                information ++;
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
                        checkformat++;
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
        if(fgetc(pictureFile) != '3')
        {
            printf("fail type picture\n");
            fclose(pictureFile);
            return ERREUR_FORMAT;
        }
        checkformat++;
    }
    // Check size
    fscanf(pictureFile,"%d %d", p_colonnes, p_lignes);
    if(*p_colonnes > MAX_LARGEUR || *p_lignes > MAX_HAUTEUR)
    {
        fclose(pictureFile);
        return ERREUR_TAILLE;
    }
    checkformat ++;
    
    // Read max value
    fscanf(pictureFile, "%d", p_maxval);
    checkformat ++;

    if(checkformat != 3) // verifier que le format respect le pgm.
    {
        return ERREUR_FORMAT;
    }

    // Read matrix
    for(int i = 0; i < *p_lignes; i++)
    {
        for(int j = 0; j < *p_colonnes; j++)
        {
            fscanf(pictureFile, "%d", &matrice[i][j].valeurR);
            fscanf(pictureFile, "%d", &matrice[i][j].valeurG);
            fscanf(pictureFile, "%d", &matrice[i][j].valeurB);
        }
    }
    fclose(pictureFile);
    // printf("%s\n",p_metadonnees->auteur);
    // printf("%s\n",p_metadonnees->dateCreation);
    // printf("%s\n",p_metadonnees->lieuCreation);
    return OK;
}


int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
    FILE *pictureFile;
    // verifier que le nom du fichier a un .txt dedans! peut-etre
    pictureFile = fopen(nom_fichier,"w");
    if(pictureFile == NULL)
        return -1;

    fprintf(pictureFile,"#%s;%s;%s\n",metadonnees.auteur,metadonnees.dateCreation,metadonnees.lieuCreation);
    fprintf(pictureFile,"P3\n");
    fprintf(pictureFile,"%d %d\n",colonnes,lignes);
    fprintf(pictureFile,"%d\n",maxval);

    int compteur_char = 0;
    for(int i = 0; i < lignes; i++)
    {
        for(int j = 0; j < colonnes; j++)
        {
            if(compteur_char > 3)
            {
                fprintf(pictureFile,"\n");
                compteur_char = 0;        
            }
                
            fprintf(pictureFile,"%d ",matrice[i][j].valeurR);
            fprintf(pictureFile,"%d ",matrice[i][j].valeurG);
            fprintf(pictureFile,"%d ",matrice[i][j].valeurB);
            compteur_char ++;
        }
    }
    fclose(pictureFile);
    return OK;
}


int ppm_copier(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
    if(lignes1 == 0 || colonnes1 == 0)
        return -1;
    
    *p_lignes2 = lignes1;
    *p_colonnes2 = colonnes1;

    for(int i = 0; i < lignes1; i++)
    {
        for(int j = 0; j < colonnes1; j++)
        {
            matrice2[i][j].valeurR = matrice1[i][j].valeurR;
            matrice2[i][j].valeurG = matrice1[i][j].valeurG;
            matrice2[i][j].valeurB = matrice1[i][j].valeurB;
        }
    }
    return OK;
}


int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
    if(lignes1 != lignes2 || colonnes1 !=  colonnes2)
        return ERREUR;

    for(int i = 0; i < lignes1; i++)
    {
        for(int j = 0; j < colonnes1; j++)
        {
            if(matrice1[i][j].valeurR != matrice2[i][j].valeurR ||
               matrice1[i][j].valeurB != matrice2[i][j].valeurB ||
               matrice1[i][j].valeurG != matrice2[i][j].valeurG)
                return DIFFERENTES;
        }
    }
    return IDENTIQUES;
}


int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
    int lignes2 = *p_lignes;
    int colonnes2 = *p_colonnes;

    if(sens != 0 && sens != 1)
        return ERREUR;
    
    
    struct RGB MatriceCopie[MAX_HAUTEUR][MAX_LARGEUR];

	for (int a=0;a<*p_lignes;a++)
	{
		for (int b=0;b<*p_colonnes;b++)
		{
			MatriceCopie[a][b].valeurR=matrice[a][b].valeurR;
            MatriceCopie[a][b].valeurG=matrice[a][b].valeurG;
            MatriceCopie[a][b].valeurB=matrice[a][b].valeurB;
		}
	}

	for (int i=0;i<*p_lignes;i++)
	{
		for (int j=0;j<*p_colonnes;j++)
		{
			if (sens==1)
			{
				matrice[j][*p_lignes-i-1].valeurR=MatriceCopie[i][j].valeurR;
                matrice[j][*p_lignes-i-1].valeurG=MatriceCopie[i][j].valeurG;
                matrice[j][*p_lignes-i-1].valeurB=MatriceCopie[i][j].valeurB;

			}
			else
			{
				matrice[*p_colonnes-j-1][i].valeurR=MatriceCopie[i][j].valeurR;
                matrice[*p_colonnes-j-1][i].valeurG=MatriceCopie[i][j].valeurG;
                matrice[*p_colonnes-j-1][i].valeurB=MatriceCopie[i][j].valeurB;
			}
		}
	}
    *p_lignes = colonnes2;
    *p_colonnes = lignes2;
    return OK;
}



