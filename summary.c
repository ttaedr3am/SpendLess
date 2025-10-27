#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "summary.h"

struct Expense expenses[MAX];
int count = 0;
float totalBudget = 0.0;

void setBudget() {
    printf("Set your monthly budget: ₹");
    scanf("%f", &totalBudget);
}

// Add a new expense
void addExpense() {
    if (count >= MAX) {
        printf("\nExpense list full!\n");
        return;
    }
    printf("\nEnter category: ");
    scanf("%s", expenses[count].category);
    printf("Enter amount: ");
    scanf("%f", &expenses[count].amount);
    count++;
    printf("\n✅ Expense added successfully!\n");
}

// Calculate total expenses
float calculateTotal() {
    float total = 0;
    for (int i = 0; i < count; i++)
        total += expenses[i].amount;
    return total;
}

// Budget notification
void showNotification(float total) {
    printf("\n==============================\n");
    printf(" 🔔 POP-UP NOTIFICATION 🔔\n");
    printf("==============================\n");
    if (total > totalBudget)
        printf("⚠  You have exceeded your monthly budget!\n");
    else if (total > 0.8 * totalBudget)
        printf("⚠  You’ve reached 80%% of your budget limit!\n");
    else
        printf("✅ You are within your budget.\n");
    printf("==============================\n\n");
}

// Display all expenses
void viewExpenses() {
    if (count == 0) {
        printf("\nNo expenses added yet.\n");
        return;
    }
    printf("\n----- Expense List -----\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s : ₹%.2f\n", i + 1, expenses[i].category, expenses[i].amount);
    }
}

// Pie chart summary (text)
void showPieChart() {
    if (count == 0) {
        printf("\nNo expenses to show pie chart.\n");
        return;
    }

    float total = calculateTotal();
    printf("\n📊 EXPENSE SUMMARY (Pie Chart)\n");
    printf("---------------------------------\n");
    for (int i = 0; i < count; i++) {
        float percent = (expenses[i].amount / total) * 100;
        printf("%-12s : %6.2f%% | ", expenses[i].category, percent);
        int stars = (int)(percent / 2); // 1 star per 2%
        for (int j = 0; j < stars; j++) printf("*");
        printf("\n");
    }
    printf("---------------------------------\n");
    printf("Total spent: ₹%.2f\n", total);
}
