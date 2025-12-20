/**
 * ============================================================================
 * PROGRAMME DE GESTION DES ÉTUDIANTS (VERSION CONSOLE/CMD)
 * ============================================================================
 *
 * Description:
 *   Ce programme permet d'insérer un nouvel étudiant dans un fichier CSV
 *   de gestion d'étudiants. Il utilise une recherche binaire pour trouver
 *   la position d'insertion correcte (par ordre alphabétique du nom) et
 *   maintient le fichier CSV trié.
 *
 * Fonctionnalités:
 *   1. Charge les étudiants existants depuis un fichier CSV
 *   2. Affiche le nombre d'étudiants actuels
 *   3. Demande la saisie des informations d'un nouvel étudiant
 *   4. Vérifie que le matricule n'existe pas déjà
 *   5. Trouve la position d'insertion (tri alphabétique par nom)
 *   6. Insère le nouvel étudiant de manière triée
 *   7. Sauvegarde les modifications dans le fichier CSV
 *
 * Fichier CSV attendu: "test.csv" avec format
 *   nom;prenom;classe;email;matricule;sex
 * ============================================================================
 */

#include "lib/fonctions.h"
#include "lib/etudiant.h"

int main()
{
    // ========== DÉCLARATION DES VARIABLES ==========
    const char *filename = "test.csv"; // Nom du fichier CSV de données
    Etudiant tableau[MAX_STUD];        // Tableau pour stocker les étudiants existants
    Etudiant etudiant;                 // Structure pour le nouvel étudiant à ajouter

    // ========== CHARGEMENT DU FICHIER CSV ==========
    // Lecture du fichier CSV existant et remplissage du tableau
    // Retourne le nombre d'étudiants actuellement dans le fichier
    int n = lire_csv(filename, tableau);

    // ========== AFFICHAGE DE L'EN-TÊTE DU PROGRAMME ==========
    // Affiche un message de bienvenue formaté et coloré en utilisant les codes ANSI
    // bord = couleur pour l'encadré, JAUNE = titre, DEFAUT = retour à la couleur normale
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

    // ========== SAISIE DES INFORMATIONS DE L'ÉTUDIANT ==========
    // Appelle la fonction saisir_etudiant() qui demande à l'utilisateur
    // de saisir via stdin tous les champs de la structure Etudiant
    saisir_etudiant(&etudiant);

    // ========== VÉRIFICATION DE DOUBLON (PAR MATRICULE) ==========
    // Parcourt linéairement le tableau pour vérifier que le matricule du nouvel
    // étudiant n'existe pas déjà (les matricules sont uniques)
    // Si trouvé -> affiche un message d'erreur et termine le programme
    for (int i = 0; i < n; i++)
    {
        if (compare_mots(tableau[i].matricule, etudiant.matricule) == 0)
        {
            // Utilise la couleur "erreur" pour signaler l'erreur à l'utilisateur
            definir_couleur(erreur);
            printf("\nL'etudiant(e) %s %s est dejà present(e) dans %s (ligne %d).\n", etudiant.nom, etudiant.prenom, filename, i + 1);
            definir_couleur(DEFAUT);
            return 0; // Arrêt du programme
        }
    }

    // ========== RECHERCHE BINAIRE DE POSITION D'INSERTION ==========
    // Utilise la fonction cher_pos_ins() pour trouver la position où insérer
    // le nouvel étudiant de manière à conserver l'ordre alphabétique par nom
    // Complexité: O(log n)
    int pos = cher_pos_ins(tableau, n, etudiant.nom);
    if (pos < 0) // Sécurité: si position invalide, ajouter à la fin
        pos = n;

    // ========== VÉRIFICATION DE CAPACITÉ ==========
    // Vérifie que le tableau n'a pas atteint sa capacité maximale (MAX_STUD = 1000)
    if (n + 1 > MAX_STUD)
    {
        definir_couleur(erreur);
        printf("\nFichier plein !!!\n");
        definir_couleur(DEFAUT);
        return 1; // Code d'erreur 1
    }

    // ========== INSERTION AVEC DÉCALAGE ==========
    // Décale les éléments du tableau vers la droite à partir de la position d'insertion
    // Cela crée un "espace" à la position pos pour le nouvel étudiant
    for (int i = n; i > pos; i--)
    {
        tableau[i] = tableau[i - 1]; // Décalage à droite
    }

    // Insère le nouvel étudiant à la position correcte
    tableau[pos] = etudiant;
    n++; // Incrémente le nombre d'étudiants

    // ========== SAUVEGARDE DANS LE FICHIER CSV ==========
    // Écrit tous les étudiants du tableau (incluant le nouvel) dans le fichier CSV
    // Le fichier est remplacé complètement (mode "w")
    if (vers_csv(filename, tableau, n))
    {
        // Succès: affiche un message coloré en vert (reussite)
        definir_couleur(reussite);
        printf("\nEtudiant(e) insere(e) en position %d et fichier mis à jour (%s).\n", pos + 1, filename);
        definir_couleur(DEFAUT);
    }
    else
    {
        // Erreur lors de l'écriture du fichier
        definir_couleur(erreur);
        printf("\nErreur d'ecriture du fichier.\n");
        definir_couleur(DEFAUT);
    }

    // ========== MESSAGE DE FERMETURE ==========
    // Affiche un encadré indiquant que le programme se termine
    afficher_menu(1); // afficher_menu(1) -> message de fin formaté

    return 0; // Fin du programme avec code de succès
}
