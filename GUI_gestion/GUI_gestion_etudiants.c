/**
 * ============================================================================
 * PROGRAMME DE GESTION DES ÉTUDIANTS (VERSION GRAPHIQUE GTK+)
 * ============================================================================
 *
 * Description:
 *   Application graphique GTK+ pour gérer une base d'étudiants stockée dans
 *   un fichier CSV. Permet d'insérer de nouveaux étudiants en maintenant
 *   l'ordre alphabétique par nom.
 *
 * Dépendances:
 *   - GTK+ 3.0 ou supérieur
 *   - Bibliothèques de gestion d'étudiants (fonctions.h, etudiant.h)
 *
 * Fonctionnalités:
 *   1. Interface graphique pour la saisie des informations étudiants
 *   2. Validation des champs obligatoires (Nom, Prénom, Matricule)
 *   3. Insertion triée par nom dans le fichier CSV
 *   4. Messages de confirmation/erreur avec boîtes de dialogue
 *   5. Chargement de style CSS personnalisé depuis "style.css"
 * ============================================================================
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/fonctions.h"
#include "../libs/etudiant.h"

/**
 * Structure AppWidgets - Contient les pointeurs vers les widgets d'entrée
 *
 * Cette structure est utilisée pour stocker les références des champs de
 * saisie (GtkEntry) afin d'y accéder facilement depuis les callbacks de
 * signaux (fonctions déclenchées par les clics boutons).
 */
typedef struct
{
    GtkWidget *entry_nom;       // Champ de saisie pour le nom
    GtkWidget *entry_prenom;    // Champ de saisie pour le prénom
    GtkWidget *entry_classe;    // Champ de saisie pour la classe
    GtkWidget *entry_matricule; // Champ de saisie pour le matricule
    GtkWidget *entry_email;     // Champ de saisie pour l'email
    GtkWidget *entry_sex;       // Champ de saisie pour le sexe
} AppWidgets;

/**
 * quand_btn_inserer_cliquer - Callback déclenché au clic sur le bouton "Insérer"
 * @button: pointeur vers le bouton qui a déclenché le signal
 * @user_data: pointeur vers la structure AppWidgets contenant les champs de saisie
 *
 * Description:
 *   Cette fonction est appelée quand l'utilisateur clique sur le bouton "Insérer".
 *   Elle effectue les opérations suivantes:
 *   1. Récupère les valeurs saisies dans les champs de texte
 *   2. Valide que les champs obligatoires (nom, prénom, matricule) ne sont pas vides
 *   3. Charge les étudiants existants depuis le fichier CSV
 *   4. Vérifie que le fichier n'est pas plein
 *   5. Trouve la position d'insertion (ordre alphabétique par nom)
 *   6. Insère le nouvel étudiant dans le tableau
 *   7. Sauvegarde les modifications dans le fichier CSV
 *   8. Affiche un message de confirmation ou d'erreur
 */
static void quand_btn_inserer_cliquer(GtkButton *button, gpointer user_data)
{
    // ========== CONVERSION DES POINTEURS ==========
    // Convertit le pointeur générique user_data en structure AppWidgets
    AppWidgets *widgets = (AppWidgets *)user_data;

    // ========== RÉCUPÉRATION DES VALEURS SAISIES ==========
    // Extrait les textes des champs d'entrée GTK
    const char *nom = gtk_entry_get_text(GTK_ENTRY(widgets->entry_nom));
    const char *prenom = gtk_entry_get_text(GTK_ENTRY(widgets->entry_prenom));
    const char *classe = gtk_entry_get_text(GTK_ENTRY(widgets->entry_classe));
    const char *matricule = gtk_entry_get_text(GTK_ENTRY(widgets->entry_matricule));
    const char *email = gtk_entry_get_text(GTK_ENTRY(widgets->entry_email));
    const char *sex = gtk_entry_get_text(GTK_ENTRY(widgets->entry_sex));

    // ========== VALIDATION DES CHAMPS OBLIGATOIRES ==========
    // Vérifie que les champs essentiels ne sont pas vides
    if (strlen(nom) == 0 || strlen(prenom) == 0 || strlen(matricule) == 0)
    {
        // Affiche une boîte de dialogue d'erreur
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Veuillez remplir tous les champs obligatoires (Nom, Prénom, Matricule)");

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return; // Retour sans insérer
    }

    // ========== CRÉATION DE LA STRUCTURE ETUDIANT ==========
    // Crée une nouvelle structure Etudiant et copie les données saisies
    Etudiant nouveau;
    safe_strncpy(nouveau.nom, nom, MAX_CHAMP);
    safe_strncpy(nouveau.prenom, prenom, MAX_CHAMP);
    safe_strncpy(nouveau.classe, classe, MAX_CHAMP);
    safe_strncpy(nouveau.email, email, MAX_CHAMP);
    safe_strncpy(nouveau.matricule, matricule, MAX_CHAMP);
    safe_strncpy(nouveau.sex, sex, MAX_CHAMP);

    // ========== CHARGEMENT DES ÉTUDIANTS EXISTANTS ==========
    // Lit le fichier CSV et remplit le tableau avec les étudiants existants
    Etudiant etudiants[MAX_STUD];
    int n = lire_csv(FILENAME, etudiants);

    // ========== VÉRIFICATION DE CAPACITÉ ==========
    // Vérifie que le fichier n'a pas atteint la limite de MAX_STUD
    if (n >= MAX_STUD)
    {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Limite d'étudiants atteinte (%d)", MAX_STUD);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // ========== RECHERCHE DE LA POSITION D'INSERTION ==========
    // Utilise une recherche binaire pour trouver où insérer le nouvel étudiant
    // (maintient l'ordre alphabétique par nom)
    int pos = cher_pos_ins(etudiants, n, nouveau.nom);

    // ========== DÉCALAGE ET INSERTION ==========
    // Décale les éléments à droite et insère le nouvel étudiant à sa position
    for (int i = n; i > pos; i--)
    {
        etudiants[i] = etudiants[i - 1];
    }

    // Insère le nouvel étudiant à la position correcte
    etudiants[pos] = nouveau;
    n++;

    // ========== SAUVEGARDE DANS LE FICHIER CSV ==========
    // Écrit tous les étudiants (incluant le nouvel) dans le fichier CSV
    if (vers_csv(FILENAME, etudiants, n))
    {
        // ========== SUCCÈS: NETTOYAGE DES CHAMPS ==========
        // Efface les champs d'entrée après l'insertion réussie
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_nom), "");
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_prenom), "");
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_classe), "");
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_matricule), "");
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_email), "");
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_sex), "");

        // Affiche un message de confirmation
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Étudiant(e) ajouté(e) avec succès !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    else
    {
        // ========== ERREUR: AFFICHAGE D'UN MESSAGE D'ERREUR ==========
        // Le fichier n'a pas pu être écrit (problème d'accès, disque plein, etc.)
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Erreur lors de l'écriture dans le fichier.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

/**
 * on_button_quit_clicked - Callback pour le bouton "Quitter"
 * @button: pointeur vers le bouton qui a déclenché le signal
 * @user_data: pointeur vers la fenêtre principale (GtkWindow)
 *
 * Description:
 *   Ferme la fenêtre principale et termine l'application.
 */
static void on_button_quit_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = GTK_WIDGET(user_data);
    gtk_window_close(GTK_WINDOW(window));
}

/**
 * load_css - Charge un fichier CSS pour personnaliser l'apparence
 *
 * Description:
 *   Charge le fichier "style.css" et l'applique au style global de GTK+.
 *   Si le fichier n'existe pas ou ne peut pas être chargé, l'application
 *   continue quand même (avec le style par défaut).
 */
static void load_css(void)
{
    // ========== INITIALISATION DES VARIABLES ==========
    GtkCssProvider *provider; // Fournisseur de styles CSS pour GTK
    GdkDisplay *display;      // Affichage/écran principal
    GdkScreen *screen;        // Écran sur lequel appliquer le style

    const gchar *css_file = "style.css";           // Chemin du fichier CSS
    GFile *css_fp = g_file_new_for_path(css_file); // Objet fichier GTK
    GError *error = 0;                             // Variable pour les erreurs éventuelles

    // ========== CRÉATION DU FOURNISSEUR CSS ==========
    // Crée un nouveau fournisseur de styles CSS
    provider = gtk_css_provider_new();

    // ========== RÉCUPÉRATION DE L'AFFICHAGE ==========
    // Obtient l'écran par défaut pour appliquer le style
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    // ========== APPLICATION DU STYLE ==========
    // Ajoute le fournisseur CSS à l'écran avec une priorité APPLICATION
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // ========== CHARGEMENT DU FICHIER CSS ==========
    // Charge le fichier CSS depuis le disque
    gtk_css_provider_load_from_file(provider, css_fp, &error);

    // Libère la mémoire du fournisseur
    g_object_unref(provider);
}

/**
 * main - Fonction principale: initialise et lance l'interface GTK+
 * @argc: nombre d'arguments en ligne de commande
 * @argv: tableau des arguments en ligne de commande
 *
 * Retour:
 *   0 en cas de succès, code d'erreur sinon
 *
 * Description:
 *   Cette fonction:
 *   1. Initialise GTK+
 *   2. Charge les styles CSS personnalisés
 *   3. Crée la fenêtre principale et ses widgets
 *   4. Configure les signaux et callbacks
 *   5. Affiche l'interface et entre la boucle d'événements GTK
 */
int main(int argc, char **argv)
{
    // ========== INITIALISATION GTK+ ==========
    // Initialise la bibliothèque GTK+ avec les arguments en ligne de commande
    gtk_init(&argc, &argv);

    // ========== CHARGEMENT DES STYLES ==========
    // Charge le fichier CSS pour personnaliser l'apparence
    load_css();

    // ========== ALLOCATION MÉMOIRE POUR LES WIDGETS ==========
    // Alloue la mémoire pour la structure contenant les pointeurs aux widgets
    AppWidgets *widgets = g_malloc(sizeof(AppWidgets));

    // ========== CRÉATION DE LA FENÊTRE PRINCIPALE ==========
    // Crée une nouvelle fenêtre GTK (fenêtre de niveau supérieur)
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Gestion Étudiants");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 350);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);             // Fenêtre non redimensionnable
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Centrer la fenêtre
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);       // Marges autour

    // ========== CRÉATION DE LA BOÎTE PRINCIPALE ==========
    // Crée une boîte verticale qui contiendra tous les éléments
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Crée un conteneur d'alignement pour les marges supplémentaires
    GtkWidget *alignment = gtk_alignment_new(0.5, 0.5, 0.9, 0.9);
    gtk_container_add(GTK_CONTAINER(alignment), vbox);
    gtk_container_add(GTK_CONTAINER(window), alignment);

    // ========== CRÉATION DE LA GRILLE POUR LES CHAMPS ==========
    // Crée une grille GTK pour organiser les labels et champs de saisie
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);     // Espacement entre les lignes
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10); // Espacement entre les colonnes
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    // ========== CRÉATION DES CHAMPS DE SAISIE ==========
    // Crée les labels et les champs d'entrée (GtkEntry) pour chaque information
    int row = 0;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Nom :"), 0, row, 1, 1);
    widgets->entry_nom = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_nom, 1, row, 1, 1);
    row++;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Prénom :"), 0, row, 1, 1);
    widgets->entry_prenom = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_prenom, 1, row, 1, 1);
    row++;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Classe :"), 0, row, 1, 1);
    widgets->entry_classe = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_classe, 1, row, 1, 1);
    row++;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Matricule :"), 0, row, 1, 1);
    widgets->entry_matricule = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_matricule, 1, row, 1, 1);
    row++;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Email :"), 0, row, 1, 1);
    widgets->entry_email = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_email, 1, row, 1, 1);
    row++;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Sexe :"), 0, row, 1, 1);
    widgets->entry_sex = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_sex, 1, row, 1, 1);
    row++;

    // ========== CRÉATION DES BOUTONS ==========
    // Crée une boîte horizontale pour les boutons Insérer et Quitter
    GtkWidget *button_box = gtk_box_new(TRUE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, FALSE, FALSE, 10);

    // Bouton "Insérer" pour ajouter un nouvel étudiant
    GtkWidget *insert_button = gtk_button_new_with_label("Insérer");
    gtk_widget_set_name(insert_button, "insert_button"); // Nom pour les styles CSS

    // Bouton "Quitter" pour fermer l'application
    GtkWidget *quit_button = gtk_button_new_with_label("Quitter");

    gtk_box_pack_start(GTK_BOX(button_box), insert_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box), quit_button, TRUE, TRUE, 0);

    // ========== CONNEXION DES SIGNAUX ==========
    // Connecte les signaux (événements) aux fonctions de rappel (callbacks)

    // Signal "clicked" du bouton Insérer -> appelle quand_btn_inserer_cliquer
    g_signal_connect(insert_button, "clicked", G_CALLBACK(quand_btn_inserer_cliquer), widgets);

    // Signal "clicked" du bouton Quitter -> appelle on_button_quit_clicked
    g_signal_connect(quit_button, "clicked", G_CALLBACK(on_button_quit_clicked), window);

    // Signal "destroy" de la fenêtre -> quitte la boucle d'événements GTK
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Signal pour libérer la mémoire allouée à widgets lors de la destruction de la fenêtre
    g_signal_connect_swapped(window, "destroy", G_CALLBACK(g_free), widgets);

    // ========== AFFICHAGE ET BOUCLE PRINCIPALE ==========
    // Affiche tous les widgets (récursivement)
    gtk_widget_show_all(window);

    // Lance la boucle d'événements GTK (bloquant jusqu'à fermeture)
    gtk_main();

    return 0;
}