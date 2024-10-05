#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef STANDARD_H
#define STANDARD_H

// STructure de la donnée fournie
typedef struct
{
    int num;
    int time;
    int deadline;
    int period;
    int priority;
}Tache;

typedef struct
{
    int tache_num;
    int new_time;
    int next_tache;
    int next_taches;
    int* deadline_relative;
}DeadLineRelative;



#endif // STANDARD_H