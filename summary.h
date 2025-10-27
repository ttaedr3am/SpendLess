#ifndef SUMMARY_H
#define SUMMARY_H

#define MAX 100

struct Expense {
    char category[30];
    float amount;
};

// Global variables
extern struct Expense expenses[MAX];
extern int count;
extern float totalBudget;

// Expense management functions
void setBudget();
void addExpense();
void viewExpenses();
float calculateTotal();
void showNotification(float total);
void showPieChart();

#endif
