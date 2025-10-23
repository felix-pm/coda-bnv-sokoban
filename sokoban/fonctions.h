#ifndef TESTS_FONCTIONS_H
#define TESTS_FONCTIONS_H
#include "struct.h"




int placer_user(char board[], char user);
int placer_box(char board[], char box);
int placer_objectif(char board[], char objectif);
void move(char board[], position *pos, char direction);

#endif
