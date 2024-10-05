#include"./highest first priority.h"

int main(int argc, char const *argv[])
{
    Tache tab_origine[] = {
        {1, 2, 7, 7, 20},
        {2, 3, 11, 11, 15},
        {3, 5, 13, 13, 10}
    };
    Tache tab[3];
    for (int i = 0; i < 3; i++) {
        tab[i] = tab_origine[i];  // Copie de chaque élément
    }
    // if()
    int res = etudeFaisabilite(highestFirstPriority(tab,tab_origine, 3),3);
    printf("Automate Faisable car pas de dépasssement de deadline\n") ? res == 0 : printf("Automate non Faisable car dépasssement de deadline\n");

    return 0;
}
