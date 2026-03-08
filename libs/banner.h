#ifndef BANNER_H
#define BANNER_H

/**
 * afficher_accueil - Affiche le banner de bienvenue du programme
 * @filename: chemin du fichier CSV
 *
 * Description:
 *   Affiche un encadré ASCII colorisé avec le message de bienvenue
 *   et le nombre d'étudiants actuellement dans le fichier.
 *
 * Effets de bord:
 *   - Écrit sur stdout
 *   - Modifie les couleurs via definir_couleur()
 */
extern void afficher_accueil(const char *filename);

/**
 * afficher_menu_principal - Affiche le menu principal du programme
 *
 * Description:
 *   Affiche les options principales du gestionnaire d'étudiants:
 *   - Afficher tous les étudiants
 *   - Ajouter un étudiant
 *   - Modifier un étudiant
 *   - Supprimer un étudiant
 *   - Rechercher un étudiant
 *   - Quitter
 *
 * Effets de bord:
 *   - Écrit sur stdout
 *   - Modifie les couleurs via definir_couleur()
 */
extern void afficher_menu_principal(void);

/**
 * afficher_menu_tri - Affiche les options de tri pour les étudiants
 *
 * Description:
 *   Affiche les options de tri disponibles:
 *   - Par nom (croissant)
 *   - Par nom (décroissant)
 *   - Par classe (croissant)
 *   - Par classe (décroissant)
 *
 * Effets de bord:
 *   - Écrit sur stdout
 *   - Modifie les couleurs via definir_couleur()
 */
extern void afficher_menu_tri(void);

/**
 * afficher_message_fin - Affiche le message de fin du programme
 *
 * Description:
 *   Affiche un encadré ASCII indiquant que le programme est terminé.
 *
 * Effets de bord:
 *   - Écrit sur stdout
 *   - Modifie les couleurs via definir_couleur()
 */
extern void afficher_message_fin(void);

/**
 * afficher_separateur - Affiche un séparateur visuel
 *
 * Description:
 *   Affiche une ligne de séparation pour améliorer la lisibilité.
 *
 * Effets de bord:
 *   - Écrit sur stdout
 */
extern void afficher_separateur(void);

#endif /* BANNER_H */

