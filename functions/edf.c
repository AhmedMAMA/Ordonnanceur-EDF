#include "new_test.h"

int main(){
    Tache tache[] = {
        {1, 2, 4, 6, 20},
        {2, 3, 8, 8, 15},
        {3, 1, 3, 4, 10}
    };
    printf("Période de testing : %d",periodEtudde(tache,3));
    printf("Matrice Initial\n");
    display_tasks(tache,sizeof(tache)/sizeof(tache[0]));
    printf("\n\n");
    // display_tasks(tache,sizeof(tache)/sizeof(tache[0]));

    RemainingTime(tache,3);

    printf("Execution 1\n\n");
    execution(tache, 3,TachePrioritaire(tache,3));
    display_tasks(tache,sizeof(tache)/sizeof(tache[0]));
    printf("Execution 2\n\n");
    execution(tache, 3,TachePrioritaire(tache,3));
    printf("\n\n");
    display_tasks(tache,sizeof(tache)/sizeof(tache[0]));
    printf("Execution 3\n\n");
    execution(tache, 3,TachePrioritaire(tache,3));
    printf("\n\n");
    display_tasks(tache,sizeof(tache)/sizeof(tache[0]));
    printf("Execution 4\n\n");
    execution(tache, 3,TachePrioritaire(tache,3));
    printf("\n\n");
    display_tasks(tache,sizeof(tache)/sizeof(tache[0]));

}
