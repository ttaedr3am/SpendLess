#include <stdio.h>
#include <stdlib.h>
#include "user_auth.h" 
#include "summary.h" 
#include "expenses.h" 
#include "goals_reminders.h"
#include "give_take.h" 


int main() {
    int choice, loggedIn = 0;
    char username[50];
    // This is your variable name
    struct Goal *goalHead = NULL; 

    printf("=== SMART BUDGET & EXPENSE TRACKER ===\n");

    while (1) {
        printf("\n1. Signup\n2. Login\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: signup(); break; 
            case 2:
                if (login()) { 
                    printf("Enter your username again: ");
                    scanf("%s", username);
                    // CHANGED: Use goalHead
                    loadGoalsFromFile(&goalHead, username); 
                    loggedIn = 1;
                    setBudget();
                }
                break;
            case 3: exit(0);
            default: printf("Invalid choice!\n");
        }

        while (loggedIn) {
            printf("\n--- MAIN MENU ---\n");
            printf("1. Add Expense\n");
            printf("2. View Expenses\n");
            printf("3. View Monthly Summary\n");
            printf("4. Show Pie Chart Summary\n");
            printf("5. Show Budget Notification\n");
            printf("6. Manage Saving Goals\n");
            printf("7. View Goal Reminders\n");
            printf("8. Manage Give/Take\n");
            printf("9. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: addExpense(); break; 
                case 2: viewExpenses(); break; 
                case 3: monthlySummary(); break;
                case 4: showPieChart(); break; 
                case 5: showNotification(calculateTotal()); break; 

                case 6: {
                    int gch;
                    printf("\n--- SAVING GOAL SECTION ---\n");
                    printf("1. Add Goal\n2. Update Goal\n3. View Goals\n4. Back\nChoice: ");
                    scanf("%d", &gch);
                    if (gch == 1) {
                        // CHANGED: Use goalHead
                        addGoal(&goalHead); 
                        // CHANGED: Use goalHead
                        if (goalHead) { 
                            // CHANGED: Use goalHead
                            addGoalReminder(username, goalHead->name, goalHead->deadline);
                        }
                    } else if (gch == 2) {
                        // CHANGED: Use goalHead
                        updateGoal(goalHead); 
                    } else if (gch == 3) {
                         // CHANGED: Use goalHead
                        viewGoals(goalHead);
                    }
                    break;
                }

                case 7: viewGoalReminders(username); break;
                
                case 8: giveTakeMenu(username); break;

                case 9:
                    // CHANGED: Use goalHead
                    saveGoalsToFile(goalHead, username); 
                    loggedIn = 0;
                    break;

                default:
                    printf("Invalid choice!\n");
            }
        }
    }
    return 0;
}