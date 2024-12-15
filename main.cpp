#include <iostream>
#include <string>
#include "Account.h"
#include "Transaction.h"

using namespace std;

int main() {
    Account userAccount("123456", 5000.0);
    cout << "Account created with initial balance: " << userAccount.getBalance() << endl;

    SpendingCategory food("Food", 1000.0);
    SpendingCategory entertainment("Entertainment", 500.0);

    food.getCategoryStatistics();
    entertainment.getCategoryStatistics();

    TransactionHandle transactionManager;

    userAccount.withdraw(300);
    transactionManager.recordTransaction("T001", "2024-12-07", 300, &food);
    food.addSpend(300);

    userAccount.withdraw(200);
    transactionManager.recordTransaction("T002", "2024-12-08", 200, &entertainment);
    entertainment.addSpend(200);

    cout << "\nTransaction History:" << endl;
    transactionManager.getTransactionHistory();

    cout << "\nSpending Statistics:" << endl;
    food.getCategoryStatistics();
    entertainment.getCategoryStatistics();

    userAccount.integrateWithBank();

    return 0;
}
