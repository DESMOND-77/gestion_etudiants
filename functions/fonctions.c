#include "../libs/fonctions.h"
#include "../libs/banner.h"
#include <string.h>

void balise_deb()
{
    definir_couleur(BLEUE);
    printf("\t==> ");
    definir_couleur(DEFAUT);
}
int definir_couleur(int couleur)
{
    printf("\033[%dm", couleur);
    return couleur;
}
void recupere_champ(const char *output)
{
    if (!output)
        return;
    printf("%s", output);
    definir_couleur(MAGENTA);
}

int taille_mot(char *mot)
{
    int taille = 0;
    if (mot)
    {
        while (mot[taille])
            taille++;
    }
    return taille;
}

int minuscule(char mot)

{

    if (mot >= 'A' && mot <= 'Z')
        return mot - 'A' + 'a';
    return mot;
}

int compare_mots(const char *mot1, const char *mot2)
{
    int i = 0;
    while (mot1[i] && mot2[i])
    {
        char char_a = minuscule(mot1[i]);
        char char_b = minuscule(mot2[i]);
        if (char_a < char_b)
            return -1;
        if (char_a > char_b)
            return 1;
        i++;
    }
    if (mot1[i])
        return 1;
    if (mot2[i])
        return -1;
    return 0;
}

int cher_pos_ins(Etudiant tableau[], int n, const char *nom)
{
    int debut = 0, fin = n - 1;
    int pos = n;
    while (debut <= fin)
    {
        int centre = (debut + fin) / 2;
        int cmp = compare_mots(tableau[centre].nom, nom);
        if (cmp == 0)
        {
            return centre; /* trouve */
        }
        else if (cmp < 0)
        {
            debut = centre + 1;
            pos = debut;
        }
        else
        {
            pos = centre;
            fin = centre - 1;
        }
    }
    return pos;
}

int vers_csv(const char *filename, Etudiant tableau[], int n)
{
    // Ouverture du fichier CSV en mode ecriture
    FILE *fichier = fopen(filename, "w");

    // Si le fichier n'existe pas
    if (!fichier)
        return 0; // Arrête la fonction
    for (int i = 0; i < n; i++)
    {
        fprintf(fichier, "%s;%s;%s;%s;%s;%s\n",
                tableau[i].nom, tableau[i].prenom, tableau[i].classe, tableau[i].email, tableau[i].matricule, tableau[i].sex);
    }
    fclose(fichier);
    return 1;
}

int lire_csv(const char *filename, Etudiant tableau[])
{
    FILE *fichier = fopen(filename, "r");
    if (!fichier)
        return 0;

    char ligne[MAX_LIGNE];
    int n = 0;

    while (fgets(ligne, sizeof(ligne), fichier) && n < MAX_STUD)
    {
        if (ligne[0] == '\n' || ligne[0] == '\0')
            continue;

        Etudiant etudiant;
        if (parse_csv_line(ligne, &etudiant) >= 6)
        {
            tableau[n] = etudiant;
            n++;
        }
    }

    fclose(fichier);
    return n;
}

void safe_strncpy(char *dst, const char *src, size_t dst_size)
{
    if (!dst || dst_size == 0)
        return;
    if (!src)
    {
        dst[0] = '\0';
        return;
    }
    size_t i;
    for (i = 0; i + 1 < dst_size && src[i]; i++)
        dst[i] = src[i];
    dst[i] = '\0';
}

int parse_csv_line(const char *line, Etudiant *etudiant)
{
    if (!line || !etudiant)
        return 0;

    int champ = 0;
    int i = 0;
    int p = 0;
    char actuelle[MAX_CHAMP];
    int in_quote = 0;

    while (line[i] != '\0' && i <= MAX_LIGNE)
    {
        char ch = line[i];

        if (in_quote)
        {
            if (ch == '"')
            {
                /* If double quote followed by another quote, it's an escaped quote */
                if (line[i + 1] == '"')
                {
                    if (p < MAX_CHAMP - 1)
                        actuelle[p++] = '"';
                    i += 2;
                    continue;
                }
                else
                {
                    /* end of quoted field */
                    in_quote = 0;
                    i++;
                    continue;
                }
            }
            else
            {
                if (p < MAX_CHAMP - 1)
                    actuelle[p++] = ch;
                i++;
                continue;
            }
        }

        /* not in quote */
        if (ch == '"')
        {
            in_quote = 1;
            i++;
            continue;
        }

        if (ch == ';' || ch == '\n' || ch == '\r' || ch == '\0')
        {
            actuelle[p] = '\0';
            switch (champ)
            {
            case 0:
                safe_strncpy(etudiant->nom, actuelle, MAX_CHAMP);
                break;
            case 1:
                safe_strncpy(etudiant->prenom, actuelle, MAX_CHAMP);
                break;
            case 2:
                safe_strncpy(etudiant->classe, actuelle, MAX_CHAMP);
                break;
            case 3:
                safe_strncpy(etudiant->email, actuelle, MAX_CHAMP);
                break;
            case 4:
                safe_strncpy(etudiant->matricule, actuelle, MAX_CHAMP);
                break;
            case 5:
                safe_strncpy(etudiant->sex, actuelle, MAX_CHAMP);
                break;
            default:
                /* champs supplementaires ignores */
                break;
            }
            champ++;
            p = 0;

            if (ch == ';')
            {
                i++;
                continue;
            }
            else
            {
                /* newline or end -> finish */
                break;
            }
        }
        else
        {
            if (p < MAX_CHAMP - 1)
                actuelle[p++] = ch;
            i++;
        }
    }

    /* If line ended while still collecting a field (no trailing newline/comma) */
    if (p > 0 || (line[0] != '\0' && champ == 0))
    {
        actuelle[p] = '\0';
        switch (champ)
        {
        case 0:
            safe_strncpy(etudiant->nom, actuelle, MAX_CHAMP);
            break;
        case 1:
            safe_strncpy(etudiant->prenom, actuelle, MAX_CHAMP);
            break;
        case 2:
            safe_strncpy(etudiant->classe, actuelle, MAX_CHAMP);
            break;
        case 3:
            safe_strncpy(etudiant->email, actuelle, MAX_CHAMP);
            break;
        case 4:
            safe_strncpy(etudiant->matricule, actuelle, MAX_CHAMP);
            break;
        case 5:
            safe_strncpy(etudiant->sex, actuelle, MAX_CHAMP);
            break;
        default:
            break;
        }
        champ++;
    }

    return champ;
}

void vider_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int charger_etudiants(const char *filename, Etudiant tableau[])
{
    return lire_csv(filename, tableau);
}

int sauvegarder_etudiants(const char *filename, Etudiant tableau[], int n)
{
    return vers_csv(filename, tableau, n);
}

void traiter_option(const char *filename, Etudiant tableau[], int *n, int option)
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

/* ============================================
 * FONCTIONS ADDITIONNELLES POUR LA GESTION
 * ============================================ */

int contient_sous_chaine(const char *texte, const char *sous_chaine)
{
    if (!texte || !sous_chaine)
        return 0;

    /* Convertir les deux chaînes en minuscules pour la comparaison */
    char texte_lower[MAX_CHAMP];
    char sous_chaine_lower[MAX_CHAMP];

    int i = 0;
    while (texte[i] && i < MAX_CHAMP - 1)
    {
        texte_lower[i] = minuscule(texte[i]);
        i++;
    }
    texte_lower[i] = '\0';

    i = 0;
    while (sous_chaine[i] && i < MAX_CHAMP - 1)
    {
        sous_chaine_lower[i] = minuscule(sous_chaine[i]);
        i++;
    }
    sous_chaine_lower[i] = '\0';

    /* Utiliser strstr pour la recherche de sous-chaîne */
    return (strstr(texte_lower, sous_chaine_lower) != NULL) ? 1 : 0;
}

void calculer_largeurs_colonnes(Etudiant tableau[], int n, ColWidths *widths)
{
    /* Initialiser avec les largeurs des en-têtes */
    widths->nom = strlen("NOM");
    widths->prenom = strlen("PRENOM");
    widths->classe = strlen("CLASSE");
    widths->matricule = strlen("MATRICULE");
    widths->email = strlen("EMAIL");

    /* Trouver le maximum pour chaque colonne */
    for (int i = 0; i < n; i++)
    {
        int len_nom = strlen(tableau[i].nom);
        int len_prenom = strlen(tableau[i].prenom);
        int len_classe = strlen(tableau[i].classe);
        int len_matricule = strlen(tableau[i].matricule);
        int len_email = strlen(tableau[i].email);

        if (len_nom > widths->nom)
            widths->nom = len_nom;
        if (len_prenom > widths->prenom)
            widths->prenom = len_prenom;
        if (len_classe > widths->classe)
            widths->classe = len_classe;
        if (len_matricule > widths->matricule)
            widths->matricule = len_matricule;
        if (len_email > widths->email)
            widths->email = len_email;
    }
}

void afficher_ligne_separatrice(ColWidths *widths, int pad)
{
    /* Ajouter un petit padding pour l'esthétique */
    widths->nom += pad;
    widths->prenom += pad;
    widths->classe += pad;
    widths->matricule += pad;
    widths->email += pad;
    printf("+");
    for (int i = 0; i < widths->nom; i++)
        printf("-");
    printf("+");
    for (int i = 0; i < widths->prenom; i++)
        printf("-");
    printf("+");
    for (int i = 0; i < widths->classe; i++)
        printf("-");
    printf("+");
    for (int i = 0; i < widths->matricule; i++)
        printf("-");
    printf("+");
    for (int i = 0; i < widths->email; i++)
        printf("-");
    printf("+\n");
    /* Enlever le petit padding */
    widths->nom -= pad;
    widths->prenom -= pad;
    widths->classe -= pad;
    widths->matricule -= pad;
    widths->email -= pad;
}

void afficher_tous_etudiants(Etudiant tableau[], int n)
{
    if (n == 0)
    {
        printf("\nAucun etudiant dans la base de donnees.\n");
        return;
    }

    /* Calculer les largeurs dynamiques */
    ColWidths widths;
    calculer_largeurs_colonnes(tableau, n, &widths);

    printf("\n");
    afficher_ligne_separatrice(&widths, tab_pad);

    /* En-têtes */
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           widths.nom, "NOM",
           widths.prenom, "PRENOM",
           widths.classe, "CLASSE",
           widths.matricule, "MATRICULE",
           widths.email, "EMAIL");

    afficher_ligne_separatrice(&widths, tab_pad);

    /* Données */
    for (int i = 0; i < n; i++)
    {
        printf("| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
               widths.nom, tableau[i].nom,
               widths.prenom, tableau[i].prenom,
               widths.classe, tableau[i].classe,
               widths.matricule, tableau[i].matricule,
               widths.email, tableau[i].email);
    }

    afficher_ligne_separatrice(&widths, tab_pad);
    printf("Total: %d etudiant(s)\n", n);
}

int supprimer_etudiant_par_matricule(const char *filename, const char *matricule, Etudiant tableau[], int *n)
{
    int pos = -1;

    /* Recherche de l'étudiant par matricule */
    for (int i = 0; i < *n; i++)
    {
        if (compare_mots(tableau[i].matricule, matricule) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        definir_couleur(erreur);
        printf("\nEtudiant avec le matricule \"%s\" non trouve.\n", matricule);
        definir_couleur(DEFAUT);
        return 0;
    }

    /* Confirmation de la suppression */
    definir_couleur(JAUNE);
    printf("\nEtudiant trouve: %s %s (Matricule: %s)\n",
           tableau[pos].nom, tableau[pos].prenom, tableau[pos].matricule);
    definir_couleur(DEFAUT);

    /* Décalage des éléments vers la gauche */
    for (int i = pos; i < *n - 1; i++)
    {
        tableau[i] = tableau[i + 1];
    }

    (*n)--;

    /* Sauvegarde dans le fichier CSV */
    if (vers_csv(filename, tableau, *n))
    {
        definir_couleur(reussite);
        printf("Etudiant supprime avec succes.\n");
        definir_couleur(DEFAUT);
        return 1;
    }
    else
    {
        definir_couleur(erreur);
        printf("Erreur lors de la sauvegarde du fichier.\n");
        definir_couleur(DEFAUT);
        return 0;
    }
}

int modifier_etudiant_par_matricule(const char *filename, const char *matricule, Etudiant *nouveau, Etudiant tableau[], int n)
{
    int pos = -1;

    /* Recherche de l'étudiant par matricule */
    for (int i = 0; i < n; i++)
    {
        if (compare_mots(tableau[i].matricule, matricule) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        definir_couleur(erreur);
        printf("\nEtudiant avec le matricule \"%s\" non trouve.\n", matricule);
        definir_couleur(DEFAUT);
        return 0;
    }

    /* Affichage de l'étudiant actuel */
    definir_couleur(JAUNE);
    printf("\nEtudiant actuel: %s %s (Classe: %s, Email: %s)\n",
           tableau[pos].nom, tableau[pos].prenom, tableau[pos].classe, tableau[pos].email);
    definir_couleur(DEFAUT);

    /* Mise à jour de l'étudiant */
    tableau[pos] = *nouveau;

    /* Sauvegarde dans le fichier CSV */
    if (vers_csv(filename, tableau, n))
    {
        definir_couleur(reussite);
        printf("Etudiant modifie avec succes.\n");
        definir_couleur(DEFAUT);
        return 1;
    }
    else
    {
        definir_couleur(erreur);
        printf("Erreur lors de la sauvegarde du fichier.\n");
        definir_couleur(DEFAUT);
        return 0;
    }
}

int rechercher_etudiant_par_nom(Etudiant tableau[], int n, const char *nom)
{
    int count = 0;

    if (n == 0)
    {
        definir_couleur(erreur);
        printf("\nAucun etudiant dans la base de donnees.\n");
        definir_couleur(DEFAUT);
        return 0;
    }
    definir_couleur(MAGENTA);
    /* Calculer les largeurs dynamiques */
    ColWidths widths;
    calculer_largeurs_colonnes(tableau, n, &widths);

    printf("\n");
    afficher_ligne_separatrice(&widths, tab_pad);
    /* En-têtes */
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           widths.nom, "NOM",
           widths.prenom, "PRENOM",
           widths.classe, "CLASSE",
           widths.matricule, "MATRICULE",
           widths.email, "EMAIL");

    afficher_ligne_separatrice(&widths, tab_pad);

    for (int i = 0; i < n; i++)
    {
        /* Recherche insensible à la casse et partielle */
        if (contient_sous_chaine(tableau[i].nom, nom) || strstr(tableau[i].nom, nom) != NULL ||
            strstr(nom, tableau[i].nom) != NULL ||
            compare_mots(tableau[i].nom, nom) == 0)
        {
            printf("| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
                   widths.nom, tableau[i].nom,
                   widths.prenom, tableau[i].prenom,
                   widths.classe, tableau[i].classe,
                   widths.matricule, tableau[i].matricule,
                   widths.email, tableau[i].email);
            count++;
        }
    }

    if (count == 0)
    {
        definir_couleur(JAUNE);
        afficher_ligne_separatrice(&widths, tab_pad);
        printf("Aucun resultat pour la recherche: \"%s\"\n", nom);
        definir_couleur(DEFAUT);
    }
    else
    {
        afficher_ligne_separatrice(&widths, tab_pad);
        printf("Total: %d etudiant(s) trouve(s)\n", count);
    }
    definir_couleur(DEFAUT);
    return count;
}

/* =============================================
 * FONCTIONS DE COMPARAISON QSORT ET DE TRIE
 * ============================================= */
int comparer_par_nom_asc(const void *a, const void *b)
{
    Etudiant *ea = (Etudiant *)a;
    Etudiant *eb = (Etudiant *)b;
    return compare_mots(ea->nom, eb->nom);
}

int comparer_par_nom_desc(const void *a, const void *b)
{
    Etudiant *ea = (Etudiant *)a;
    Etudiant *eb = (Etudiant *)b;
    return compare_mots(eb->nom, ea->nom);
}

int comparer_par_classe_asc(const void *a, const void *b)
{
    Etudiant *ea = (Etudiant *)a;
    Etudiant *eb = (Etudiant *)b;
    return compare_mots(ea->classe, eb->classe);
}

int comparer_par_classe_desc(const void *a, const void *b)
{
    Etudiant *ea = (Etudiant *)a;
    Etudiant *eb = (Etudiant *)b;
    return compare_mots(eb->classe, ea->classe);
}

void trier_etudiants(Etudiant tableau[], int n, int option)
{
    if (n == 0)
    {
        printf("\nAucun etudiant a trier.\n");
        return;
    }

    switch (option)
    {
    case 1:
        qsort(tableau, n, sizeof(Etudiant), comparer_par_nom_asc);
        printf("\nEtudiants tries par nom (croissant).\n");
        break;
    case 2:
        qsort(tableau, n, sizeof(Etudiant), comparer_par_nom_desc);
        printf("\nEtudiants tries par nom (decroissant).\n");
        break;
    case 3:
        qsort(tableau, n, sizeof(Etudiant), comparer_par_classe_asc);
        printf("\nEtudiants tries par classe (croissant).\n");
        break;
    case 4:
        qsort(tableau, n, sizeof(Etudiant), comparer_par_classe_desc);
        printf("\nEtudiants tries par classe (decroissant).\n");
        break;
    default:
        printf("\nOption de tri invalide.\n");
        return;
    }
}
