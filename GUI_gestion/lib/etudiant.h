#include <stdio.h>
#include <stdlib.h>

#ifndef ETUDIANT_H
#define ETUDIANT_H


#define MAX_STUD 1000
#define MAX_CHAMP 128
#define MAX_LIGNE 512

typedef struct
{
    char nom[MAX_CHAMP];
    char prenom[MAX_CHAMP];
    char classe[MAX_CHAMP];
    char matricule[MAX_CHAMP];
    char email[MAX_CHAMP];
    char sex[MAX_CHAMP];
} Etudiant;

#endif
