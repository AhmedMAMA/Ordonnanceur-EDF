#include"../functions/new_test.h"
#include"../functions/highest first priority.h"
int main(){
    int choix =0;
    // do
    // {
    printf("\033[37m""Bienvenue sur le logiciel de similation des ordonnanceur temps réels EDF & HPF\nFaite votre choix d'algorythme:\n1- EDF\n2- HPF.\n\nVotre choix : ""\033[0m");
    scanf("%d",&choix);
    switch (choix)
    {
        case 1:
            MAIN_EDF();
            break;
        case 2:
            MAIN_HPF();
            break;
        default:
            printf("\033[34m""Fin de simulation.!!!""\033[0m");
            break;
    }    
}