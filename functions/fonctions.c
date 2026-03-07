#include "../libs/fonctions.h"

void balise_deb()
{
    definir_couleur(BLEUE);
    printf("\t==> ");
    definir_couleur(DEFAUT);
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

    /* If line ended while still collecting a field (no trailing newline/comma)
     * we need to commit it. This also covers the case where the line ended
     * right after a quoted field without a newline.
     */
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

void afficher_menu(int m)
{
    switch (m)
    {
    case 0:
        printf("\n");
        printf("Choisissez une option :\n");
        balise_deb();
        printf("1. Affichage des etudiants.\n");
        balise_deb();
        printf("2. Insertion de(s) etudiant(s).");
        break;
    case 2:

        break;
    case 1:
        definir_couleur(bord);
        printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        printf("@@\t\t\t\t\t\t\t@@\n");
        printf("@@\t   ");
        definir_couleur(JAUNE);
        printf("Programme terminer !!!. \t");
        definir_couleur(bord);
        printf("@@\n");
        printf("@@\t\t\t\t\t\t\t@@\n");
        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        definir_couleur(DEFAUT);
        break;
    default:
        break;
    }
}

int definir_couleur(int couleur)
{
    printf("\033[%dm", couleur);
    return couleur;
}