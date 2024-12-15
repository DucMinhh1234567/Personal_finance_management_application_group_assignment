#ifndef TRANS_H
#define TRANS_H

#include "SpendingCategory.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SpendingCategory;

class Transaction {
    private:
        string transactionId;
        string date;
        double amount;
        SpendingCategory* category;

    public:
        Transaction(string id, string date, double amount, SpendingCategory* cate)
            : transactionId(id), date(date), amount(amount), category(cate) {}

        void displayTransaction() const {
            cout << "Transaction ID: " << transactionId << " | Date: " << date
                << " | Amount: " << amount << " | Category: " << category->getName() << endl;
        }
};

class TransactionHandle {
    private:
        vector<Transaction> transactions;

    public:
        void recordTransaction(string id, string date, double amount, SpendingCategory* category) {
            Transaction newTransaction(id, date, amount, category);
            transactions.push_back(newTransaction);
            cout << "Transaction recorded successfully." << endl;
        }

        void getTransactionHistory() const {
            for (const auto& trans : transactions) {
                trans.displayTransaction();
            }
        }
};

#endif