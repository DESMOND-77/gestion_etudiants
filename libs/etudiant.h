#include <stdio.h>
#include <stdlib.h>
#include "couleurs.h"

#ifndef ETUDIANT_H
#define ETUDIANT_H

#define MAX_STUD 1000
#define MAX_CHAMP 128
#define MAX_LIGNE 512
#define FILENAME "../donnees/Etudiants.csv"
typedef struct
{
    char nom[MAX_CHAMP];
    char prenom[MAX_CHAMP];
    char classe[MAX_CHAMP];
    char matricule[MAX_CHAMP];
    char email[MAX_CHAMP];
    char sex[MAX_CHAMP];
} Etudiant;

/**
 * saisir_etudiant - Invite à la saisie des champs d'un étudiant
 * @e: pointeur vers la structure Etudiant à remplir (doit être non-NULL)
 *
 * Description:
 *   Demande à l'utilisateur, via la sortie et l'entrée standard, de
 *   renseigner successivement les champs suivants de la structure `Etudiant`:
 *     - nom
 *     - prenom
 *     - classe
 *     - email
 *     - matricule
 *     - sex
 *
 * Comportement et validations:
 *   - Si `e` est NULL la fonction retourne immédiatement sans effet.
 *   - Chaque lecture utilise `fgets()` avec la taille du buffer pour
 *     éviter les débordements ; la fin de ligne lue est ensuite remplacée
 *     par '\0' en s'appuyant sur `taille_mot()` pour localiser le dernier
 *     caractère (attention: si l'entrée dépasse la taille du buffer, la
 *     suppression du '\n' n'aura pas lieu et le comportement reste celui
 *     de `fgets`).
 *   - Utilise `balise_deb()` et `recupere_champ()` pour l'affichage des
 *     invites et des couleurs.
 *
 * Effets de bord:
 *   - Lit depuis `stdin` et écrit des invites sur `stdout`.
 */
extern void saisir_etudiant(Etudiant *e);
void balise_deb();

/**
 * afficher_etudiant - Affiche les informations d'un étudiant
 * @e: structure `Etudiant` à afficher (passée par valeur)
 *
 * Description:
 *   Écrit sur `stdout` les champs principaux de la structure `Etudiant`
 *   dans un format lisible (nom, prénom, classe, email, matricule, sexe).
 *
 * Remarques:
 *   - La fonction prend la structure par valeur ; si certains champs
 *     contiennent des données non terminées correctement, le résultat
 *     d'affichage dépendra de ces données.
 */
extern void afficher_etudiant(Etudiant e);

#endif
