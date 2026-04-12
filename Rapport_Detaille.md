# RAPPORT DÉTAILLÉ
## Système de Gestion des Étudiants - USTM

---

# Plan

1. [Introduction et Contexte](#1-introduction-et-contexte)
2. [Problématique et Objectifs](#2-problématique-et-objectifs)
3. [Concept et Définition](#3-concept-et-définition)
4. [Architecture du Projet](#4-architecture-du-projet)
5. [Structure de Données](#5-structure-de-données)
6. [Algorithmes Implémentés](#6-algorithmes-implémentés)
7. [Implémentation Technique](#7-implémentation-technique)
8. [Format des Données CSV](#8-format-des-données-csv)
9. [Guide d'Utilisation](#9-guide-dutilisation)
10. [Applications au Contexte Gabonais](#10-applications-au-contexte-gabonais)
11. [Conclusion et Perspectives](#11-conclusion-et-perspectives)

---

# 1. Introduction et Contexte

## 1.1 Présentation de l'Institution

L'**USTM** (Université des Sciences et Techniques de Masuku) est une université publique située à Franceville, au Gabon. Elle fait partie des établissements supérieurs majeurs du pays et forme des étudiants dans diverses disciplines scientifiques et techniques.

## 1.2 Contexte Académique

Ce projet s'inscrit dans le cadre du cours de **Programmation Avancée** du semestre **S1** de la formation **DUT2-GRT** (Diplôme Universitaire de Technologie - Génie Réseaux et Télécommunications).

## 1.3 Nature du Projet

Il s'agit d'un **projet académique** visant à développer une application de gestion des étudiants en langage **C**, permettant de gérer une base de données d'étudiants stockée dans un fichier CSV.

---

# 2. Problématique et Objectifs

## 2.1 Problématique

La recherche d'informations est très utile dans de nombreux domaines. Les archives peuvent être :
- **Papier** : Documents physiques, dossiers administratifs
- **Numérique** : Fichiers informatiques, bases de données

Lors de la recherche d'information, le temps alloué à cette tâche peut être :
- **Dérisoire** : Recherche rapide et efficace
- **Extrêmement complexe** : Volumes importants de données

**Le défi principal** : L'insertion de l'information au bon endroit est un autre challenge de taille, surtout quand les données sont numériques.

## 2.2 Problème Spécifique

Le projet consiste à développer un programme C qui :
1. Insérera au bon endroit les informations d'un(e) étudiant(e)
2. Un fichier au format `.csv` regroupera tou(te)s les étudiant(e)s
3. Sur chaque nouvelle ligne seront indiquées les données de chaque étudiant(e)
4. Lorsque la secrétaire voudra insérer un(e) nouvel(le) étudiant(e), le programme cherchera dans le fichier CSV
5. Si l'étudiant est inexistant, on l'insérera au bon endroit, suivant l'**ordre alphabétique croissant des noms**
6. S'il existe, on dira que l'étudiant est déjà présent, avant de quitter le programme

## 2.3 Objectifs

| Objectif | Description |
|----------|-------------|
| Maintenir l'ordre alphabétique | Insertion automatique triée par nom |
| Vérifier l'unicité | Détection des doublons par matricule |
| Gérer les données persistantes | Stockage dans un fichier CSV |
| Offrir deux interfaces | Version Console et Version Graphique (GTK+) |

---

# 3. Concept et Définition

## 3.1 Définition du Concept

Le **concept choisi** est un **Système de Gestion des Étudiants (SGE)** - une application qui permet de :

- **Créer** : Ajouter de nouveaux étudiants avec vérification automatique
- **Lire** : Afficher et rechercher des étudiants
- **Mettre à jour** : Modifier les informations d'un étudiant
- **Supprimer** : Retirer un étudiant de la base de données

## 3.2 Caractéristiques Principales

### Insertion Triée Automatique

L'innovation principale réside dans l'**insertion automatique triée** :
- Le programme trouve automatiquement la position correcte d'insertion
- Les étudiants sont classés par ordre alphabétique des noms
- Aucune manipulation manuelle du fichier n'est nécessaire

### Gestion des Doublons

- Chaque étudiant possède un **matricule unique**
- Le programme vérifie l'unicité avant toute insertion
- Si le matricule existe déjà, l'opération est refusée

## 3.3 Données Gérées

Chaque étudiant possède les champs suivants :

| Champ | Type | Description | Obligatoire |
|-------|------|-------------|-------------|
| Nom | Texte (max 128) | Nom de famille | Oui |
| Prénom | Texte (max 128) | Prénom | Oui |
| Classe | Texte (max 128) | Niveau/filière | Non |
| Email | Texte (max 128) | Adresse email | Non |
| Matricule | Texte (max 128) | Identifiant unique | Oui |
| Sexe | Texte (max 128) | Genre (M/F) | Non |

---

# 4. Architecture du Projet

## 4.1 Structure des Fichiers

```
gestion_etudiants/
│
├── CMD_gestion/                    # Version Console
│   └── CMD_gestion_etudiants.c     # Programme principal
│
├── GUI_gestion/                    # Version Graphique
│   ├── GUI_gestion_etudiants.c    # Programme principal GTK+
│   └── style.css                  # Styles CSS
│
├── functions/                      # Fonctions partagées
│   ├── fonctions.c                 # Fonctions utilitaires
│   ├── etudiant.c                 # Saisie/affichage
│   └── banner.c                   # Messages d'accueil
│
├── libs/                           # Bibliothèques (headers)
│   ├── fonctions.h                 # Déclarations
│   ├── etudiant.h                 # Structure Etudiant
│   ├── couleurs.h                 # Codes ANSI couleurs
│   └── banner.h                   # Déclarations bannières
│
├── data/                           # Données
│   └── Etudiants.csv               # Base de données
│
├── makefile                        # Script de compilation
├── README.md                       # Documentation
└── help.txt                       # Guide d'utilisation
```

## 4.2 Architecture en Couches

```
┌─────────────────────────────────────────┐
│         Interface Utilisateur           │
│      (CMD Console / GUI GTK+ 3.0)       │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│              Logique Métier             │
│  (Insertion, Recherche, Tri, Suppression)│
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│           Gestion des Données           │
│       (Lecture/Écriture CSV, Parsing)   │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│            Structure de Données          │
│          (Tableau d'Étudiants)          │
└─────────────────────────────────────────┘
```

## 4.3 Modularité

Le projet suit le principe de la **programmation modulaire** :
- Séparation du code en plusieurs fichiers (.c/.h)
- Réutilisation des fonctions communes
- Makefile pour gérer les dépendances

---

# 5. Structure de Données

## 5.1 Structure Etudiant

```c
typedef struct
{
    char nom[MAX_CHAMP];      // Nom de l'étudiant
    char prenom[MAX_CHAMP];   // Prénom de l'étudiant
    char classe[MAX_CHAMP];  // Classe/Niveau
    char matricule[MAX_CHAMP];// Identifiant unique
    char email[MAX_CHAMP];    // Adresse email
    char sex[MAX_CHAMP];      // Sexe/Genre
} Etudiant;
```

## 5.2 Constantes Défines

| Constante | Valeur | Description |
|-----------|--------|-------------|
| `MAX_STUD` | 1000 | Nombre maximum d'étudiants |
| `MAX_CHAMP` | 128 | Longueur maximale d'un champ |
| `MAX_LIGNE` | 512 | Longueur maximale d'une ligne CSV |
| `FILENAME` | "data/Etudiants.csv" | Chemin du fichier de données |

## 5.3 Tableau d'Étudiants

Les étudiants sont stockés dans un tableau statique :

```c
Etudiant etudiants[MAX_STUD];
int nombre_etudiants = 0;
```

---

# 6. Algorithmes Implémentés

## 6.1 Recherche Binaire pour l'Insertion

### Fonction : `cher_pos_ins()`

**Objectif** : Trouver la position d'insertion optimale pour maintenir le tri alphabétique par nom.

**Complexité** : **O(log n)** - très efficace même pour de grandes quantités d'étudiants.

### Pseudocode

```
chercher_position(tableau, n, nom):
    debut = 0
    fin = n - 1
    position = n
    
    tant que debut <= fin:
        milieu = (debut + fin) / 2
        
        si tableau[milieu].nom == nom:
            return milieu
        sinon si tableau[milieu].nom < nom:
            debut = milieu + 1
            position = debut
        sinon:
            fin = milieu - 1
            position = milieu
    
    return position
```

### Exemple d'Exécution

```
Tableau initial (trié par nom):
["Dupont", "Martin", "Nguema", "Obame"]

Insertion de "Biyiti":
- Comparaison avec "Martin" (milieu) → "B" < "M" → droite
- Comparaison avec "Dupont" → "B" < "D" → droite  
- Position d'insertion: 0

Résultat:
["Biyiti", "Dupont", "Martin", "Nguema", "Obame"]
```

## 6.2 Détection de Doublons

### Fonction : Vérification du matricule

**Objectif** : Vérifier que le matricule n'existe pas déjà.

**Complexité** : **O(n)** - parcours linéaire du tableau.

```c
for (int i = 0; i < n; i++)
{
    if (compare_mots(tableau[i].matricule, etudiant.matricule) == 0)
    {
        // Doublon détecté !
        return -1;
    }
}
```

## 6.3 Insertion avec Décalage

### Fonction : Insertion dans le tableau

**Objectif** : Insérer le nouvel étudiant à la position trouvée.

**Complexité** : **O(n)** dans le pire des cas (décalage de tous les éléments).

```c
// Décalage des éléments vers la droite
for (int i = n; i > position; i--)
{
    tableau[i] = tableau[i - 1];
}

// Insertion du nouvel étudiant
tableau[position] = nouvel_etudiant;
n++; // Incrémenter le compteur
```

## 6.4 Parsing CSV avec Guillemets

### Fonction : `parse_csv_line()`

Le programme gère correctement :
- Champs simples : `nom;prenom;classe`
- Champs cités avec séparateurs : `"Nom;Particule";prenom;classe`
- Guillemets échappés : `"Nom ""Surnom""";prenom`

### Exemple de Parsing

```
Ligne CSV: Dupont;Jean;L1 Info;jean.dupont@ustm.fr;MAT001;M

Résultat:
- nom: "Dupont"
- prenom: "Jean"
- classe: "L1 Info"
- email: "jean.dupont@ustm.fr"
- matricule: "MAT001"
- sex: "M"
```

---

# 7. Implémentation Technique

## 7.1 Technologies Utilisées

| Technologie | Description |
|-------------|-------------|
| **Langage** | C (Standard C99) |
| **Compilateur** | GCC (GNU Compiler Collection) |
| **Interface Console** | ANSI Colors (codes d'échappement) |
| **Interface Graphique** | GTK+ 3.0 |
| **Outil de build** | Makefile |

## 7.2 Version Console (CMD)

### Caractéristiques

- Interface en ligne de commande
- Support des couleurs ANSI
- Menu interactif numéroté
- Messages de confirmation/erreur

### Menu Principal

```
================================================================================
==                                                                            ==
==                   GESTION DES ÉTUDIANTS - USTM                             ==
==                                                                            ==
================================================================================

                        Nombre d'étudiants: X

                        1. Ajouter un étudiant
                        2. Afficher tous les étudiants
                        3. Rechercher par nom
                        4. Modifier un étudiant
                        5. Supprimer un étudiant
                        6. Trier les étudiants
                        0. Quitter

                        Votre choix :
```

## 7.3 Version Graphique (GUI)

### Bibliothèques GTK+ Utilisées

- `gtk/gtk.h` : Noyau GTK+
- `gdk/gdk.h` : Abstraction graphique
- `glib/glib.h` : Structures de données

### Composants de l'Interface

| Composant | Description |
|-----------|-------------|
| Champs de saisie | Nom, Prénom, Classe, Email, Matricule, Sexe |
| Boutons | Insérer, Afficher, Rechercher, Modifier, Supprimer, Trier, Quitter |
| TreeView | Affichage tabulaire des étudiants |

---

# 8. Format des Données CSV

## 8.1 Structure du Fichier

**Emplacement** : `data/Etudiants.csv`

**Délimiteur** : `;` (point-virgule)

## 8.2 Exemple de Contenu

```csv
nom;prenom;classe;email;matricule;sex
Dupont;Jean;L1 Info;jean.dupont@etud.ustm.fr;MAT2024001;M
Martin;Marie;L2 Info;marie.martin@etud.ustm.fr;MAT2024002;F
Nguema;Paul;L3 Tech;paul.nguema@etud.ustm.fr;MAT2024003;M
Obame;Claire;L1 Info;claire.obame@etud.ustm.fr;MAT2024004;F
```

## 8.3 Caractères Spéciaux

| Caractère dans les données | Représentation CSV |
|---------------------------|-------------------|
| Point-virgule `;` | `"Nom;Particule"` |
| Guillemet double `"` | `""` (doublé) |

---

# 9. Guide d'Utilisation

## 9.1 Compilation

### Avec Makefile (Recommandé)

```bash
# Compiler les deux versions
make all

# Compiler uniquement la version console
make cmd

# Compiler uniquement la version GUI
make gui

# Nettoyer les fichiers compilés
make clean
```

### Compilation Manuelle

#### Version Console

```bash
gcc -Wall -Wextra -std=c99 -I./libs \
    CMD_gestion/CMD_gestion_etudiants.c \
    functions/etudiant.c \
    functions/fonctions.c \
    functions/banner.c \
    -o cmd_gestion_etudiants
```

#### Version GUI

```bash
gcc -Wall -Wextra -std=c99 -I./libs \
    GUI_gestion/GUI_gestion_etudiants.c \
    functions/fonctions.c \
    functions/banner.c \
    `pkg-config --cflags gtk+-3.0` \
    `pkg-config --libs gtk+-3.0` \
    -o gui_gestion_etudiants
```

## 9.2 Exécution

### Version Console

```bash
./cmd_gestion_etudiants
```

### Version GUI

```bash
./gui_gestion_etudiants
```

---

# 10. Applications au Contexte Gabonais

## 10.1 Problématiques Locales

Au Gabon, comme dans de nombreux pays africains, les institutions éducatives font face à :

1. **Gestion administrative complexe**
   - Volumes importants d'étudiants
   - Multiples filières et niveaux
   - Turn-over du personnel

2. **Archives souvent mixtes**
   - Documents papier anciens
   - Migration vers le numérique
   - Besoin de centralisation

3. **Ressources limitées**
   - Connectivité internet variable
   - Besoin d'applications légères
   - Coût des licences logicielles

## 10.2 Solutions Proposées

### Pour les Universités (USTM, UOB, etc.)

| Application | Bénéfice |
|-------------|----------|
| Gestion des inscriptions | Insertion automatique triée, gain de temps |
| Suivi des étudiants par classe | Recherche rapide, modification aisée |
| Exportation des données | Compatibilité CSV avec tableurs |

### Pour les Établissements Scolaires

| Application | Bénéfice |
|-------------|----------|
| Gestion des élèves | Duplication du système pour les lycées/collèges |
| Archives numériques | Transition papier → numérique |
| Listes de classe | Tri automatique, recherche par nom |

## 10.3 Adaptation aux Besoins Gabonais

### Avantages du Système

1. **Léger et gratuit** : Pas de coût de licence, fonctionne sur PC modeste
2. **Open Source** : Code modifiable selon les besoins
3. **Format standard** : CSV compatible avec Excel, LibreOffice
4. **Double interface** : Console (peu de ressources) ou GUI (conviviale)
5. **Performance** : Recherche binaire O(log n) - très rapide

### Cas d'Usage Réels

1. **Inscription annuelle** : Ajout de centaines de nouveaux étudiants
2. **Mise à jour des informations** : Changement de classe, d'email
3. **Recherche d'un étudiant** : Par nom pour les procès-verbaux
4. **Génération de listes** : Par classe pour les examens

---

# 11. Conclusion et Perspectives

## 11.1 Résumé

Ce projet a permis de développer une application complète de gestion des étudiants en langage C, featuring :

- ✅ **Insertion triée automatique** par recherche binaire (O(log n))
- ✅ **Gestion des doublons** par vérification de matricule
- ✅ **Deux interfaces** : Console et Graphique (GTK+)
- ✅ **Stockage CSV** pour la persistance et l'interopérabilité
- ✅ **Code modulaire** avec Makefile

## 11.2 Compétences Démontrées

| Compétence | Niveau |
|------------|--------|
| Programmation modulaire en C | Maîtrisé |
| Structures de données | Maîtrisé |
| Algorithmes de recherche | Maîtrisé |
| Gestion de fichiers (CSV) | Maîtrisé |
| Interfaces utilisateur (Console/GUI) | Maîtrisé |
| Makefile et build automation | Maîtrisé |

## 11.3 Perspectives d'Amélioration

### Fonctionnalités Futures

- [ ] Export PDF des listes d'étudiants
- [ ] Import depuis Excel/JSON
- [ ] Authentification par mot de passe
- [ ] Sauvegarde automatique
- [ ] Statistiques et graphiques

### Améliorations Techniques

- [ ] Base de données SQLite
- [ ] Interface Web (HTML/CSS/JavaScript)
- [ ] Application mobile Android
- [ ] Tests unitaires automatisés
- [ ] Internationalisation (multilingue)

---

# Annexes

## Annexe A : Liste des Fichiers Sources

| Fichier | Description |
|---------|-------------|
| `CMD_gestion_etudiants.c` | Programme principal version console |
| `GUI_gestion_etudiants.c` | Programme principal version GUI |
| `fonctions.c` | Fonctions utilitaires (parsing, recherche, tri) |
| `etudiant.c` | Fonctions de saisie et d'affichage |
| `banner.c` | Messages de bienvenue |

## Annexe B : Commandes de Compilation

```bash
# Windows (MSYS2)
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-gtk3

# Linux (Debian/Ubuntu)
sudo apt install gcc make pkg-config libgtk-3-dev
```

---

**Document préparé pour :**
- Université : USTM (Université des Sciences et Techniques de Masuku)
- Formation : DUT2-GRT S1
- Cours : Programmation Avancée
- Année : 2025-2026

**Auteur** : Étudiant(e) DUT2-GRT

**Date** : Mars 2026

---