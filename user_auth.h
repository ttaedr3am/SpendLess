#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

struct User {
    char username[MAX_LEN];
    char password[MAX_LEN];
};

int signup();
int login();

#endif
