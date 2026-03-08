# Système de Gestion des Étudiants

## Projet Académique - Programmation Avancée (USTM DUT2-GRT)

---

## 📋 Table des Matières

1. [Présentation Générale](#1-présentation-générale)
2. [Objectifs Pédagogiques](#2-objectifs-pédagogiques)
3. [Fonctionnalités Implémentées](#3-fonctionnalités-implémentées)
4. [Architecture du Projet](#4-architecture-du-projet)
5. [Structure de Données](#5-structure-de-données)
6. [Algorithmes Utilisés](#6-algorithmes-utilisés)
7. [Complexité Algorithmique](#7-complexité-algorithmique)
8. [Technologies et Outils](#8-technologies-et-outils)
9. [Installation et Compilation](#9-installation-et-compilation)
10. [Guide d'Utilisation](#10-guide-dutilisation)
11. [Format des Données](#11-format-des-données)
12. [Sécurité et Robustesse](#12-sécurité-et-robustesse)
13. [Améliorations Possibles](#13-améliorations-possibles)
14. [Auteurs et Contexte](#14-auteurs-et-contexte)

---

## 1. Présentation Générale

Ce projet est une application de **gestion des étudiants** développée en langage C dans le cadre du cours de **Programmation Avancée** à l'USTM (Université des Sciences et Techniques de Masuku).

L'application offre deux interfaces distinctes pour la gestion d'une base de données d'étudiants :

- **Version Console (CMD)** : Interface en ligne de commande avec support des couleurs ANSI pour une meilleure lisibilité.
- **Version Graphique (GUI)** : Interface graphique moderne utilisant la bibliothèque **GTK+ 3.0**.

Les données sont persistées dans un fichier au format **CSV** (Comma-Separated Values), permettant une manipulation facile et un échanges avec d'autres logiciels tableurs.

---

## 2. Objectifs Pédagogiques

Ce projet a été conçu pour démontrer la maîtrise de plusieurs concepts fondamentaux de la programmation en C :

| Compétence                   | Description                                                                      |
| ---------------------------- | -------------------------------------------------------------------------------- |
| **Programmation modulaire**  | Séparation du code en plusieurs fichiers (.c/.h) pour une meilleure organisation |
| **Structures de données**    | Utilisation de structures (struct) pour représenter les entités                  |
| **Allocation mémoire**       | Manipulation de tableaux dynamiques et statiques                                 |
| **Gestion de fichiers**      | Lecture/Écriture de fichiers CSV avec parsing complexe                           |
| **Algorithmes de recherche** | Implémentation de la recherche binaire et linéaire                               |
| **Interfaces utilisateur**   | Développement d'interfaces console et graphique                                  |
| **Makefile**                 | Automatisation de la compilation avec gestion des dépendances                    |

---

## 3. Fonctionnalités Implémentées

### 3.1 Fonctionnalités Communes (CMD et GUI)

| Fonctionnalité                         | Description                                                            |
| -------------------------------------- | ---------------------------------------------------------------------- |
| ➕ **Insertion d'un étudiant**         | Ajout d'un nouvel étudiant avec tri automatique par ordre alphabétique |
| 📋 **Affichage de tous les étudiants** | Liste complète de la base de données avec formatage soigné             |
| 🔍 **Recherche par nom**               | Recherche insensible à la casse (recherche partielle supportée)        |
| ✏️ **Modification d'un étudiant**      | Modification des informations via le matricule unique                  |
| 🗑️ **Suppression d'un étudiant**       | Suppression d'un étudiant par son matricule                            |
| ↕️ **Tri des étudiants**               | Tri par nom ou par classe (croissant/décroissant)                      |

### 3.2 Données Gérées par Étudiant

Chaque étudiant possède les champs suivants :

- **Nom** (obligatoire) - Maximum 128 caractères
- **Prénom** (obligatoire) - Maximum 128 caractères
- **Classe** (optionnel) - Maximum 128 caractères
- **Email** (optionnel) - Maximum 128 caractères
- **Matricule** (obligatoire, unique) - Identifiant unique de l'étudiant
- **Sexe** (optionnel) - Maximum 128 caractères

### 3.3 Caractéristiques Techniques

- ✅ Insertion triée automatique (maintien de l'ordre alphabétique)
- ✅ Validation des données (matricule unique)
- ✅ Recherche binaire pour l'optimisation de l'insertion (O(log n))
- ✅ Gestion des erreurs et messages explicites
- ✅ Interface console colorée (codes ANSI)
- ✅ Interface graphique intuitive (GTK+ 3.0)
- ✅ Support des guillemets dans les fichiers CSV

---

## 4. Architecture du Projet

### 4.1 Structure des Fichiers

```text
gestion_etudiants/
│
├── 📁 CMD_gestion/                    # Version Console
│   └── CMD_gestion_etudiants.c        # Programme principal CMD
│
├── 📁 GUI_gestion/                     # Version Graphique
│   ├── GUI_gestion_etudiants.c         # Programme principal GUI (GTK+)
│   └── style.css                       # Styles personnalisés GTK+
│
├── 📁 functions/                       # Fonctions partagées
│   ├── fonctions.c                      # Implémentation des fonctions utilitaires
│   ├── etudiant.c                       # Fonctions de saisie/affichage
│   └── banner.c                         # Messages de bienvenue/bannières
│
├── 📁 libs/                            # Bibliothèques (headers)
│   ├── fonctions.h                     # Déclarations des fonctions
│   ├── etudiant.h                      # Définition de la structure Etudiant
│   ├── couleurs.h                      # Codes ANSI pour les couleurs
│   └── banner.h                        # Déclarations des bannières
│
├── 📁 data/                            # Données
│   └── Etudiants.csv                   # Base de données (généré automatiquement)
│
├── 📄 makefile                         # Script de compilation
├── 📄 README.md                        # Documentation principale
└── 📄 a_faire.md                       # Liste des fonctionnalités implémentées
```

### 4.2 Architecture Modulaire

Le projet suit une architecture en couches :

```text
┌─────────────────────────────────────────┐
│           Interface Utilisateur         │
│        (CMD Console / GUI GTK+)         │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│           Logique Métier                │
│  (Insertion, Recherche, Tri, Suppression)│
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│         Gestion des Données             │
│     (Lecture/Écriture CSV, Parsing)     │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│         Structure de Données            │
│           (Tableau d'Étudiants)         │
└─────────────────────────────────────────┘
```

---

## 5. Structure de Données

### 5.1 Structure Etudiant

```c
typedef struct {
    char nom[MAX_CHAMP];      // Nom de l'étudiant
    char prenom[MAX_CHAMP];   // Prénom de l'étudiant
    char classe[MAX_CHAMP];   // Classe/Niveau
    char matricule[MAX_CHAMP]; // Identifiant unique
    char email[MAX_CHAMP];    // Adresse email
    char sex[MAX_CHAMP];      // Sexe/Genre
} Etudiant;
```

### 5.2 Constantes Défines

| Constante   | Valeur               | Description                       |
| ----------- | -------------------- | --------------------------------- |
| `MAX_STUD`  | 1000                 | Nombre maximum d'étudiants        |
| `MAX_CHAMP` | 128                  | Longueur maximale d'un champ      |
| `MAX_LIGNE` | 512                  | Longueur maximale d'une ligne CSV |
| `FILENAME`  | "data/Etudiants.csv" | Chemin du fichier de données      |

---

## 6. Algorithmes Utilisés

### 6.1 Recherche Binaire (`cher_pos_ins`)

**Objectif** : Trouver la position d'insertion optimale pour maintenir le tri alphabétique.

**Complexité** : O(log n)

**Principe** :

- Le tableau est maintenu trié par nom
- La recherche binaire divise récursivement l'intervalle de recherche
- Retourne l'indice d'insertion où le nouvel étudiant doit être placé

```c
// Pseudocode simplifié
gauche = 0, droite = n - 1
tant que gauche <= droite:
    milieu = (gauche + droite) / 2
    si tableau[milieu].nom == nom: return milieu
    sinon si tableau[milieu].nom < nom: gauche = milieu + 1
    sinon: droite = milieu - 1
return gauche  // Position d'insertion
```

### 6.2 Recherche Linéaire (Détection de Doublons)

**Objectif** : Vérifier l'unicité du matricule avant insertion.

**Complexité** : O(n)

### 6.3 Insertion avec Décalage

**Objectif** : Insérer un nouvel étudiant à la position trouvée tout en décalant les éléments existants.

**Complexité** : O(n) dans le pire des cas

### 6.4 Parsing CSV avec Guillemets

**Objectif** : Analyser correctement les lignes CSV, y compris les champs spéciaux.

**Gestion supportée** :

- Champs simples : `nom;prenom;classe`
- Champs cités avec séparateurs : `"Nom;Marticule";prenom;classe`
- Guillemets échappés : `"Nom ""Surnom""";prenom`

---

## 7. Complexité Algorithmique

| Opération            | Complexité | Description                          |
| -------------------- | ---------- | ------------------------------------ |
| Recherche binaire    | O(log n)   | Recherche de la position d'insertion |
| Vérification doublon | O(n)       | Recherche linéaire du matricule      |
| Insertion triée      | O(n)       | Décalage + insertion                 |
| Parsing CSV          | O(m)       | Lecture d'une ligne (m = longueur)   |
| Recherche par nom    | O(n)       | Parcours linéaire (texte partiel)    |
| Tri (qsort)          | O(n log n) | Tri rapide standard                  |

---

## 8. Technologies et Outils

### 8.1 Langage et Compilateur

- **Langage** : C (standard C99)
- **Compilateur** : GCC (GNU Compiler Collection)
- **Outil de build** : Makefile

### 8.2 Bibliothèques

#### Version Console

- **libc** : Bibliothèque standard C
  - `stdio.h` : Entrées/sorties
  - `stdlib.h` : Allocation mémoire, conversions
  - `string.h` : Manipulation de chaînes

#### Version Graphique

- **GTK+ 3.0** : Bibliothèque graphique multiplateforme
  - `libgtk-3-0` : Noyau GTK+
  - `libgdk-3-0` : Abstraction graphique
  - `libglib-2.0` : Structures de données
  - Support CSS pour le stylage

### 8.3 Format de Données

- **CSV** (Comma-Separated Values)
- Délimiteur : `;` (point-virgule)
- Encodage : UTF-8 recommandé

---

## 9. Installation et Compilation

### 9.1 Prérequis

#### Windows (avec MSYS2)

```bash
# Installer MSYS2 depuis https://www.msys2.org/
# Dans le terminal MSYS2 MinGW 64-bit :

# Mettre à jour
pacman -Syu

# Installer GCC et outils
pacman -S mingw-w64-x86_64-toolchain

# Installer GTK+ 3.0
pacman -S mingw-w64-x86_64-gtk3
pacman -S mingw-w64-x86_64-pkg-config
```

#### Linux (Debian/Ubuntu)

```bash
sudo apt update
sudo apt install gcc
sudo apt install pkg-config
sudo apt install libgtk-3-dev
```

#### Linux (Fedora)

```bash
sudo dnf install gcc
sudo dnf install pkg-config
sudo dnf install gtk3-devel
```

### 9.2 Compilation avec Makefile

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

### 9.3 Compilation Manuelle

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

---

## 10. Guide d'Utilisation

### 10.1 Lancement

#### Version Console

```bash
./cmd_gestion_etudiants
```

#### Version GUI

```bash
./gui_gestion_etudiants
```

### 10.2 Menu Principal (Console)

```text
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

### 10.3 Exemple d'Utilisation (Console)

```text
==> Tapez le(s) nom(s)    : Dupont
==> Tapez le(s) prenom(s) : Jean
==> Tapez la classe       : L1 Info
==> Tapez l'email         : jean.dupont@etud.ustm.fr
==> Tapez le matricule    : MAT2024001
==> Tapez le sexe         : M

[SUCCÈS] Étudiant inséré en position 3
```

---

## 11. Format des Données

### 11.1 Structure du Fichier CSV

```csv
nom;prenom;classe;email;matricule;sex
Dupont;Jean;L1 Info;jean.dupont@etud.ustm.fr;MAT2024001;M
Martin;Marie;L2 Info;marie.martin@etud.ustm.fr;MAT2024002;F
```

### 11.2 Gestion des Caractères Spéciaux

| Caractère dans les données | Représentation CSV |
| -------------------------- | ------------------ |
| Point-virgule `;`          | `"Nom;Particule"`  |
| Guillemet double `"`       | `""` (doublé)      |

---

## 12. Sécurité et Robustesse

Le code implémente plusieurs mesures de sécurité :

| Mesure                             | Description                                                 |
| ---------------------------------- | ----------------------------------------------------------- |
| **Limitation des buffers**         | Tous les champs sont limités à `MAX_CHAMP` (128 caractères) |
| **Protection overflow**            | Utilisation de `safe_strncpy()` avec vérification de taille |
| **Vérification des fichiers**      | Contrôle des pointeurs NULL avant accès                     |
| **Validation des entrées**         | Vérification des données saisies par l'utilisateur          |
| **Gestion des erreurs**            | Messages d'erreur explicites et codes de retour             |
| **Parcours de tableaux sécurisés** | Vérification des indices avant accès                        |

---

## 13. Améliorations Possibles

### Fonctionnalités Futures

- [ ] Export PDF de la liste des étudiants
- [ ] Import depuis d'autres formats (Excel, JSON)
- [ ] Authentification multi-utilisateurs
- [ ] Sauvegarde automatique dans le cloud
- [ ] Historique des modifications
- [ ] Statistiques et graphiques

### Améliorations Techniques

- [ ] Utilisation d'une base de données SQLite
- [ ] Interface web (HTML/CSS/JavaScript)
- [ ] Internationalisation (multilingue)
- [ ] Tests unitaires automatisés

---

## 14. Auteurs et Contexte

### Contexte Académique

- **Université** : USTM (Université des Sciences et Techniques de Masuku)
- **Formation** : DUT2-GRT (Diplôme Universitaire de Technologie - Génie Réseaux et Télécommunications)
- **Semestre** : S1
- **Cours** : Programmation Avancée
- **Année** : 2025-2026

### Licence

Ce projet est un travail académique. Il est libre d'utilisation à des fins éducatives.

---

## Support

Pour toute question ou problème :

1. Consulter le fichier [help.txt](help.txt)
2. Examiner les commentaires dans le code source
3. Vérifier la configuration de l'environnement de développement

---

**Dernière mise à jour** : Mars 2026
