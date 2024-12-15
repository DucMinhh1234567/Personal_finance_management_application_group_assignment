#include <iostream>
#include <string>

using namespace std;

class Account {
    private:
        string accountId;
        double balance;
        bool bankIntegration;

    public:
        Account(string id, double initialBalance)
            : accountId(id), balance(initialBalance), bankIntegration(false) {}

        void deposit(double amount) {
            if (amount <= 0) {
                cout << "Invalid deposit amount." << endl;
            }
            balance += amount;
            cout << "Deposited: " << amount << " | New Balance: " << balance << endl;
        }

        bool withdraw(double amount) {
            if (amount > 0 && amount <= balance) {
                balance -= amount;
                cout << "Withdrawn: " << amount << " | Remaining Balance: " << balance << endl;
                return true;
            }
            cout << "Invalid withdraw amount or insufficient balance." << endl;
            return false;
        }

        double getBalance() const {
            return balance;
        }

        void integrateWithBank() {
            bankIntegration = true;
            cout << "Bank integration enabled." << endl;
        }
};
