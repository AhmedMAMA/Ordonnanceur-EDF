#include "new_test.h"

int main(){
    tmp_exc =0;
    Tache tache[] = {
        {1, 2, 4, 6, 20},
        {2, 3, 8, 8, 15},
        {3, 1, 3, 4, 10}
    };
    printf("\n\n");

    RemainingTime(tache,3);
    int bigdeadline = BigDeadline(tache,sizeof(tache)/sizeof(tache[0]) + 1);
    for (int i = 0; i < bigdeadline; i++)
    {
        execution(tache,3,TachePrioritaire(tache,3));
        display_tasks(tache,sizeof(tache)/sizeof(tache[0]));
        // printf("tmp_exec : %d - i :%d\n",tmp_exc,i);
    }
    ValidationSyst(tache,3);
    RemainingTime(tache,3);
    
}