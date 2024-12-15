#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <conio.h>
#include "Account.h"
#include "SpendingCategory.h"
#include "Transaction.h"

using namespace std;

void clearScreen() {
    system("cls");
}

void displayMenu() {
    clearScreen();
    cout << "\n===== PERSONAL EXPENSE MANAGEMENT =====\n";
    cout << "1. Deposit Money\n";
    cout << "2. Withdraw Money\n";
    cout << "3. Check Balance\n";
    cout << "4. Create New Spending Category\n";
    cout << "5. Add Expense\n";
    cout << "6. View Category Statistics\n";
    cout << "7. Record Transaction\n";
    cout << "8. View Transaction History\n";
    cout << "0. Exit\n";
    cout << "Select an option: ";
}

void pauseAndClear() {
    cout << "\nPress any key to continue...";
    _getch();
    clearScreen();
}

void runExpenseManagementSystem() {
    Account myAccount("ACC001", 5000.0);
    
    vector<SpendingCategory> categories;
    categories.push_back(SpendingCategory("Food", 1500.0));
    categories.push_back(SpendingCategory("Entertainment", 800.0));
    categories.push_back(SpendingCategory("Transportation", 600.0));
    categories.push_back(SpendingCategory("Clothing", 1000.0));
    categories.push_back(SpendingCategory("Education", 500.0));

    TransactionHandle transactionManager;

    int choice;
    double amount;
    string date;

    do {
        displayMenu();
        choice = _getch() - '0';
        
        clearScreen();

        switch(choice) {
            case 1: {
                cout << "Enter deposit amount: ";
                cin >> amount;
                myAccount.deposit(amount);
                pauseAndClear();
                break;
            }
            case 2: {
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                myAccount.withdraw(amount);
                pauseAndClear();
                break;
            }
            case 3: {
                cout << "Current Balance: " << myAccount.getBalance() << endl;
                pauseAndClear();
                break;
            }
            case 4: {
                string categoryName;
                double categoryLimit;
                
                cout << "Enter new spending category name: ";
                getline(cin, categoryName);
                
                cout << "Enter spending limit: ";
                cin >> categoryLimit;
                
                categories.push_back(SpendingCategory(categoryName, categoryLimit));
                cout << "New category created: " << categoryName << endl;
                pauseAndClear();
                break;
            }
            case 5: {
                cout << "Select spending category:\n";
                for (size_t i = 0; i < categories.size(); ++i) {
                    cout << i+1 << ". " << categories[i].getName() << endl;
                }
                
                int categoryIndex;
                cout << "Enter category number: ";
                cin >> categoryIndex;
                
                if (categoryIndex > 0 && categoryIndex <= categories.size()) {
                    cout << "Enter expense amount: ";
                    cin >> amount;
                    
                    categories[categoryIndex-1].addSpend(amount);
                    
                    cout << "Enter transaction date (YYYY-MM-DD): ";
                    cin >> date;
                    
                    transactionManager.recordTransaction(
                        "TRANS" + to_string(rand()), 
                        date, 
                        amount, 
                        &categories[categoryIndex-1]
                    );
                } else {
                    cout << "Invalid selection.\n";
                }
                pauseAndClear();
                break;
            }
            case 6: {
                cout << "Spending Category Statistics:\n";
                for (auto& category : categories) {
                    category.getCategoryStatistics();
                }
                pauseAndClear();
                break;
            }
            case 7: {
                cout << "Enter transaction ID: ";
                string transId;
                cin >> transId;
                
                cout << "Enter transaction date (YYYY-MM-DD): ";
                cin >> date;
                
                cout << "Enter amount: ";
                cin >> amount;
                
                cout << "Select spending category:\n";
                for (size_t i = 0; i < categories.size(); ++i) {
                    cout << i+1 << ". " << categories[i].getName() << endl;
                }
                
                int categoryIndex;
                cout << "Enter category number: ";
                cin >> categoryIndex;
                
                if (categoryIndex > 0 && categoryIndex <= categories.size()) {
                    transactionManager.recordTransaction(
                        transId, 
                        date, 
                        amount, 
                        &categories[categoryIndex-1]
                    );
                } else {
                    cout << "Invalid selection.\n";
                }
                pauseAndClear();
                break;
            }
            case 8: {
                cout << "Transaction History:\n";
                transactionManager.getTransactionHistory();
                pauseAndClear();
                break;
            }
            case 0:
                cout << "Program ended. Thank you!\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
                pauseAndClear();
        }

    } while (choice != 0);
}

int main() {
    runExpenseManagementSystem();
    return 0;
}