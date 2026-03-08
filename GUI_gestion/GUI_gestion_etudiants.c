/**
 * ============================================================================
 * PROGRAMME DE GESTION DES ÉTUDIANTS (VERSION GRAPHIQUE GTK+)
 * ============================================================================
 *
 * Description:
 *   Application graphique GTK+ pour gérer une base d'étudiants stockée dans
 *   un fichier CSV. Permet:
 *   - Ajouter de nouveaux étudiants
 *   - Afficher tous les étudiants
 *   - Modifier un étudiant
 *   - Supprimer un étudiant
 *   - Rechercher un étudiant par nom
 *   - Trier les étudiants par nom ou classe
 *
 * Dépendances:
 *   - GTK+ 3.0 ou supérieur
 *   - Bibliothèques de gestion d'étudiants (fonctions.h, etudiant.h)
 * ============================================================================
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/fonctions.h"
#include "../libs/etudiant.h"

/* ============================================
 * DÉFINITIONS DES STRUCTURES
 * ============================================ */

/**
 * Structure AppWidgets - Contient les pointeurs vers tous les widgets
 */
typedef struct
{
    /* Fenêtre principale */
    GtkWidget *window;

    /* Notebook (onglets) */
    GtkWidget *notebook;

    /* Tab 1: Ajouter un étudiant */
    GtkWidget *entry_nom;
    GtkWidget *entry_prenom;
    GtkWidget *entry_classe;
    GtkWidget *entry_matricule;
    GtkWidget *entry_email;
    GtkWidget *entry_sex;
    GtkWidget *btn_ajouter;

    /* Tab 2: Afficher tous les étudiants */
    GtkWidget *tree_view;
    GtkListStore *list_store;

    /* Tab 3: Rechercher */
    GtkWidget *entry_recherche;
    GtkWidget *tree_view_recherche;
    GtkListStore *list_store_recherche;
    GtkWidget *btn_rechercher;

    /* Tab 4: Modifier/Supprimer */
    GtkWidget *entry_matricule_modif;
    GtkWidget *btn_rechercher_modif;
    GtkWidget *entry_nom_modif;
    GtkWidget *entry_prenom_modif;
    GtkWidget *entry_classe_modif;
    GtkWidget *entry_email_modif;
    GtkWidget *entry_sex_modif;
    GtkWidget *btn_modifier;
    GtkWidget *btn_supprimer;

    /* Status bar */
    GtkWidget *status_bar;
    guint status_context_id;
} AppWidgets;

/* ============================================
 * FONCTIONS UTILITAIRES
 * ============================================ */

/**
 * afficher_message - Affiche une boîte de dialogue
 */
static void afficher_message(GtkWindow *parent, GtkMessageType type, const char *message)
{
    GtkWidget *dialog = gtk_message_dialog_new(parent,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               type,
                                               GTK_BUTTONS_OK,
                                               "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/**
 * mettre_a_jour_status - Met à jour la barre de statut
 */
static void mettre_a_jour_status(AppWidgets *widgets, const char *message)
{
    gtk_statusbar_push(GTK_STATUSBAR(widgets->status_bar),
                       gtk_statusbar_get_context_id(GTK_STATUSBAR(widgets->status_bar), message),
                       message);
}

/**
 * charger_etudiants_dans_tree_view - Charge les étudiants dans un TreeView
 */
static void charger_etudiants_dans_tree_view(AppWidgets *widgets, GtkListStore *store, Etudiant etudiants[], int n)
{
    gtk_list_store_clear(store);

    for (int i = 0; i < n; i++)
    {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                          0, etudiants[i].nom,
                          1, etudiants[i].prenom,
                          2, etudiants[i].classe,
                          3, etudiants[i].email,
                          4, etudiants[i].matricule,
                          5, etudiants[i].sex,
                          -1);
    }
}

/* ============================================
 * CALLBACKS DES BOUTONS
 * ============================================ */

/**
 * Callback: Ajouter un étudiant
 */
static void on_btn_ajouter_clicked(GtkButton *button, gpointer user_data)
{
    AppWidgets *widgets = (AppWidgets *)user_data;

    const char *nom = gtk_entry_get_text(GTK_ENTRY(widgets->entry_nom));
    const char *prenom = gtk_entry_get_text(GTK_ENTRY(widgets->entry_prenom));
    const char *classe = gtk_entry_get_text(GTK_ENTRY(widgets->entry_classe));
    const char *matricule = gtk_entry_get_text(GTK_ENTRY(widgets->entry_matricule));
    const char *email = gtk_entry_get_text(GTK_ENTRY(widgets->entry_email));
    const char *sex = gtk_entry_get_text(GTK_ENTRY(widgets->entry_sex));

    /* Validation des champs obligatoires */
    if (strlen(nom) == 0 || strlen(prenom) == 0 || strlen(matricule) == 0)
    {
        afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_ERROR,
                        "Veuillez remplir tous les champs obligatoires (Nom, Prénom, Matricule)");
        return;
    }

    /* Chargement des étudiants existants */
    Etudiant etudiants[MAX_STUD];
    int n = lire_csv(FILENAME, etudiants);

    /* Vérification de capacité */
    if (n >= MAX_STUD)
    {
        afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_ERROR,
                        "Limite d'étudiants atteinte");
        return;
    }

    /* Vérification de doublon par matricule */
    for (int i = 0; i < n; i++)
    {
        if (compare_mots(etudiants[i].matricule, matricule) == 0)
        {
            afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_ERROR,
                            "Un étudiant avec ce matricule existe déjà");
            return;
        }
    }

    /* Création du nouvel étudiant */
    Etudiant nouveau;
    safe_strncpy(nouveau.nom, nom, MAX_CHAMP);
    safe_strncpy(nouveau.prenom, prenom, MAX_CHAMP);
    safe_strncpy(nouveau.classe, classe, MAX_CHAMP);
    safe_strncpy(nouveau.email, email, MAX_CHAMP);
    safe_strncpy(nouveau.matricule, matricule, MAX_CHAMP);
    safe_strncpy(nouveau.sex, sex, MAX_CHAMP);

    /* Insertion triée par nom */
    int pos = cher_pos_ins(etudiants, n, nouveau.nom);
    for (int i = n; i > pos; i--)
    {
        etudiants[i] = etudiants[i - 1];
    }
    etudiants[pos] = nouveau;
    n++;

    /* Sauvegarde */
    if (vers_csv(FILENAME, etudiants, n))
    {
        /* Nettoyage des champs */
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_nom), "");
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_prenom), "");
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_classe), "");
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_matricule), "");
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_email), "");
        gtk_entry_set_text(GTK_ENTRY(widgets->entry_sex), "");

        afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_INFO,
                        "Étudiant ajouté avec succès !");
        mettre_a_jour_status(widgets, "Étudiant ajouté avec succès");
    }
    else
    {
        afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_ERROR,
                        "Erreur lors de l'écriture dans le fichier");
    }
}

/**
 * Callback: Afficher tous les étudiants (raffraîchir)
 */
static void on_btn_afficher_clicked(GtkButton *button, gpointer user_data)
{
    AppWidgets *widgets = (AppWidgets *)user_data;

    Etudiant etudiants[MAX_STUD];
    int n = lire_csv(FILENAME, etudiants);

    charger_etudiants_dans_tree_view(widgets, widgets->list_store, etudiants, n);

    char message[256];
    snprintf(message, sizeof(message), "%d étudiant(s) chargé(s)", n);
    mettre_a_jour_status(widgets, message);
}

/**
 * Callback: Rechercher un étudiant
 */
static void on_btn_rechercher_clicked(GtkButton *button, gpointer user_data)
{
    AppWidgets *widgets = (AppWidgets *)user_data;

    const char *nom = gtk_entry_get_text(GTK_ENTRY(widgets->entry_recherche));

    if (strlen(nom) == 0)
    {
        afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_WARNING,
                        "Veuillez entrer un nom à rechercher");
        return;
    }

    /* Chargement de tous les étudiants */
    Etudiant etudiants[MAX_STUD];
    int n = lire_csv(FILENAME, etudiants);

    /* Recherche */
    gtk_list_store_clear(widgets->list_store_recherche);
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (contient_sous_chaine(etudiants[i].nom, nom) ||strstr(etudiants[i].nom, nom) != NULL ||
            strstr(nom, etudiants[i].nom) != NULL ||
            compare_mots(etudiants[i].nom, nom) == 0)
        {
            GtkTreeIter iter;
            gtk_list_store_append(widgets->list_store_recherche, &iter);
            gtk_list_store_set(widgets->list_store_recherche, &iter,
                              0, etudiants[i].nom,
                              1, etudiants[i].prenom,
                              2, etudiants[i].classe,
                              3, etudiants[i].email,
                              4, etudiants[i].matricule,
                              5, etudiants[i].sex,
                              -1);
            count++;
        }
    }

    char message[256];
    snprintf(message, sizeof(message), "%d résultat(s) trouvé(s)", count);
    mettre_a_jour_status(widgets, message);
}

/**
 * Callback: Rechercher pour modification
 */
static void on_btn_rechercher_modif_clicked(GtkButton *button, gpointer user_data)
{
    AppWidgets *widgets = (AppWidgets *)user_data;

    const char *matricule = gtk_entry_get_text(GTK_ENTRY(widgets->entry_matricule_modif));

    if (strlen(matricule) == 0)
    {
        afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_WARNING,
                        "Veuillez entrer un matricule");
        return;
    }

    /* Chargement des étudiants */
    Etudiant etudiants[MAX_STUD];
    int n = lire_csv(FILENAME, etudiants);

    /* Recherche par matricule */
    for (int i = 0; i < n; i++)
    {
        if (compare_mots(etudiants[i].matricule, matricule) == 0)
        {
            /* Remplir les champs */
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_nom_modif), etudiants[i].nom);
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_prenom_modif), etudiants[i].prenom);
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_classe_modif), etudiants[i].classe);
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_email_modif), etudiants[i].email);
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_sex_modif), etudiants[i].sex);

            mettre_a_jour_status(widgets, "Étudiant trouvé");
            return;
        }
    }

    /* Non trouvé */
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_nom_modif), "");
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_prenom_modif), "");
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_classe_modif), "");
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_email_modif), "");
    gtk_entry_set_text(GTK_ENTRY(widgets->entry_sex_modif), "");

    afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_WARNING,
                    "Aucun étudiant trouvé avec ce matricule");
}

/**
 * Callback: Modifier un étudiant
 */
static void on_btn_modifier_clicked(GtkButton *button, gpointer user_data)
{
    AppWidgets *widgets = (AppWidgets *)user_data;

    const char *matricule = gtk_entry_get_text(GTK_ENTRY(widgets->entry_matricule_modif));
    const char *nom = gtk_entry_get_text(GTK_ENTRY(widgets->entry_nom_modif));
    const char *prenom = gtk_entry_get_text(GTK_ENTRY(widgets->entry_prenom_modif));

    if (strlen(matricule) == 0 || strlen(nom) == 0 || strlen(prenom) == 0)
    {
        afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_ERROR,
                        "Le matricule, le nom et le prénom sont obligatoires");
        return;
    }

    /* Chargement des étudiants */
    Etudiant etudiants[MAX_STUD];
    int n = lire_csv(FILENAME, etudiants);

    /* Recherche et modification */
    for (int i = 0; i < n; i++)
    {
        if (compare_mots(etudiants[i].matricule, matricule) == 0)
        {
            safe_strncpy(etudiants[i].nom, nom, MAX_CHAMP);
            safe_strncpy(etudiants[i].prenom, prenom, MAX_CHAMP);
            safe_strncpy(etudiants[i].classe,
                        gtk_entry_get_text(GTK_ENTRY(widgets->entry_classe_modif)), MAX_CHAMP);
            safe_strncpy(etudiants[i].email,
                        gtk_entry_get_text(GTK_ENTRY(widgets->entry_email_modif)), MAX_CHAMP);
            safe_strncpy(etudiants[i].sex,
                        gtk_entry_get_text(GTK_ENTRY(widgets->entry_sex_modif)), MAX_CHAMP);

            /* Sauvegarde */
            if (vers_csv(FILENAME, etudiants, n))
            {
                afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_INFO,
                                "Étudiant modifié avec succès !");
                mettre_a_jour_status(widgets, "Étudiant modifié");

                /* Nettoyage */
                gtk_entry_set_text(GTK_ENTRY(widgets->entry_matricule_modif), "");
                gtk_entry_set_text(GTK_ENTRY(widgets->entry_nom_modif), "");
                gtk_entry_set_text(GTK_ENTRY(widgets->entry_prenom_modif), "");
                gtk_entry_set_text(GTK_ENTRY(widgets->entry_classe_modif), "");
                gtk_entry_set_text(GTK_ENTRY(widgets->entry_email_modif), "");
                gtk_entry_set_text(GTK_ENTRY(widgets->entry_sex_modif), "");
            }
            else
            {
                afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_ERROR,
                                "Erreur lors de la sauvegarde");
            }
            return;
        }
    }

    afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_WARNING,
                    "Étudiant non trouvé");
}

/**
 * Callback: Supprimer un étudiant
 */
static void on_btn_supprimer_clicked(GtkButton *button, gpointer user_data)
{
    AppWidgets *widgets = (AppWidgets *)user_data;

    const char *matricule = gtk_entry_get_text(GTK_ENTRY(widgets->entry_matricule_modif));

    if (strlen(matricule) == 0)
    {
        afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_WARNING,
                        "Veuillez entrer un matricule à supprimer");
        return;
    }

    /* Chargement des étudiants */
    Etudiant etudiants[MAX_STUD];
    int n = lire_csv(FILENAME, etudiants);

    /* Recherche */
    int pos = -1;
    for (int i = 0; i < n; i++)
    {
        if (compare_mots(etudiants[i].matricule, matricule) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_WARNING,
                        "Aucun étudiant trouvé avec ce matricule");
        return;
    }

    /* Confirmation */
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(widgets->window),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_QUESTION,
                                               GTK_BUTTONS_YES_NO,
                                               "Voulez-vous vraiment supprimer l'étudiant %s %s ?",
                                               etudiants[pos].nom, etudiants[pos].prenom);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    if (response == GTK_RESPONSE_YES)
    {
        /* Suppression (décalage) */
        for (int i = pos; i < n - 1; i++)
        {
            etudiants[i] = etudiants[i + 1];
        }
        n--;

        /* Sauvegarde */
        if (vers_csv(FILENAME, etudiants, n))
        {
            /* Nettoyage */
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_matricule_modif), "");
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_nom_modif), "");
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_prenom_modif), "");
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_classe_modif), "");
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_email_modif), "");
            gtk_entry_set_text(GTK_ENTRY(widgets->entry_sex_modif), "");

            afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_INFO,
                            "Étudiant supprimé avec succès !");
            mettre_a_jour_status(widgets, "Étudiant supprimé");
        }
        else
        {
            afficher_message(GTK_WINDOW(widgets->window), GTK_MESSAGE_ERROR,
                            "Erreur lors de la sauvegarde");
        }
    }
}

/**
 * Callback: Quitter l'application
 */
static void on_btn_quit_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = GTK_WIDGET(user_data);
    gtk_window_close(GTK_WINDOW(window));
}

/* ============================================
 * CRÉATION DE L'INTERFACE
 * ============================================ */

/**
 * creer_colonnes - Crée les colonnes pour le TreeView
 */
static void creer_colonnes(GtkTreeView *tree_view)
{
    GtkCellRendererText *renderer;
    GtkTreeViewColumn *column;

    /* Nom */
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(tree_view, column);

    /* Prénom */
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(tree_view, column);

    /* Classe */
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Classe", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(tree_view, column);

    /* Email */
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(tree_view, column);

    /* Matricule */
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Matricule", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(tree_view, column);

    /* Sexe */
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(tree_view, column);
}

/**
 * creer_tab_ajouter - Crée l'onglet "Ajouter un étudiant"
 */
static GtkWidget *creer_tab_ajouter(AppWidgets *widgets)
{
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    /* Titre */
    GtkWidget *label_titre = gtk_label_new("<span size='16' weight='bold'>Ajouter un étudiant</span>");
    gtk_label_set_use_markup(GTK_LABEL(label_titre), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), label_titre, FALSE, FALSE, 10);

    /* Grille pour les champs */
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    int row = 0;

    /* Nom */
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Nom *:"), 0, row, 1, 1);
    widgets->entry_nom = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_nom, 1, row, 1, 1);
    row++;

    /* Prénom */
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Prénom *:"), 0, row, 1, 1);
    widgets->entry_prenom = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_prenom, 1, row, 1, 1);
    row++;

    /* Classe */
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Classe:"), 0, row, 1, 1);
    widgets->entry_classe = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_classe, 1, row, 1, 1);
    row++;

    /* Matricule */
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Matricule *:"), 0, row, 1, 1);
    widgets->entry_matricule = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_matricule, 1, row, 1, 1);
    row++;

    /* Email */
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Email:"), 0, row, 1, 1);
    widgets->entry_email = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_email, 1, row, 1, 1);
    row++;

    /* Sexe */
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Sexe:"), 0, row, 1, 1);
    widgets->entry_sex = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_sex, 1, row, 1, 1);
    row++;

    /* Note */
    GtkWidget *note = gtk_label_new("* Champs obligatoires");
    gtk_box_pack_start(GTK_BOX(vbox), note, FALSE, FALSE, 5);

    /* Bouton Ajouter */
    widgets->btn_ajouter = gtk_button_new_with_label("Ajouter l'étudiant");
    gtk_widget_set_name(widgets->btn_ajouter, "btn_ajouter");
    gtk_box_pack_start(GTK_BOX(vbox), widgets->btn_ajouter, FALSE, FALSE, 10);

    return vbox;
}

/**
 * creer_tab_afficher - Crée l'onglet "Afficher tous les étudiants"
 */
static GtkWidget *creer_tab_afficher(AppWidgets *widgets)
{
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    /* Titre */
    GtkWidget *label_titre = gtk_label_new("<span size='16' weight='bold'>Liste des étudiants</span>");
    gtk_label_set_use_markup(GTK_LABEL(label_titre), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), label_titre, FALSE, FALSE, 10);

    /* Bouton Rafraîchir */
    GtkWidget *btn_rafraichir = gtk_button_new_with_label("Rafraîchir");
    gtk_box_pack_start(GTK_BOX(vbox), btn_rafraichir, FALSE, FALSE, 5);

    /* Scroll Window */
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);

    /* TreeView */
    widgets->list_store = gtk_list_store_new(6, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                              G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    widgets->tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(widgets->list_store));
    gtk_container_add(GTK_CONTAINER(scrolled), widgets->tree_view);

    /* Créer les colonnes */
    creer_colonnes(GTK_TREE_VIEW(widgets->tree_view));

    return vbox;
}

/**
 * creer_tab_rechercher - Crée l'onglet "Rechercher"
 */
static GtkWidget *creer_tab_rechercher(AppWidgets *widgets)
{
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    /* Titre */
    GtkWidget *label_titre = gtk_label_new("<span size='16' weight='bold'>Rechercher un étudiant</span>");
    gtk_label_set_use_markup(GTK_LABEL(label_titre), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), label_titre, FALSE, FALSE, 10);

    /* Zone de recherche */
    GtkWidget *hbox_recherche = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_recherche, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(hbox_recherche), gtk_label_new("Nom à rechercher:"), FALSE, FALSE, 5);
    widgets->entry_recherche = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_recherche), "Entrez un nom...");
    gtk_box_pack_start(GTK_BOX(hbox_recherche), widgets->entry_recherche, TRUE, TRUE, 5);

    widgets->btn_rechercher = gtk_button_new_with_label("Rechercher");
    gtk_box_pack_start(GTK_BOX(hbox_recherche), widgets->btn_rechercher, FALSE, FALSE, 5);

    /* Scroll Window */
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);

    /* TreeView */
    widgets->list_store_recherche = gtk_list_store_new(6, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                                       G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    widgets->tree_view_recherche = gtk_tree_view_new_with_model(GTK_TREE_MODEL(widgets->list_store_recherche));
    gtk_container_add(GTK_CONTAINER(scrolled), widgets->tree_view_recherche);

    /* Créer les colonnes */
    creer_colonnes(GTK_TREE_VIEW(widgets->tree_view_recherche));

    return vbox;
}

/**
 * creer_tab_modifier - Crée l'onglet "Modifier/Supprimer"
 */
static GtkWidget *creer_tab_modifier(AppWidgets *widgets)
{
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    /* Titre */
    GtkWidget *label_titre = gtk_label_new("<span size='16' weight='bold'>Modifier / Supprimer</span>");
    gtk_label_set_use_markup(GTK_LABEL(label_titre), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), label_titre, FALSE, FALSE, 10);

    /* Recherche par matricule */
    GtkWidget *hbox_recherche = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_recherche, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(hbox_recherche), gtk_label_new("Matricule:"), FALSE, FALSE, 5);
    widgets->entry_matricule_modif = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry_matricule_modif), "Entrez le matricule...");
    gtk_box_pack_start(GTK_BOX(hbox_recherche), widgets->entry_matricule_modif, TRUE, TRUE, 5);

    widgets->btn_rechercher_modif = gtk_button_new_with_label("Rechercher");
    gtk_box_pack_start(GTK_BOX(hbox_recherche), widgets->btn_rechercher_modif, FALSE, FALSE, 5);

    /* Séparateur */
    gtk_box_pack_start(GTK_BOX(vbox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL), FALSE, FALSE, 10);

    /* Formulaire de modification */
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    int row = 0;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Nom:"), 0, row, 1, 1);
    widgets->entry_nom_modif = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_nom_modif, 1, row, 1, 1);
    row++;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Prénom:"), 0, row, 1, 1);
    widgets->entry_prenom_modif = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_prenom_modif, 1, row, 1, 1);
    row++;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Classe:"), 0, row, 1, 1);
    widgets->entry_classe_modif = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_classe_modif, 1, row, 1, 1);
    row++;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Email:"), 0, row, 1, 1);
    widgets->entry_email_modif = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_email_modif, 1, row, 1, 1);
    row++;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Sexe:"), 0, row, 1, 1);
    widgets->entry_sex_modif = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), widgets->entry_sex_modif, 1, row, 1, 1);
    row++;

    /* Boutons */
    GtkWidget *hbox_boutons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_boutons, FALSE, FALSE, 10);

    widgets->btn_modifier = gtk_button_new_with_label("Modifier");
    gtk_widget_set_name(widgets->btn_modifier, "btn_modifier");
    gtk_box_pack_start(GTK_BOX(hbox_boutons), widgets->btn_modifier, TRUE, TRUE, 0);

    widgets->btn_supprimer = gtk_button_new_with_label("Supprimer");
    gtk_widget_set_name(widgets->btn_supprimer, "btn_supprimer");
    gtk_box_pack_start(GTK_BOX(hbox_boutons), widgets->btn_supprimer, TRUE, TRUE, 0);

    return vbox;
}

/**
 * load_css - Charge un fichier CSS pour personnaliser l'apparence
 */
static void load_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    /* Essayer de charger le fichier CSS */
    GFile *css_fp = g_file_new_for_path("style.css");
    GError *error = 0;
    gtk_css_provider_load_from_file(provider, css_fp, &error);
    g_object_unref(provider);
}

/* ============================================
 * FONCTION PRINCIPALE
 * ============================================ */

int main(int argc, char **argv)
{
    /* Initialisation GTK+ */
    gtk_init(&argc, &argv);
    load_css();

    /* Allocation des widgets */
    AppWidgets *widgets = g_malloc(sizeof(AppWidgets));

    /* Fenêtre principale */
    widgets->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(widgets->window), "Gestion des Étudiants");
    gtk_window_set_default_size(GTK_WINDOW(widgets->window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(widgets->window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(widgets->window), 0);

    /* Boîte principale */
    GtkWidget *vbox_main = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(widgets->window), vbox_main);

    /* En-tête avec boutons Quitter */
    GtkWidget *header_bar = gtk_header_bar_new();
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Gestion des Étudiants");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(widgets->window), header_bar);

    GtkWidget *btn_quit = gtk_button_new_with_label("Quitter");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header_bar), btn_quit);

    /* Notebook (onglets) */
    widgets->notebook = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(vbox_main), widgets->notebook, TRUE, TRUE, 0);

    /* Tab 1: Ajouter */
    GtkWidget *tab_ajouter = creer_tab_ajouter(widgets);
    gtk_notebook_append_page(GTK_NOTEBOOK(widgets->notebook), tab_ajouter,
                            gtk_label_new("Ajouter"));

    /* Tab 2: Afficher */
    GtkWidget *tab_afficher = creer_tab_afficher(widgets);
    gtk_notebook_append_page(GTK_NOTEBOOK(widgets->notebook), tab_afficher,
                            gtk_label_new("Afficher tout"));

    /* Tab 3: Rechercher */
    GtkWidget *tab_rechercher = creer_tab_rechercher(widgets);
    gtk_notebook_append_page(GTK_NOTEBOOK(widgets->notebook), tab_rechercher,
                            gtk_label_new("Rechercher"));

    /* Tab 4: Modifier/Supprimer */
    GtkWidget *tab_modifier = creer_tab_modifier(widgets);
    gtk_notebook_append_page(GTK_NOTEBOOK(widgets->notebook), tab_modifier,
                            gtk_label_new("Modifier/Supprimer"));

    /* Status bar */
    widgets->status_bar = gtk_statusbar_new();
    widgets->status_context_id = 0;
    gtk_box_pack_start(GTK_BOX(vbox_main), widgets->status_bar, FALSE, FALSE, 0);

    /* Créer le bouton rafraichir et le stocker temporairement */
    GtkWidget *btn_rafraichir = gtk_button_new_with_label("Rafraîchir");

    /* Connexion des signaux */
    g_signal_connect(widgets->btn_ajouter, "clicked",
                   G_CALLBACK(on_btn_ajouter_clicked), widgets);

    g_signal_connect(btn_rafraichir, "clicked",
                   G_CALLBACK(on_btn_afficher_clicked), widgets);

    g_signal_connect(widgets->btn_rechercher, "clicked",
                   G_CALLBACK(on_btn_rechercher_clicked), widgets);

    g_signal_connect(widgets->btn_rechercher_modif, "clicked",
                   G_CALLBACK(on_btn_rechercher_modif_clicked), widgets);

    g_signal_connect(widgets->btn_modifier, "clicked",
                   G_CALLBACK(on_btn_modifier_clicked), widgets);

    g_signal_connect(widgets->btn_supprimer, "clicked",
                   G_CALLBACK(on_btn_supprimer_clicked), widgets);

    g_signal_connect(btn_quit, "clicked",
                   G_CALLBACK(on_btn_quit_clicked), widgets->window);

    g_signal_connect(widgets->window, "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect_swapped(widgets->window, "destroy",
                           G_CALLBACK(g_free), widgets);

    /* Affichage et boucle principale */
    gtk_widget_show_all(widgets->window);

    /* Charger les étudiants au démarrage */
    on_btn_afficher_clicked(NULL, widgets);

    gtk_main();

    return 0;
}

