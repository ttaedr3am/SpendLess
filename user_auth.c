#include "user_auth.h"

int signup() {
    struct User user;
    char filename[MAX_LEN + 10];
    printf("\nEnter username: ");
    scanf("%s", user.username);

    sprintf(filename, "users/%s.txt", user.username);
    FILE *file = fopen(filename, "r");
    if (file) {
        printf("Username already exists! Try logging in.\n");
        fclose(file);
        return 0;
    }

    printf("Enter password: ");
    scanf("%s", user.password);

    file = fopen(filename, "w");
    fprintf(file, "%s %s\n", user.username, user.password);
    fclose(file);

    printf("Signup successful! You can now log in.\n");
    return 1;
}

int login() {
    struct User user;
    char filename[MAX_LEN + 10];
    char fileUser[MAX_LEN], filePass[MAX_LEN];

    printf("\nEnter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    scanf("%s", user.password);

    sprintf(filename, "users/%s.txt", user.username);
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("User not found. Please sign up first.\n");
        return 0;
    }

    fscanf(file, "%s %s", fileUser, filePass);
    fclose(file);

    if (strcmp(filePass, user.password) == 0) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Incorrect password.\n");
        return 0;
    }
}
