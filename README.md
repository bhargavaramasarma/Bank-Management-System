# Bank Management System

This is a simple bank management system implemented in C programming language. The program allows users to create accounts, deposit and withdraw money, check account balances, and store account details in a CSV file.

## Features

- **Creating Account:** Users can create a new bank account by providing their account number, name, and initial balance.
- **Depositing Money:** Users can deposit money into their accounts by specifying the account number and deposit amount.
- **Withdrawing Money:** Users can withdraw money from their accounts by specifying the account number and withdrawal amount.
- **Checking Balance:** Users can check the balance of their accounts by specifying the account number.
- **Data Persistence:** Account details are stored in a CSV file ("BankDetails.csv"), allowing data to persist across program executions.

## Usage

1. **Compilation:**
    ```
    gcc bank_management_system.c -o bank_management_system
    ```

2. **Execution:**
    ```
    ./a.out
    ```

3. **Menu Navigation:**
    - Enter the corresponding number for the desired operation in the main menu.
    - Follow the on-screen prompts to input necessary information.

## File Structure

- **Bank_Management_System.c:** Main source code file containing the implementation of bank management functionalities.
- **Bank_Management_System.csv:** CSV file to store account details.

## Dependencies

- This program requires a C compiler (e.g., GCC) to compile and execute.

