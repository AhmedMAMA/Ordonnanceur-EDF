#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
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
        printf("Tâche à exécuter : %d\n\n\n", task[tache].id); // Afficher l'identifiant de la tâche
    } else {
        printf("Aucune tâche prête à exécuter.\n");
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
    // Retourner -1 si aucune valeur négative n'a été trouvée
    return trouve ? tache : -1; 
}

// Exécition de l'algo EDF
void execution(Tache task[], int n,int tache_prioritaire){
    printf("tmp_exec : %d|=| tache_prioritaire : %d\n\n",tmp_exc,tache_prioritaire+1);
    DeadLineRelative deadline;
    deadline.deadline_absolue = (int*) malloc(n * sizeof(int));
    deadline.period_absolu = (int*) malloc(n * sizeof(int));

    // Calcul des deadline relative de la tâche à exécuter par rapport au autres tâches y compris elle
    for (int i = 0; i < n; i++)
    {
        deadline.deadline_absolue[i] = task[i].deadline - tmp_exc - task[tache_prioritaire].remaining_time;
        deadline.period_absolu[i] = task[i].period - tmp_exc - task[tache_prioritaire].remaining_time;
        printf("Tache %d : Deadline_absolue = %d Period_absolu = %d\n ",i + 1,deadline.deadline_absolue[i],deadline.period_absolu[i]);
    }

    // Vérifie que l'instant de la tâche en cours ne dépasse pas sa propre deadline
    if(tmp_exc + task[tache_prioritaire].remaining_time >= task[tache_prioritaire].deadline){
        printf("tmp_exc %d |=| tmp_exc + task[tache_prioritaire].execution_time : %d\n",tmp_exc,tmp_exc + task[tache_prioritaire].execution_time);
        printf("Dépassment de la deadline\n"); //Control
    }
    else{
        // Identifier si la tâche en cours doit être interompu pour une tâche prioritaire
        int tache_suivant = verifier_temps_activation(deadline.period_absolu,3);
        if(tache_suivant!=-1){
            printf("Interruption de la tâche %d pour exécuter la tâche %d\n", tache_prioritaire +1, tache_suivant);
        }
        else{
            // 
            printf("La tâche %d est exécutée pour %ds a t= %ds\n", tache_prioritaire +1,task[tache_prioritaire].remaining_time ,tmp_exc);
            task[tache_prioritaire].remaining_time = 0;
            tmp_exc += task[tache_prioritaire].execution_time;
            task[tache_prioritaire].nbre_exc++; 
        }   
    }
}


// Revoir utilité de cette fonction
int periodEtudde(Tache* task, int n) {
    int t = 1;   // Temps courant
    int W = 0;   // Temps de réponse accumulé

    // Boucle jusqu'à ce que toutes les tâches soient prises en compte
    for (int i = 0; i < n; i++) {
        W +=(int)ceil((t / task[i].period) * task[i].execution_time); // Corriger la division
        if (t == W) {  // Si t et W sont égaux, sortir de la boucle
            break;
        }
        t = W;  // Mettre à jour t avec W
    }
    
    return W; // Retourner la valeur de W
}