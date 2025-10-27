#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "give_take.h"
// ADDED: Include this to get the reminder functions
#include "goals_reminders.h"

// --- Internal Helper Functions ---
// Made STATIC to fix the linker error

static void loadGiveTakeTransactions(struct Transaction **head, char username[50]) {
    char filename[60];
    sprintf(filename, "%s_transactions.txt", username);
    FILE *fp = fopen(filename, "r");
    if (!fp) return; // No file, nothing to load

    struct Transaction temp;
    while (fscanf(fp, "%s %s %f %s", temp.type, temp.person, &temp.amount, temp.deadline) != EOF) {
        struct Transaction *newNode = (struct Transaction *)malloc(sizeof(struct Transaction));
        if (!newNode) continue; // Malloc failed

        strcpy(newNode->type, temp.type);
        strcpy(newNode->person, temp.person);
        newNode->amount = temp.amount;
        strcpy(newNode->deadline, temp.deadline);
        
        newNode->next = *head;
        *head = newNode;
    }
    fclose(fp);
}

static void saveGiveTakeTransactions(struct Transaction *head, char username[50]) {
    char filename[60];
    sprintf(filename, "%s_transactions.txt", username);
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not save transactions.\n");
        return;
    }
    
    struct Transaction *temp = head;
    while (temp) {
        fprintf(fp, "%s %s %.2f %s\n", temp->type, temp->person, temp->amount, temp->deadline);
        temp = temp->next;
    }
    fclose(fp);
}

// RENAMED: was viewTransactions
static void viewGiveTakeTransactions(struct Transaction *head) {
    if (!head) {
        printf("No transactions yet.\n");
        return;
    }
    printf("\n--- Give/Take List ---\n");
    struct Transaction *temp = head;
    while (temp) {
        printf("%s -> %s : %.2f (till %s)\n", temp->type, temp->person, temp->amount, temp->deadline);
        temp = temp->next;
    }
}

// RENAMED: was addTransaction
// Now takes 'username' to create a reminder
static void addGiveTakeTransaction(struct Transaction **head, const char *username) {
    struct Transaction *newNode = malloc(sizeof(struct Transaction));
    if (!newNode) {
        printf("Error: Memory allocation failed!\n");
        return;
    }

    printf("Is this a Give or Take? ");
    scanf("%s", newNode->type);

    if (strcmp(newNode->type, "Give") == 0) {
        printf("Whom to give: ");
        scanf("%s", newNode->person);
        printf("How much to give: ");
        scanf("%f", &newNode->amount);
        printf("Till when to give (DD/MM/YYYY): ");
        scanf("%s", newNode->deadline);
    } else {
        strcpy(newNode->type, "Take"); // Standardize
        printf("From whom to take: ");
        scanf("%s", newNode->person);
        printf("How much to take: ");
        scanf("%f", &newNode->amount);
        printf("Till when to take (DD/MM/YYYY): ");
        scanf("%s", newNode->deadline);
    }

    newNode->next = *head;
    *head = newNode;
    
    // ADDED: Automatically create the reminder
    // Note: Your addPaymentReminder expects "give" or "take" (lowercase)
    char reminderType[10];
    strcpy(reminderType, newNode->type);
    if (strcmp(reminderType, "Give") == 0) strcpy(reminderType, "give");
    if (strcmp(reminderType, "Take") == 0) strcpy(reminderType, "take");
    
    addPaymentReminder(username, reminderType, newNode->amount, newNode->person);
    printf("✅ Transaction added and reminder set.\n");
}

static void freeGiveTakeList(struct Transaction *head) {
    while(head != NULL) {
        struct Transaction *temp = head;
        head = head->next;
        free(temp);
    }
}

// --- Public Menu Function ---

void giveTakeMenu(char username[50]) {
    struct Transaction *head = NULL;
    int choice;

    // ADDED: Load transactions when menu opens
    loadGiveTakeTransactions(&head, username);

    while (1) {
        printf("\n--- Give/Take Menu ---\n");
        printf("1. Add Give/Take\n");
        printf("2. View Give/Take List\n");
        printf("3. View Give/Take Reminders\n"); // ADDED
        printf("4. Back to Main Menu\n"); // CHANGED
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // CHANGED: Call renamed function
                addGiveTakeTransaction(&head, username);
                saveGiveTakeTransactions(head, username);
                break;
            case 2:
                // CHANGED: Call renamed function
                viewGiveTakeTransactions(head);
                break;
            case 3:
                // ADDED: Call reminder function
                viewPaymentReminders(username);
                break;
            case 4:
                // CHANGED: Save, free memory, and return
                saveGiveTakeTransactions(head, username);
                freeGiveTakeList(head);
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}