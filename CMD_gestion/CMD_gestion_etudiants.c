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

/**
 * vider_buffer - Vide le buffer d'entrée stdin
 */
static void vider_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
/**
 * charger_etudiants - Charge les étudiants depuis le fichier CSV
 * @filename: chemin du fichier CSV
 * @tableau: tableau où stocker les étudiants
 *
 * Retour: nombre d'étudiants chargés
 */
static int charger_etudiants(const char *filename, Etudiant tableau[])
{
    return lire_csv(filename, tableau);
}

/**
 * sauvegarder_etudiants - Sauvegarde les étudiants dans le fichier CSV
 * @filename: chemin du fichier CSV
 * @tableau: tableau d'étudiants à sauvegarder
 * @n: nombre d'étudiants
 *
 * Retour: 1 en cas de succès, 0 en cas d'échec
 */
static int sauvegarder_etudiants(const char *filename, Etudiant tableau[], int n)
{
    return vers_csv(filename, tableau, n);
}

/**
 * afficher_accueil - Affiche l'écran d'accueil avec le nombre d'étudiants
 * @filename: chemin du fichier CSV
 */
static void afficher_accueil(const char *filename)
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
    printf("||\t");
    definir_couleur(JAUNE);
    printf("Nombre d'etudiants actuellement dans \"%s\" : %d \t\t", filename, n);
    definir_couleur(bord);
    printf("||\n");
    printf("==========================================================================\n");
    definir_couleur(DEFAUT);
}

/**
 * traiter_option - Traite l'option choisie par l'utilisateur
 * @filename: chemin du fichier CSV
 * @tableau: tableau d'étudiants
 * @n: pointeur vers le nombre d'étudiants
 * @option: option choisie
 */
static void traiter_option(const char *filename, Etudiant tableau[], int *n, int option)
{
    char buffer[MAX_CHAMP];
    int choix;

    switch (option)
    {
    case 1: /* Afficher tous les étudiants */
        afficher_separateur();
        printf("                        LISTE DES ETUDIANTS\n");
        afficher_separateur();
        afficher_tous_etudiants(tableau, *n);
        break;

    case 2: /* Ajouter un étudiant */
        afficher_separateur();
        printf("                        AJOUTER UN ETUDIANT\n");
        afficher_separateur();

        /* Vérification de capacité */
        if (*n + 1 > MAX_STUD)
        {
            definir_couleur(erreur);
            printf("\nFichier plein !!!\n");
            definir_couleur(DEFAUT);
            break;
        }

        Etudiant etudiant;
        saisir_etudiant(&etudiant);

        /* Vérification de doublon par matricule */
        for (int i = 0; i < *n; i++)
        {
            if (compare_mots(tableau[i].matricule, etudiant.matricule) == 0)
            {
                definir_couleur(erreur);
                printf("\nL'etudiant(e) %s %s est dejà present(e) dans %s.\n",
                       etudiant.nom, etudiant.prenom, filename);
                definir_couleur(DEFAUT);
                return;
            }
        }

        /* Recherche de la position d'insertion (tri alphabétique par nom) */
        int pos = cher_pos_ins(tableau, *n, etudiant.nom);
        if (pos < 0)
            pos = *n;

        /* Décalage et insertion */
        for (int i = *n; i > pos; i--)
        {
            tableau[i] = tableau[i - 1];
        }
        tableau[pos] = etudiant;
        (*n)++;

        /* Sauvegarde */
        if (sauvegarder_etudiants(filename, tableau, *n))
        {
            definir_couleur(reussite);
            printf("\nEtudiant(e) insere(e) avec succes.\n");
            definir_couleur(DEFAUT);
        }
        else
        {
            definir_couleur(erreur);
            printf("\nErreur d'ecriture du fichier.\n");
            definir_couleur(DEFAUT);
        }
        break;

    case 3:
        afficher_separateur();
        printf("                        MODIFIER UN ETUDIANT\n");
        afficher_separateur();

        printf("\nEntrez le matricule de l'etudiant a modifier : ");
        definir_couleur(MAGENTA);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[taille_mot(buffer) - 1] = '\0';
        definir_couleur(DEFAUT);

        /* Vérifier si l'étudiant existe */
        int pos_mod = -1;
        for (int i = 0; i < *n; i++)
        {
            if (compare_mots(tableau[i].matricule, buffer) == 0)
            {
                pos_mod = i;
                break;
            }
        }

        if (pos_mod == -1)
        {
            definir_couleur(erreur);
            printf("\nEtudiant avec le matricule \"%s\" non trouve.\n", buffer);
            definir_couleur(DEFAUT);
            break;
        }

        /* Afficher les informations actuelles */
        printf("\nInformations actuelles:\n");
        printf("  Nom: %s\n", tableau[pos_mod].nom);
        printf("  Prenom: %s\n", tableau[pos_mod].prenom);
        printf("  Classe: %s\n", tableau[pos_mod].classe);
        printf("  Email: %s\n", tableau[pos_mod].email);
        printf("  Sexe: %s\n", tableau[pos_mod].sex);

        /* Saisie des nouvelles informations */
        printf("\nEntrez les nouvelles informations:\n");
        Etudiant nouveau;
        saisir_etudiant(&nouveau);

        /* Conserver l'ancien matricule pour la recherche */
        safe_strncpy(nouveau.matricule, buffer, MAX_CHAMP);

        /* Mise à jour */
        if (modifier_etudiant_par_matricule(filename, buffer, &nouveau, tableau, *n))
        {
            /* Recharger les données */
            *n = charger_etudiants(filename, tableau);
        }
        break;

    case 4: /* Supprimer un étudiant */
        afficher_separateur();
        printf("                        SUPPRIMER UN ETUDIANT\n");
        afficher_separateur();

        printf("\nEntrez le matricule de l'etudiant a supprimer : ");
        definir_couleur(MAGENTA);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[taille_mot(buffer) - 1] = '\0';
        definir_couleur(DEFAUT);

        supprimer_etudiant_par_matricule(filename, buffer, tableau, n);
        break;

    case 5: /* Rechercher un étudiant par nom */
        afficher_separateur();
        printf("                        RECHERCHER UN ETUDIANT\n");
        afficher_separateur();

        printf("\nEntrez le nom a rechercher : ");
        definir_couleur(MAGENTA);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[taille_mot(buffer) - 1] = '\0';
        definir_couleur(DEFAUT);

        rechercher_etudiant_par_nom(tableau, *n, buffer);
        break;

    case 6: /* Trier les étudiants */
        afficher_separateur();
        printf("                        TRIER LES ETUDIANTS\n");
        afficher_separateur();

        afficher_menu_tri();

        /* Lire le choix de tri */
        if (scanf("%d", &choix) != 1)
        {
            vider_buffer();
            definir_couleur(erreur);
            printf("\nEntree invalide.\n");
            definir_couleur(DEFAUT);
            break;
        }
        vider_buffer();

        /* Appliquer le tri */
        trier_etudiants(tableau, *n, choix);
        afficher_tous_etudiants(tableau, *n);
        /* Demander si l'utilisateur veut sauvegarder */
        // if (choix >= 1 && choix <= 4)
        // {
        //     printf("\nVoulez-vous sauvegarder le tri ? (1: Oui, 0: Non) : ");
        //     if (scanf("%d", &choix) == 1 && choix == 1)
        //     {
        //         sauvegarder_etudiants(filename, tableau, *n);
        //         definir_couleur(reussite);
        //         printf("Tri sauvegarde avec succes.\n");
        //         definir_couleur(DEFAUT);
        //     }
        //     vider_buffer();
        // }
        break;

    case 0: /* Quitter */
        /* Ne rien faire, la boucle principale gérera la sortie */
        break;

    default:
        definir_couleur(erreur);
        printf("\nOption invalide. Veuillez choisir une option valide.\n");
        definir_couleur(DEFAUT);
        break;
    }
}

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
