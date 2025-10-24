#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "grid.h"
#include "win.h"
#include "fonctions.h"
#include "struct.h"


int check_defaite(char board[], position *pos);


int main()
{
    srand(time(NULL));
    char board[100] = {
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
        };
        print_welcome();
        printf(" \n");
        printf(" \n");
        printf(" \n");
        printf(" \n");


        position pos;
        pos.pos_user = placer_user(board, 'O');
        pos.pos_box = placer_box(board, 'X');
        pos.pos_objectif = placer_objectif(board, '.');
        print_positions(&pos);
        print_grid(board);

    while (1)
    {
        // Demande  l'utilisateur de choisir la direction qu'il veut prendre ou s'il veut quitter le jeu
        char move_user;
        printf("Déplace le joueur (z/q/s/d) ou 'l' pour quitter : \n");
        scanf(" %c", &move_user);
        if (move_user == 'l') break;
        move(board, &pos, move_user);




        // Condition d'arrêt qui arrête le jeu une fois que la box est sur le '.'
        if (board[pos.pos_box] == board[pos.pos_objectif])
        {
            print_positions(&pos);
            print_grid(board);
            printf("Bravo !\n");
            print_win();
            break;
        }

        if (check_defaite(board, &pos) == 1)
        {
            print_positions(&pos);
            print_grid(board);
            printf("Défaite ! \n");
            print_loose();
            break;
        }
        
        print_positions(&pos);
        print_grid(board);
    }
    exit(0);
}
