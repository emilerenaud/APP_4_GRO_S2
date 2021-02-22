Pour compiler les fichiers de la problématique dans Geany:

  - Ouvrir le menu déroulant de "Construire" et choisir "Définir les commandes de construction". Ceci ouvre un dialogue.

  - Dans ce dialogue, changer l'instruction associée à "Construire" ("Build", en anglais) pour la suivante:
    gcc -Wall -o gestion_images gestion_images.c bibliotheque_images.c

Le fichier exécutable qui est généré se nomme "gestion_images.exe" 
