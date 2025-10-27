#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "goals_reminders.h"

// ====================== SAVING GOALS =========================

void addGoal(struct Goal **head) {
    struct Goal *newGoal = (struct Goal *)malloc(sizeof(struct Goal));
    printf("Enter goal name: ");
    scanf(" %[^\n]", newGoal->name);
    printf("Enter target amount: ");
    scanf("%f", &newGoal->target);
    printf("Enter deadline (DD/MM/YYYY): ");
    scanf("%s", newGoal->deadline);
    newGoal->saved = 0;
    newGoal->next = *head;
    *head = newGoal;
    printf("✅ Goal '%s' added successfully!\n", newGoal->name);
}

void updateGoal(struct Goal *head) {
    if (!head) {
        printf("No goals to update.\n");
        return;
    }

    char name[50];
    printf("Enter goal name to update: ");
    scanf(" %[^\n]", name);

    struct Goal *temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            float add;
            printf("Enter amount to add: ");
            scanf("%f", &add);
            temp->saved += add;

            if (temp->saved >= temp->target)
                printf("🎉 Goal '%s' achieved!\n", temp->name);
            else
                printf("Progress updated. Remaining: %.2f\n", temp->target - temp->saved);
            return;
        }
        temp = temp->next;
    }
    printf("Goal not found.\n");
}

void viewGoals(struct Goal *head) {
    if (!head) {
        printf("No goals set.\n");
        return;
    }

    printf("\n==== SAVING GOALS ====\n");
    while (head) {
        printf("Goal: %s\nTarget: ₹%.2f | Saved: ₹%.2f | Remaining: ₹%.2f\nDeadline: %s\n",
               head->name, head->target, head->saved, head->target - head->saved, head->deadline);
        printf("---------------------------------\n");
        head = head->next;
    }
}

void saveGoalsToFile(struct Goal *head, const char *username) {
    char filename[100];
    sprintf(filename, "goals_%s.txt", username);
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    while (head) {
        fprintf(fp, "%s %.2f %.2f %s\n", head->name, head->target, head->saved, head->deadline);
        head = head->next;
    }
    fclose(fp);
}

void loadGoalsFromFile(struct Goal **head, const char *username) {
    char filename[100];
    sprintf(filename, "goals_%s.txt", username);
    FILE *fp = fopen(filename, "r");
    if (!fp) return;

    struct Goal temp;
    while (fscanf(fp, "%s %f %f %s", temp.name, &temp.target, &temp.saved, temp.deadline) != EOF) {
        struct Goal *newGoal = (struct Goal *)malloc(sizeof(struct Goal));
        *newGoal = temp;
        newGoal->next = *head;
        *head = newGoal;
    }
    fclose(fp);
}

// ================== GOAL REMINDERS ======================

void addGoalReminder(const char *username, const char *goalName, const char *deadline) {
    char filename[100];
    sprintf(filename, "goal_reminders_%s.txt", username);
    FILE *fp = fopen(filename, "a");
    if (!fp) {
        printf("Error saving goal reminder.\n");
        return;
    }

    fprintf(fp, "Remember to reach goal '%s' before %s.\n", goalName, deadline);
    fclose(fp);
}

void viewGoalReminders(const char *username) {
    char filename[100];
    sprintf(filename, "goal_reminders_%s.txt", username);
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No goal reminders found.\n");
        return;
    }

    printf("\n==== GOAL REMINDERS ====\n");
    char line[200];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        printf("%d. %s", ++count, line);
    }
    if (count == 0) printf("No goal reminders found.\n");
    fclose(fp);
}

// ================== GIVE / TAKE REMINDERS ======================

void addPaymentReminder(const char *username, const char *type, float amount, const char *person) {
    char filename[100];
    sprintf(filename, "payment_reminders_%s.txt", username);

    FILE *fp = fopen(filename, "a");
    if (!fp) {
        printf("Error saving payment reminder.\n");
        return;
    }

    if (strcmp(type, "give") == 0)
        fprintf(fp, "Pay Rs. %.2f to %s soon.\n", amount, person);
    else if (strcmp(type, "take") == 0)
        fprintf(fp, "%s owes you Rs. %.2f.\n", person, amount);

    fclose(fp);
}

void viewPaymentReminders(const char *username) {
    char filename[100];
    sprintf(filename, "payment_reminders_%s.txt", username);
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No payment reminders.\n");
        return;
    }

    printf("\n==== GIVE / TAKE REMINDERS ====\n");
    char line[200];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        printf("%d. %s", ++count, line);
    }
    if (count == 0) printf("No reminders found.\n");
    fclose(fp);
}
