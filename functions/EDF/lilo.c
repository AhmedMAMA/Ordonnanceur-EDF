
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int exec_time;
    int deadLine;
    int periode;
    int priorite;
    _Bool deja_lance;
    int nbre_exec_deja_realisees;
} Taches;

void execution(Taches *taches,int nbre_taches, int busy_period,int index_actuel)
{
    /* printf("index %d : \n\n",index_actuel);
    for (int i = 0; i < nbre_taches; i++)
    {
        printf("tache[%d], nbre_realise = %d",i,taches[i].nbre_exec_deja_realisees);
        if(taches[i].deja_lance)printf(",deja lance \n");else printf("\n");
        
    }  */

   //On peut ajouter des conditions pour verifier que l index_actuelle n 'est pas negatif ou que
   //la busy_period n 'est pas negatif ou est superieur a l index actuel
     if(index_actuel == busy_period)
        {
            printf("\nTermine....!!!\n\n");
        }
    else
        {
            int index_tache_a_executer = 0, distances_to_deadlines[nbre_taches];
            for (int i = 0; i < nbre_taches; i++)
                {
                    distances_to_deadlines[i] = taches[i].deadLine - index_actuel;
                    if(distances_to_deadlines[i] <=  0 )while(distances_to_deadlines[i] <= 0) distances_to_deadlines[i] += taches[i].periode;
                           
                }


            for(int i = 0; i < nbre_taches ; i++)
                {
                 //   printf("index_actuel = %d,tache[%d],nbre_deja_realisees = %d,deadline = %d\n",index_actuel,i,taches[i].nbre_exec_deja_realisees,taches[i].deadLine);
                    if(taches[i].exec_time > taches[i].nbre_exec_deja_realisees)
                        {
                            //printf("tache[%d],distance_to_deadline = %d\n",i,distances_to_deadlines[i]);
                            if(distances_to_deadlines[i] == distances_to_deadlines[index_tache_a_executer])
                                {if(taches[i].deja_lance) index_tache_a_executer = i;}
                            else if(distances_to_deadlines[i] < distances_to_deadlines[index_tache_a_executer])index_tache_a_executer = i;

                        }

                    else 
                        if(index_tache_a_executer == i)index_tache_a_executer++;
                }
            
            printf("\n%d- La tache %d s'execute...\n\n",index_actuel, index_tache_a_executer+1);
            taches[index_tache_a_executer].deja_lance = 1;
            taches[index_tache_a_executer].nbre_exec_deja_realisees++;

            for(int i = 0; i < nbre_taches;i++)
                {
                    if(taches[i].deja_lance){
                        if(index_actuel == taches[i].periode){
                            //printf("la tache[%d] est ici\n",i);
                            taches[i].deja_lance = 0;
                            taches[i].nbre_exec_deja_realisees = 0;
                        }
                        else if(index_actuel > taches[i].periode){
                            //printf("index_actuel = %d, tache[%d].periode = %d, index_actuel (modulo) taches[i].periode = %d\n",index_actuel,i,taches[i].periode,index_actuel%taches[i].periode);
                            if(!(index_actuel%taches[i].periode)){
                                //printf("la tache[%d] est icii\n",i);

                                taches[i].deja_lance = 0;
                                taches[i].nbre_exec_deja_realisees = 0;
                                }
                            }
                            }
                        
                    }
                            
                        
                
  

            index_actuel++;

            execution(taches,nbre_taches,busy_period,index_actuel);

        }
}

Taches creation_de_tache(int id,int exec_time,int deadLine,int periode,int priorite)
{
    Taches tache_creee;
    tache_creee.id = id;
    tache_creee.exec_time = exec_time;
    tache_creee.deadLine = deadLine;
    tache_creee.periode = periode;
    tache_creee.priorite = priorite;
    tache_creee.nbre_exec_deja_realisees = 0;
    tache_creee.deja_lance = 0;
    return tache_creee;
}

int busy_period(Taches *taches, int nbre_de_taches)
{
    int t = 1,W = 1;
    do 
    {
        t = W;
        W = 0;
        for(int i = 0; i < nbre_de_taches;i++)
        {  
            int w = 1 + t/taches[i].periode;
            W += w*taches[i].exec_time;
        }
    }
    while (t != W);
    
    return W;
}

int main(int arg, char const *argv[])
{
    Taches t[3];
    t[0] = creation_de_tache(0,2,4,6,5);
    t[1] = creation_de_tache(1,3,8,8,5);
    t[2] = creation_de_tache(2,1,3,4,5);

    int W = busy_period(t,3);
    

    printf("Busy periode du data set = %d\n\n",W);

    execution(t,3,W+1,1);
    return EXIT_SUCCESS;
}