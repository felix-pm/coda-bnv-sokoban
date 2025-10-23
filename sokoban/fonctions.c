#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "fonctions.h"
#include "grid.h"

int placer_box(char board[], char box) {
    int tab_box[36] = {22, 23, 24, 25, 26, 27, 32, 33, 34, 35, 36, 37, 42, 43, 44, 45, 46, 47, 52, 53, 54, 55, 56, 57, 62, 63, 64, 65, 66, 67, 72, 73, 74, 75, 76, 77};
    int random_index = rand() % 36;
    int random_value = tab_box[random_index];
    board[random_value] = box;
    return random_value;
}

int placer_user(char board[], char user) {
    int pos = rand() % 100;
    while (board[pos] == '#') {
        pos++;
        if (pos >= 100) pos = 0;
    }
    board[pos] = user;
    return pos;
}

int placer_objectif(char board[], char objectif) {
    int pos = rand() % 100;
    while (board[pos] == '#') {
        pos++;
        if (pos >= 100) pos = 0;
    }
    board[pos] = objectif;
    return pos;
}

// Fonction pour déplacer le joueur et pousser la boîte
void move(char board[], position *pos, char move_user) {
    int direction = 0;
    if (move_user == 'q') {
        direction = -1;
    } 
    else if (move_user == 'd') {
        direction = 1;  
        }
    else if (move_user == 'z') {
        direction = -10; 
        }
    else if (move_user == 's') {
        direction = 10; 
        }
    int next_pos = pos->pos_user + direction; 

    // Vérifier si la case cible est vide ou si c'est un objectif
    if (board[next_pos] == ' ' || board[next_pos] == '.') {
        board[pos->pos_user] = ' ';  
        pos->pos_user = next_pos;    
        board[pos->pos_user] = 'O'; 
        return;                  
    }

    // Vérifier si la case cible contient la boîte
    if (next_pos == pos->pos_box) {
        int box_target = pos->pos_box + direction;

        // Déplacement boîte 
        if (board[box_target] == ' ' || board[box_target] == '.') {
            board[pos->pos_box] = ' '; 
            pos->pos_box = box_target; 
            board[pos->pos_box] = 'X';    

            // Déplacer ensuite le joueur dans la case précédemment occupée par la boîte
            board[pos->pos_user] = ' ';
            pos->pos_user = next_pos;
            board[pos->pos_user] = 'O';
        }
        // Sinon, si la boîte est bloquée, rien ne bouge
    }
}

