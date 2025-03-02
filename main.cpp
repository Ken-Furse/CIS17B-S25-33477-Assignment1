/*
Authour: Kenneth Furse
Assignment: assignment 1
Date: 03/02/2025
*/

#include <iomanip>;
#include <iostream>;
#include <string>;
using namespace std;

class BankAccount {
private:
    string accountHolderName;
    int accountNumber;
    double balance;

public:
    // Constructor
    BankAccount(string name, double initialBalance)
        : accountHolderName(name), balance(initialBalance) {
        accountNumber = generateAccountNumber();
    }

    // Generate a unique 6-digit account number
    static int generateAccountNumber() {
        return 100000 + rand() % 900000; // Ensures a 6-digit number
    }

    // Deposit money
    void deposit(double amount) {
        try {
            if (amount <= 0) {
                throw invalid_argument("Deposit amount must be positive.\n");
            }
            balance += amount;
            cout << "Deposit successful! New balance: $" << fixed << setprecision(2) << balance << "\n";
        }
        catch (const invalid_argument& e) {
            cout << e.what();
        }
    }

    // Withdraw money
    void withdraw(double amount) {
        try {
            if (amount <= 0) {
                throw invalid_argument("Withdrawal amount must be positive.\n");
            }
            if (amount > balance) {
                throw invalid_argument("Insufficient funds!\n");
            }
            balance -= amount;
            cout << "Withdrawal successful! New balance: $" << fixed << setprecision(2) << balance << "\n";
        }
        catch (const invalid_argument& e) {
            cout << e.what();
        }
    }

    // Display balance
    void displayBalance() const {
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << "\n";
    }
};

// Function to handle user input validation
double getValidAmount() {
    double amount;
    while (true) {
        try {
            cin >> amount;
            if (cin.fail()) {
                throw invalid_argument("Invalid input. Please enter a valid positive amount: ");
            }
            if (amount < 0) {
                throw invalid_argument("Invalid input. Amount cannot be negative.\n");
            }
            return amount;
        }
        catch (const invalid_argument& e) {
            cout << e.what();
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

int main() {
    srand(time(0)); // Seed random number generator
    BankAccount* account = nullptr;
    int choice;
    string name;
    double initialBalance;

    do {
        if (account == nullptr) {
            cout << "\nWelcome to Simple Bank System" << endl;
            cout << "1. Create Account" << endl;
            cout << "2. Deposit Money" << endl;
            cout << "3. Withdraw Money" << endl;
            cout << "4. Check Balance" << endl;
            cout << "5. Exit" << endl << endl;
        }
        else {
            cout << "\nBanking System Menu:" << endl;
            cout << "1. Deposit Money" << endl;
            cout << "2. Withdraw Money" << endl;
            cout << "3. Check Balance" << endl;
            cout << "4. Exit" << endl << endl;
        }

        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Please enter a valid number.\n";
            continue;
        }

        if (account == nullptr) {
            switch (choice) {
            case 1:
                cout << "Enter account holder's name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter initial balance: ";
                initialBalance = getValidAmount();
                account = new BankAccount(name, initialBalance);
                cout << "\nAccount created successfully!\n\n";
                break;
            case 5:
                cout << "Exiting system. Thank you!\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            }
        }
        else {
            switch (choice) {
            case 1:
                cout << "Enter deposit amount: ";
                account->deposit(getValidAmount());
                break;
            case 2:
                cout << "Enter withdrawal amount: ";
                account->withdraw(getValidAmount());
                break;
            case 3:
                account->displayBalance();
                break;
            case 4:
                cout << "Exiting system. Thank you!\n";
                delete account;
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid number.\n";
            }
        }
    } while (true);

    delete account;
    return 0;
}