#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "fonctions.h"




int main()
{
    position pos;
    pos.pos_user = placer_user(char board[], char user);
    pos.pos_box = placer_box(char board[], char box);
    pos.pos_objectif = void placer_objectif(char board[], char objectif);

    printf("La position de la case est Y : %d; X : %d\n", pos.pos_user, pos.pos_box, pos.pos_objectif);

    exit(0);
}