# Système de Gestion des Étudiants (Student Management System)

## Table des matières

1. [Description du projet](#-description-du-projet)
2. [Structure du projet](#-structure-du-projet)
3. [Ressources utilisées](#-ressources-utilisées)
4. [Prérequis système](#-prérequis-système)
5. [Mise en place de l'environnement](#-mise-en-place-de-lenvironnement)
6. [Choix techniques](#-choix-techniques)
7. [Sécurité et Robustesse](#-sécurité-et-Robustesse)
8. [Compilation et exécution](#-compilation-et-exécution)
9. [Utilisation](#-utilisation)
10. [Architecture et algorithmes](#-architecture-et-algorithmes)
11. [Dépannage](#-dépannage)
12. [Fichiers importants](#-fichiers-importants)

---

## 🎯 Description du projet

### Objectif général

Ce projet implémente un système complet de gestion d'étudiantsen C, offrant deux interfaces différentes :

- **Version Console (CMD)** :

Interface en ligne de commande avec support des couleurs ANSI

- **Version Graphique (GUI)** : Interface graphique utilisant la bibliothèque GTK+ 3.0

### Fonctionnalités principales

- [x] **Insertion d'étudiants triés** - Les étudiants sont automatiquement insérés en ordre alphabétique par nom  
- [x] **Gestion des fichiers CSV** - Sauvegarde persistante dans un fichier CSV  
- [x] **Validation des données** - Vérification des doublons (matricule unique)  
- [x] **Recherche binaire** - O(log n) pour trouver la position d'insertion optimale  
- [x] **Gestion des erreurs** - Messages d'erreur détaillés et codes d'erreur appropriés  
- [x] **Interface colorée** (CMD) - Utilisation des codes d'échappement ANSI pour la lisibilité  
- [x] **Interface graphique** (GUI) - Formulaire intuitif avec boîtes de dialogue  

### Données gérées par étudiant

- **Nom** (obligatoire)
- **Prénom** (obligatoire)
- **Classe** (optionnel)
- **Email** (optionnel)
- **Matricule** (obligatoire, unique)
- **Sexe** (optionnel)

---

## 📁 Structure du projet

```python
gestion_etudiants/
├── 📝 README.md                         # Ce fichier
├── 📄 help.txt                          # Guide d'installation rapide
├── 📄 test.c                            # Fichier de test
│
├── 📁 CMD_gestion/                     # Version Console
│   ├── 📄 CMD_gestion_etudiants.c      # Programme principal (CMD)
│   ├── 📄 etudiant.c                   # Implémentation des opérations sur étudiants
│   ├── 📄 fonctions.c                  # Implémentation des fonctions utilitaires
│   ├── 📄 Etudiants.csv                # Fichier de données (créé automatiquement)
│   └── 📁 lib/
│       ├── ⚡ couleurs.h               # Codes ANSI pour les couleurs
│       ├── ⚡ etudiant.h               # Définition de la structure Etudiant
│       └── ⚡ fonctions.h              # Déclarations des fonctions
│
└── 📁 GUI_gestion/                     # Version Graphique
    ├── 📄 GUI_gestion_etudiants.c      # Programme principal (GUI avec GTK+)
    ├── 📄 gestion_etudiants_gui.c      # Fichier alternate du GUI
    ├── 📄 fonctions.c                  # Implémentation partagée
    ├── 🎨 style.css                    # Styles personnalisés GTK+
    ├── Etudiants.csv                   # Fichier de données (créé automatiquement)
    └── 📁 lib/
        ├── ⚡etudiant.h                # Définition de la structure Etudiant
        └── ⚡fonctions.h               # Déclarations des fonctions
```

---

## 🔧 Ressources utilisées

### Langages et outils

- **Langage C** - C99 (GNU C)
- **Compilateur** - GCC (MinGW-w64 sur Windows via MSYS2)
- **Système de gestion de paquets** - MSYS2 Pacman
- **Outil de configuration** - pkg-config

### Bibliothèques utilisées

#### Version Console

- **libc** - Bibliothèque standard C (stdio, stdlib, string.h)
- Standard ANSI C pour I/O et manipulation de chaînes

#### Version Graphique

- **GTK+ 3.0** - Bibliothèque graphique
  - `libgtk-3-0` - Noyau de GTK+
  - `libgdk-3-0` - Abstraction des opérations graphiques
  - `libgio-2.0` - Utilitaires de fichiers et E/S
  - `libglib-2.0` - Bibliothèque de base (structures, listes, etc.)
  - Support CSS pour la personnalisation

### Formats de données

- **CSV** (Comma-Separated Values / Semicolon-Separated Values)
  - Délimiteur: `;` (point-virgule)
  - Format: `nom;prenom;classe;email;matricule;sex`
  - Lecture/Écriture avec gestion des guillemets pour champs complexes

---

## 💻 Prérequis système

### Système d'exploitation

- **Windows 10 ou supérieur** (avec MSYS2 installé)
- **Linux** (Debian/Ubuntu, Fedora, Arch, openSUSE, etc.)
- macOS (adaptation possible des commandes de compilation)

### Ressources minimales

- **Disque** : ~200 MB pour MSYS2 et GTK+
- **RAM** : 512 MB minimum
- **Processeur** : Processeur 64-bit recommandé

### Logiciels préalables

1. **MSYS2** installé et configuré
2. **GCC** et toolchain MinGW-w64
3. **pkg-config** pour la gestion des drapeaux de compilation

---

## 🚀 Mise en place de l'environnement

### Étape 1: Installer MSYS2

1. **Télécharger MSYS2**
   - Visitez <https://www.msys2.org/>
   - Téléchargez l'installateur 64-bit (`msys2-x86_64-20240113.exe` ou similaire)

2. **Lancer l'installation**
   - Exécutez l'installateur
   - Acceptez les paramètres par défaut
   - Choisissez un dossier d'installation (par défaut: `C:\msys64`)

3. **Lancer MSYS2**
   - Ouvrez le raccourci **MSYS2 MinGW 64-bit** depuis le menu Démarrer
   - Une fenêtre de terminal s'ouvrira

### Étape 2: Mettre à jour MSYS2

```bash
# Mettre à jour la base de données des paquets
pacman -Syu

# Répondez 'y' à toutes les questions
# La fenêtre peut se fermer à la fin, c'est normal
# Relancez MSYS2 après la mise à jour
```

### Étape 3: Installer le compilateur GCC et les outils

```bash
# Installer le toolchain MinGW-w64 complet
pacman -S mingw-w64-x86_64-toolchain

# Cela inclut:
# - gcc (compilateur C/C++)
# - gdb (débogeur)
# - make (outil de build)
# - binutils (utilitaires binaires)
```

Répondez `y` quand on vous le demande. L'installation prendra quelques minutes.

### Étape 4: Installer GTK+ 3.0 et dépendances

```bash
# Installer GTK+ 3.0 et toutes ses dépendances
pacman -S mingw-w64-x86_64-gtk3

# Installer également pkg-config (nécessaire pour compiler)
pacman -S mingw-w64-x86_64-pkg-config

# Vérifier l'installation (optionnel)
pkg-config --modversion gtk+-3.0
# Doit afficher: 3.x.x (version de GTK+)
```

### Étape 5: Vérifier l'installation

```bash
# Vérifier GCC
gcc --version
# Doit afficher: gcc (GCC) version...

# Vérifier pkg-config
pkg-config --list-all | grep gtk
# Doit afficher: gtk+-3.0 ...

# Naviguer vers le répertoire du projet
cd c:/Users/votre_nom_utilisateur/chemin/vers/gestion_etudiants
```

---

### 🐧 Configuration pour Linux

Cette section détaille l'installation des outils nécessaires pour compiler et exécuter le projet sur un système Linux.

#### Option A: Distributions basées sur Debian/Ubuntu

```bash
# Mettre à jour la liste des paquets
sudo apt update

# Installer le compilateur GCC
sudo apt install gcc

# Installer pkg-config
sudo apt install pkg-config

# Installer GTK+ 3.0 et ses dépendances (pour la version GUI)
sudo apt install libgtk-3-dev

# Vérifier l'installation
gcc --version
pkg-config --modversion gtk+-3.0
```

#### Option B: Distributions basées sur Fedora/RHEL/CentOS

```bash
# Installer le compilateur GCC
sudo dnf install gcc

# Installer pkg-config
sudo dnf install pkg-config

# Installer GTK+ 3.0 et ses dépendances (pour la version GUI)
sudo dnf install gtk3-devel

# Vérifier l'installation
gcc --version
pkg-config --modversion gtk+-3.0
```

#### Option C: Distributions basées sur Arch Linux

```bash
# Installer le compilateur GCC
sudo pacman -S gcc

# Installer pkg-config
sudo pacman -S pkg-config

# Installer GTK+ 3.0 et ses dépendances (pour la version GUI)
sudo pacman -S gtk3

# Vérifier l'installation
gcc --version
pkg-config --modversion gtk+-3.0
```

#### Option D: Distributions basées sur openSUSE

```bash
# Installer le compilateur GCC
sudo zypper install gcc

# Installer pkg-config
sudo zypper install pkg-config

# Installer GTK+ 3.0 et ses dépendances (pour la version GUI)
sudo zypper install gtk3-devel

# Vérifier l'installation
gcc --version
pkg-config --modversion gtk+-3.0
```

#### Navigation vers le répertoire du projet (Linux)

```bash
# Naviguer vers le répertoire du projet
cd /home/votre_nom_utilisateur/chemin/vers/gestion_etudiants

# Vérifier que vous êtes au bon endroit
ls
# Doit afficher: CMD_gestion/  GUI_gestion/  README.md  help.txt
```

---

## ⚙️ Choix Techniques

### 📄 Pourquoi CSV ?

- Format simple et portable
- Pas de dépendances externes
- Facilement éditable
- Suffisant pour un projet académique

### 🔎 Pourquoi Recherche Binaire ?

- Complexité : **O(log n)**
- Maintien du tri automatique
- Optimisation des performances

### 🖥 Pourquoi GTK+ 3 ?

- Bibliothèque mature
- Portable (Windows / Linux)
- Support CSS intégré

---

## 📊 Complexité Algorithmique

| Fonction | Complexité |
| ---------- | ------------ |
| Recherche binaire | O(log n) |
| Vérification doublon | O(n) |
| Insertion triée | O(n) |
| Parsing CSV | O(m) |

---

## 🔐 Sécurité & Robustesse

- ✔ Limitation taille buffers (`MAX_CHAMP`)
- ✔ Protection contre overflow
- ✔ Vérification des fichiers (`NULL`)
- ✔ Validation des entrées utilisateur
- ✔ Gestion des erreurs système
- ✔ Messages d'erreurs explicites

---

## 🔨 Compilation et exécution

### Utilisation de Makefile (recommandé)

Si un fichier `Makefile` est présent dans le répertoire racine, vous pouvez compiler facilement :

```bash
# Compiler la version Console
make cmd

# Compiler la version Graphique
make gui

# Nettoyer les fichiers compilés
make clean
```

### ⚠️ Note importante pour Linux

Sur Linux, les exécutables n'ont pas besoin de l'extension `.exe`. Utilisez simplement `gestion_etudiants` au lieu de `gestion_etudiants.exe`.

### Version Console (CMD)

#### Compilation-cmd (Windows)

```bash
# Naviguer vers le répertoire CMD_gestion
cd CMD_gestion

# Compiler tous les fichiers ensemble
gcc -o gestion_etudiants.exe CMD_gestion_etudiants.c etudiant.c fonctions.c

# Ou avec GCC compilé pour Windows (compilation optimisée)
gcc -Wall -g -o gestion_etudiants.exe CMD_gestion_etudiants.c etudiant.c fonctions.c
```

#### Compilation-cmd (Linux)

```bash
# Naviguer vers le répertoire CMD_gestion
cd CMD_gestion

# Compiler tous les fichiers ensemble (sans extension .exe)
gcc -o gestion_etudiants CMD_gestion_etudiants.c etudiant.c fonctions.c

# Ou avec options complètes (recommandé)
gcc -Wall -Wextra -o gestion_etudiants CMD_gestion_etudiants.c etudiant.c fonctions.c
```

**Explication des options gcc:**

- `-o gestion_etudiants` : Nom du fichier exécutable (sans .exe sur Linux)
- `-Wall -Wextra` : Afficher tous les avertissements (optionnel mais recommandé)
- `-g` : Inclure les informations de débogage (optionnel)

#### Exécution-cmd (Windows)

```bash
# Lancer le programme
./gestion_etudiants.exe

# Ou directement
gestion_etudiants.exe
```

#### Exécution-cmd (Linux)

```bash
# Lancer le programme
./gestion_etudiants

# Si le fichier n'est pas exécutable, rendez-le exécutable
chmod +x gestion_etudiants
./gestion_etudiants
```

Le programme affichera un menu de bienvenue et vous demandera les informations de l'étudiant.

#### Processus d'utilisation (CMD)

```text
1. Affichage du nombre d'étudiants existants
2. Saisie des informations du nouvel étudiant
3. Vérification de l'unicité du matricule
4. Insertion triée dans le fichier CSV
5. Message de confirmation ou d'erreur
```

---

### Version Graphique (GUI)

#### Compilation (Windows)

```bash
# Naviguer vers le répertoire GUI_gestion
cd GUI_gestion

# Compiler avec GTK+ 3.0
gcc -o GUI_gestion_etudiants.exe GUI_gestion_etudiants.c fonctions.c \
    `pkg-config --cflags gtk+-3.0` \
    `pkg-config --libs gtk+-3.0`

# Ou sur une seule ligne
gcc -o GUI_gestion_etudiants.exe GUI_gestion_etudiants.c fonctions.c `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`
```

#### Compilation (Linux)

```bash
# Naviguer vers le répertoire GUI_gestion
cd GUI_gestion

# Compiler avec GTK+ 3.0 (sans extension .exe)
gcc -o GUI_gestion_etudiants GUI_gestion_etudiants.c fonctions.c \
    `pkg-config --cflags gtk+-3.0` \
    `pkg-config --libs gtk+-3.0`

# Ou sur une seule ligne
gcc -o GUI_gestion_etudiants GUI_gestion_etudiants.c fonctions.c `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`

# Avec options supplémentaires (recommandé)
gcc -Wall -Wextra -o GUI_gestion_etudiants GUI_gestion_etudiants.c fonctions.c `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`
```

**Explication:**

- ``pkg-config --cflags gtk+-3.0`` : Inclut les chemins d'en-têtes GTK+
- ``pkg-config --libs gtk+-3.0`` : Inclut les bibliothèques à lier
- Les backticks (`) exécutent la commande et insèrent le résultat

#### Exécution (Windows)

```bash
# Lancer le programme GUI
./GUI_gestion_etudiants.exe
```

#### Exécution (Linux)

```bash
# Lancer le programme GUI
./GUI_gestion_etudiants

# Si le fichier n'est pas exécutable, rendez-le exécutable
chmod +x gestion_etudiants_gui
./GUI_gestion_etudiants
```

Une fenêtre GTK+ s'ouvrira avec un formulaire de saisie.

**Note importante pour les environnements sans écran (serveur):**
Si vous exécutez sur un serveur sans interface graphique, vous pouvez:

- Utiliser uniquement la version Console
- Ou installer un serveur X virtuel comme Xvfb: `sudo apt install xvfb` puis `xvfb-run ./gestion_etudiants_gui`

#### Processus d'utilisation (GUI)

```text
1. Une fenêtre graphique s'ouvre avec 6 champs de texte
2. Remplissez les champs (Nom, Prénom, Classe, Matricule, Email, Sexe)
3. Cliquez sur le bouton "Insérer"
4. Un message de confirmation/erreur s'affiche
5. Les champs se vident automatiquement en cas de succès
6. Cliquez sur "Quitter" pour fermer l'application
```

---

## 🏗️ Architecture Modulaire

Voici la structure modulaire du projet:

```text
                ┌───────────────────┐
                │    Interface      │
                │  (CMD / GUI)      │
                └─────────┬─────────┘
                          ↓
                ┌───────────────────┐
                │  Logique Métier   │
                │  (Insertion,      │
                │   Recherche)      │
                └─────────┬─────────┘
                          ↓
                ┌───────────────────┐
                │ Gestion CSV       │
                │ Lecture / Écriture│
                └─────────┬─────────┘
                          ↓
                ┌───────────────────┐
                │ Structure Etudiant│
                └───────────────────┘
```

---

## 📖 Utilisation

### Format du fichier CSV

Le fichier `Etudiants.csv` est stocké dans le même répertoire que l'exécutable.

**Format attendu:**

```csv
nom;prenom;classe;email;matricule;sex
Dupont;Jean;L1;jean@example.com;MAT001;M
Martin;Marie;L1;marie@example.com;MAT002;F
```

**Gestion des guillemets:**

- Les champs contenant `;` doivent être entourés de guillemets: `"Nom;Particule";Prenom;...`
- Les guillemets doubles sont échappés par `""`: `"Nom ""Alias""";...`

### Limites

- **Nombre maximum d'étudiants**: 1000 (MAX_STUD)
- **Longueur maximale d'un champ**: 128 caractères (MAX_CHAMP)
- **Longueur maximale d'une ligne CSV**: 512 caractères (MAX_LIGNE)

### Exemple d'utilisation (CMD)

```bash
##########################################################################
##                                                                      ##
##   Bienvenue dans le programme de gestion des etudiants.              ##
##                                                                      ##
##########################################################################
||                                                                      ||
||  Nombre d'etudiants actuellement dans "test.csv" : 5                 ||
==========================================================================

Saisis des infos de l'etudiant(e):

==> Tapez le(s) nom(s)    : Leclerc
==> Tapez le(s) prenom(s) : Pierre
==> Tapez la classe       : L2
==> Tapez l'email         : pierre@example.com
==> Tapez le matricule    : MAT123
==> Tapez le sexe         : M

Etudiant(e) insere(e) en position 3 et fichier mis à jour (test.csv).

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@                                    @@
@@   Programme terminer !!!.          @@
@@                                    @@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
```

---

## 🏗️ Architecture et algorithmes

### Structure de données

```c
typedef struct {
    char nom[128];        // Nom de l'étudiant
    char prenom[128];     // Prénom de l'étudiant
    char classe[128];     // Classe/Niveau
    char matricule[128];  // Identifiant unique
    char email[128];      // Adresse email
    char sex[128];        // Sexe/Genre
} Etudiant;
```

### Algorithmes implémentés

#### 1. **Recherche binaire** (`cher_pos_ins`)

- **Complexité**: O(log n)
- **Objectif**: Trouver la position d'insertion pour maintenir le tri alphabétique
- **Retour**:
  - Indice si l'élément existe
  - Position d'insertion sinon (entre 0 et n)

```algobox
Exemple avec noms: ["Alice", "Bob", "David"]
- Insérer "Charles" → position 2
- Tableau devient: ["Alice", "Bob", "Charles", "David"]
```

#### 2. **Recherche linéaire** (Détection de doublon)

- **Complexité**: O(n)
- **Objectif**: Vérifier que le matricule n'existe pas déjà
- **Retour**: Position du doublon ou -1 si absent

#### 3. **Insertion triée avec décalage**

- **Complexité**: O(n) dans le pire cas
- **Processus**:
  1. Décaler tous les éléments à droite de la position
  2. Insérer le nouvel élément à la position correcte
  3. Incrémenter le compteur

#### 4. **Parsage CSV avec guillemets**

- **Complexité**: O(m) où m = longueur de la ligne
- **Gestion**:
  - Champs simples: séparés par `;`
  - Champs cités: `"..."` peuvent contenir `;`
  - Guillemets échappés: `""` → `"`

### Flux de données

```flow
[Fichier CSV] 
    ↓
[lire_csv()] → Tableau d'Etudiants en mémoire
    ↓
[Saisir nouveau]
    ↓
[Vérifier doublon (linéaire)]
    ↓
[Trouver position (binaire)]
    ↓
[Décaler + Insérer]
    ↓
[vers_csv()] → Fichier CSV mis à jour
```

### Gestion des couleurs (CMD)

Les codes ANSI utilisés (définis dans `couleurs.h`):

- `\033[31m` - Rouge (erreur)
- `\033[32m` - Vert (succès)
- `\033[33m` - Jaune (titres)
- `\033[34m` - Bleu (flèches)
- `\033[0m` - Réinitialiser (défaut)

### 📊 Complexité Algorithmique

| Fonction | Complexité |
| ---------- | ------------ |
| Recherche binaire | O(log n) |
| Vérification doublon | O(n) |
| Insertion triée | O(n) |
| Parsing CSV | O(m) |

---

## 🐛 Dépannage

### Erreur: "pkg-config: command not found"

**Solution (Windows):**

```bash
pacman -S mingw-w64-x86_64-pkg-config
```

**Solution (Linux - Debian/Ubuntu):**

```bash
sudo apt install pkg-config
```

**Solution (Linux - Fedora):**

```bash
sudo dnf install pkg-config
```

**Solution (Linux - Arch):**

```bash
sudo pacman -S pkg-config
```

### Erreur: "cannot find -lgtk-3"

**Solution (Windows):**

```bash
pacman -S mingw-w64-x86_64-gtk3
# Puis relancer la compilation avec les backticks corrects
```

**Solution (Linux - Debian/Ubuntu):**

```bash
sudo apt install libgtk-3-dev
```

**Solution (Linux - Fedora):**

```bash
sudo dnf install gtk3-devel
```

**Solution (Linux - Arch):**

```bash
sudo pacman -S gtk3
```

### Erreur: "undefined reference to `gtk_*'"

**Cause**: Les drapeaux GTK+ ne sont pas correctement inclus
**Solution**: Vérifier la commande de compilation avec backticks

### Erreur: "gcc: command not found"

**Solution (Linux - Debian/Ubuntu):**

```bash
sudo apt install gcc
```

**Solution (Linux - Fedora):**

```bash
sudo dnf install gcc
```

**Solution (Linux - Arch):**

```bash
sudo pacman -S gcc
```

### Le fichier CSV n'est pas créé

**Cause**: Le programme n'a pas la permission d'écrire
**Solution**: Vérifier les droits d'accès du répertoire ou lancer en tant qu'administrateur

### Interface GTK+ ne s'affiche pas

**Cause**: Variable d'affichage non définie (rare sur Windows)
**Solution**: Relancer le programme ou installer un serveur X si sur WSL

### Erreur: "Permission denied" lors de l'exécution

**Cause**: Le fichier compilé n'a pas les droits d'exécution
**Solution (Linux):**

```bash
chmod +x gestion_etudiants
chmod +x gestion_etudiants_gui
```

### Erreur: Cannot open display (serveur sans interface graphique)

**Cause**: Pas de serveur X disponible
**Solution**: Installer Xvfb pour les environnements sans écran

```bash
# Debian/Ubuntu
sudo apt install xvfb
xvfb-run ./gestion_etudiants_gui

# Fedora
sudo dnf install xorg-x11-server-Xvfb
xvfb-run ./gestion_etudiants_gui
```

---

## 📝 Fichiers importants

| Fichier | Description |
| --------- | ------------- |
| `CMD_gestion_etudiants.c` | Programme principal console |
| `GUI_gestion_etudiants.c` | Programme principal GTK+ |
| `fonctions.c` | Implémentation des opérations (CSV, recherche, etc.) |
| `etudiant.c` | Implémentation de la saisie et affichage d'étudiant |
| `couleurs.h` | Définition des codes ANSI pour couleurs |
| `etudiant.h` | Définition de la structure Etudiant |
| `fonctions.h` | Déclarations des fonctions |
| `style.css` | Styles GTK+ personnalisés |
| `Etudiants.csv` | Base de données persistante (généré à l'exécution) |

---

### Apercu

![Interface GUI](images/gui.png)
![Version Console](images/cmd.png)

## 📚 Améliorations futures possibles

- [ ] Interface web avec HTML/CSS/JavaScript
- [ ] Base de données SQL (SQLite)
- [ ] Recherche/Filtrage d'étudiants
- [ ] Modification/Suppression d'étudiants
- [ ] Affichage de tous les étudiants
- [ ] Export en PDF
- [ ] Multi-utilisateurs avec authentification
- [ ] Sauvegarde en nuage
- [ ] Historique des modifications

---

## 👨‍💻 Auteur(s)

Développement dans le cadre du cours de Programmation Avancée - USTM DUT2-GRT

## 📄 Licence

Projet académique - Libre d'utilisation à titre éducatif

---

## ⭐ Contribution

Les contributions sont les bienvenues ! Vous pouvez :

- Fork le projet
- Créer des Pull Requests
- Signaler des problèmes (Issues)
- Proposer des améliorations

---

## 📞 Support

Pour toute question ou problème:

1. Vérifier le fichier [help.txt](help.txt)
2. Consulter les commentaires détaillés dans le code source
3. Vérifier que l'environnement MSYS2 est correctement configuré

---

**Dernière mise à jour**: mars 2026
