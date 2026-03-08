#include "../libs/banner.h"
#include "../libs/couleurs.h"
#include "../libs/fonctions.h"

void afficher_accueil(const char *filename)
{
    Etudiant temp[MAX_STUD];
    int n = charger_etudiants(filename, temp);

    definir_couleur(bord);
    printf("##########################################################################\n");
    printf("##\t\t\t\t\t\t\t\t\t##\n");
    printf("##\t");
    definir_couleur(JAUNE);
    printf("Bienvenue dans le programme de gestion des etudiants.\t\t");
    definir_couleur(bord);
    printf("##\n");
    printf("##\t\t\t\t\t\t\t\t\t##\n");
    printf("##########################################################################\n");
    printf("||\t\t\t\t\t\t\t\t\t||\n");
    printf("||\t\t");
    definir_couleur(JAUNE);
    printf("       Nombre d'etudiants actuel: %d  \t\t\t", n);
    definir_couleur(bord);
    printf("||\n");
    printf("==========================================================================\n");
    definir_couleur(DEFAUT);
}

void afficher_menu_principal(void)
{
    printf("\n");
    printf("================== MENU PRINCIPAL ==================\n\n");
    balise_deb();
    printf("1. Afficher tous les etudiants\n");
    balise_deb();
    printf("2. Ajouter un etudiant\n");
    balise_deb();
    printf("3. Modifier un etudiant\n");
    balise_deb();
    printf("4. Supprimer un etudiant\n");
    balise_deb();
    printf("5. Rechercher un etudiant\n");
    balise_deb();
    printf("6. Trier les etudiants\n");
    balise_deb();
    printf("0. Quitter\n\n");
    printf("=====================================================\n");
    printf("\nChoisissez une option : ");
    definir_couleur(MAGENTA);
}

void afficher_menu_tri(void)
{
    printf("\n");
    printf("================== MENU DE TRI ==================\n\n");
    balise_deb();
    printf("1. Trier par nom (croissant)\n");
    balise_deb();
    printf("2. Trier par nom (decroissant)\n");
    balise_deb();
    printf("3. Trier par classe (croissant)\n");
    balise_deb();
    printf("4. Trier par classe (decroissant)\n");
    balise_deb();
    printf("0. Retour au menu principal\n\n");
    printf("===================================================\n");
    printf("\nChoisissez une option : ");
    definir_couleur(MAGENTA);
}

void afficher_message_fin(void)
{
    definir_couleur(bord);
    printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@@\t\t\t\t\t@@\n");
    printf("@@\t   ");
    definir_couleur(JAUNE);
    printf("Programme terminer !!!. \t");
    definir_couleur(bord);
    printf("@@\n");
    printf("@@\t\t\t\t\t@@\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    definir_couleur(DEFAUT);
}

void afficher_separateur(void)
{
    printf("--------------------------------------------------------------------------\n");
}

