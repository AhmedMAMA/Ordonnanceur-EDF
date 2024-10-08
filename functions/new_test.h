#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define INT_MAX 99999
#define INT_MIN -9999
int tmp_exc = 0; // Compteur
// Structure représentant une tâche
typedef struct {
    int id;         // Numéro de la tâche
    int execution_time; // Temps d'exécution initial
    int deadline;     // Deadline de la tâche
    int period;      // Période de la tâche
    int priority;    // Priorité de la tâche
    int tache_en_attente; // Tâche en attente
    int nbre_exc; // Nombre d'éxecution par tâche
    int remaining_time;        // Temps d'exécution restant
} Tache;

typedef struct
{
    int tache_num;
    int* period_absolu;
    int* deadline_absolue;
}DeadLineRelative;



#ifndef EDF_FUNCTION
#define EDF_FUNCTION
void PetitePeriod(Tache*, int, int*, int);
void execution(Tache* , int ,int );
#endif

// Fonction pour la détermination de la grande deadline 
int BigDeadline(Tache task[],int n){
    int busy_period = 0;
    int previous_period = -1;
    int t = 1;
    while (busy_period != previous_period) {
        previous_period = busy_period;
        busy_period = 0;
        
        for (int i = 0; i < n; i++) {
            busy_period += (int) ceil((double)t / (double)task[i].period) * task[i].execution_time;
        }
        t = busy_period;
    }
    printf("\033[1;34m" "Notre Busy_Period vaut %d\n""\033[0m", busy_period);
    return busy_period;
}


// Afficher les tâches
void display_tasks(Tache tasks[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Tâche %d: Période = %d, Deadline = %d, Temps d'exécution = %d,  Temps d'exécution restant = %d, Nombre d'exécution = %d\n", 
            tasks[i].id,tasks[i].period, tasks[i].deadline, tasks[i].execution_time, tasks[i].remaining_time,tasks[i].nbre_exc);
    }
}

// Mettre à jours les temps d'exécution restant & de la tâche en attente
void RemainingTime(Tache task[],int n){
    for(int i = 0; i < n; i++){
        task[i].remaining_time = task[i].execution_time;
        task[i].tache_en_attente = -1;
    }
}

// Recherche la tâche avec la plus proche échéance qui n'est pas en cours d'exécution
int TachePrioritaire(Tache task[], int n) {
    int tache = -1;  // Initialiser à -1 pour indiquer aucune tâche trouvée
    int min_deadline = INT_MAX; // Initialiser à une valeur très élevée pour comparer les deadlines

    for (int i = 0; i < n; i++) {
        // Vérifier si la tâche est prête à être exécutée (remaining_time > 0)
        if (task[i].remaining_time > 0 && task[i].deadline < min_deadline) {
            min_deadline = task[i].deadline; // Mettre à jour la plus petite deadline
            tache = i; // Mettre à jour l'index de la tâche prioritaire
        }
    }

    if (tache != -1) {
        printf("\033[1;34m""Tâche à exécuter : %d  |=|  A t =%d \n""\033[0m", task[tache].id,tmp_exc); // Afficher l'identifiant de la tâche
    } else {
        printf("\033[1;34m""Aucune tâche prête à exécuter.\n""\033[0m");
    }
    return tache;  // Retourner l'index de la tâche avec la plus petite deadline ou -1 si aucune
}


// Verifier si la tâche en cours à atteint l'instant d'activation d'une autre
int verifier_temps_activation(int tableau[], int taille) {
    int min_neg = INT_MIN; // Initialiser à la plus petite valeur possible
    int trouve = 0; // Indique si une valeur négative a été trouvée
    int tache;

    for (int i = 0; i < taille; i++) {
        if (tableau[i] < 0) { // Vérifie si la valeur est négative
            if (trouve == 0 || tableau[i] > min_neg) {
                min_neg = tableau[i]; // Mettre à jour la plus petite valeur négative
                trouve = 1; // Une valeur négative a été trouvée
                tache = i;
            }
        }
    }
    return trouve ? tache : -1; 
}

int IdentifieurPetitTime(int tableau[], int taille) {
    int min_neg = INT_MIN; // Initialiser à la plus petite valeur possible
    int trouve = 0; // Indique si une valeur négative a été trouvée

    for (int i = 0; i < taille; i++) {
        if (tableau[i] < 0) { // Vérifie si la valeur est négative
            if (trouve == 0 || tableau[i] > min_neg) {
                min_neg = tableau[i]; // Mettre à jour la plus petite valeur négative
                trouve = 1; // Une valeur négative a été trouvée
            }
        }
    }
    // Retourner -1 si aucune valeur négative n'a été trouvée
    return trouve ? min_neg : -1; 
}

//Ajustement des deadline des tâches pour un ebonne config
void PetitePeriod(Tache task[], int n, int* period_absolu, int tache_en_attente) {
    int tmp = IdentifieurPetitTime(period_absolu,n);
    int next_cout = task[tache_en_attente].remaining_time;
    task[tache_en_attente].remaining_time += tmp;
    // task[tache_en_attente].execution_time = task[tache_en_attente].execution_time - task[tache_en_attente].remaining_time;
    printf("\033[1;31m" "\n\nInterruption de la tâche %d pour %ds.\n""\033[0m",tache_en_attente + 1,task[tache_en_attente].execution_time );
    execution(task,n,tache_en_attente);
    task[tache_en_attente].remaining_time = next_cout - task[tache_en_attente].remaining_time;
}

// Exécition de l'algo EDF
void execution(Tache task[], int n,int tache_prioritaire){
    DeadLineRelative deadline;
    deadline.deadline_absolue = (int*) malloc(n * sizeof(int));
    deadline.period_absolu = (int*) malloc(n * sizeof(int));
    // printf("\033[1;34m""\n\nCalculs des dealines relatives :\n\n""\033[0m");
    // Calcul des deadline relative de la tâche à exécuter par rapport au autres tâches y compris elle
    for (int i = 0; i < n; i++)
    {
        deadline.deadline_absolue[i] = task[i].deadline - tmp_exc - task[tache_prioritaire].remaining_time;
        deadline.period_absolu[i] = task[i].period - tmp_exc - task[tache_prioritaire].remaining_time;
        // printf("Tache %d : Deadline_absolue = %d Period_absolu = %d\n",i + 1,deadline.deadline_absolue[i],deadline.period_absolu[i]);
    }

    // Vérifie que l'instant de la tâche en cours ne dépasse pas sa propre deadline
    if(tmp_exc + task[tache_prioritaire].remaining_time >= task[tache_prioritaire].deadline * (task[tache_prioritaire].nbre_exc + 1) ) printf("Dépassment de la deadline\n"); //Control
    else{
        // Identifier si la tâche en cours doit être interompu pour une tâche prioritaire
        int tache_suivant = verifier_temps_activation(deadline.period_absolu,3);
        if(tache_suivant!=-1){//
            task[tache_suivant].remaining_time = task[tache_suivant].execution_time;
            PetitePeriod(task,n,deadline.period_absolu,tache_prioritaire);
            task[tache_suivant].deadline += tmp_exc;
            task[tache_suivant].period += tmp_exc;
        }
        else{
            printf("\033[1;32m""\nLa tâche %d est exécutée complétement pour %ds à t= %ds\n\n""\033[0m", tache_prioritaire +1,task[tache_prioritaire].remaining_time ,tmp_exc);
            tmp_exc += task[tache_prioritaire].remaining_time;
            task[tache_prioritaire].remaining_time = 0;
            task[tache_prioritaire].nbre_exc++; 
        }   
    }
    free(deadline.deadline_absolue );
    free(deadline.period_absolu );
}

// Validation
void ValidationSyst(Tache tache[],int n){
    int valide;
    for (int i = 0; i < n; i++)
    {
        if(tache[i].remaining_time == tache[i].execution_time || tache[i].remaining_time == 0) valide ++;
    }
    if(valide == n) printf("Système faisable"); else printf("Système non faisable");
}

// Lecteur fichier
int lire_fichier_taches(const char* chemin, Tache** tableau, int* taille) {
    FILE* fichier = fopen(chemin, "r");
    if (fichier == NULL) {
        printf("\033[1;31m""Erreur : impossible d'ouvrir le fichier %s\n""\033[0m", chemin);
        return -1;
    }

    // Compter le nombre de tâches dans le fichier
    int compteur = 0;
    Tache tache_temp;
    while (fscanf(fichier, "%d %d %d %d %d ", 
                  &tache_temp.id, &tache_temp.execution_time, &tache_temp.deadline,
                  &tache_temp.period, &tache_temp.priority) == 5) {
        compteur++;
    }

    // Allouer la mémoire pour le tableau de tâches
    *tableau = (Tache*)malloc(compteur * sizeof(Tache));
    if (*tableau == NULL) {
        printf("\033[1;31m""Erreur : impossible d'allouer la mémoire\n""\033[0m");
        fclose(fichier);
        return -1;
    }

    // Revenir au début du fichier pour lire les tâches
    rewind(fichier);

    // Lire les tâches et les stocker dans le tableau
    int index = 0;
    while (fscanf(fichier, "%d %d %d %d %d", 
                  &(*tableau)[index].id, &(*tableau)[index].execution_time, 
                  &(*tableau)[index].deadline, &(*tableau)[index].period, 
                  &(*tableau)[index].priority) == 5) {
        index++;
    }

    // Fermer le fichier et renvoyer le nombre de tâches lues
    fclose(fichier);
    *taille = compteur;
    return 0;
}



// Primary function that equal to the main
int MAIN_EDF(){
    Tache* tache = NULL; // Initialiser tache à NULL
    int taille = 0;      // Initialiser taille à 0
    char* chemin = malloc(150 * sizeof(char)); // Allocation de mémoire pour le chemin
    char* nom_fichier = malloc(100 * sizeof(char)); // Allocation de mémoire pour le nom de fichier

    // Vérifier si l'allocation a réussi
    if (chemin == NULL || nom_fichier == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return 1; // Sortir avec une erreur
    }

    // Message d'avertissement avec une partie colorée
    printf("\033[1;31m" "Veuillez à ce que le fichier à entrer respecte la structure ligne : "
           "N°tache Coût Deadline Période Priorité & est(sont) stocké(s) dans le dossier data"
           "\033[0m" "\n");

    // Demander à l'utilisateur de saisir le nom du fichier
    printf("Entrez le nom du fichier : ");
    scanf("%99s", nom_fichier);  // Limiter la saisie à 99 caractères pour éviter le dépassement

    // Construire le chemin complet du fichier en concaténant
    strcpy(chemin, "../data/");  // Copier le chemin de base
    strcat(chemin, nom_fichier);    // Ajouter le nom du fichier

    printf("chemin : %s\n", chemin);

    // Lire les tâches à partir du fichier
    if (lire_fichier_taches(chemin, &tache, &taille) == 0) {
        printf("\033[1;32m" "Lancement de l'algorithme EDF.....\n" "\033[0m");
        RemainingTime(tache, taille);
        int bigdeadline = BigDeadline(tache, taille);
        for (int i = 0; i < bigdeadline; i++) {
            execution(tache, taille, TachePrioritaire(tache, taille));
            display_tasks(tache, taille);
        }
        ValidationSyst(tache, taille);
        RemainingTime(tache, taille);
    } else {
        printf("\033[1;31m""Erreur lors de la lecture des tâches.\n""\033[0m");
    }

    // Libérer la mémoire
    free(chemin);
    free(nom_fichier);
    free(tache); // Assurez-vous que tache a été alloué dynamiquement dans lire_fichier_taches

    return 0;

}