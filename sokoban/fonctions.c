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
    while (board[pos] == '#' || board[pos] == 'X' || board[pos] == '.') {
        pos++;
        if (pos >= 100) pos = 0;
    }
    board[pos] = user;
    return pos;
}

int placer_objectif(char board[], char objectif) {
    int pos = rand() % 100;
    while (board[pos] == '#' || board[pos] == 'X' || board[pos] == 'O') {
        pos++;
        if (pos >= 100) pos = 0;
    }
    board[pos] = objectif;
    return pos;
}


void print_positions(position *pos)
{
    printf("\n----------------------------------\n");
    printf("Localisations actuelles :\n");
    printf("   Joueur (O)     → case %d (ligne %d, colonne %d)\n",
           pos->pos_user, pos->pos_user / 10, pos->pos_user % 10);
    printf("   Boîte  (X)     → case %d (ligne %d, colonne %d)\n",
           pos->pos_box, pos->pos_box / 10, pos->pos_box % 10);
    printf("   Objectif (.)   → case %d (ligne %d, colonne %d)\n",
           pos->pos_objectif, pos->pos_objectif / 10, pos->pos_objectif % 10);
    printf("----------------------------------\n\n");
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

    // Vérifier si la case cible est un objectif
    if (board[next_pos] == '.') {
        printf("Vous ne pouvez pas déplacer l'objectif !\n");
        return; // Ne fait rien
    }

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

            // Déplacement du joueur dans la case précédente
            board[pos->pos_user] = ' ';
            pos->pos_user = next_pos;
            board[pos->pos_user] = 'O';
        }
    }
}




int check_defaite(char board[], position *pos) {
    int box = pos->pos_box;
    int objectif = pos->pos_objectif;

    // On note les cases collées aux murs
    int mur_haut[8]   = {11, 12, 13, 14, 15, 16, 17, 18};
    int mur_bas[18]    = {81, 82, 83, 84, 85, 86, 87, 88};
    int mur_gauche[8]  = {11, 21, 31, 41, 51, 61, 71, 81};
    int mur_droite[8]  = {18, 28, 38, 48, 58, 68, 78, 88};

    int box_sur_mur = 0;
    int objectif_sur_mur = 0;
    int mur_box = -1; // 0=haut 1=bas 2=gauche 3=droite

    int i = 0;

    // On vérifie si la box est collée à un des murs
    i = 0;
    while (i < 10) {
        if (box == mur_haut[i]) {
            box_sur_mur = 1;
            mur_box = 0;
        }

        if (box == mur_bas[i]) {
            box_sur_mur = 1;
            mur_box = 1;
        }

        if (i < 8 && box == mur_gauche[i]) {
            box_sur_mur = 1;
            mur_box = 2;
        }

        if (i < 8 && box == mur_droite[i]) {
            box_sur_mur = 1;
            mur_box = 3;
        }

        i++;
    }

    // On vérifie si l’objectif est sur le même mur intérieur que la box
    i = 0;
    while (i < 10) {
        if (objectif == mur_haut[i] && mur_box == 0) {
            objectif_sur_mur = 1;
        }

        if (objectif == mur_bas[i] && mur_box == 1) {
            objectif_sur_mur = 1;
        }

        if (i < 8 && objectif == mur_gauche[i] && mur_box == 2) {
            objectif_sur_mur = 1;
        }

        if (i < 8 && objectif == mur_droite[i] && mur_box == 3) {
            objectif_sur_mur = 1;
        }

        i++;
    }

    // On vérifie si la box n’est pas collée à un mur continue
    if (!box_sur_mur) {
        return 0;
    }

    // On vérifie si la boîte est collée à un mur mais que l’objectif n’est pas sur le même mur, c'est une défaite
    if (box_sur_mur && !objectif_sur_mur) {
        return 1;
    }

    return 0;
}
