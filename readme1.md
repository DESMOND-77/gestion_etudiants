# 🎓 Student Management System (C / GTK)

> Système modulaire de gestion d’étudiants développé en C  
> Version Console (ANSI) + Version Graphique (GTK+ 3)

---

## 📌 Overview

Ce projet implémente un **système complet de gestion d’étudiants** avec :

- 🔹 Insertion triée automatique (ordre alphabétique)
- 🔹 Détection de doublons (matricule unique)
- 🔹 Persistance via fichier CSV
- 🔹 Recherche binaire O(log n)
- 🔹 Interface Console (ANSI Colors)
- 🔹 Interface Graphique GTK+ 3

Projet réalisé dans le cadre du cours de **Programmation Avancée – DUT2 GRT**.

---

# 🏗 Architecture du Projet

## 🧠 Architecture Modulaire

```
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

# 📂 Structure du Projet

```
gestion_etudiants/
│
├── README.md
├── Makefile
│
├── CMD_gestion/
│   ├── CMD_gestion_etudiants.c
│   ├── etudiant.c
│   ├── fonctions.c
│   └── lib/
│       ├── etudiant.h
│       ├── fonctions.h
│       └── couleurs.h
│
└── GUI_gestion/
    ├── gestion_etudiants_gui.c
    ├── fonctions.c
    ├── style.css
    └── lib/
        ├── etudiant.h
        └── fonctions.h
```

---

# ⚙️ Choix Techniques

## 📄 Pourquoi CSV ?

- Format simple et portable
- Pas de dépendances externes
- Facilement éditable
- Suffisant pour un projet académique

## 🔎 Pourquoi Recherche Binaire ?

- Complexité : **O(log n)**
- Maintien du tri automatique
- Optimisation des performances

## 🖥 Pourquoi GTK+ 3 ?

- Bibliothèque mature
- Portable (Windows / Linux)
- Support CSS intégré

---

# 📊 Complexité Algorithmique

| Fonction | Complexité |
|----------|------------|
| Recherche binaire | O(log n) |
| Vérification doublon | O(n) |
| Insertion triée | O(n) |
| Parsing CSV | O(m) |

---

# 🔐 Sécurité & Robustesse

- ✔ Limitation taille buffers (`MAX_CHAMP`)
- ✔ Protection contre overflow
- ✔ Vérification des fichiers (`NULL`)
- ✔ Validation des entrées utilisateur
- ✔ Gestion des erreurs système
- ✔ Messages d’erreurs explicites

---

# 🚀 Compilation

## 🔹 Version Console

```bash
make cmd
```

## 🔹 Version Graphique

```bash
make gui
```

## 🔹 Nettoyer

```bash
make clean
```

---

# 🖥 Exécution

## Console

```bash
./bin/gestion_etudiants
```

## GUI

```bash
./bin/gestion_etudiants_gui
```

---

# 🧪 Fonctionnement

1. Lecture du fichier CSV
2. Chargement en mémoire
3. Vérification doublon
4. Recherche position (binaire)
5. Insertion triée
6. Réécriture du fichier

---

![Interface GUI](images/gui.png)
![Version Console](images/cmd.png)

# 📈 Améliorations Futures

- [ ] Suppression d’étudiant
- [ ] Modification d’étudiant
- [ ] Recherche multi-critères
- [ ] Base SQLite
- [ ] Export PDF
- [ ] Interface Web
- [ ] Authentification multi-utilisateurs
- [ ] Tests unitaires

---

# 🧰 Technologies

- C99
- GCC
- GTK+ 3
- pkg-config
- MSYS2 (Windows)
- Linux (Debian / Fedora / Arch)

---

# 📜 Licence

Projet académique – Usage éducatif autorisé.

---

# 👨‍💻 Auteur

Développé dans le cadre du DUT2 – Génie Réseaux & Télécommunications.

---

# ⭐ Contribution

Les contributions sont les bienvenues :
- Fork
- Pull Request
- Issue

---

**Dernière mise à jour : 2025**