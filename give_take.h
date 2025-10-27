#ifndef GIVE_TAKE_H
#define GIVE_TAKE_H

struct Transaction {
    char type[10];  // "Give" or "Take"
    char person[30];
    float amount;
    char deadline[20];
    struct Transaction *next;
};

void giveTakeMenu(char username[50]);

#endif
