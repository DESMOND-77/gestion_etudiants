# PRÉSENTATION POWERPOINT
## Système de Gestion des Étudiants - USTM

---

# DIAPOSITIVE 1 : TITRE

## 🎓 PROJET DE PROGRAMMATION AVANCÉE
### Système de Gestion des Étudiants

**Université :** USTM (Université des Sciences et Techniques de Masuku)  
**Formation :** DUT2-GRT S1  
**Cours :** Programmation Avancée  
**Année :** 2025-2026

---

# DIAPOSITIVE 2 : PLAN DE LA PRÉSENTATION

## 📋 Plan

1. **Contexte et Problématique**
2. **Concept et Définition**
3. **Architecture du Projet**
4. **Algorithmes Clés**
5. **Démonstration**
6. **Applications au Gabon**
7. **Conclusion**

---

# DIAPOSITIVE 3 : CONTEXTE

## 🏫 Contexte du Projet

### L'USTM
- Université des Sciences et Techniques de Masuku
- Située à Franceville, Gabon
- Formation : DUT2-GRT (Génie Réseaux et Télécommunications)

### Le Cours
- **Programmation Avancée** - Semestre S1
- Langage : **C**
- Objectif : Développer une application de gestion

---

# DIAPOSITIVE 4 : PROBLÉMATIQUE

## ❓ Problematiques Rencontrées

### Problème 1 : La Recherche d'Information
- Archives **papier** ou **numérique**
- Temps parfois **dérisoire** ou **extrêmement complexe**

### Problème 2 : Insertion au Bon Endroit
- Données **numériques** = challenge supplémentaire
- Besoin de maintenir l'**ordre alphabétique**

### Problème 3 : Gestion des Doublons
- Vérifier l'**unicité** des informations
- Éviter les **données en double**

---

# DIAPOSITIVE 5 : LE PROJET

## 💡 Le Projet : Projet 02|c

### Objectif Principal
Développer un programme **C** qui insère les informations d'un(e) étudiant(e) au **bon endroit** dans un fichier CSV.

### Spécifications
- ✅ Fichier au format **.csv**
- ✅ Chaque ligne = données d'un(e) étudiant(e)
- ✅ Insertion par **ordre alphabétique** des noms
- ✅ Vérification des **doublons** par matricule

---

# DIAPOSITIVE 6 : CONCEPT

## 🎯 Le Concept : Insertion Triée Automatique

### Principe
Le programme trouve **automatiquement** la position correcte d'insertion :
- Recherche de la position par **recherche binaire**
- Décale les éléments si nécessaire
- Insère le nouvel étudiant

### Avantages
| Avantage | Description |
|----------|-------------|
| Rapide | Complexité O(log n) |
| Automatique | Pas de tri manuel |
| Fiable | Pas d'erreur d'ordre |

---

# DIAPOSITIVE 7 : DONNÉES GÉRÉES

## 📊 Données d'un Étudiant

| Champ | Type | Description |
|-------|------|-------------|
| **Nom** | Texte | Nom de famille |
| **Prénom** | Texte | Prénom |
| **Classe** | Texte | Niveau/filière |
| **Email** | Texte | Adresse email |
| **Matricule** | Texte | Identifiant unique ⚠️ |
| **Sexe** | Texte | Genre (M/F) |

---

# DIAPOSITIVE 8 : ARCHITECTURE

## 🏗️ Architecture du Projet

### Structure
```
gestion_etudiants/
├── CMD_gestion/       # Version Console
├── GUI_gestion/       # Version Graphique (GTK+)
├── functions/         # Fonctions partagées
├── libs/              # Headers
└── data/              # Fichier CSV
```

### Deux Interfaces
1. **Console (CMD)** : Ligne de commande avec couleurs
2. **Graphique (GUI)** : Interface GTK+ 3.0

---

# DIAPOSITIVE 9 : ALGORITHME DE RECHERCHE

## 🔍 Recherche Binaire : Cher_pos_ins()

### Complexité : O(log n)
- Très efficace même pour 1000 étudiants

### Étapes
```
1. Début = 0, Fin = n-1
2. Calculer le milieu
3. Comparer avec l'élément du milieu
4. Éliminer la moitié pertinente
5. Répéter jusqu'à trouver la position
```

---

# DIAPOSITIVE 10 : ALGORITHME D'INSERTION

## ➕ Insertion avec Décalage

### Étapes
```
1. Vérifier si le matricule existe (O(n))
2. Trouver la position (O(log n))
3. Décaler les éléments vers la droite (O(n))
4. Insérer le nouvel étudiant
5. Sauvegarder dans le fichier CSV
```

### Complexité Totale
- **Temps** : O(n) dans le pire cas
- **Mémoire** : Tableau statique (1000 étudiants max)

---

# DIAPOSITIVE 11 : FORMAT CSV

## 📄 Format des Données

### Structure
```csv
nom;prenom;classe;email;matricule;sex
Dupont;Jean;L1 Info;jean.dupont@ustm.fr;MAT001;M
Martin;Marie;L2 Info;marie.martin@ustm.fr;MAT002;F
```

### Caractéristiques
- **Délimiteur** : Point-virgule (;)
- **Compatibilité** : Excel, LibreOffice, Google Sheets
- **Gestion** : Guillemets, caractères spéciaux

---

# DIAPOSITIVE 12 : FONCTIONNALITÉS

## ⚙️ Fonctionnalités Implémentées

| Fonctionnalité | Description |
|-----------------|-------------|
| ➕ **Ajouter** | Insertion triée automatique |
| 📋 **Afficher** | Liste complète formatée |
| 🔍 **Rechercher** | Recherche par nom |
| ✏️ **Modifier** | Mise à jour par matricule |
| 🗑️ **Supprimer** | Suppression par matricule |
| ↕️ **Trier** | Par nom ou par classe |

---

# DIAPOSITIVE 13 : INTERFACE CONSOLE

## 💻 Version Console (CMD)

### Caractéristiques
- Menu interactif
- Couleurs ANSI
- Messages d'erreur/succès
- Saisie sécurisée

### Capture d'écran (Concept)
```
========================================
     GESTION DES ÉTUDIANTS - USTM
========================================

     1. Ajouter un étudiant
     2. Afficher tous les étudiants
     3. Rechercher par nom
     0. Quitter

     Votre choix : _
```

---

# DIAPOSITIVE 14 : INTERFACE GRAPHIQUE

## 🖥️ Version Graphique (GTK+)

### Composants
- **Champs de saisie** : Nom, Prénom, Classe, Email, Matricule, Sexe
- **Boutons** : Insérer, Afficher, Rechercher, Modifier, Supprimer
- **TreeView** : Affichage tabulaire

### Bibliothèques
- GTK+ 3.0
- GLib
- GDK

---

# DIAPOSITIVE 15 : APPLICATIONS AU GABON

## 🌍 Contexte Gabonais

### Problématiques Locales
1. **Gestion administrative** des milliers d'étudiants
2. **Archives mixtes** (papier → numérique)
3. **Ressources limitées** (infrastructure)

### Solutions Proposées

| Institution | Application |
|-------------|-------------|
| USTM / UOB | Gestion des inscriptions |
| Lycées / Collèges | Gestion des élèves |
| Administrations | Archives numériques |

---

# DIAPOSITIVE 16 : CAS D'USAGE

## 💼 Exemples d'Utilisation

### 1. Inscription Annuelle
- Ajout de centaines de nouveaux étudiants
- Tri automatique par nom
- Matricule unique généré

### 2. Mise à Jour
- Changement de classe
- Modification d'email
- Correction d'erreurs

### 3. Recherche
- Retrouver un étudiant par son nom
- Préparer les listes d'examens

---

# DIAPOSITIVE 17 : AVANTAGES TECHNIQUES

## ✨ Points Forts du Système

| Avantage | Description |
|----------|-------------|
| **Léger** | Fonctionne sur PC modeste |
| **Gratuit** | Pas de licence, open source |
| **Standard** | Format CSV interopérable |
| **Efficace** | Recherche binaire O(log n) |
| **Double interface** | Console ou GUI |

---

# DIAPOSITIVE 18 : COMPÉTENCES ACQUISES

## 🎓 Objectifs Pédagogiques Atteints

- ✅ Programmation **modulaire** en C
- ✅ Utilisation des **structures de données**
- ✅ **Algorithmes** de recherche et tri
- ✅ Gestion de **fichiers** (CSV)
- ✅ Développement d'**interfaces** (Console/GUI)
- ✅ Utilisation du **Makefile**

---

# DIAPOSITIVE 19 : PERSPECTIVES

## 🚀 Améliorations Futures

### Court Terme
- [ ] Export PDF des listes
- [ ] Import depuis Excel

### Long Terme
- [ ] Base de données SQLite
- [ ] Interface Web
- [ ] Application mobile

---

# DIAPOSITIVE 20 : CONCLUSION

## 📝 Résumé

Ce projet a permis de développer :
- Une **application complète** de gestion des étudiants
- **Deux interfaces** (Console et GUI)
- Un **algorithme performant** de recherche binaire
- Une **solution adaptée** au contexte africain

### Message Final
> *"La programmation avancée permet de résoudre des problèmes réels avec efficacité et élégance."*

---

# DIAPOSITIVE 21 : REMERCIEMENTS

## 🙏 Remerciements

**À :**
- Notre professeur de Programmation Avancée
- L'USTM pour l'environnement de travail
- Nos camarades pour la collaboration

**Contact :**
- Email : [À compléter]
- Université : USTM

---

# DIAPOSITIVE 22 : QUESTIONS

## ❓ Questions ?

### Merci de votre attention !

*N'hésitez pas à poser vos questions*

---

# INFORMATIONS SUPPLÉMENTAIRES

## Pour créer le fichier PPTX

Vous pouvez utiliser l'un des outils suivants :

1. **Microsoft PowerPoint** (Windows/Mac)
2. **LibreOffice Impress** (Linux/Windows/Mac)
3. **Google Slides** (En ligne)
4. **pandoc** (Conversion depuis Markdown)

### Exemple avec pandoc :
```bash
pandoc -o presentation.pptx Presentation_PowerPoint.md
```

### Suggestion de design :
- Couleurs : Bleu USTM (#003366)
- Police : Arial ou Liberation Sans
- Images : Logo USTM, captures d'écran

---

**Fin de la présentation**

