#ifndef GOALS_REMINDERS_H
#define GOALS_REMINDERS_H

// ==== STRUCTURES ====

struct Goal {
    char name[50];
    float target;
    float saved;
    char deadline[15];  // "DD/MM/YYYY"
    struct Goal *next;
};

struct Reminder {
    char message[150];
    char date[15];
    struct Reminder *next;
};

// ==== FUNCTION DECLARATIONS ====

// --- Goal Management ---
void addGoal(struct Goal **head);
void updateGoal(struct Goal *head);
void viewGoals(struct Goal *head);
void saveGoalsToFile(struct Goal *head, const char *username);
void loadGoalsFromFile(struct Goal **head, const char *username);

// --- Goal Reminders ---
void addGoalReminder(const char *username, const char *goalName, const char *deadline);
void viewGoalReminders(const char *username);

// --- Give/Take Reminders ---
void addPaymentReminder(const char *username, const char *type, float amount, const char *person);
void viewPaymentReminders(const char *username);

#endif
