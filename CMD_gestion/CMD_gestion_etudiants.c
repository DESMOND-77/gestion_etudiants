/**
 * ============================================================================
 * PROGRAMME DE GESTION DES ÉTUDIANTS (VERSION CONSOLE/CMD)
 * ============================================================================
 *
 * Description:
 *   Ce programme permet de gérer les étudiants dans un fichier CSV.
 *   Il offre les fonctionnalités suivantes:
 *   - Afficher tous les étudiants
 *   - Ajouter un étudiant
 *   - Modifier un étudiant (par matricule)
 *   - Supprimer un étudiant (par matricule)
 *   - Rechercher un étudiant (par nom)
 *   - Trier les étudiants (par nom ou classe)
 *
 * Fichier CSV attendu: "data/Etudiants.csv" avec format
 *   nom;prenom;classe;email;matricule;sex
 * ============================================================================
 */

#include "../libs/fonctions.h"
#include "../libs/banner.h"
#include <string.h>

int main()
{
    /* ========== DÉCLARATION DES VARIABLES ========== */
    const char *filename = FILENAME; /* Nom du fichier CSV de données */
    Etudiant tableau[MAX_STUD];      /* Tableau pour stocker les étudiants */
    int n = 0;                       /* Nombre d'étudiants actuels */
    int option = 0;                  /* Option choisie par l'utilisateur */
    int continuer = 1;               /* Drapeau pour continuer la boucle */

    /* ========== CHARGEMENT DU FICHIER CSV ========== */
    n = charger_etudiants(filename, tableau);

    /* ========== BOUCLE PRINCIPALE ========== */
    while (continuer)
    {
        /* Affichage de l'écran d'accueil */
        afficher_accueil(filename);

        /* Affichage du menu principal */
        afficher_menu_principal();

        /* Lecture de l'option */
        if (scanf("%d", &option) != 1)
        {
            vider_buffer();
            definir_couleur(erreur);
            printf("\nEntree invalide. Veuillez entrer un nombre.\n");
            definir_couleur(DEFAUT);
            continue;
        }
        vider_buffer();

        /* Traitement de l'option */
        if (option == 0)
        {
            continuer = 0;
        }
        else
        {
            /* Recharger les données avant chaque opération */
            n = charger_etudiants(filename, tableau);

            traiter_option(filename, tableau, &n, option);
        }
    }

    /* ========== MESSAGE DE FERMETURE ========== */
    afficher_message_fin();

    return 0;
}
