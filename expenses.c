#include <stdio.h>
#include <string.h>
#include "expenses.h"
#include "summary.h" // Include to get global 'expenses' and 'count'

// CHANGED: Function now uses global 'expenses' and 'count'
// from summary.c, so it takes no parameters.
void monthlySummary() {
    float food = 0, travel = 0, rent = 0, others = 0;

    // Summing expenses category-wise
    // USES GLOBAL 'count' and 'expenses' 
    for (int i = 0; i < count; i++) {
        if (strcmp(expenses[i].category, "Food") == 0)
            food += expenses[i].amount;
        else if (strcmp(expenses[i].category, "Travel") == 0)
            travel += expenses[i].amount;
        else if (strcmp(expenses[i].category, "Rent") == 0)
            rent += expenses[i].amount;
        else
            others += expenses[i].amount;
    }

    float total = food + travel + rent + others;

    // Printing summary table
    printf("\n==============================\n");
    printf("     MONTHLY SUMMARY TABLE    \n");
    printf("==============================\n");
    printf("%-15s | %-10s\n", "CATEGORY", "AMOUNT");
    printf("------------------------------\n");
    printf("%-15s | %-10.2f\n", "Food", food);
    printf("%-15s | %-10.2f\n", "Travel", travel);
    printf("%-15s | %-10.2f\n", "Rent", rent);
    printf("%-15s | %-10.2f\n", "Others", others);
    printf("------------------------------\n");
    printf("%-15s | %-10.2f\n", "TOTAL", total);
    printf("==============================\n");

    // Optional: Export data for pie chart use
    FILE *fp = fopen("monthly_summary.txt", "w");
    if (fp) {
        fprintf(fp, "Food %.2f\nTravel %.2f\nRent %.2f\nOthers %.2f\nTotal %.2f\n",
                food, travel, rent, others, total);
        fclose(fp);
    }
}