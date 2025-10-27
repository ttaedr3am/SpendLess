#include "tracker.h"

void addTransaction(char username[]) {
    struct Transaction t;
    char filename[60];
    sprintf(filename, "users/%s_data.txt", username);

    printf("\nEnter transaction type (give/take): ");
    scanf("%s", t.type);
    printf("Enter amount: ");
    scanf("%f", &t.amount);
    printf("Enter note (e.g., food, rent, etc.): ");
    scanf("%s", t.note);

    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%s %.2f %s\n", t.type, t.amount, t.note);
    fclose(file);

    printf("Transaction added successfully!\n");
}

void viewTransactions(char username[]) {
    char filename[60], type[10], note[50];
    float amount;
    sprintf(filename, "users/%s_data.txt", username);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No transactions yet.\n");
        return;
    }

    printf("\n--- Transaction History for %s ---\n", username);
    while (fscanf(file, "%s %f %s", type, &amount, note) != EOF) {
        printf("%-6s  %-10.2f  %s\n", type, amount, note);
    }
    fclose(file);
}

void calculateBalance(char username[]) {
    char filename[60], type[10], note[50];
    float amount, balance = 0;
    sprintf(filename, "users/%s_data.txt", username);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No transactions to calculate balance.\n");
        return;
    }

    while (fscanf(file, "%s %f %s", type, &amount, note) != EOF) {
        if (strcmp(type, "give") == 0)
            balance -= amount;
        else if (strcmp(type, "take") == 0)
            balance += amount;
    }
    fclose(file);

    printf("\nCurrent Balance: %.2f\n", balance);
}
