#ifndef TRACKER_H
#define TRACKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Transaction {
    char type[10];   // "give" or "take"
    char note[50];
    float amount;
    struct Transaction *next;
};

void addTransaction(char username[]);
void viewTransactions(char username[]);
void calculateBalance(char username[]);

#endif
