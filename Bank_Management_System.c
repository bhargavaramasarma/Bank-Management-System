#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100
#define FILENAME "Bank_Management_System.csv"

// Structure to represent a bank account
struct Account {
    int accNumber;
    char name[50];
    float balance;
};

// Array of pointers to Account structs
struct Account *accounts[MAX_CUSTOMERS];
int numAccounts = 0;

// Function prototypes
void createAccount();
void deposit();
void withdraw();
void checkBalance();
void saveToFile();
void readFromFile();

int main() {
    readFromFile(); // Load existing accounts from file

    int choice;

    do {
        printf("\nBank Management System\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                printf("Exiting...\n");
                saveToFile(); // Save accounts to file before exiting
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(1);

    return 0;
}

// Function to create a new account
void createAccount() {
    if(numAccounts >= MAX_CUSTOMERS) {
        printf("Cannot create more accounts. Maximum limit reached.\n");
        return;
    }

    struct Account *newAcc = (struct Account *)malloc(sizeof(struct Account));
    if(newAcc == NULL) {
        printf("Memory allocation failed. Please try again later.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &newAcc->accNumber);
    printf("Enter Name: ");
    getchar(); // Consume the newline character left by scanf
    fgets(newAcc->name, sizeof(newAcc->name), stdin);
    newAcc->name[strcspn(newAcc->name, "\n")] = '\0'; // Remove trailing newline character
    printf("Enter Initial Balance: ");
    scanf("%f", &newAcc->balance);

    accounts[numAccounts++] = newAcc;

    printf("Account created successfully.\n");
    saveToFile(); // Save new account to file
}

// Function to deposit money into an account
void deposit() {
    int accNum;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int found = 0;
    for(int i = 0; i < numAccounts; i++) {
        if(accounts[i]->accNumber == accNum) {
            found = 1;
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            accounts[i]->balance += amount;
            printf("Deposit successful. New balance: %.2f\n", accounts[i]->balance);
            break;
        }
    }

    if(!found)
        printf("Account not found.\n");
}

// Function to withdraw money from an account
void withdraw() {
    int accNum;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int found = 0;
    for(int i = 0; i < numAccounts; i++) {
        if(accounts[i]->accNumber == accNum) {
            found = 1;
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if(amount > accounts[i]->balance) {
                printf("Insufficient balance.\n");
            } else {
                accounts[i]->balance -= amount;
                printf("Withdrawal successful. New balance: %.2f\n", accounts[i]->balance);
            }
            break;
        }
    }

    if(!found)
        printf("Account not found.\n");
}

// Function to check balance of an account
void checkBalance() {
    int accNum;
    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int found = 0;
    for(int i = 0; i < numAccounts; i++) {
        if(accounts[i]->accNumber == accNum) {
            found = 1;
            printf("Balance of Account %d: %.2f\n", accounts[i]->accNumber, accounts[i]->balance);
            break;
        }
    }

    if(!found)
        printf("Account not found.\n");
}

// Function to save accounts to file
void saveToFile() {
    FILE *file = fopen(FILENAME, "w");
    if(file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for(int i = 0; i < numAccounts; i++) {
        fprintf(file, "%d,%s,%.2f\n", accounts[i]->accNumber, accounts[i]->name, accounts[i]->balance);
    }

    fclose(file);
}

// Function to read accounts from file
void readFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if(file == NULL) {
        printf("File does not exist. Creating new file.\n");
        return;
    }

    while(!feof(file)) {
        struct Account *newAcc = (struct Account *)malloc(sizeof(struct Account));
        if(newAcc == NULL) {
            printf("Memory allocation failed. Please try again later.\n");
            fclose(file);
            exit(1);
        }

        if(fscanf(file, "%d,%[^,],%f\n", &newAcc->accNumber, newAcc->name, &newAcc->balance) == 3) {
            accounts[numAccounts++] = newAcc;
        } else {
            free(newAcc);
        }
    }

    fclose(file);
}
