#include "lib/fonctions.h"
#include "lib/etudiant.h"

void saisir_etudiant(Etudiant *e)
{
    if (!e)
        return; // si e(ne respecte pas la structure Etudiant, fin du programme)
    printf("\n");
    printf("Saisis des infos de l'etudiant(e):\n");

    balise_deb();
    recupere_champ("Tapez le(s) nom(s)    : ");
    fgets(e->nom, sizeof e->nom, stdin);
    e->nom[taille_mot(e->nom) - 1] = '\0';

    balise_deb();
    recupere_champ("Tapez le(s) prenom(s) : ");
    fgets(e->prenom, sizeof e->prenom, stdin);
    e->prenom[taille_mot(e->prenom) - 1] = '\0';

    balise_deb();
    recupere_champ("Tapez la classe       : ");
    fgets(e->classe, sizeof e->classe, stdin);
    e->classe[taille_mot(e->classe) - 1] = '\0';

    balise_deb();
    recupere_champ("Tapez l'email         : ");
    fgets(e->email, sizeof e->email, stdin);
    e->email[taille_mot(e->email) - 1] = '\0';

    balise_deb();
    recupere_champ("Tapez le matricule    : ");
    fgets(e->matricule, sizeof e->matricule, stdin);
    e->matricule[taille_mot(e->matricule) - 1] = '\0';

    balise_deb();
    recupere_champ("Tapez le sexe         : ");
    fgets(e->sex, sizeof e->sex, stdin);
    e->sex[taille_mot(e->sex) - 1] = '\0';
}

void afficher_etudiant(Etudiant e)
{
    printf("\nNom : %s \nPrenom : %s \nClasse : %s  \nEmail : %s \nMatricule : %s \nSex : %s", e.nom, e.prenom, e.classe, e.email, e.matricule, e.sex);
}