#include "etudiant.h"
#ifndef FONCTIONS_H
#define FONCTIONS_H

/**
 * minuscule - Convertit un caractère ASCII majuscule en minuscule
 * @mot: caractère à convertir (valeur entière représentant un char)
 *
 * Retour:
 *   Si `mot` est une lettre majuscule ASCII ('A'..'Z'), retourne sa
 *   forme minuscule correspondante. Sinon retourne la valeur inchangée.
 *
 * Remarques:
 *   - Opère sur des caractères ASCII basiques et retourne un `int`.
 *   - Ne gère pas la localisation ni les caractères accentués.
 */
extern int minuscule(char mot);

/**
 * taille_mot - Calcule la longueur d'une chaîne C (comme strlen)
 * @mot: pointeur vers une chaîne terminée par '\0'
 *
 * Retour:
 *   La longueur (nombre de caractères) avant le caractère nul.
 *   Si `mot` est NULL, retourne 0.
 *
 * Complexité: O(n) où n est la longueur de la chaîne fournie.
 */
extern int taille_mot(char *mot);

/**
 * safe_strncpy - Copie une chaîne en garantissant la terminaison nulle
 * @dst: buffer destination
 * @src: chaîne source (peut être NULL)
 * @dst_size: taille du buffer destination en octets
 *
 * Description:
 *   Copie au plus `dst_size - 1` octets depuis `src` vers `dst` et
 *   place un caractère nul final. Si `src` est NULL, `dst` devient
 *   une chaîne vide. Si `dst` est NULL ou `dst_size` est 0, la fonction
 *   ne fait rien.
 */
extern void safe_strncpy(char *dst, const char *src, size_t dst_size);

/**
 * compare_mots - Compare deux chaînes en ignorant la casse ASCII
 * @mot1: première chaîne (peut être non-NULL)
 * @mot2: deuxième chaîne (peut être non-NULL)
 *
 * Retour:
 *   - 0 si les deux chaînes sont égales (insensible à la casse ASCII)
 *   - 1 si `mot1` est lexicographiquement supérieur à `mot2`
 *   - -1 si `mot1` est lexicographiquement inférieur à `mot2`
 *
 * Détails:
 *   - La comparaison se fait caractère par caractère après conversion
 *     en minuscule via `minuscule()` (traitement ASCII simple).
 *   - Lorsqu'une chaîne est un préfixe de l'autre, la plus longue est
 *     considérée comme supérieure.
 *
 * Complexité: O(min(len(mot1), len(mot2))).
 */
extern int compare_mots(const char *mot1, const char *mot2);

/**
 * vers_csv - Écrit un tableau d'étudiants dans un fichier CSV
 * @filename: chemin du fichier à écrire (créé/tronqué)
 * @tableau: tableau d'`Etudiant` à écrire
 * @n: nombre d'éléments valides dans `tableau`
 *
 * Format CSV:
 *   Chaque étudiant occupe une ligne au format:
 *     nom;prenom;classe;email;matricule;sex\n
 * Retour:
 *   - 1 en cas de succès
 *   - 0 si le fichier n'a pas pu être ouvert pour écriture
 *
 * Effets de bord:
 *   - Remplace le contenu existant du fichier `filename`.
 *
 * Remarques:
 *   - La fonction n'échappe pas les séparateurs ';' dans les champs.
 */
extern int vers_csv(const char *filename, Etudiant arr[], int n);

/**
 * lire_csv - Lit un fichier CSV et remplit un tableau d'`Etudiant`
 * @filename: chemin du fichier CSV à lire
 * @tableau: tableau préalloué d'`Etudiant` où stocker les résultats
 *
 * Description:
 *   Ouvre `filename` en lecture et parcourt chaque ligne. Chaque ligne
 *   est analysée par `parse_csv_line()` ; si au moins 6 champs sont
 *   lus, la ligne est copiée dans le tableau. La lecture s'arrête lorsque
 *   EOF est atteint ou lorsque `MAX_STUD` est atteint.
 *
 * Retour:
 *   - Nombre d'étudiants lus (0..MAX_STUD)
 *   - 0 si le fichier n'a pas pu être ouvert
 *
 * Remarques:
 *   - Ignore les lignes vides.
 */
extern int lire_csv(const char *filename, Etudiant tableau[]);

/**
 * cher_pos_ins - Recherche binaire de la position d'insertion par nom
 * @tableau: tableau trié d'`Etudiant` par champ `nom` (ordre alphabétique)
 * @n: nombre d'éléments valides dans `tableau` (>= 0)
 * @nom: nom à rechercher / insérer
 *
 * Description:
 *   Effectue une recherche binaire pour trouver l'indice où `nom` doit
 *   être inséré afin de préserver l'ordre trié. Si un étudiant portant
 *   exactement `nom` est trouvé, la fonction retourne l'indice de cet
 *   étudiant.
 *
 * Retour:
 *   - Indice (0..n-1) si `nom` existe déjà dans le tableau.
 *   - Indice d'insertion (valeur entre 0 et n) si `nom` n'existe pas.
 *
 * Exemples:
 *   - si n == 0 retourne 0 (insertion en début dans un tableau vide)
 *   - si `nom` est lexicographiquement après tous les éléments retourne n
 *
 * Complexité: O(log n)
 */
extern int cher_pos_ins(Etudiant tableau[], int n, const char *nom);

/**
 * parse_csv_line - Analyse une ligne CSV et remplit une structure Etudiant
 * @line: ligne CSV (terminée par '\0')
 * @etudiant: pointeur vers la structure à remplir (doit être non-NULL)
 *
 * Description:
 *   Parse la ligne `line` en six champs attendus dans l'ordre:
 *     0: nom
 *     1: prenom
 *     2: classe
 *     3: email
 *     4: matricule
 *     5: sex
 *
 *   Les champs sont séparés par ';'. Les champs peuvent être entourés
 *   de guillemets doubles ("...") ; une paire de guillemets "" à
 *   l'intérieur d'un champ cité est interprétée comme un guillemet
 *   littéral. Les caractères supplémentaires après le sixième champ
 *   sont ignorés.
 *
 * Retour:
 *   - Nombre de champs lus/assignés (0..)
 *   - 0 si `line` ou `etudiant` est NULL
 *
 * Remarques:
 *   - Les champs sont copiés dans les buffers de `etudiant` via
 *     `safe_strncpy()` (taille MAX_CHAMP).
 *   - Gère correctement les champs cités et les guillemets échappés.
 */
extern int parse_csv_line(const char *line, Etudiant *etudiant);

/**
 * afficher_menu - Affiche un menu simple selon le code fourni
 * @m: code du menu / style (0: menu principal, 1: message de fin, 2: réservé)
 *
 * Description:
 *   Produit sur la sortie standard différentes présentations selon la
 *   valeur de `m`. Cette fonction est principalement destinée à l'UI
 *   console du gestionnaire d'étudiants et utilise `balise_deb()` et
 *   `definir_couleur()` pour améliorer l'affichage.
 *
 * Comportement:
 *   - m == 0: affiche les options disponibles.
 *   - m == 1: affiche un encadré indiquant que le programme est terminé.
 *   - m == 2: réservé (aucune action actuellement).
 *
 * Effets de bord: écrit sur la sortie standard et modifie les couleurs.
 */
extern void afficher_menu(int m);

/**
 * definir_couleur - Applique une couleur via séquence d'échappement ANSI
 * @couleur: code numérique de couleur/attribut (défini dans `couleurs.h`)
 *
 * Description:
 *   Écrit la séquence d'échappement ANSI correspondante pour changer la
 *   couleur/attribut du texte dans un terminal supportant ANSI. La
 *   fonction retourne la valeur passée pour compatibilité mais n'effectue
 *   pas de vérification du terminal.
 *
 * Retour:
 *   Valeur entière égale à `couleur` (utile pour chaîner ou tester).
 */
extern int definir_couleur(int couleur);
/**
 * balise_deb - Affiche une flèche de début de champ en couleur
 *
 * Description:
 *   Émet sur la sortie standard une petite flèche/indicateur formaté
 *   pour marquer le début d'une invite de saisie. La fonction change
 *   temporairement la couleur du texte à `BLEUE`, affiche la
 *   séquence "\t==> " puis remet la couleur à la valeur par défaut.
 *
 * Effets de bord:
 *   - Appelle `definir_couleur()` pour modifier l'état d'affichage du
 *     terminal (séquence d'échappement ANSI). Cette fonction n'affecte
 *     pas de données en mémoire autre que la sortie standard.
 *
 * Comportement attendu:
 *   - Ne vérifie pas la validité du terminal ; écrit simplement des
 *     séquences d'échappement et du texte sur `stdout`.
 *
 * Exemple:
 *   balise_deb(); // affiche un préfixe coloré avant une invite
 */
extern void balise_deb();
/**
 * recupere_champ - Affiche un texte d'invite puis change la couleur
 * @output: chaîne à afficher (peut être une invite ou un message)
 *
 * Description:
 *   Imprime la chaîne fournie sur `stdout` sans ajout de fin de ligne
 *   (la chaîne doit contenir la ponctuation désirée) puis applique
 *   la couleur `MAGENTA` pour la saisie ou la mise en évidence qui
 *   suit. Ne modifie pas la chaîne fournie.
 *
 * Effets de bord:
 *   - Écrit sur la sortie standard.
 *   - Modifie l'état de couleur via `definir_couleur()`.
 */
extern void recupere_champ(const char *output);

#endif