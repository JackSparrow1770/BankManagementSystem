# Bank Management System

A simple **Bank Management System** built with C++ that allows users to manage bank accounts, perform transactions, and view account details. This application is designed to demonstrate object-oriented programming concepts and file handling in C++.

---

## Features

### 1. Account Management

- **Open an Account**: Create a new bank account with a unique account number, first name, last name, and initial balance.
- **Close an Account**: Permanently delete an account from the system.

### 2. Transactions

- **Deposit**: Add funds to an existing account.
- **Withdraw**: Withdraw funds from an account, ensuring the balance does not fall below the minimum balance of 100.

### 3. Account Information

- **Balance Enquiry**: Check the current balance and details of an account.
- **Show All Accounts**: Display details of all accounts in the system.

### 4. Persistent Storage

- All account data is saved to a file (`Bank.data`) to ensure data persistence between program runs.

---

## How It Works

1. **Classes**:

   - `Cl_Accounts`: Represents a bank account with attributes like account number, first name, last name, and balance.
   - `Bank`: Manages all accounts and provides methods for account operations.

2. **File Handling**:

   - Account data is saved to and loaded from a file (`Bank.data`) using file streams (`ifstream` and `ofstream`).

3. **Error Handling**:
   - Throws exceptions for insufficient funds, invalid account numbers, and other errors.

---

## Usage

### Menu Options

When you run the program, you will see the following menu:

Select One Option Below
1 Open an Account
2 Balance Enquiry
3 Deposit
4 Withdrawal
5 Close an Account
6 Show All Accounts
7 Quit

### Example Workflow

1. **Open an Account**:

   - Enter the first name, last name, and initial balance.
   - The system will generate a unique account number and save the account details.

2. **Deposit**:

   - Enter the account number and the amount to deposit.
   - The system updates the balance and displays the updated account details.

3. **Withdraw**:

   - Enter the account number and the amount to withdraw.
   - The system checks if the balance is sufficient and updates the account.

4. **Close an Account**:

   - Enter the account number to delete the account.
   - The system removes the account from the file.

5. **Show All Accounts**:
   - Displays all accounts with their details.

---

## Requirements

- **C++ Compiler**: Any modern C++ compiler (e.g., GCC, Clang, MSVC).
- **Development Environment**: Visual Studio Code, Code::Blocks, or any IDE of your choice.

---

## How to Run

1. Clone the repository or copy the source files to your local machine.
2. Compile the code using your C++ compiler:

   ```bash
   g++ Bank.cpp -o BankManagementSystem
   ```

3. Run the executable: ./BankManagementSystem
4. Follow the on-screen instructions to use the application.

## Future Enhancements

-Add a Graphical User Interface (GUI) using a library like Qt or wxWidgets.
-Implement multi-threading for concurrent account operations.
-Add encryption for secure storage of account data.
-Support internationalization for multiple languages.

## License

This project is licensed under the MIT License. Feel free to use, modify, and distribute it as needed.

## Author

Fahad Siddique Faisal
Developer passionate about C++ and software engineering.
