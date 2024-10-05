#ifndef HPF
#define HPF
#include "./struct.h"
int RechercheTachePrioritaire(Tache*, int, int);
void deadlineRelative(Tache*, int, int, Tache*);
bool FiniHighestFirstPriority(Tache*, int);
bool etudeFaisabilite(int*,int);
int* highestFirstPriority(Tache*, Tache* , int);
#endif
/*
    * SI la deadline & la période ne sont pas égales.*
*/

// Recherche la tâche dont la priorité est haute et qui n'est pas en cours exétuer au travers de la tâchAcctuelle
int RechercheTachePrioritaire(Tache* taches, int taille,int tacheActuelle) {
    if (taille == 0) {
        return -1; // Si la taille est 0, pas de tâche, retourne une valeur invalide
    }
    int priorite = -1;
    int tache = 1;
    for (int i = 0; i < taille; i++) {
        if (taches[i].priority > priorite && taches[i].time > 0 && tacheActuelle != taches[i].num) {
            priorite = taches[i].priority;
            tache = taches[i].num;
        }
    }
    return tache;
}


void deadlineRelative(Tache* taches,int tachePrioritaire, int taille,Tache* tache_orgine){
    DeadLineRelative deadline_par_rapport_a_tous_tache;
    deadline_par_rapport_a_tous_tache.deadline_relative = (int*) malloc(taille * sizeof(int));
    deadline_par_rapport_a_tous_tache.tache_num = tachePrioritaire;

    // Calcul des deadline relative de la tâche à exécuter par rapport au autres tâches y compris elle
    for (int i = 0; i < taille; i++)
    {
        if(taches[i].deadline!=0){
            deadline_par_rapport_a_tous_tache.deadline_relative[i] = taches[i].deadline - taches[tachePrioritaire - 1].time;
            // taches[i].period -= taches[tachePrioritaire - 1].time;
            taches[i].deadline = deadline_par_rapport_a_tous_tache.deadline_relative[i];
        }
    }


    int tache_avec_deadline_atteinte = -1;
    int plus_valeur_negative = 0;

    // Détection de l'éechéance d'une tâche atteint [Tache_avec_deadline_atteinte]
    for(int i = 0; i < taille; i++){
        if(deadline_par_rapport_a_tous_tache.deadline_relative[i] < plus_valeur_negative){
            plus_valeur_negative = deadline_par_rapport_a_tous_tache.deadline_relative[i];
            tache_avec_deadline_atteinte = taches[i].num;
        }
    }

    if(plus_valeur_negative!=0) // Présence de tâche dont la deadline est atteinte
    {
        int time_original = taches[tachePrioritaire - 1].time;
        deadline_par_rapport_a_tous_tache.new_time = time_original + taches[tache_avec_deadline_atteinte - 1].deadline;
        for(int i = 0; i < taille; i++){
            if(taches[i].deadline!=0){
                deadline_par_rapport_a_tous_tache.deadline_relative[i] = taches[i].deadline - taches[tache_avec_deadline_atteinte - 1].deadline;
                // taches[i].period -= taches[tachePrioritaire - 1].time;
            }
        }
        for(int i = 0; i < taille; i++){
            if(i < tachePrioritaire -1 && taches[i].deadline != 0){
                taches[i].time = tache_orgine[i].time;
                // taches[i].period = tache_orgine[tachePrioritaire - 1].period;
            }
            taches[i].deadline = deadline_par_rapport_a_tous_tache.deadline_relative[i];
        }
        taches[tachePrioritaire-1].time = time_original - deadline_par_rapport_a_tous_tache.new_time;
    }
    else taches[tachePrioritaire-1].time =0 ;
}

bool FiniHighestFirstPriority(Tache* taches, int nbreTache){
    int nbre_tache_finis = 0;
    for(int i = 0; i < nbreTache; i++){
        if(taches[i].deadline == 0){
            nbre_tache_finis += 1;
        }
    }
    return true ? nbre_tache_finis == nbreTache : false;
}

int* highestFirstPriority(Tache* taches,Tache* tache_orgine, int taille){
    int tacheActuelle = -1;
    printf("Début d'excution...........\n");
    while(!FiniHighestFirstPriority(taches,taille)){
        tacheActuelle = RechercheTachePrioritaire(taches, taille,tacheActuelle);
        deadlineRelative(taches,tacheActuelle,taille,tache_orgine);
        printf("\nTâche en cours d'exécution: %d.\n\nSortie de l'exécution : \n",tacheActuelle);
        for (int i = 0; i < taille; i++)
        {
            printf("Tâche: %d - Durée : %d - Echeance :%d - Période : %d - Priorité : %d\n",taches[i].num,taches[i].time,taches[i].deadline,taches[i].period, taches[i].priority);
        }
    }
    int* lastTime = (int*) malloc(taille * sizeof(int));
    for (int i = 0; i < taille; i++)lastTime[i] = taches[i].time;
    return lastTime;
}


bool etudeFaisabilite(int* time, int taille){ // Retour True si pas_zero vaut 0;
    int pas_zero = 0;
    // int test = (sizeof(time)/sizeof(time[0])) +1;
    // printf("test de time dans etudeFaisabilite: %d \n",test);
    for(int i = 0; i < taille; i++){
        if(time[i] != 0) pas_zero += 1; 
    }
    return pas_zero == 0;
};