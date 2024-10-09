# ![](https://www.efrei.fr/wp-content/uploads/2022/01/LOGO_EFREI-PRINT_EFREI-WEB.png)

# Rapport sur l'implémentation des Ordonnanceur de planification de temps réels en C

## Auteurs Du Projet & Responsable d'enseignement
* **``Responsable``** : ****Lamine BOUGUEROUA****
*   **``Auteur``** : **Rodrigue Laurel DO REGO && Ahmed MAMA**

## Introduction

Le but du TP est d'implémenter dans le language de notre choix deux algorithmes de planification de tâche **``Earliest Deadline First (EDF)`` et Highest ``Priority First (HPF)``**. Nous avions opté pour le language C car c'est le language native du temps réel qui permet de prendre le contrôle sur les actions que doivent mené les tâches mais aussi pour ``une bonne gestion de la mémoire afin de viser une belle optiminsation``.

## Structure Du Projet

### 1. **Bibliothèques Incluses**

Le code inclut plusieurs bibliothèques standard nécessaires :
- `stdio.h` : pour les entrées/sorties standard.
- `stdlib.h` : pour l'allocation dynamique de mémoire.
- `stdbool.h` : pour l'utilisation de types booléens.
- `math.h` : pour les fonctions mathématiques (comme `ceil`).
- `string.h` : pour la manipulation de chaînes de caractères.

### 2. **Définitions de Constantes**

Les constantes `INT_MAX` et `INT_MIN` sont définies pour représenter les valeurs maximales et minimales utilisées dans les calculs de deadlines & pour la recherche des tâches par priorité.

### 3. **Structures de Données**
#### 3.1 Pour ``EDF`` :

Le code définit deux structures principales pour l'algorithme "**EDF**" :
- `Tache` : représente une tâche avec des attributs tels que l'identifiant, le temps d'exécution, la deadline, la période, la priorité, le nombre d'exécutions.
- `DeadLineRelative` : stocke des informations relatives aux deadlines et aux périodes des tâches en fonction de la position ou du temps d'exécution.
#### 3.2 Pour ``HPF``
Le code définit deux structures principales :
- `TacheHPF` : représente une tâche avec des attributs tels que l'identifiant, le temps d'exécution, la deadline, la période, la priorité, le nombre d'exécutions.
- `DeadLineRelativeHPF` : stocke des informations relatives aux deadlines et aux périodes des tâches en fonction de la position ou du temps d'exécution.
### 3.3 **POURQUOI CETTE STRUCTURE?**
-   Parce que les deux algoritmes n'utilisent pas les même attribut pour fonctionner. Autrement dire; avec ``EDF`` l'on priorise les tâches avec des echéances petite soit (**Période & Deadline**) or avec ``HPF`` c'est le plus grande priorité soit **Période & Priorité**.
### 4. **Fonctions Principales**

#### a. **Fonctions pour ``EDF``**
* **Fonction ``BigDeadline``**

    ```c
    int BigDeadline(Tache task[],int n);
    ```
    Cette fonction détermine le **busy period** (période chargée) en calculant le temps total d'exécution nécessaire pour exécuter toutes les tâches dans un cycle.

* **Fonction ``display_tasks``**

    ```c
    void display_tasks(Tache tasks[], int n);
    ```
    Affiche les informations sur les tâches, y compris leur période, deadline et temps d'exécution restant.

* **Fonction ``RemainingTime``**

    ```c
    void RemainingTime(Tache task[],int n);
    ```
    Met à jour le temps d'exécution restant et initialise les tâches en attente.

* **Fonction ``TachePrioritaire``**

    ```c
    int TachePrioritaire(Tache task[], int n);
    ```
    Identifie la tâche avec la plus proche deadline qui est prête à être exécutée.

* **Fonction ``execution``**

    ```c
    void execution(Tache task[], int n,int tache_prioritaire);
    ```
    Exécute la tâche prioritaire en tenant compte des délais relatifs et met à jour les informations nécessaires.

##### b. FOnctions pour ``HPF``
* **Function ``RechercheTachePrioritaire``**

    ```c
    int RechercheTachePrioritaire(TacheHPF* taches, int taille, int tacheActuelle);
    ```

    Cette fonction recherche et retourne le numéro de la tâche ayant la plus haute priorité qui n'est pas en cours d'exécution. Elle vérifie les priorités et s'assure que la tâche actuelle ne soit pas incluse dans la recherche.

* **Function ``deadlineRelative``**

    ```c
    void deadlineRelative(TacheHPF* taches, int tachePrioritaire, int taille, TacheHPF* tache_orgine);
    ```

    Cette fonction calcule les deadlines relatives des tâches en prenant en compte le temps d'exécution de la tâche prioritaire. Elle met à jour les deadlines des tâches et vérifie si une tâche a dépassé sa deadline.

* **Function ``FiniHighestFirstPriority``**

    ```c
    bool FiniHighestFirstPriority(TacheHPF* taches, int nbreTache);
    ```

    Cette fonction détermine si toutes les tâches ont été terminées en vérifiant leurs deadlines.

* **Function ``highestFirstPriority``**

    ```c
    int* highestFirstPriority(TacheHPF* taches, TacheHPF* tache_orgine, int taille);
    ```

    Cette fonction exécute le plan de tâches selon la méthode de priorité élevée. Elle affiche le statut d'exécution des tâches et retourne le temps restant pour chaque tâche.

* **Function ``etudeFaisabilite``**

    ```c
    bool etudeFaisabilite(int* time, int taille);
    ```
    Vérifie si le plan est faisable en s'assurant qu'il n'y a pas de dépassement de deadlines.
### 5. **Fonctions d'Entrée/Sauvegarde de Données**

#### a. **Fonction ``lire_fichier_taches``**

```c
int lire_fichier_taches(const char* chemin, Tache** tableau, int* taille);
```
Lit les tâches depuis un fichier spécifié et les stocke dans un tableau dynamique.

#### b. **Fonction ``MAIN_EDF``**

```c
int MAIN_EDF();
```
C'est la fonction principale qui exécute l'algorithme. Elle demande à l'utilisateur le nom du fichier contenant les tâches, lit les tâches, et exécute l'algorithme EDF.

#### c. **Function ``MAIN_HPF``**
Fonction principale qui exécute l'algorithme HDF,
en utilisant un tableau statique.

## Execution du projet
Le fichier source servant à exécuter le programme se trouve dans le dossier ``main``.
De plus, son exécution se fais par :
#### **Sur Linux**
```bash
cd Tp_Ahmed_MAMA_Laurel_Rodrigue/main
gcc main.c -lm
```

## Conclusion
Ce rapport présente l'implémentation des algorithmes EDF et HPF pour la planification de tâches en C, mettant en évidence la structure des données, les fonctions clés et le fonctionnement général du code. Ces algorithmes permettent une gestion efficace des ressources dans les systèmes embarqués, en respectant les contraintes de temps imposées par les tâches.
Toutefois, nous avions eu quelques difficultés d'ordre technique dont :
- **La gestion de la mémoire de façon efficace;**
- **Les interruptions pour une gestion cohérentes des tâches;**
- **Le mécanisme de déroulement des tâches.**

## Améliorations envisagées:
#### Le mécanisme de la function HPF pour une exécution depuis un fichier txt avec gestion des interruptoion de façon convenable.