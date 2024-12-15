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
    cout << "5. Edit Spending Category\n";
    cout << "6. Add Expense\n";
    cout << "7. View Category Statistics\n";
    cout << "8. Record Transaction\n";
    cout << "9. View Transaction History\n";
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
                cin.ignore();
                getline(cin, categoryName);
                
                cout << "Enter spending limit: ";
                cin >> categoryLimit;
                
                categories.push_back(SpendingCategory(categoryName, categoryLimit));
                cout << "New category created: " << categoryName << endl;
                pauseAndClear();
                break;
            }
            case 5: {
                if (categories.empty()) {
                    cout << "No categories to edit. Create a category first.\n";
                    pauseAndClear();
                    break;
                }

                cout << "Select category to edit:\n";
                for (size_t i = 0; i < categories.size(); ++i) {
                    cout << i+1 << ". " << categories[i].getName() 
                         << " (Current Limit: " << categories[i].getCurrentLimit() << ")\n";
                }

                int categoryIndex;
                cout << "Enter category number: ";
                cin >> categoryIndex;

                if (categoryIndex > 0 && categoryIndex <= categories.size()) {
                    cout << "\nEdit Options:\n";
                    cout << "1. Change Category Name\n";
                    cout << "2. Change Spending Limit\n";
                    cout << "3. Cancel\n";
                    cout << "Select edit option: ";

                    int editChoice;
                    cin >> editChoice;

                    categoryIndex--;

                    switch(editChoice) {
                        case 1: {
                            string newName;
                            cout << "Enter new category name: ";
                            cin.ignore();
                            getline(cin, newName);
                            
                            double currentLimit = categories[categoryIndex].getCurrentLimit();
                            
                            categories[categoryIndex] = SpendingCategory(newName, currentLimit);
                            
                            cout << "Category name updated successfully.\n";
                            break;
                        }
                        case 2: {
                            double newLimit;
                            cout << "Enter new spending limit: ";
                            cin >> newLimit;
                            
                            categories[categoryIndex].setCategoryLimit(newLimit);
                            cout << "Spending limit updated successfully.\n";
                            break;
                        }
                        case 3:
                            cout << "Edit cancelled.\n";
                            break;
                        default:
                            cout << "Invalid option.\n";
                    }
                } else {
                    cout << "Invalid category selection.\n";
                }
                pauseAndClear();
                break;
            }
            case 6: {
                if (categories.empty()) {
                    cout << "No categories available. Create a category first.\n";
                    pauseAndClear();
                    break;
                }

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
            case 7: {
                if (categories.empty()) {
                    cout << "No categories to display.\n";
                } else {
                    cout << "Spending Category Statistics:\n";
                    for (auto& category : categories) {
                        category.getCategoryStatistics();
                    }
                }
                pauseAndClear();
                break;
            }
            case 8: {
                if (categories.empty()) {
                    cout << "No categories available. Create a category first.\n";
                    pauseAndClear();
                    break;
                }

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
            case 9: {
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